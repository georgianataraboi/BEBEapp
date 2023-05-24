#include "CException.h"

CException::CException()
{
	this->cod = 0;
	this->err = nullptr;
}

CException::CException(int cod, string err)
{
	this->cod = cod;
	this->err = err;

}

void CException::what()
{
	cout << this->cod << " " << this->err;
}
