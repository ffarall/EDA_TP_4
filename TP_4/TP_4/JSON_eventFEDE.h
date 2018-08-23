#ifndef EVENTCLASS_H
#define EVENTCLASS_H

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

typedef enum { BRACE_OPEN, BRACE_CLOSE, COMMA, WHITE_SPACE, STRING, NUMBER, BRACKET_OPEN, BRACKET_CLOSE, BOOLEAN, _NULL, COLLON, OTHER } JSONParserEventTypes_n;

typedef struct
{
	void(*action) (void *);
	int nextState;
}celltype_n;

typedef struct
{
	char c; // el caracter que causo el error
	JSONErrorType_n type;
}JSONParserError_n;

typedef struct
{
	char content;
	JSONParserEventTypes_n type;
} JSONParserEvent_n;

class Event
{
	celltype_n ev;
	JSONMember_n instancia;


public:
	void noAction (void);
	JSONMember_n error(void *);
	JSONMember_n finish (void);
	void fsm_Empty(void);
}

#endif 

