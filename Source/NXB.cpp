#include "NXB.h"

NXB::NXB(string _name, string _username, string _password, TYPEUSER _type = PUBLISHING)
{
	name = _name;
	username = _username;
	password = _password;
	type = _type;
}


NXB::NXB()
{
	type = PUBLISHING;
}


NXB::~NXB()
{
}
