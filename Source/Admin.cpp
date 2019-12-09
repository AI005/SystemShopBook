#include "Admin.h"

Admin::Admin(string _name, string _username, string _password, TYPEUSER _type)
{
	User::name     = _name;
	User::username = _username;
	User::password = _password;
	User::type     = _type;
}

Admin::Admin()
{
	User::type = ADMIN;
}


Admin::~Admin()
{

}
