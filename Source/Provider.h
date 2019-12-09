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
	Book editBook(string namebook);
	bool add_detail(Book& book);
	bool remove_detail(string name);
	void editPrice(string nameBook, double newPrice);
	bool allow_sell(string namebook, bool check);
	void view_lstBook();
	Provider();
	Provider(string _name, string _username, string _password, TYPEUSER _type);
	~Provider();
};

