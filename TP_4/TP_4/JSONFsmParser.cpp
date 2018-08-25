#include "JSONFsmParser.h"
#include "JSON_object.h"



void JSONFsmParser::fsm_cycle()
{
	(JSONObjectFsmMatrix[currentState][JSONFsmParser_get_event()]).action_routine(this);
	currentState = (JSONObjectFsmMatrix[currentState][JSONFsmParser_get_event()]).nextState;
}

JSONFsmParser::JSONFsmParser()
{

}

JSONFsmParser::JSONFsmParser(JSONObject * JSONobj, JSONParserEvent * evSource)
{
	error = { '\0', NO_ERROR_YET };
	currentState = WAIT_BRACE_OPEN;
	eventSource = evSource;
	objectDestination = JSONobj;
}

JSONFsmParser::JSONFsmParser(string & s, JSONParserStates_n initState)
{
	error = { '\0', NO_ERROR_YET };
	currentState = initState;
}

JSONFsmParser::JSONFsmParser(const char * s, JSONParserStates_n initState)
{
	error = { '\0', NO_ERROR_YET };
	currentState = initState;
}

JSONParserError_n JSONFsmParser::get_error()
{
	return error;
}

JSONField * JSONFsmParser::get_pointer_to_field()
{
	return objectDestination->get_pointer_to_field();
}

uint JSONFsmParser::get_fieldCount()
{
	return objectDestination->get_fieldCount();
}

string JSONFsmParser::get_field_name(uint numberOfField)
{
	return objectDestination->get_field_name(numberOfField);
}

string JSONFsmParser::get_field_value(uint numberOfField)
{
	return objectDestination->get_field_value(numberOfField);
}

string JSONFsmParser::get_field_valueType(uint numberOfField)
{
	return objectDestination->get_field_valueType(numberOfField);
}

string JSONFsmParser::get_field_elementsType(uint numberOfField)
{
	return objectDestination->get_field_elementsType(numberOfField);
}

JSONErrorType_n JSONFsmParser::get_field_error(uint numberOfField)
{
	return objectDestination->get_field_error(numberOfField);
}

uint JSONFsmParser::get_field_count(uint numberOfField)
{
	return objectDestination->get_field_count(numberOfField);
}

void JSONFsmParser::write_pointer_to_field(JSONField * p)
{
	objectDestination->write_pointer_to_field(p);
}

void JSONFsmParser::write_error(JSONParserError_n err)
{
	error = err;
}

void JSONFsmParser::inc_fieldCount()
{
	objectDestination->inc_fieldCount();
}

void JSONFsmParser::write_field_name(string s, uint numberOfField)
{
	objectDestination->write_field_name(s, numberOfField);
}

void JSONFsmParser::write_field_value(string s, uint numberOfField)
{
	objectDestination->write_field_value(s, numberOfField);
}

void JSONFsmParser::write_field_valueType(string s, uint numberOfField)
{
	objectDestination->write_field_valueType(s, numberOfField);
}

void JSONFsmParser::write_field_elementsType(string s, uint numberOfField)
{
	objectDestination->write_field_elementsType(s, numberOfField);
}

void JSONFsmParser::write_field_error(JSONErrorType_n err, uint numberOfField)
{
	objectDestination->write_field_error(err, numberOfField);
}

void JSONFsmParser::write_field_count(uint vc, uint numberOfField)
{
	objectDestination->write_field_count(vc, numberOfField);
}

void JSONFsmParser::get_new_event()
{
	eventSource->generate_event();
}

bool JSONFsmParser::JSONFsmParser_is_event()
{
	return eventSource->JSONParserEvent_is_event();
}

JSONParserEventTypes_n JSONFsmParser::JSONFsmParser_get_event()
{
	return eventSource->JSONParserEvent_get_event();
}

char JSONFsmParser::get_event_content()
{
	return eventSource->JSONParserEvent_get_content();
}

