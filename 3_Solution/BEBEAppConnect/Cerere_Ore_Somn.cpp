#include "Cerere_Ore_Somn.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Ore_Somn::Cerere_Ore_Somn()
{
	this->mesaj = nullptr;
	this->interval_orar = nullptr;
	this->nume_copil = nullptr;
    this->nr = nullptr;
}

Cerere_Ore_Somn::Cerere_Ore_Somn(string msg)
{

    std::vector<std::string> parts;
    std::stringstream ss(msg);
    std::string part;

    
    while (std::getline(ss, part, '/')) {
        parts.push_back(part);
    }

    this->nr = parts[0];
    this->interval_orar = parts[1];
    this->nume_copil = parts[2];



}

void Cerere_Ore_Somn::mesaj_client()
{
    bool aux = BD_Connection::create_Instance()->addSleep(this->nr, this->interval_orar, this->nume_copil);

    if (aux)
    {
        this->mesaj = "Copilul cu numele: " + this->nume_copil + " a dormit in intervalul orar " + this->interval_orar;
    }
    else
    {
        this->mesaj = "Informatiile legate de somnul copilului " +this->nume_copil+ " NU au fost inregistrate";
        throw new CException(8, this->mesaj);
    }

}

string Cerere_Ore_Somn::raspuns_client()
{
    return this->mesaj;
}
