#pragma once
#include <string>
using namespace std;
class Token
{

public:
	Token()
	{
		value = "";
		type = "";
	}
	Token(string v, string t)
	{
		value = v;
		type = t;
	}
	void setValue(string v)
	{
		value = v;
	}
	string getValue()
	{
		return value;
	}
	void setType(string t)
	{
		type = t;
	}
	string getType()
	{
		return type;
	}
	string printToken()
	{
		return value + " : " + type;
	}
private:
	string value;
	string type;
};