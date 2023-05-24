#include "Cerere_Update_Monitorizare_Crestere.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Update_Monitorizare_Crestere::Cerere_Update_Monitorizare_Crestere()
{
	this->dimensiune_cap = 0;
	this->inaltime = 0;
	this->greutate = 0;
	this->nume_copil = nullptr;
	this->mesaj = nullptr;
	this->nr = nullptr;
}

Cerere_Update_Monitorizare_Crestere::Cerere_Update_Monitorizare_Crestere(string msg)
{
    std::vector<std::string> parts;
    std::stringstream ss(msg);
    std::string part;

    
    while (std::getline(ss, part, '/')) {
        parts.push_back(part);
    }

    this->nr = parts[0];
    this->dimensiune_cap = stoi(parts[1]);
    this->inaltime = stoi(parts[2]);
    this->greutate = stoi(parts[3]);
    this->nume_copil = parts[4];
}

void Cerere_Update_Monitorizare_Crestere::mesaj_client()
{
    bool aux = BD_Connection::create_Instance()->updateSize(this->nr, this->dimensiune_cap, this->inaltime, this->greutate, this->nume_copil);

    if (aux)
    {
        this->mesaj = "Informatiile legate de cresterea copilului: "+this->nume_copil+" au fost modificate";
    }
    else
    {
        this->mesaj = "Informatiile legate de cresterea copilului: "+this->nume_copil+" NU au fost modificate";
        throw new CException(13, this->mesaj);
    }
}

string Cerere_Update_Monitorizare_Crestere::raspuns_client()
{
    return this->mesaj;
}
