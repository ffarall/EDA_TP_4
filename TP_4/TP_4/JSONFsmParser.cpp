#include "JSONFsmParser.h"



JSONFsmParser::JSONFsmParser()
{

}

JSONFsmParser::JSONFsmParser(string& s) :eventSource(s), objectDestination()
{
	error = { '\0', NO_ERROR_YET };
	currentState = WAIT_BRACE_OPEN;
}

JSONFsmParser::JSONFsmParser(const char * s) :eventSource(s), objectDestination()
{
	error = { '\0', NO_ERROR_YET };
	currentState = WAIT_BRACE_OPEN;
}

JSONParserError_n JSONFsmParser::get_error()
{
	return error;
}

JSONField * JSONFsmParser::get_pointer_to_field()
{
	return objectDestination.get_pointer_to_field();
}

uint JSONFsmParser::get_fieldCount()
{
	return objectDestination.get_fieldCount();
}

string JSONFsmParser::get_field_name(uint numberOfField)
{
	return objectDestination.get_field_name(numberOfField);
}

string JSONFsmParser::get_field_value(uint numberOfField)
{
	return objectDestination.get_field_value(numberOfField);
}

string JSONFsmParser::get_field_valueType(uint numberOfField)
{
	return objectDestination.get_field_valueType(numberOfField);
}

string JSONFsmParser::get_field_elementsType(uint numberOfField)
{
	return objectDestination.get_field_elementsType(numberOfField);
}

JSONErrorType_n JSONFsmParser::get_field_error(uint numberOfField)
{
	return objectDestination.get_field_error(numberOfField);
}

uint JSONFsmParser::get_field_count(uint numberOfField)
{
	return objectDestination.get_field_count(numberOfField);
}

void JSONFsmParser::write_pointer_to_field(JSONField * p)
{
	objectDestination.write_pointer_to_field(p);
}

void JSONFsmParser::write_error(JSONParserError_n err)
{
	error = err;
}

void JSONFsmParser::inc_fieldCount()
{
	objectDestination.inc_fieldCount();
}

void JSONFsmParser::write_field_name(string s, uint numberOfField)
{
	objectDestination.write_field_name(s, numberOfField);
}

void JSONFsmParser::write_field_value(string s, uint numberOfField)
{
	objectDestination.write_field_value(s, numberOfField);
}

void JSONFsmParser::write_field_valueType(string s, uint numberOfField)
{
	objectDestination.write_field_valueType(s, numberOfField);
}

void JSONFsmParser::write_field_elementsType(string s, uint numberOfField)
{
	objectDestination.write_field_elementsType(s, numberOfField);
}

void JSONFsmParser::write_field_error(JSONErrorType_n err, uint numberOfField)
{
	objectDestination.write_field_error(err, numberOfField);
}

void JSONFsmParser::write_field_count(uint vc, uint numberOfField)
{
	objectDestination.write_field_count(vc, numberOfField);
}

void JSONFsmParser::get_new_event()
{
	eventSource.generate_event();
}

bool JSONFsmParser::JSONFsmParser_is_event()
{
	return eventSource.JSONParserEvent_is_event();
}

JSONParserEventTypes_n JSONFsmParser::JSONFsmParser_get_next_event()
{
	return eventSource.JSONParserEvent_get_next_event();
}

char JSONFsmParser::get_event_content()
{
	return eventSource.JSONParserEvent_get_content();
}

JSONParserStates_n JSONFsmParser::get_currentState()
{
	return currentState;
}

JSONFsmParser::~JSONFsmParser()
{
}

void no_action_routine(JSONFsmParser & fsm)
{

}

void err_routine(JSONFsmParser & fsm)
{
	switch (fsm.get_currentState())// se asigna el error correspondiente
	{
	case WAIT_BRACE_OPEN:
		fsm.write_error({ fsm.get_event_content(), ERROR_DURING_BRACE_OPEN });
		break;
	case WAIT_NAME:
		fsm.write_error({ fsm.get_event_content(), ERROR_DURING_WAIT_NAME });
		break;
	case WAIT_COLLON:
		fsm.write_error({ fsm.get_event_content(), ERROR_DURING_WAIT_COLLON });
		break;
	case WAIT_VALUE:
		fsm.write_error({ fsm.get_event_content(), ERROR_DURING_WAIT_VALUE });
		break;
	case WAIT_END:
		fsm.write_error({ fsm.get_event_content(), ERROR_DURING_WAIT_END });
		break;
	}

}

