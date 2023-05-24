#include "Cerere_Update_Copil.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Update_Copil::Cerere_Update_Copil()
{
	this->nume_copil = nullptr;
	this->prenume_copil = nullptr;
	this->data_nastere = nullptr;
	this->mesaj = nullptr;
	this->mesaj = nullptr;
	this->nr = nullptr;
	this->nume_copil2 = nullptr;
	this->varsta = 0;
    this->id_tutore = 0;
}

Cerere_Update_Copil::Cerere_Update_Copil(string msg)
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
    this->varsta = stoi(parts[3]);
    this->data_nastere = parts[4];
    this->id_tutore = stoi(parts[5]);
    this->nume_copil2 = parts[6];


}

void Cerere_Update_Copil::mesaj_client()
{
    bool aux = BD_Connection::create_Instance()->updateKid(this->nr, this->nume_copil,this->prenume_copil, this->varsta, this->data_nastere, this->nume_copil2, this->id_tutore);

    if (aux)
    {
        this->mesaj = "Ati modificat informatiile unui copil";
    }
    else
    {
        this->mesaj = "NU ati putut modifica informatiile despre un copil";
        throw new CException(11, this->mesaj);
    }

}

string Cerere_Update_Copil::raspuns_client()
{
    return this->mesaj;
}
