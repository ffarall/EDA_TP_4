#include "fsmNumber.h"

int main(void)
{
	//fsmNumber object("+340.6E2");
	fsmNumber object("");
	//cout << "numero ingresado: +340.6E2" << endl;
	cout << "numero ingresado: " << endl;
	cout << "Numero: " << object.getNumber() << endl; 
	cout << "error: " << object.getError() << endl;
	getchar();
	return 0;
}