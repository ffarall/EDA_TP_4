#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "JSON_event.h"
#include "JSON_error.h"

using namespace std;

// void fsm_cycle(/*stateType*/int *current_state, const /*event_type*/int current_event, void *User_Data);


#define STATE_COUNT 5
#define EVENT_COUNT 12

typedef enum { STRING, NUMBER, OBJECT, ARRAY, BOOLLEAN, _NULL, EMPTY } JSONMemberType_n;


#endif