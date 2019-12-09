#pragma once
#include "Custom.h"
#include "NXB.h"
#include "Author.h"

class Admin:public Author, public NXB, public Custom
{
public:
	using Custom::type;
	using Custom::name;
	using Custom::username;
	using Custom::password;
public:
	Admin(string _name, string _username, string _password, TYPEUSER _type);
	Admin();
	~Admin();
};

