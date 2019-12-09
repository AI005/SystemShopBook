#pragma once
#include "Provider.h"
class NXB:public virtual Provider
{
public:
	using Provider::type;
	using Provider::name;
	using Provider::username;
	using Provider::password;
public:
	NXB(string _name, string _username, string _password, TYPEUSER _type);
	NXB();
	~NXB();
};

