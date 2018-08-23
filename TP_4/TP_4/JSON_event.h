#ifndef JSON_EVENT
#define JSON_EVENT

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "celltype.h"
#include "JSON_error.h"

using namespace std;

typedef enum { BRACE_OPEN, BRACE_CLOSE, COMMA, WHITE_SPACE, STRING, NUMBER, BRACKET_OPEN, BRACKET_CLOSE, BOOLEAN, _NULL, COLLON, OTHER } JSONParserEventTypes_n;

class JSONParserEvent
{
private:
	char content;
	JSONParserEventTypes_n type;

public:
	JSONParserEvent();
	bool JSONParserEvent_is_event();
	JSONParserEventTypes_n JSONParserEvent_get_next_event();
	char JSONParserEvent_get_content();
};


#endif
