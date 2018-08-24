#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "celltype.h"
#include "JSON_event.h"
#include "JSON_error.h"

using namespace std;

// void fsm_cycle(/*stateType*/int *current_state, const /*event_type*/int current_event, void *User_Data);
#define JSON_PARSER_STATES_COUNT 5
#define JSON_PARSER_EVENTS_COUNT 12

/*#ifndef JSON_VALUE_TYPE
#define JSON_VALUE_TYPE
typedef enum { STRING, NUMBER, OBJECT, ARRAY, BOOLLEAN, _NULL, EMPTY } JSONValueType_n;
#endif // !JSON_VALUE_TYPE*/

void no_action_routine(JSONFsmParser& fsm);
void err_routine(JSONFsmParser& fsm);


class JSONFsmParser
{
	const fsmParserCell_n JSONObjectFsmMatrix[JSON_PARSER_EVENTS_COUNT][JSON_PARSER_STATES_COUNT] =
//				WAIT_BRACE_OPEN				WAIT_NAME						WAIT_COLLON					WAIT_VALUE						WAIT_END

	{ { { no_action_routine, WAIT_NAME },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ ev.fsm_BraceOpen, WAIT_END },{ err_routine, WAIT_END } },	//	{
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ ev.fsm_BracketOpen, WAIT_END },{ err_routine, WAIT_END } },	//	[
	{ { no_action_routine, WAIT_BRACE_OPEN },{ no_action_routine, WAIT_NAME },{ no_action_routine, WAIT_COLLON },{ no_action_routine, WAIT_VALUE },{ no_action_routine, WAIT_END } },	//	WHITE_SPACE
	{ { ev.finish, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ err_routine, WAIT_VALUE },{ ev.finish, WAIT_END } },	//	}
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ err_routine, WAIT_VALUE },{ err_routine, WAIT_END } },	//	]
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ err_routine, WAIT_VALUE },{ no_action_routine, WAIT_VALUE } },	//	,
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ no_action_routine, WAIT_VALUE },{ err_routine, WAIT_VALUE },{ err_routine, WAIT_END } },	//	:
	{ { err_routine, WAIT_BRACE_OPEN },{ ev.fsm_String, WAIT_COLLON },{ err_routine, WAIT_COLLON },{ ev.fsm_String, WAIT_END },{ err_routine, WAIT_END } },	//	"
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ ev.fsm_Number, WAIT_END },{ err_routine, WAIT_END } },	//	NUMBER
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ ev.fsm_Bool, WAIT_END },{ err_routine, WAIT_END } },	//	BOOL
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ ev.fsm_Null, WAIT_END },{ err_routine, WAIT_END } },	//	NULL
	{ { err_routine, WAIT_BRACE_OPEN },{ ev.fsm_Empty, WAIT_END },{ err_routine, WAIT_COLLON },{ err_routine, WAIT_VALUE },{ err_routine, WAIT_END } }	//	VACIO
	};

	JSONParserError_n err;
	JSONParserStates_n currentState;
	
public:
	JSONFsmParser();
	~JSONFsmParser();

};


#endif
