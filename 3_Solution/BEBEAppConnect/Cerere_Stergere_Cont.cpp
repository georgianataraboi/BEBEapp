#include "Cerere_Stergere_Cont.h"
#include "BD_Connection.h"
#include "CException.h"


Cerere_Stergere_Cont::Cerere_Stergere_Cont()
{
	this->mesaj = nullptr;
	this->parola = nullptr;
	this->username = nullptr;
	this->nr = nullptr;


}

Cerere_Stergere_Cont::Cerere_Stergere_Cont(string msg)
{
	string unu;
	string doi;
	string trei;
	size_t position = msg.find("/");
	if (position != std::string::npos) {
		unu = msg.substr(0, position);
		size_t secondposition = msg.find("/", position + 1);
		if (secondposition != std::string::npos) {
			doi = msg.substr(position + 1, secondposition - position - 1);


			trei = msg.substr(secondposition + 1);
		}
		
	}
	this->nr = unu;
	this->username = doi;
	this->parola = trei;

}

void Cerere_Stergere_Cont::mesaj_client()
{

	bool aux = BD_Connection::create_Instance()->deleteAccount(this->nr, this->username, this->parola);
	if (aux)
	{
		this->mesaj = "Ati sters un cont de utilizator";
	}
	else
	{
		this->mesaj = "Stergerea unui cont de utilizator nu a putut fi efectuata pentru ca, nu s-a gasit utilizatorul respectiv !";
		throw new CException(9, this->mesaj);
	}


}

string Cerere_Stergere_Cont::raspuns_client()
{
	return this->mesaj;
}
