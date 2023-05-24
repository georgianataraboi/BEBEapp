#include "Cerere_Boli.h"
#include <string>
#include <vector>
#include <sstream>
#include "BD_Connection.h"
#include "CException.h"

Cerere_Boli::Cerere_Boli()
{
	this->nume_boala = nullptr;
	this->perioada_temperatura = nullptr;
	this->ora_consultatie_medic = nullptr;
	this->concluzie_medic = nullptr;
	this->analize = nullptr;
	this->rezultate_analize = nullptr;
	this->lista_vaccinuri = nullptr;
	this->nume_copil = nullptr;
	this->mesaj = nullptr;



}

Cerere_Boli::Cerere_Boli(string msg)
{
	std::vector<std::string> parts;
	std::stringstream ss(msg);
	std::string part;

	
	while (std::getline(ss, part, '/')) {
		parts.push_back(part);
	}

	this->nr = parts[0];
	this->nume_boala = parts[1];
	this->perioada_temperatura= parts[2];
	this->ora_consultatie_medic = parts[3];
	this->concluzie_medic = parts[4];
	this->analize = parts[5];
	this->rezultate_analize = parts[6];
	this->lista_vaccinuri = parts[7];
	this->nume_copil = parts[8];

}

void Cerere_Boli::mesaj_client()
{

	bool aux = BD_Connection::create_Instance()->addIllnesses(this->nr, this->nume_boala, this->perioada_temperatura, this->ora_consultatie_medic, this->concluzie_medic, this->analize,this->rezultate_analize, this->lista_vaccinuri, this->nume_copil);

	if (aux)
	{
		this->mesaj = "Informatiile legate de starea de sanatate a copilului: " + this->nume_copil + " au fost inregistarte!";
	}
	else
	{
		this->mesaj = "Informatiile legate de starea de sanatate a copilului: " + this->nume_copil + " NU au putut fi inregistarte!";
		throw new CException(2, this->mesaj);
	}

}

string Cerere_Boli::raspuns_client()
{
	return this->mesaj;
}
