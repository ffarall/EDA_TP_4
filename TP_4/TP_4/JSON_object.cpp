#include "JSON_object.h"



JSONObject::JSONObject()
{
	fieldCount = 0;
	pToFirstField = nullptr;
}

JSONObject::JSONObject(string & s)
{
}


JSONObject::~JSONObject()
{
}

JSONField * JSONObject::get_pointer_to_field()
{
	return pToFirstField;
}

uint JSONObject::get_fieldCount()
{
	return fieldCount;
}

void JSONObject::write_pointer_to_field(JSONField* p)
{
	pToFirstField = p;
}

void JSONObject::inc_fieldCount()
{
	fieldCount++;
}

string JSONObject::get_field_name(uint numberOfField)
{
	return (pToFirstField+numberOfField)->get_field_name();
}

string JSONObject::get_field_value(uint numberOfField)
{
	return (pToFirstField + numberOfField)->get_field_name();
}

string JSONObject::get_field_valueType(uint numberOfField)
{
	return (pToFirstField + numberOfField)->get_field_valueType();
}

string JSONObject::get_field_elementsType(uint numberOfField)
{
	return (pToFirstField + numberOfField)->get_field_elementsType();
}

JSONErrorType_n JSONObject::get_field_error(uint numberOfField)
{
	return (pToFirstField + numberOfField)->get_field_error();
}

uint JSONObject::get_field_count(uint numberOfField)
{
	return (pToFirstField + numberOfField)->get_count();
}

void JSONObject::write_field_name(string s, uint numberOfField)
{
	(pToFirstField + numberOfField)->write_field_name(s);
}

void JSONObject::write_field_value(string s, uint numberOfField)
{
	(pToFirstField + numberOfField)->write_field_value(s);
}

void JSONObject::write_field_valueType(string s, uint numberOfField)
{
	(pToFirstField + numberOfField)->write_field_valueType(s);
}

void JSONObject::write_field_elementsType(string s, uint numberOfField)
{
	(pToFirstField + numberOfField)->write_field_elementsType(s);
}

void JSONObject::write_field_error(JSONErrorType_n err, uint numberOfField)
{
	(pToFirstField + numberOfField)->write_field_error(err);
}

void JSONObject::write_field_count(uint vc, uint numberOfField)
{
	(pToFirstField + numberOfField)->write_count(vc);
}
