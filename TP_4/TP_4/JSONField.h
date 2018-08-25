#include <iostream>
#include <cstdlib>
#include <string>
#include "JSON_error.h"

using namespace std;

typedef unsigned int uint;


class JSONField
{
private:
	string name;
	string value;
	string valueType;
	uint count;
	string elementsType; // In case of valueType = array.
	JSONErrorType_n error;
public:
	JSONField();
	~JSONField();
	string get_field_name();
	string get_field_value();
	string get_field_valueType();
	string get_field_elementsType();
	JSONErrorType_n get_field_error();
	uint get_count();
	void write_field_name(string s);
	void write_field_value(string s);
	void write_field_valueType(string s);
	void write_field_elementsType(string s);
	void write_field_error(JSONErrorType_n err);
	void write_count(uint vc);
};

