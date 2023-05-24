#include "Cerere_LogIn.h"
#include "CException.h"

Cerere_LogIn::Cerere_LogIn()
{
	this->nr = nullptr;
	this->mesaj = nullptr;
	this->username = nullptr;
	this->username = nullptr;

}

Cerere_LogIn::Cerere_LogIn(string msg)
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

void Cerere_LogIn::mesaj_client()
{	bool aux= BD_Connection::create_Instance()->Get_LogIn(this->nr, this->username, this->parola);
	if (aux) {
		this->mesaj = "Tutorele cu usernameul: " + this->username + " s-a logat cu succes!";


	}
	else {
		
		this->mesaj = "Tutorele cu usernameul: " + this->username + " NU  s-a putut loga";
		throw new CException(5, this->mesaj);
	}



}

string Cerere_LogIn::raspuns_client()
{
	return this->mesaj;
}

