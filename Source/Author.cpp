#include "Author.h"

Author::Author(string _name, string _username, string _password, TYPEUSER _type = AUTHOR)
{
	name = _name;
	username = _username;
	password = _password;
	type = _type;
}

Author::Author()
{
	type = AUTHOR;
}

Author::~Author()
{

}