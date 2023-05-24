#include "Cerere_Update_Hraniri.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Update_Hraniri::Cerere_Update_Hraniri()
{
	this->mesaj = nullptr;
	this->tip_hrana = nullptr;
	this->cantitate_hrana = 0;
	this->moment_hranire = nullptr;
	this->nume_copil = nullptr;
	this->nr = nullptr;

}

Cerere_Update_Hraniri::Cerere_Update_Hraniri(string msg)
{	
    std::vector<std::string> parts;
    std::stringstream ss(msg);
    std::string part;

    
    while (std::getline(ss, part, '/')) {
        parts.push_back(part);
    }

    this->nr = parts[0];
    this->tip_hrana = parts[1];
    this->cantitate_hrana = stoi(parts[2]);
    this->moment_hranire = parts[3];
    this->nume_copil = parts[4];



}

void Cerere_Update_Hraniri::mesaj_client()
{
    bool aux = BD_Connection::create_Instance()->updateFood(this->nr, this->tip_hrana, this->cantitate_hrana, this->moment_hranire, this->nume_copil);

    if (aux)
    {
        this->mesaj = "Informatiile cu privire la hrana copilului: "+this->nume_copil+"  au fost modificate!";
    }
    else
    {
        this->mesaj = "Informatiile cu privire la hrana copilului: "+this->nume_copil+" NU au fost modificate!";
        throw new CException(12, this->mesaj);
    }

}

string Cerere_Update_Hraniri::raspuns_client()
{
    return this->mesaj;
}
