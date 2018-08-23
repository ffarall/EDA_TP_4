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

#ifndef JSON_MEMBER_TYPE
#define JSON_MEMBER_TYPE

typedef enum { STRING, NUMBER, OBJECT, ARRAY, BOOLLEAN, _NULL, EMPTY } JSONMemberType_n;

#endif // !JSON_MEMBER_TYPE

class JSONFsmParser
{
	const fsmParserCell_n FSMtable[][] =
		//				WAIT_BRACE_OPEN						WAIT_NAME						WAIT_COLLON						WAIT_VALUE							WAIT_END

	{ { { ev.noAction, WAIT_NAME },{ ev.error, WAIT_NAME },{ ev.error, WAIT_COLLON },{ ev.fsm_BraceOpen, WAIT_END },{ ev.error, WAIT_END } },	//	{
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.error, WAIT_NAME },{ ev.error, WAIT_COLLON },{ ev.fsm_BracketOpen, WAIT_END },{ ev.error, WAIT_END } },	//	[
	{ { ev.noAction, WAIT_BRACE_OPEN },{ ev.noAction, WAIT_NAME },{ ev.noAction, WAIT_COLLON },{ ev.noAction, WAIT_VALUE },{ ev.noAction, WAIT_END } },	//	WHITE_SPACE
	{ { ev.finish, WAIT_BRACE_OPEN },{ ev.error, WAIT_NAME },{ ev.error, WAIT_COLLON },{ ev.error, WAIT_VALUE },{ ev.finish, WAIT_END } },	//	}
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.error, WAIT_NAME },{ ev.error, WAIT_COLLON },{ ev.error, WAIT_VALUE },{ ev.error, WAIT_END } },	//	]
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.error, WAIT_NAME },{ ev.error, WAIT_COLLON },{ ev.error, WAIT_VALUE },{ ev.noAction, WAIT_VALUE } },	//	,
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.error, WAIT_NAME },{ ev.noAction, WAIT_VALUE },{ ev.error, WAIT_VALUE },{ ev.error, WAIT_END } },	//	:
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.fsm_String, WAIT_COLLON },{ ev.error, WAIT_COLLON },{ ev.fsm_String, WAIT_END },{ ev.error, WAIT_END } },	//	"
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.error, WAIT_NAME },{ ev.error, WAIT_COLLON },{ ev.fsm_Number, WAIT_END },{ ev.error, WAIT_END } },	//	NUMBER
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.error, WAIT_NAME },{ ev.error, WAIT_COLLON },{ ev.fsm_Bool, WAIT_END },{ ev.error, WAIT_END } },	//	BOOL
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.error, WAIT_NAME },{ ev.error, WAIT_COLLON },{ ev.fsm_Null, WAIT_END },{ ev.error, WAIT_END } },	//	NULL
	{ { ev.error, WAIT_BRACE_OPEN },{ ev.fsm_Empty, WAIT_END },{ ev.error, WAIT_COLLON },{ ev.error, WAIT_VALUE },{ ev.error, WAIT_END } }	//	VACIO
	};


	JSONParserError_n err;
public:
	JSONFsmParser();
	~JSONFsmParser();
};


#endif
