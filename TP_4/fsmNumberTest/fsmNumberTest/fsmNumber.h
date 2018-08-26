#ifndef FSMNUMBER_H
#define FSMNUMBER_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

#define NUMBER_NOT_VALID 1
#define STATE_COUNT 6
#define EVENT_COUNT 4
#define POSITIVE 1
#define NEGATIVE -1

typedef enum { WAIT_STRING, SIGN, INTEGER, FRACTIONAL, EXPONENTIAL, EXPONENTIAL_SIGN } stateType;

typedef enum { NUMBER, PLUS_MINUS, E_e, POINT } NumberEvents;


class fsmNumber
{
	bool error;
	char character;
	double integerNumber;
	double fractionalNumber;
	double countFractional;
	double exponentialNumber;
	double signo;
	double expSign;
	double numberValue;
	stateType currentState;
	void fsmNumCycle(const NumberEvents evento, void *userData);


public:
	fsmNumber(string str);

	double getNumber(void);
	char getCharacter(void);
	double getIntegerNumber(void);
	double getFractionalNumber(void);
	double getExponentialNumber(void);
	double getSigno(void);
	double getExpSign(void);
	double getCountFractional(void);
	stateType getCurrentState(void);
	bool getError(void);

	void setCharacter(char);
	void setIntegerNumber(double);
	void setFractionalNumber(double);
	void setExponentialNumber(double);
	void setSigno(double);
	void setExpSign(double);
	void setError(bool);
	void setCountFractional(double);

};

void readChar(void *);
void changeSign(void *);
void nothing(void *);
void withError(void *);

typedef struct
{
	void(*action) (void *);
	stateType nextState;
}celltype_n;

#endif FSMNUMBER_H