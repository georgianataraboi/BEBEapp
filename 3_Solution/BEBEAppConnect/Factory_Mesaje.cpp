#include "Factory_Mesaje.h"
#include "Cerere_Inregistrare.h"
#include "Cerere_LogIn.h"
#include "Cerere_Stergere_Cont.h"
#include "Cerere_Adauga_Copil.h"
#include "Cerere_Hraniri.h"
#include "Cerere_Ore_Somn.h"
#include "Cerere_Boli.h"
#include "Cerere_Monitorizare_Crestere.h"
#include "Cerere_Update_Copil.h"
#include "Cerere_Update_Boli.h"
#include "Cerere_Update_Hraniri.h"
#include "Cerere_Update_Monitorizare_Crestere.h"
#include "Cerere_Update_OreSomn.h"

I_Mesaje* Factory_Mesaje::get_mesaj(string msg) {

	if (msg[0] == '0') {
		return new Cerere_Inregistrare(msg);
	}
	else if(msg[0]=='1') {
		return new Cerere_LogIn(msg);
	}
	else if (msg[0] == '2') {
		return new Cerere_Stergere_Cont(msg);
	}
	else if (msg[0] == '3') {
		return new	Cerere_Adauga_Copil(msg);
	}
	else if (msg[0] == '4') {
		return new Cerere_Hraniri(msg);
	}
	else if (msg[0] == '5') {
		return new Cerere_Ore_Somn(msg);
	}
	else if (msg[0] == '6') {
		return new Cerere_Boli(msg);
	}
	else if (msg[0] == '7') {
		return new Cerere_Monitorizare_Crestere(msg);
	}
	else if (msg[0] == '8') {
		return new Cerere_Update_Copil(msg);
	}
	else if (msg[0] == '9') {
		return new Cerere_Update_Boli(msg);
	}
	else if (msg[0] == 'a') {
		return new Cerere_Update_Hraniri(msg);
	}
	else if (msg[0] == 'b') {
		return new Cerere_Update_Monitorizare_Crestere(msg);
	}
	else if (msg[0] == 'c') {
		return new Cerere_Update_OreSomn(msg);
	}


}