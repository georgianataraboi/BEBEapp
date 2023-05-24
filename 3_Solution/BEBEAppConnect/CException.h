#pragma once
#include<iostream>

using namespace std;

class CException
{
private:
	string err;
	int cod;
public:
	CException();
	CException(int cod, string err);
	void what();
};

