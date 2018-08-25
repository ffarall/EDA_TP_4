#include "JSONField.h"



JSONField::JSONField()
{

}


JSONField::~JSONField()
{
}

string JSONField::get_field_name()
{
	return name;
}

string JSONField::get_field_value()
{
	return value;
}

string JSONField::get_field_valueType()
{
	return valueType;
}

string JSONField::get_field_elementsType()
{
	return elementsType;
}

JSONErrorType_n JSONField::get_field_error()
{
	return error;
}

uint JSONField::get_count()
{
	return count;
}

void JSONField::write_field_name(string s)
{
	name = s;
}

void JSONField::write_field_value(string s)
{
	value = s;
}

void JSONField::write_field_valueType(string s)
{
	valueType = s;
}

void JSONField::write_field_elementsType(string s)
{
	elementsType = s;
}

void JSONField::write_field_error(JSONErrorType_n err)
{
	error = err;
}

void JSONField::write_count(uint vc)
{
	count = vc;
}
