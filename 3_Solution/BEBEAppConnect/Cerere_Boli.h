#pragma once
#include "I_Mesaje.h"
class Cerere_Boli :public I_Mesaje
{private:
	string nume_boala;
	string perioada_temperatura;
	string ora_consultatie_medic;
	string concluzie_medic;
	string analize;
	string rezultate_analize;
	string lista_vaccinuri;
	string nume_copil;
	string mesaj;
	string nr;
public:
	Cerere_Boli();
	Cerere_Boli(string msg);
	void mesaj_client();
	string raspuns_client();




};

