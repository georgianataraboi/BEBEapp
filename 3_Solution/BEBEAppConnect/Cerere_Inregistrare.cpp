#include "Cerere_Inregistrare.h"
#include "BD_Connection.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Inregistrare::Cerere_Inregistrare()
{
	this->username = nullptr;
	this->parola = nullptr;
	this->mesaj = nullptr;
}

Cerere_Inregistrare::Cerere_Inregistrare(string msg)
{
	
	std::vector<std::string> parts;
	std::stringstream ss(msg);
	std::string part;

	
	while (std::getline(ss, part, '/')) {
		parts.push_back(part);
	}

	this->nr = parts[0];
	this->username = parts[1];
	this->parola = parts[2];
	this->nume = parts[3];
	this->prenume = parts[4];

	

}

void Cerere_Inregistrare::mesaj_client()
{
	bool aux = BD_Connection::create_Instance()->createUser(this->nr,this->username, this->parola, this->nume, this->prenume);
	if (aux)
	{
		this->mesaj = "Tutorele cu numele: " + this->username + " a fost inregistrat cu succes!";
	}
	else
	{
		this->mesaj = "Tutorele cu numele: " + this->username + " NU a fost inregistrat cu succes!";
		throw new CException(4, this->mesaj);
	}

}

string Cerere_Inregistrare::raspuns_client()
{
	return this->mesaj;
}

