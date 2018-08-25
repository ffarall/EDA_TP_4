#include <iostream>
#include <cstdlib>
#include <string>
#include "JSON_error.h"
#include "JSONField.h"
#include "JSON_event.h"
#include "JSONFsmParser.h"

using namespace std;

typedef unsigned int uint;


class JSONObject
{
private:
	string JSONSource;
	uint fieldCount;
	JSONField *pToFirstField;

public:
	JSONObject();
	~JSONObject();
	JSONObject(string& s);
	JSONObject(const char * s);

	/* FUNCIONS TO CREATE THE OBJECT  */
	void parse_JSON();

	JSONField* get_pointer_to_field();
	uint get_fieldCount();
	void write_pointer_to_field(JSONField* p);
	void inc_fieldCount();

	string get_field_name(uint numberOfField);
	string get_field_value(uint numberOfField);
	string get_field_valueType(uint numberOfField);
	string get_field_elementsType(uint numberOfField);
	JSONErrorType_n get_field_error(uint numberOfField);
	uint get_field_count(uint numberOfField);
	void write_field_name(string s, uint numberOfField);
	void write_field_value(string s, uint numberOfField);
	void write_field_valueType(string s, uint numberOfField);
	void write_field_elementsType(string s, uint numberOfField);
	void write_field_error(JSONErrorType_n err, uint numberOfField);
	void write_field_count(uint vc, uint numberOfField);
	/************************************/

	unsigned int getFieldCount(void);
	const char *  getFieldType(const char * f);
	const char *  getArrayType(const char * f);
	unsigned int getFieldSize(const char * f);
	bool isFieldPresent(const char * f);
	void * copyField(const char * f);
	void * copyArrayValue(const char * f, unsigned int pos);
	void print(void);
	JSONErrorType_n getError(void);
	bool parseString(const char * s);
	bool parseString(string& s);

};

