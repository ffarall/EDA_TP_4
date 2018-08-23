#ifndef EVENTCLASS_H
#define EVENTCLASS_H

typedef struct
{
	void (*action) (void *);
	/*stateType*/int nextState;
}celltype_n;

typedef struct
{
	char c; // el caracter que causo el error
	JSONError_Type_n type;
}JSONParserError;

typedef struct
{
	string name;
	string value;
	JSONMemberType_n type;
	JSONParserError err;
}JSONMember_n;

class evento
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

