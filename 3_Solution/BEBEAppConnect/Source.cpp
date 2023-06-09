﻿#undef UNICODE
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WALL_H


#define WIN32_LEAN_AND_MEAN


#include <vector>
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <fstream>

#include <nanodbc/nanodbc.h>
#include "BD_Connection.h"
#include "Factory_Mesaje.h"
#include <odbcss.h>
#include "Cerere_Inregistrare.h"
#include "CException.h"


using namespace std;

#define BUFFER_SIZE 256


// Need to link with Ws2_32.lib


#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27015"


int __cdecl main(void)
{
    //-----------------------------------------conexiunea cu baza de date------------------------------------------
    
        std::string connection_string = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=BEBEApp;Trusted_Connection=yes;";
        //BD_Connection() : conn("Driver={ODBC Driver 17 for SQL Server};Server=LAPTOP-VPG5B1UA\\SQLEXPRESS;Database=BEBEApp;Trusted_Connection=yes;") {}
        BD_Connection::create_Instance();
 

        WSADATA wsaData;
        int wsaErr;
        int port = 1995;

        SOCKET serverSocket = INVALID_SOCKET;
        SOCKET acceptSocket = INVALID_SOCKET;

        WORD wVersionRequested = MAKEWORD(2, 2);

        //dll setup
        wsaErr = WSAStartup(wVersionRequested, &wsaData);

        if (wsaErr != 0) {
            cout << "The Winsock dll not found!" << endl;
            return 1;
        }
        else
        {
            cout << "The Winsock dll found!" << endl;
            cout << "The status: " << wsaData.szSystemStatus << endl;
        }

        //server socket setup
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            cout << "Error at socket(): " << WSAGetLastError() << endl;
            WSACleanup();
            return 1;
        }
        else {
            cout << "socket() is OK!" << endl;
        }

        //binding
        sockaddr_in service;
        service.sin_family = AF_INET;
        InetPton(AF_INET, "0.0.0.0", &service.sin_addr.s_addr);
        service.sin_port = htons(port);
        if (::bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
            cout << "BIND() failed: " << WSAGetLastError() << endl;
            closesocket(serverSocket);
            WSACleanup();
            return 0;

        }
        else {
            cout << "bind is OK!\n";
        }

        if (listen(serverSocket, 1) == SOCKET_ERROR) {
            cout << "listen(): Error listening on socket" << WSAGetLastError() << endl;
        }
        else {
            cout << "listen() is OK, waiting for connections..." << endl;
        }

     



        SOCKET activeSockets[FD_SETSIZE]{ 0 };
        std::memset(activeSockets, 0, sizeof(activeSockets));

        // Adăugare socket de ascultare în lista de socketuri active.
        activeSockets[0] = serverSocket;



        int i = 0, result = 0;
        SOCKET currentSocket = INVALID_SOCKET;
        fd_set readSet;
        FD_ZERO(&readSet);

        while (TRUE) {

            for (i = 0; i < FD_SETSIZE; i++)
            {
                currentSocket = activeSockets[i];
                if (currentSocket != 0)
                {
                    FD_SET(currentSocket, &readSet);
                }
            }

            result = select(0, &readSet, NULL, NULL, NULL);
            if (result == SOCKET_ERROR)
            {
                printf("select a esuat: %ld\n", WSAGetLastError());
                break;
            }

            for (i = 0; i < FD_SETSIZE; i++)
            {
                currentSocket = activeSockets[i];
                if (FD_ISSET(currentSocket, &readSet))
                {
                    if (currentSocket == serverSocket)
                    {
                        // Un client nou se încearcă să se conecteze.
                        struct sockaddr_in clientAddr = { 0 };
                        clientAddr.sin_family = AF_INET;
                        clientAddr.sin_port = htons(port);
                        int clientAddrSize = sizeof(clientAddr);
                        SOCKET newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
                        if (newSocket == INVALID_SOCKET)
                        {
                            printf("accept a esuat: %ld\n", WSAGetLastError());
                        }
                        else
                        {
                            printf("Client conectat: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
                            for (i = 1; i < FD_SETSIZE; i++)
                            {
                                if (activeSockets[i] == 0)
                                {
                                    activeSockets[i] = newSocket;
                                    break;
                                }
                            }
                        }

                    }
                    else {

                        // Un client existent trimite date.
                        char buffer[BUFFER_SIZE] = "TEST";
                        int bytesReceived = recv(currentSocket, buffer, BUFFER_SIZE, 0);
                        if (bytesReceived <= 0)
                        {
                            // Clientul a închis conexiunea sau a apărut o eroare.
                            printf("Client deconectat.\n");
                            closesocket(currentSocket);
                            activeSockets[i] = 0;
                        }
                        else
                        {
                            // Procesare date primite.
                            printf("Date primite: %.*s", bytesReceived, buffer);

                            try{
                                I_Mesaje* mesaj = Factory_Mesaje::get_mesaj(buffer);
                                mesaj->mesaj_client();
                                cout << mesaj->raspuns_client();
                                ofstream out("Jurnalizare_actiuni_server.txt", ios::app);
                                if (out.is_open()) {
                                    out << mesaj->raspuns_client() << endl;
                                }
                                
                            }
                            catch (CException *e) {
                                e->what();
                            }
                            
                            
                          
                            
                            // Trimite înapoi datele către client.
                            send(currentSocket, buffer, bytesReceived, 0);
                        }
                    }
                }
            }


        }
        closesocket(serverSocket);
        for (i = 0; i < FD_SETSIZE; i++)
        {
            currentSocket = activeSockets[i];
            if (currentSocket != 0)
            {
                closesocket(currentSocket);
            }
        }

        // Dezactivare Winsock.
        WSACleanup();


        return 0;
    
}