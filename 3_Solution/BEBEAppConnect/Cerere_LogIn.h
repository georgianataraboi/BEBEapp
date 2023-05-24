#pragma once
#include "I_Mesaje.h"
#include "BD_Connection.h"
class Cerere_LogIn :public I_Mesaje
{private:

	string username;
	string parola;
	string nr;
	string mesaj;
public:
	Cerere_LogIn();
	Cerere_LogIn(string msg);
	void mesaj_client();
	string raspuns_client();



};

