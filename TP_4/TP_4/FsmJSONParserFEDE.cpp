#include "JSON_object_parser.h"
#include "JSON_event.h"

void fsm_cycle(/*stateType*/int *current_state, const /*event_type*/int current_event, void *User_Data)
{
	Event ev;
	const fsmParserCell_n FSMtable [EVENT_COUNT][STATE_COUNT] =
	//				WAIT_BRACE_OPEN						WAIT_NAME						WAIT_COLLON						WAIT_VALUE							WAIT_END

	{	{	{ev.noAction, WAIT_NAME},			{ev.error, WAIT_NAME},			{ev.error, WAIT_COLLON},		{ev.fsm_BraceOpen, WAIT_END},		{ev.error, WAIT_END}		},	//	{
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.error, WAIT_NAME},			{ev.error, WAIT_COLLON},		{ev.fsm_BracketOpen, WAIT_END},		{ev.error, WAIT_END}		},	//	[
		{	{ev.noAction, WAIT_BRACE_OPEN},		{ev.noAction, WAIT_NAME},		{ev.noAction, WAIT_COLLON},		{ev.noAction, WAIT_VALUE},			{ev.noAction, WAIT_END}	},	//	WHITE_SPACE
		{	{ev.finish, WAIT_BRACE_OPEN},		{ev.error, WAIT_NAME},			{ev.error, WAIT_COLLON},		{ev.error, WAIT_VALUE},				{ev.finish, WAIT_END}		},	//	}
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.error, WAIT_NAME},			{ev.error, WAIT_COLLON},		{ev.error, WAIT_VALUE},				{ev.error, WAIT_END}		},	//	]
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.error, WAIT_NAME},			{ev.error, WAIT_COLLON},		{ev.error, WAIT_VALUE},				{ev.noAction, WAIT_VALUE}	},	//	,
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.error, WAIT_NAME},			{ev.noAction, WAIT_VALUE},		{ev.error, WAIT_VALUE},				{ev.error, WAIT_END}		},	//	:
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.fsm_String, WAIT_COLLON},	{ev.error, WAIT_COLLON},		{ev.fsm_String, WAIT_END},			{ev.error, WAIT_END}		},	//	"
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.error, WAIT_NAME},			{ev.error, WAIT_COLLON},		{ev.fsm_Number, WAIT_END},			{ev.error, WAIT_END}		},	//	NUMBER
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.error, WAIT_NAME},			{ev.error, WAIT_COLLON},		{ev.fsm_Bool, WAIT_END},			{ev.error, WAIT_END}		},	//	BOOL
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.error, WAIT_NAME},			{ev.error, WAIT_COLLON},		{ev.fsm_Null, WAIT_END},			{ev.error, WAIT_END}		},	//	NULL
		{	{ev.error, WAIT_BRACE_OPEN},		{ev.fsm_Empty, WAIT_END},		{ev.error, WAIT_COLLON},		{ev.error, WAIT_VALUE},				{ev.error, WAIT_END}		}	//	VACIO
	};

	
	(FSMtable[current_event][*current_state]).action(User_Data);
	*current_state = (FSMtable[current_event][*current_state]).nextState;
}

void Event::noAction(void)
{
	return; //no hace nada
}

JSONMember_n Event::error(void *UserData)
{
	switch(ev.nextState) // se asigna el error correspondiente
	{
	case WAIT_BRACE_OPEN:
		instancia.err.type = ERROR_DURING_BRACE_OPEN;
		break;
	case WAIT_NAME:
		instancia.err.type = ERROR_DURING_WAIT_NAME;
		break;
	case WAIT_COLLON:
		instancia.err.type = ERROR_DURING_WAIT_COLLON;
		break;
	case WAIT_VALUE:
		instancia.err.type = ERROR_DURING_WAIT_VALUE;
		break;
	case WAIT_END:
		instancia.err.type = ERROR_DURING_WAIT_END;
		break;
	}
	instancia.err.c = *(char *)UserData;
	
}
 
JSONMember_n Event::finish(void)
{
	instancia.err.type = FINISH_WITH_NO_ERROR; // se indica que se finalizo sin errores... en c no hay nada
	return instancia;
}

void Event::fsm_Empty(void)
{

}



//crear las fuciones de fsm_string que reciban un void* los cuales pueden recibir por refencia:
//1) un string name
//2) un string value

void fsm_string(void)
{
	
}