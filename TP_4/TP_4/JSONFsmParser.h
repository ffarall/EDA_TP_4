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
#define MAX_FIELDS 100
#define INVERTED_COMMAS_ASCII 34
#define REVERSE_SOLIDUS_ASCII 92
#define BRACE_OPEN_ASCII 123
#define BRACE_CLOSE_ASCII 125
#define BRACKET_OPEN_ASCII 91
#define BRACKET_CLOSE_ASCII 93
#define COMMA_ASCII 44

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

	JSONParserError_n error;
	JSONParserStates_n currentState;
	JSONParserEvent eventSource;
	JSONObject objectDestination;
	
public:
	JSONFsmParser();
	~JSONFsmParser();
	JSONFsmParser(string& s);
	JSONFsmParser(const char* s);

	JSONParserStates_n get_currentState();
	JSONParserError_n get_error();
	JSONField* get_pointer_to_field();
	uint get_fieldCount();
	void write_error(JSONParserError_n err);
	void write_pointer_to_field(JSONField* p);
	void inc_fieldCount();

	string get_field_name(uint numberOfField);
	string get_field_value(uint numberOfField);
	string get_field_valueType(uint numberOfField);
	string get_field_elementsType(uint numberOfField);
	JSONErrorType_n get_field_error(uint numberOfField);
	uint get_field_count(uint numberOfField);
	void write_field_name(string s, uint numberOfField);
	void write_field_value(string s, uint numberOfField);
	void write_field_valueType(string s, uint numberOfField);
	void write_field_elementsType(string s, uint numberOfField);
	void write_field_error(JSONErrorType_n err, uint numberOfField);
	void write_field_count(uint vc, uint numberOfField);

	void get_new_event();
	bool JSONFsmParser_is_event();
	JSONParserEventTypes_n JSONFsmParser_get_next_event();
	char get_event_content();

	void run_fsm();
};


#endif
