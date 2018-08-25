#include "JSONFsmParser.h"



JSONFsmParser::JSONFsmParser()
{

}

JSONFsmParser::JSONFsmParser(JSONParserEvent* eventS, JSONObject* JSONo)
{
	err = { '\0', NO_ERROR_YET };
	currentState = WAIT_BRACE_OPEN;
	objectDestination = JSONo;
	eventSource = eventS;
}

JSONField_n * JSONFsmParser::get_pointer_to_field()
{
	return objectDestination->get_pointer_to_field();
}

JSONFsmParser::~JSONFsmParser()
{
}

void no_action_routine(JSONFsmParser & fsm)
{

}

void err_routine(JSONFsmParser & fsm)
{
}

void create_JSONObject(JSONFsmParser & fsm)
{
	if (fsm.get_pointer_to_field() != nullptr)
	{

	}
	else
	{

	}
}
