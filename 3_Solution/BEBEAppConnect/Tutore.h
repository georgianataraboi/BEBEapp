#pragma once
#include <string>
using namespace std;

#include "I_Mesaje.h"
class Tutore{
public:

    string username;
    string parola;
    Tutore() {}
    Tutore( const string& username, const string& parola)
         : username(username), parola(parola) {}

    /*Tutore newUser(int id, "Coman Miruna", "13112002Miruna");
    if (db.createUser(newUser)) {
        std::cout << "User created successfully.\n";
    }
    else {
        std::cout << "Error creating user.\n";
    }*/
    
    
};

