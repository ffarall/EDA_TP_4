#include "fsmNumber.h"



fsmNumber::fsmNumber(string str)
{
	currentState = WAIT_STRING;
	NumberEvents evento;
	error = false; // muestra que todavia no hubo errores
	integerNumber = 0;
	fractionalNumber = 0;
	exponentialNumber = 0;
	countFractional = 0;
	signo = 1;
	expSign = 1;

	string::size_type max = str.length();

	for (string::size_type i = 0; i < max && error != true ; i++)
	{
		character = str[i];
		if ((character >= '0') && (character <= '9'))
		{
			cout << "inicio: " << character << "\t";
			evento = NUMBER;
		}
		else if ((character == '-') || (character == '+'))
		{
			evento = PLUS_MINUS;
		}
		else if ((character == 'e') || (character == 'E'))
		{
			evento = E_e;
		}
		else if ((character == '.'))
		{
			evento = POINT;
		}
		else
		{
			error = true;
		}
		fsmNumCycle(evento, &character);
	}

	fractionalNumber = (fractionalNumber / pow(10.0, countFractional));

	numberValue = signo * ((integerNumber + fractionalNumber) * pow(10.0, (expSign * exponentialNumber)));

}

void fsmNumber::fsmNumCycle(NumberEvents const evento, void *userData)
{

	const celltype_n tableFsmNum[EVENT_COUNT][STATE_COUNT] =

		//		WAIT_STRING							SIGN					INTEGER									FRACTIONAL							EXPONENTIAL						EXPONENTIAL_SIGN
	{
	{	{readChar, INTEGER},				{readChar, INTEGER},		{readChar, INTEGER},					{readChar, FRACTIONAL},			{readChar, EXPONENTIAL},			{readChar, EXPONENTIAL}				},	// NUMBER
	{	{changeSign, SIGN},					{withError, SIGN},			{withError, INTEGER},					{withError, FRACTIONAL},		{withError, EXPONENTIAL},			{changeSign, EXPONENTIAL}			},	// +/-
	{	{withError, WAIT_STRING},			{withError, SIGN},			{nothing, EXPONENTIAL_SIGN},			{nothing, EXPONENTIAL_SIGN},	{withError, EXPONENTIAL},			{withError, EXPONENTIAL_SIGN}		},	// e/E
	{	{withError, WAIT_STRING},			{withError, SIGN},			{nothing, FRACTIONAL},					{withError, FRACTIONAL},		{withError, EXPONENTIAL},			{withError, EXPONENTIAL_SIGN}		},	// .
	};

	(tableFsmNum[evento][currentState]).action(this);
	currentState = (tableFsmNum[evento][currentState].nextState);

}

/*			readChar

	-recibe un puntero a void (objeto fsmNumber)
	-no devuelve nada
	-lee un caracter y en base al estado en el que se encuentra la fsm guarda el valor en la parte decimal, fraccionaria o exponencial
*/
void readChar(void *userData)
{
	fsmNumber *object = (fsmNumber *)userData;
	double charValue = (object->getCharacter() - '0');// se guarda en charvalue el valor del caracter recibido (en ascii)
	if ((charValue < 0) && (charValue > 9))
	{
		object->setError(true);
		return;
	}
	switch (object->getCurrentState())
	{
	case WAIT_STRING: case SIGN: case INTEGER:
		object->setIntegerNumber(object->getIntegerNumber() * 10);
		object->setIntegerNumber(object->getIntegerNumber() + charValue);
		break;
	case FRACTIONAL:
		object->setFractionalNumber(object->getFractionalNumber() * 10);
		object->setFractionalNumber(object->getFractionalNumber() + charValue);
		object->setCountFractional(object->getCountFractional() + 1);
		break;
	case EXPONENTIAL: case EXPONENTIAL_SIGN:
		object->setExponentialNumber(object->getExponentialNumber() * 10);
		object->setExponentialNumber(object->getExponentialNumber() + charValue);
		break;
	default:
		break;	//no puede llegar un estado que no sea alguno de los validos
	}

}

/*		withError

	-recibe un puntero a void (objeto fsmNumber)
	-no devuelve nada
	-avisa que hubo error seteando una variable de error del objeto
*/
void withError(void * userData)
{
	fsmNumber * object = (fsmNumber *)userData;
	object->setError(true);
}


double fsmNumber::getNumber()
{
	return numberValue;
}

void nothing(void * userData)
{
	return;
}
bool fsmNumber::getError(void)
{
	return error;
}


/*		changeSign

	-recibe puntero a void
	-no devuelve nada
	-si el caracter leido es un signo "+" o "-", en base al estado en el que se encuentra activa el digno del exponente o del numero
*/
void changeSign(void * userData)
{
	fsmNumber *object = (fsmNumber *)userData;
	char character = object->getCharacter();
	stateType state = object->getCurrentState();
	switch (character)
	{
	case '-':
		if (state == WAIT_STRING)
		{
			object->setSigno(NEGATIVE);
		}
		else
		{
			object->setExpSign(NEGATIVE);		
		}
		break;
	case '+':
		if (state == WAIT_STRING)
		{
			object->setSigno(POSITIVE);
		}
		else
		{
			object->setExpSign(POSITIVE);
		}
		break;
	default:
		break;		
	}
	return;
}
// GETTERS
char  fsmNumber::getCharacter(void)
{
	return character;
}
double fsmNumber::getIntegerNumber(void)
{
	return integerNumber;
}
double fsmNumber::getFractionalNumber(void)
{
	return fractionalNumber;
}
double fsmNumber::getExponentialNumber(void)
{
	return exponentialNumber;
}
double fsmNumber::getSigno(void)
{
	return signo;
}
stateType fsmNumber::getCurrentState(void)
{
	return currentState;
}
double fsmNumber::getCountFractional(void)
{
	return countFractional;
}
double fsmNumber::getExpSign(void)
{
	return expSign;
}
//SETTERS

void fsmNumber::setError(bool mistake)
{
	error = mistake;
}

void fsmNumber::setCharacter(char c)
{
	character = c;
}
void fsmNumber::setIntegerNumber(double number)
{
	integerNumber = number;
}
void fsmNumber::setFractionalNumber(double numberf)
{
	fractionalNumber = numberf;
}
void fsmNumber::setExponentialNumber(double exponentialN)
{
	exponentialNumber = exponentialN;
}
void fsmNumber::setSigno(double jamon)
{
	signo = jamon;

}
void fsmNumber::setCountFractional(double numbercf)
{
	countFractional = numbercf;
}
void fsmNumber::setExpSign(double numberes)
{
	expSign = numberes;
}
