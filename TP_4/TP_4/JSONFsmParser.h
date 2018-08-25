#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "JSON_event.h"
#include "JSON_error.h"
#include "JSON_object.h"

using namespace std;

// void fsm_cycle(/*stateType*/int *current_state, const /*event_type*/int current_event, void *User_Data);
#define JSON_PARSER_STATES_COUNT 5
#define JSON_PARSER_EVENTS_COUNT 12

typedef enum { WAIT_BRACE_OPEN, WAIT_NAME, WAIT_COLLON, WAIT_VALUE, WAIT_END }JSONParserStates_n;
typedef struct
{
	void(*action_routine) (JSONFsmParser& fsm);
	JSONParserStates_n nextState;
}fsmParserCell_n;

void no_action_routine(JSONFsmParser& fsm);
void err_routine(JSONFsmParser& fsm);
void create_JSONObject(JSONFsmParser& fsm);
void finish_parsing(JSONFsmParser& fsm);
void parse_name(JSONFsmParser& fsm);
void create_JSONObject_value(JSONFsmParser& fsm);
void create_array_value(JSONFsmParser& fsm);
void create_string_value(JSONFsmParser& fsm);
void create_number_value(JSONFsmParser& fsm);
void create_boolean_value(JSONFsmParser& fsm);
void create_null_value(JSONFsmParser& fsm);
void empty_JSONObject(JSONFsmParser& fsm);

class JSONFsmParser
{
	const fsmParserCell_n JSONObjectFsmMatrix[JSON_PARSER_EVENTS_COUNT][JSON_PARSER_STATES_COUNT] =
//				WAIT_BRACE_OPEN					WAIT_NAME						WAIT_COLLON					WAIT_VALUE						WAIT_END

	{ { { create_JSONObject, WAIT_NAME },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ create_JSONObject_value, WAIT_END },{ err_routine, WAIT_END } },	//	{
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ create_array_value, WAIT_END },{ err_routine, WAIT_END } },	//	[
	{ { no_action_routine, WAIT_BRACE_OPEN },{ no_action_routine, WAIT_NAME },{ no_action_routine, WAIT_COLLON },{ no_action_routine, WAIT_VALUE },{ no_action_routine, WAIT_END } },	//	WHITE_SPACE
	{ { finish_parsing, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ empty_JSONObject, WAIT_VALUE },{ finish_parsing, WAIT_END } },	//	}
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ err_routine, WAIT_VALUE },{ err_routine, WAIT_END } },	//	]
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ empty_JSONObject, WAIT_VALUE },{ no_action_routine, WAIT_VALUE } },	//	,
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ no_action_routine, WAIT_VALUE },{ err_routine, WAIT_VALUE },{ err_routine, WAIT_END } },	//	:
	{ { err_routine, WAIT_BRACE_OPEN },{ parse_name, WAIT_COLLON },{ err_routine, WAIT_COLLON },{ create_string_value, WAIT_END },{ err_routine, WAIT_END } },	//	"
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ create_number_value, WAIT_END },{ err_routine, WAIT_END } },	//	NUMBER
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ create_boolean_value, WAIT_END },{ err_routine, WAIT_END } },	//	BOOL
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_NAME },{ err_routine, WAIT_COLLON },{ create_null_value, WAIT_END },{ err_routine, WAIT_END } },	//	NULL
	{ { err_routine, WAIT_BRACE_OPEN },{ err_routine, WAIT_END },{ err_routine, WAIT_COLLON },{ err_routine, WAIT_VALUE },{ err_routine, WAIT_END } }	//	VACIO
	};

	JSONParserError_n err;
	JSONParserStates_n currentState;
	JSONParserEvent* eventSource;
	JSONObject* objectDestination;
	
public:
	JSONFsmParser();
	~JSONFsmParser();
	JSONFsmParser(JSONParserEvent* eventS, JSONObject* JSONo);

	JSONParserStates_n get_current_state();
	JSONParserError_n get_error();
	JSONField_n* get_pointer_to_field();

	void run_fsm();
};


#endif
