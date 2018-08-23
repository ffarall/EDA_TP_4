#ifndef CELLTYPE
#define CELLTYPE

typedef enum { WAIT_BRACE_OPEN, WAIT_NAME, WAIT_COLLON, WAIT_VALUE, WAIT_END }JSONParserStates_n;

typedef struct
{
	void(*action_routine) (void*);
	JSONParserStates_n nextState;
}fsmParserCell_n;



#endif // !CELLTYPE
