#pragma once
#include "User.h"
class Provider:public virtual User
{
public:
	using User::type;
	using User::name;
	using User::username;
	using User::password;
public:
	vector<Book>lstBook;
public:
	bool add_detail(Book& book);
	bool remove_detail(string name);
	void view_lstBook();
	void editPrice(string nameBook, double newPrice);
	bool allow_sell(string namebook, bool check);
	Provider();
	Provider(string _name, string _username, string _password, TYPEUSER _type);
	~Provider();
};

