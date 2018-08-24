#include <iostream>
#include <cstdlib>
#include <string>
#include "JSON_error.h"

using namespace std;

typedef unsigned int uint;
typedef struct
{
	uint elementsCount;
	string elementsType;
}arrayValueData_n;
typedef union
{
	uint objects;
	arrayValueData_n arrayElements;
	uint chars;
	uint doubleSize;
	uint boolSize;
}valueCounter_n;
typedef struct
{
	string valueType;
	valueCounter_n count;
}valueData_n;
typedef struct
{
	string name;
	string value;
	valueData_n valueData;
	JSONErrorType_n error;
}JSONField_n;

class JSONObject
{
private:
	uint fieldCount;
	JSONField_n *pToFirstField;

public:
	JSONObject();
	JSONObject(string& s);
	JSONObject(const char * s);
	~JSONObject();
};

