#pragma once
#include "I_Mesaje.h"
class Cerere_Adauga_Copil :public I_Mesaje
{
	string nume_copil;
	string prenume_copil;
	string data_nastere;
	string mesaj;
	string nr;
	string username;
	int varsta;
public:
	Cerere_Adauga_Copil();
	Cerere_Adauga_Copil(string msg);
	void mesaj_client();
	string raspuns_client();






};

