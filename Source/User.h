#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Book.h"

enum TYPEUSER{AUTHOR, PUBLISHING, CUSTOM, ADMIN};

struct WindowChat
{
	string filename_s; // send
	string filename_r; // receive
	vector<string>send;
	vector<string>receive;
};

class User
{
public:
	string name;
	string password;
	string username;
	TYPEUSER type;
	WindowChat message;
public:
	void ViewHistorySendMes();
	void ViewHistoryReceiveMes();
	void Send(User* a, string text);
	void Receive(string text);

	void init(string _name, string _username, string _password);
	bool login(string _username, string _password);
	void changePassword(string newPassword);
	void setName(string _name);
	string getUsername();
	TYPEUSER getType();
	string getPassword();
	string getName();
	User(string _name, string _username, string _password, TYPEUSER _type);
	// virtual for custom
	virtual void view_list_book(vector<Book>& lstBook);
	virtual int findBook(string nameBook, vector<Book>lstBook);
	virtual void buy(vector<Book>lstBook);
	virtual void edit_Bill();
	virtual double getMoney();
	virtual void viewBill();
	virtual void setVouder(double percent);
	virtual double getVoucher();
	// virtual for provider
	virtual Book editBook(string namebook);
	virtual bool add_detail(Book& book);
	virtual bool remove_detail(string name);
	virtual void view_lstBook();
	virtual void editPrice(string nameBook, double newPrice);
	virtual bool allow_sell(string namebook, bool check);
	User();
	~User();
};

