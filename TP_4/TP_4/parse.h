#ifndef PARSER.H
#define PARSER.H

#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

void fsm_cycle(/*stateType*/int *current_state, const /*event_type*/int current_event, void *User_Data);


#define STATE_COUNT 5
#define EVENT_COUNT 12

typedef enum { BRACE_OPEN, BRACE_CLOSE, COMMA, WHITE_SPACE, STRING, NUMBER, BRACKET_OPEN, BRACKET_CLOSE, BOOLEAN, NULL, COLLON, OTHER } JSONParserEventTypes_n;

typedef enum { STRING, NUMBER, OBJECT, ARRAY, BOOLLEAN, NULL, EMPTY } JSONMemberType_n;

typedef enum { WAIT_BRACE_OPEN, WAIT_NAME, WAIT_COLLON,	WAIT_VALUE, WAIT_END }JSONParserStates_n;

typedef enum { NO_ERROR_YET, FINISH_WITH_NO_ERROR, ERROR_DURING_BRACE_OPEN, ERROR_DURING_WAIT_NAME, ERROR_DURING_WAIT_COLLON, ERROR_DURING_WAIT_VALUE, ERROR_DURING_WAIT_END }JSONError_Type_n;

typedef struct
{
	char content;
	JSONParserEventTypes_n type;
} JSONParserEvent_n;



#endif