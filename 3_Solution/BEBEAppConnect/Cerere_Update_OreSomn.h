#pragma once
#include "I_Mesaje.h"
class Cerere_Update_OreSomn : public I_Mesaje
{
private:
	string mesaj;
	string interval_orar;
	string nume_copil;
	string nr;
public:
	Cerere_Update_OreSomn();
	Cerere_Update_OreSomn(string msg);
	void mesaj_client();
	string raspuns_client();



};

