#include "Cerere_Update_OreSomn.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Update_OreSomn::Cerere_Update_OreSomn()
{
	this->mesaj = nullptr;
	this->interval_orar = nullptr;
	this->nume_copil = nullptr;
	this->nr = nullptr;




}

Cerere_Update_OreSomn::Cerere_Update_OreSomn(string msg)
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

void Cerere_Update_OreSomn::mesaj_client()
{   
    bool aux = BD_Connection::create_Instance()->updateSleep(this->nr, this->interval_orar, this->nume_copil);

    if (aux)
    {
        this->mesaj = "Informatiile legate de somnul copilului: "+this->nume_copil+" au fost modificate";
    }
    else
    {
        this->mesaj = "Informatiile legate de somnul copilului: " +this->nume_copil+" NU au fost modificate";
        throw new CException(14, this->mesaj);
    }

}

string Cerere_Update_OreSomn::raspuns_client()
{
    return this->mesaj;
}