void JSONFsmParser::run_fsm()
{
	while (error.type == NO_ERROR_YET)
	{
		get_new_event();
		fsm_cycle();
	}
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
	uint arrayElementsCounter = 1;

	while (recursiveCounter != 0)
	{
		fsm.get_new_event();
		c = fsm.get_event_content();
		str += c;							// Every char gets added to the string.

		if (c == BRACKET_OPEN_ASCII && recursiveCounter == 1)
		{
			recursiveCounter++;

			fsm.get_new_event();
			c = fsm.get_event_content();
			str += c;

			if (fsm.get_field_elementsType(fsm.get_fieldCount()) != "")
			{
				switch (c)						// For the first recursive level, the type of the array elements is going to be checked.
				{
				case 'f': case 't': fsm.write_field_elementsType("bool", fsm.get_fieldCount()); break;
				case '[':
				{
					recursiveCounter++;
					fsm.write_field_elementsType("array", fsm.get_fieldCount());
				} break;
				case '{': fsm.write_field_elementsType("object", fsm.get_fieldCount()); break;
				case INVERTED_COMMAS_ASCII: fsm.write_field_elementsType("string", fsm.get_fieldCount()); break;
				case '-': case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				{
					fsm.write_field_elementsType("number", fsm.get_fieldCount());
				} break;
				default: fsm.write_error({ fsm.get_event_content(), ERR_ARRAY_SINTAX_WRONG }); break;
				}
			}
			else
			{
				fsm.write_error({ fsm.get_event_content(), ERR_INVALID_ARRAY_WITH_DIF_TYPES });
			}
		}
		else if (c == BRACKET_OPEN_ASCII)
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
			arrayElementsCounter++;
		}
	}
	fsm.write_field_value(str, fsm.get_fieldCount());
	fsm.write_field_count(arrayElementsCounter, fsm.get_fieldCount());
}

void create_string_value(JSONFsmParser & fsm)
{
	fsm.write_field_valueType("string", fsm.get_fieldCount());
	uint charCounter = 1;

	string str = "\"";
	char c = '\0';
	while (c != INVERTED_COMMAS_ASCII)
	{
		fsm.get_new_event();
		c = fsm.get_event_content();
		str += c;							// Every char gets added to the string.
		charCounter++;
		if (c == REVERSE_SOLIDUS_ASCII)
		{
			fsm.get_new_event();
			c = fsm.get_event_content();
			str += c;
			charCounter++;
			fsm.get_new_event();
			c = fsm.get_event_content();	// If an \ is received, the next char is ignored and a new one is asked for.
			str += c;
			charCounter++;
		}
	}
	fsm.write_field_value(str, fsm.get_fieldCount());
	fsm.write_field_count(charCounter, fsm.get_fieldCount());
}

void create_boolean_value(JSONFsmParser & fsm)
{
	fsm.write_field_valueType("bool", fsm.get_fieldCount());

	string str;
	str += fsm.get_event_content();			// The first digit of the bool is recovered;
	char c = '\0';
	while (c != 'e')						// Parsing ends with falsE or truE (with E).
	{
		fsm.get_new_event();
		c = fsm.get_event_content();
		str += c;							// Every char gets added to the string.
	}
	fsm.write_field_value(str, fsm.get_fieldCount());
	fsm.write_field_count(sizeof(bool), fsm.get_fieldCount());
}

void create_null_value(JSONFsmParser & fsm)
{
	fsm.write_field_valueType("object", fsm.get_fieldCount());

	for (int i = 0; i < 3; i++)				// The parser advances three chars ('u', 'l', 'l').
	{
		fsm.get_new_event();
	}
	fsm.write_field_value(NULL, fsm.get_fieldCount());
	fsm.write_field_count(0, fsm.get_fieldCount());
}

void empty_JSONObject(JSONFsmParser & fsm)
{
	err_routine(fsm);						// We will interpret an empty value as an error.
}
