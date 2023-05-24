#pragma once
#include "I_Mesaje.h"
class Cerere_Update_Hraniri : public I_Mesaje
{private:
	string mesaj;
	string tip_hrana;
	int cantitate_hrana;
	string moment_hranire;
	string nume_copil;
	string nr;
public:
	Cerere_Update_Hraniri();
	Cerere_Update_Hraniri(string msg);
	void mesaj_client();
	string raspuns_client();



};

