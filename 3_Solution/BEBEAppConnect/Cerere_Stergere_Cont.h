 #pragma once
#include "I_Mesaje.h"
class Cerere_Stergere_Cont: public I_Mesaje
{private:
	string username;
	string parola;
	string nr;
	string mesaj;
public:
	Cerere_Stergere_Cont();
	Cerere_Stergere_Cont(string msg);
	void mesaj_client();
	string raspuns_client();




};

