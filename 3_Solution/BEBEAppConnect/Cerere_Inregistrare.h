#pragma once
#include "I_Mesaje.h"
class Cerere_Inregistrare : public I_Mesaje
{
private:
	string username;
	string parola;
	string mesaj;
	string nr;
	string nume;
	string prenume;
public:
	Cerere_Inregistrare();
	Cerere_Inregistrare(string msg);
	void mesaj_client();
	string raspuns_client();
};

