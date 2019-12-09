#include "User.h"


User::User(string _name, string _username, string _password, TYPEUSER _type)
{
	name = _name;
	username = _username;
	password = _password;
	type = _type;
}

User::User()
{
}


User::~User()
{
}

void User::ViewHistorySendMes()
{
	for (auto a : message.send)
		cout << a << endl;
}

void User::ViewHistoryReceiveMes()
{
	for (auto a : message.receive)
		cout << a << endl;
}

void User::Send(User* a, string text)
{
	string str1, str2;
	str1.append("send_to " + a->getUsername() + " :");
	str2.append(username + " :");

	time_t currentTime = time(0);
	char *A = ctime(&currentTime);
	int  i = 0;
	while (A[i] != '\0') {
		str2.push_back(A[i]);
		str1.push_back(A[i]);
		i++;
	}
	message.send.push_back(str1 + text);
	a->Receive(str2 + text);
}

void User::Receive(string text)
{
	message.receive.push_back(text);
}

void User::init(string _name, string _username, string _password)
{
	name = _name;
	username = _username;
	password = _password;
	message.filename_s = "message\\" + username + "s.txt";
	message.filename_r = "message\\" + username + "r.txt";

	fstream f_s, f_r;
	f_s.open(message.filename_s, ios::in);
	f_r.open(message.filename_r, ios::in);
	string str;
	while (!f_s.eof()) {
		getline(f_s, str);
		message.send.push_back(str);
	}

	while (!f_r.eof()) {
		getline(f_r, str);
		if(!str.empty())
			message.receive.push_back(str);
	}

	f_s.close();
	f_r.close();
}

bool User::login(string _username, string _password)
{
	return username == _username && password == _password;
}

void User::changePassword(string newPassword)
{
	password = newPassword;
}

string User::getUsername()
{
	return username;
}

TYPEUSER User::getType()
{
	return type;
}

string User::getPassword()
{
	return password;
}

string User::getName()
{
	return name;
}


void User::setName(string _name)
{
	name = _name;
}

// DUMMY METHOR

int User::findBook(string nameBook, vector<Book>lstBook)
{
	return 1;
}

void User::buy(vector<Book>lstBook)
{

}

void User::edit_Bill()
{

}
double User::getMoney()
{
	return 0.0;
}
void User::viewBill()
{

}
bool User::add_detail(Book& book)
{
	return false;
}
bool User::remove_detail(string name)
{
	return false;
}

void User::view_lstBook()
{

}

void User::editPrice(string nameBook, double newPrice)
{

}

bool User::allow_sell(string namebook, bool check)
{
	return false;
}
void User::setVouder(double percent)
{

}

double User::getVoucher()
{
	return 0.0;
}