#pragma once
#include "I_Mesaje.h"
class Factory_Mesaje
{
public:
	static I_Mesaje* get_mesaj(string msg);
};

