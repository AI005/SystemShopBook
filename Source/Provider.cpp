#include "Provider.h"


Provider::Provider(string _name, string _username, string _password, TYPEUSER _type)
	:User(_name, _username, _password, _type){}

Provider::Provider()
{

}


Provider::~Provider()
{
}


//return true if add success, else false
bool Provider::add_detail(Book& book)
{

	//check the book has exist in list, if exist return false, else add the book at last
	for (auto a : lstBook) {
		if (a.getName() == book.getName())
			return false;
	}

	lstBook.push_back(book);
	return true;
}

//return true if remove success, else false
bool Provider::remove_detail(string name)
{
	int n = lstBook.size();
	for (int i = 0; i < n; ++i) {
		if (lstBook[i].getName() == name) {
			lstBook.erase(lstBook.begin() + i);
			return true;
		}
	}
	return false;
}


void Provider::editPrice(string nameBook, double newPrice)
{
	for (auto& a : lstBook)
		if (a.getName() == nameBook) {
			a.setPrice(newPrice);
			break;
		}
}

bool Provider::allow_sell(string namebook, bool check)
{
	for (auto& a : lstBook)
		if (a.getName() == namebook) {
			if (check == true)	a.OnSellMode();
			else                a.OffSellMode();
			return true;
		}
	return false;
}

void Provider::view_lstBook()
{
	struct INFORMATION
	{
		string name;
		int length;
	};
	vector<INFORMATION>info{ {"Name", 6}, {"Type", 4}, {"Author", 4}, {"ID", 1}, {"Price", 2}, {"NXB", 3}, {"Sell", 1} };
	int n = info.size();
	int minSpace = 4;
	int Width = 0;
	for (auto a : info) { Width += a.length; }
	Width = Width * minSpace + 2;

	cout << string(Width, '_') << endl;
	cout << "|";
	for (auto a : info) {
		cout << setw(minSpace* a.length) << a.name + " |";
	}
	cout << endl << string(Width, '-') << endl;

	ostringstream convert;
	for (auto a : lstBook) {
		cout << "|";
		cout << setw(minSpace*info[0].length) << a.getName() + " |";
		cout << setw(minSpace*info[1].length) << a.getType() + " |";
		cout << setw(minSpace*info[2].length) << a.getAuthor() + " |";

		convert << a.getID() << " |";
		cout << setw(minSpace*info[3].length) << convert.str();
		convert.str("");

		convert << a.getPrice() << " |";
		cout << setw(minSpace*info[4].length) << convert.str();
		convert.str("");

		cout << setw(minSpace*info[5].length) << a.getNXB() + " |";

		if (a.is_sell())	cout << setw(minSpace*info[6].length) << " On  |";
		else                cout << setw(minSpace*info[6].length) << " Off |";
		cout << endl << string(Width, '-') << endl;
	}
}