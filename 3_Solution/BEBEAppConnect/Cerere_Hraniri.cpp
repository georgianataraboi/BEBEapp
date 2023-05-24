#include "Cerere_Hraniri.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Hraniri::Cerere_Hraniri()
{
	this->nume_copil = nullptr;
	this->cantitate_hrana = 0;
	this->moment_hranire = nullptr;
	this->tip_hrana = nullptr;
	this->mesaj = nullptr;
    this->nr = nullptr;
}

Cerere_Hraniri::Cerere_Hraniri(string msg)
{
    std::vector<std::string> parts;
    std::stringstream ss(msg);
    std::string part;

    
    while (std::getline(ss, part, '/')) {
        parts.push_back(part);
    }

    this->nr = parts[0];
    this->tip_hrana = parts[1];
    this->cantitate_hrana =stoi( parts[2]);
    this->moment_hranire = parts[3];
    this->nume_copil = parts[4];




}

void Cerere_Hraniri::mesaj_client()
{
    bool aux = BD_Connection::create_Instance()->addFood(this->nr, this->tip_hrana,this->cantitate_hrana, this->moment_hranire, this->nume_copil);

    if (aux)
    {
        this->mesaj = "Copilul cu numele: " + this->nume_copil + " a fost hranit!";
    }
    else
    {
        this->mesaj = "Copilul cu numele: " + this->nume_copil + " NU a putut fi hranit!";
        throw new CException(3, this->mesaj);
    }

}

string Cerere_Hraniri::raspuns_client()
{
    return this->mesaj;
}
