#include "Cerere_Adauga_Copil.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Adauga_Copil::Cerere_Adauga_Copil()
{
	this->nume_copil = nullptr;
	this->prenume_copil = nullptr;
	this->data_nastere = nullptr;
	this->mesaj = nullptr;
	this->varsta = 0;


}

Cerere_Adauga_Copil::Cerere_Adauga_Copil(string msg)
{



    std::vector<std::string> parts;
    std::stringstream ss(msg);
    std::string part;


    while (std::getline(ss, part, '/')) {
        parts.push_back(part);
    }
   
        this->nr = parts[0];
        this->nume_copil = parts[1];
        this->prenume_copil = parts[2];
        this->data_nastere = parts[3];
        this->varsta = stoi(parts[4]);
        this->username = parts[5];
    
  
}

void Cerere_Adauga_Copil::mesaj_client()
{
    bool aux= BD_Connection::create_Instance()->creatKid(this->nr,this->nume_copil, this->prenume_copil, this->data_nastere, this->varsta, this->username);
   
    if (aux)
    {
        this->mesaj = "Copilul cu numele: " + this->nume_copil + " a fost adaugat cu succes!";
    }
    else
    {
        
        this->mesaj = "Copilul cu numele: " + this->nume_copil + " NU a putut fi adaugat!";
        throw new CException(1, this->mesaj);
    }

}

string Cerere_Adauga_Copil::raspuns_client()
{
    return this->mesaj;
}


