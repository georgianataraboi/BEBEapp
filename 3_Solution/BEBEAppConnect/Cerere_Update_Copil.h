#pragma once
#include "I_Mesaje.h"
class Cerere_Update_Copil: public I_Mesaje
{
	string nume_copil;
	string prenume_copil;
	string data_nastere;
	string mesaj;
	string nr;
	string nume_copil2;
	int varsta;
	int id_tutore;
public:
	Cerere_Update_Copil();
	Cerere_Update_Copil(string msg);
	void mesaj_client();
	string raspuns_client();





};

