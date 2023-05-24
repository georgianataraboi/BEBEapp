#pragma once
#include "I_Mesaje.h"
class Cerere_Ore_Somn :public I_Mesaje
{private:
	string mesaj;
	string interval_orar;
	string nume_copil;
	string nr;
public:
	Cerere_Ore_Somn();
	Cerere_Ore_Somn(string msg);
	void mesaj_client();
	string raspuns_client();





};