void create_JSONObject(JSONFsmParser & fsm)
{
	if (fsm.get_pointer_to_field() == nullptr)
	{
		fsm.inc_fieldCount();
		JSONField *p = new JSONField[MAX_FIELDS];
		fsm.write_pointer_to_field(p);
	}
	else
	{
		fsm.inc_fieldCount();
		if (fsm.get_fieldCount() >= MAX_FIELDS)
		{
			fsm.write_error({ '\0', ERR_NOT_ENOUGH_FIELDS });
		}
	}
}

void finish_parsing(JSONFsmParser & fsm)
{
	if (fsm.get_currentState() == WAIT_BRACE_OPEN)
	{
		if (fsm.get_pointer_to_field() == nullptr)
		{
			
		}
		fsm.write_error({ '\0', FINISH_WITH_NO_ERROR });
	}
}

void parse_name(JSONFsmParser & fsm)
{
	string str = "\"";
	char c = '\0';
	while (c != INVERTED_COMMAS_ASCII)
	{
		fsm.get_new_event();
		c = fsm.get_event_content();
		str += c;							// Every char gets added to the string.
		if (c == REVERSE_SOLIDUS_ASCII)
		{
			fsm.get_new_event();
			c = fsm.get_event_content();
			str += c;
			fsm.get_new_event();
			c = fsm.get_event_content();	// If an \ is received, the next char is ignored and a new one is asked for.
			str += c;
		}
	}
	fsm.write_field_name(str, fsm.get_fieldCount());
}

void create_JSONObject_value(JSONFsmParser & fsm)
{
	fsm.write_field_valueType("object", fsm.get_fieldCount());

	string str = "{";
	char c;
	uint recursiveCounter = 1;
	uint objectsCounter = 1;

	while (recursiveCounter != 0)
	{
		fsm.get_new_event();
		c = fsm.get_event_content();
		str += c;							// Every char gets added to the string.

		if (c == BRACE_OPEN_ASCII)
		{
			recursiveCounter++;
		}
		else if (c == BRACE_CLOSE_ASCII)
		{
			if (recursiveCounter > 0)			// This might be unnecessary.
			{
				recursiveCounter--;
			}
			else
			{
				fsm.write_error({ '\0', ERR_OBJECT_SINTAX_WRONG });
			}
		}
		else if (c == COMMA_ASCII && recursiveCounter == 1)
		{
			objectsCounter++;
		}
	}
	fsm.write_field_value(str, fsm.get_fieldCount());
	fsm.write_field_count(objectsCounter, fsm.get_fieldCount());
}

void create_array_value(JSONFsmParser & fsm)
{
	fsm.write_field_valueType("array", fsm.get_fieldCount());

	string str = "[";
	char c;
	uint recursiveCounter = 1;
	uint arraysCounter = 1;
	uint arrayElementsCounter = 1;

	while (recursiveCounter != 0)
	{
		fsm.get_new_event();
		c = fsm.get_event_content();
		str += c;							// Every char gets added to the string.

		if (c == BRACKET_OPEN_ASCII)
		{
			recursiveCounter++;
		}
		else if (c == BRACKET_CLOSE_ASCII)
		{
			if (recursiveCounter > 0)			// This might be unnecessary.
			{
				recursiveCounter--;
			}
			else
			{
				fsm.write_error({ '\0', ERR_OBJECT_SINTAX_WRONG });
			}
		}
		else if (c == COMMA_ASCII && recursiveCounter == 1)
		{
			arraysCounter++;
		}
	}
	fsm.write_field_value(str, fsm.get_fieldCount());
	fsm.write_field_count(arraysCounter, fsm.get_fieldCount());
}
