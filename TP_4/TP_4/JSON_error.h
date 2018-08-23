#ifndef _JSON_ERROR_
#define _JSON_ERROR_

typedef enum { NO_ERROR_YET, FINISH_WITH_NO_ERROR, ERROR_DURING_BRACE_OPEN, ERROR_DURING_WAIT_NAME, ERROR_DURING_WAIT_COLLON, ERROR_DURING_WAIT_VALUE, ERROR_DURING_WAIT_END }JSONErrorType_n;

typedef struct
{
	char c; // el caracter que causo el error
	JSONErrorType_n type;
}JSONParserError_n;

#endif // !_JSON_ERROR_

