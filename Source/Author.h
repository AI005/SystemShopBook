#pragma once
#include "Provider.h"
class Author:public virtual Provider
{
public:
	using Provider::type;
	using Provider::name;
	using Provider::username;
	using Provider::password;
public:
	Author(string _name, string _username, string _password, TYPEUSER _type);
	Author();
	~Author();
};

