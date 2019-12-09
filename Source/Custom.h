#pragma once
#include "User.h"
struct Post
{
	Book book;
	int amount;
};

class Custom :public virtual User
{
protected:
	vector<Post>Bill;
	double percent;
public:
	void view_list_book(vector<Book>& lstBook);
	int findBook(string nameBook, vector<Book>lstBook);
	void buy(vector<Book>lstBook);
	void edit_Bill();
	double getMoney();
	double getVoucher();
	void viewBill();
	virtual void setVouder(double percent);
	Custom(string _name, string _username, string _password, TYPEUSER _type);
	Custom();
	~Custom();

	//dummy methor


	friend class SystemLibrary;
};


