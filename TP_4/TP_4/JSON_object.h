#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class JSONObject
{
public:
	JSONObject();
	JSONObject(string& s);
	JSONObject(const char * s);
	~JSONObject();
};

