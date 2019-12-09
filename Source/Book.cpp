#include "Book.h"



Book::Book()
{
}


Book::~Book()
{
}

void Book::init(string _name, string _type, string _author, int _ID, double _price, string _NXB, bool _check)
{
	name = _name;
	type = _type;
	author = _author;
	ID = _ID;
	price = _price;
	NXB = _NXB;
	OnSell = _check;
}

string Book::getName()
{
	return this->name;
}

string Book::getType()
{
	return this->type;
}

string Book::getAuthor()
{
	return this->author;
}

int Book::getID()
{
	return this->ID;
}

double Book::getPrice()
{
	return this->price;
}

string Book::getNXB()
{
	return this->NXB;
}

int Book::getCheckSell()
{
	return OnSell;
}
//void init(string _name, string _type, string _author, int _ID, double _price, string _NXB);
void Book::input()
{
	cin.ignore(256, '\n');
	cout << "name: ";	getline(cin, name);
	
	//cin.ignore(256, '\n');
	cout << "type: ";	getline(cin, type);

	//cin.ignore(256, '\n');
	cout << "author: ";	getline(cin, author);

	//cin.ignore(256, '\n');
	cout << "NXB: ";	getline(cin, NXB);

	cout << "Price: "; cin >> price;
}

void Book::setID(int _ID)
{
	ID = _ID;
}

void Book::setPrice(double _price)
{
	price = _price;
}

bool Book::is_sell()
{
	return OnSell;
}
void Book::OnSellMode()
{
	OnSell = true;
}

void Book::OffSellMode()
{
	OnSell = false;
}

void Book::editBook()
{
	int select;
	cout
		<< "\nChange Information"
		<< "\n1. name"
		<< "\n2. type"
		<< "\n3. author"
		<< "\n4. ID"
		<< "\n5. NXB"
		<< "\n6. Price"
		<< "\nSelect: ";    cin >> select;
	switch (select) {
	case 1:
		cin.ignore(256, '\n');    cout << "new name: ";    getline(cin, name);
		break;
	case 2:
		cin.ignore(256, '\n');    cout << "new type: ";    getline(cin, type);
		break;
	case 3:
		cin.ignore(256, '\n');    cout << "new name's author: ";    getline(cin, author);
		break;
	case 4:
		cout << "new ID: ";    cin >> ID;
		break;
	case 5:
		cin.ignore(256, '\n');    cout << "new name's NXB: ";    getline(cin, NXB);
		break;
	case 6:
		cout << "new Price: ";    cin >> price;
		break;
	default:
		break;
	}
}
