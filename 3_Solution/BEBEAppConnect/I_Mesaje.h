#pragma once
#include<string>
#include<iostream>

using namespace std;

class I_Mesaje
{	public:
	virtual void mesaj_client() = 0;
	virtual string raspuns_client() = 0;

};

