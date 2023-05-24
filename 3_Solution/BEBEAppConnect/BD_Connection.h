#pragma once

#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include "Tutore.h"
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <nanodbc.h>



using namespace std;

class BD_Connection {
private:
    nanodbc::connection conn;
    static BD_Connection* instance;
    /*LAPTOP-VPG5B1UA\\SQLEXPRESS*/
    void disconnect();
    BD_Connection() : conn("Driver={ODBC Driver 17 for SQL Server};Server=localhost\\sqlexpress;Database=BEBEApp;Trusted_Connection=yes;") {}
    ~BD_Connection() {}
public:
    static BD_Connection* create_Instance()
    {
        if (!instance)
            instance = new BD_Connection();
        return instance;
    }
        

    bool createUser( string nr,string username, string parola, string nume, string prenume);
    bool Get_LogIn(string nr, string username, string parola);
    int GetIdUsername(string id);
    int getnamekid(string id);
    bool creatKid(string nr, string nume, string prenume, string data_nastere, int varsta,string username);
    bool addFood(string nr, string tip_hrana, int cantitate_hrana, string moment_hranire, string nume_copil);
    bool addSleep(string nr, string interval_orar, string nume_copil);
    bool addIllnesses(string nr, string nume_boala, string perioada_temperatura, string ora_consultatie_medic, string concluzie_medic, string analize, string rezultate_analize, string lista_vaccinuri, string nume_copil);
    bool addSize(string nr, int dimenziune_cap, int inaltime, int greutate, string nume_copil);
    bool updateKid(string nr, string nume_copil, string prenume_copil, int varsta, string data_nastere, string nume_copil2, int id_tutore);
    bool updateHealth(string nr, string nume_boala, string perioada_temperatura, string ora_consultatie_medic, string concluzie_medic, string analize, string rezultate_analize, string lista_vaccinuri, string nume_copil);
    bool updateFood(string nr, string tip_hrana, int cantitate_hrana, string moment_hranire, string nume_copil);
    bool updateSize(string nr, int dimenziune_cap, int inaltime, int greutate, string nume_copil);
    bool updateSleep(string nr, string interval_orar, string nume_copil);
    bool deleteAccount(string nr, string username, string parola);
   
   
};

