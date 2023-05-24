#pragma once
#include "I_Mesaje.h"
class Cerere_Monitorizare_Crestere : public I_Mesaje
{private:
	int dimensiune_cap;
	int inaltime;
	int greutate;
	string nume_copil;
	string mesaj;
	string nr;
public:
	Cerere_Monitorizare_Crestere();
	Cerere_Monitorizare_Crestere(string msg);
	void mesaj_client();
	string raspuns_client();



};

