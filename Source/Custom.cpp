#include "Custom.h"
Custom::Custom(string _name, string _username, string _password, TYPEUSER _type = CUSTOM) 
	:User(_name, _username, _password, _type)
{
	percent = 0;
}

Custom::Custom()
{
	type = CUSTOM;
	percent = 0;
}


Custom::~Custom()
{
}

int Custom::findBook(string nameBook, vector<Book>lstBook)
{
	int pos = -1;
	for (int i = 0; i < lstBook.size(); ++i) {
		if (lstBook[i].getName() == nameBook) {
			pos = i;
			break;
		}
	}
	return pos;
}

void Custom::buy(vector<Book>lstBook)
{
	int select;
	string nameBook;
BUY:
	cout << "\nenter name's book that you wanna buy: ";
	cin.ignore(256, '\n');	getline(cin, nameBook);

	int _amount;	cout << "amount: ";    cin >> _amount;
	int pos = findBook(nameBook, lstBook);
	if (pos == -1)	cout << "\nthis book is not on list\n\n";
	else if (!lstBook[pos].is_sell()) cout << "\nthis book is not sell\n\n";
	else{
		int Flag = false;
		for (auto &a : Bill) {
			if (a.book.getName() == nameBook && a.book.is_sell()) {
				Flag = true;
				a.amount += _amount;
				break;
			}
		}
		if (!Flag) {
			Post item{ lstBook[pos], _amount };
			Bill.push_back(item);
		}
		cout << "\nalready bought";
	}

	cout
		<< "\nDo you wanna buy more"
		<< "\n1. Yes"
		<< "\n2. No"
		<< "\nSelect: ";	cin >> select;
	switch (select)
	{
	case 1:
		goto BUY;
		break;
	default:
		break;
	}
}

void Custom::edit_Bill()
{
	do {
		system("cls");
		viewBill();
		string nameBook;
		int amount;

		cin.ignore(256, '\n');
		cout << "\nenter name's book that you wanna edit bill: ";
		getline(cin, nameBook);

		int Flag = -1;
		for (int i = 0; i < Bill.size(); i++) {
			if (Bill[i].book.getName() == nameBook) {
				Flag = i;
				break;
			}
		}

		if (Flag == -1) {
			cout << "\nthis book is no-exist on your bill";
		}
		else {
			cout << "new amount (0 == delete) : ";	cin >> amount;
			Bill[Flag].amount = amount;
		}

		cout
			<< "\nDo you wanna continue to edit"
			<< "\n1. Yes"
			<< "\n2. No"
			<< "\nSelect: ";
		int select;    cin >> select;
		switch (select)
		{
		case 1:
			break;
		case 2:
			for (int i = 0; i < Bill.size(); i++) {
				if (Bill[i].amount == 0) {
					Bill.erase(Bill.begin() + i);
					i--;
				}
			}
			return;
		default:
			break;
		}
	} while (true);
}

double Custom::getMoney()
{
	double total = 0;
	for (auto a : Bill) {
		total += a.book.getPrice()*a.amount;
	}
	return total * percent;
}

double Custom::getVoucher()
{
	return percent;
}

void Custom::viewBill()
{
	vector<string>info{ "Name", "Price", "Amount", "Money" };
	int n = info.size();
	int maxSpace = 18;

	cout << string(n*maxSpace, '_') << endl;
	cout << "|";
	for (auto a : info) {
		cout << setw(maxSpace) << a + " |";
	}
	cout << endl << string(n*maxSpace, '-') << endl;

	ostringstream convert;
	for (auto a : Bill) {
		cout << "|";
		cout << setw(maxSpace) << a.book.getName() + " |";

		convert << a.book.getPrice() << " |";
		cout << setw(maxSpace) << convert.str();	convert.str(""); // clear convert

		convert << a.amount << " |";
		cout << setw(maxSpace) << convert.str();	convert.str("");

		convert << a.amount*a.book.getPrice() << " |";
		cout << setw(maxSpace) << convert.str();	convert.str("");

		cout << endl << string(n*maxSpace, '-') << endl;
	}
	convert << "Sale: " << percent * 100 << "%";
	cout << string((n - 2)*maxSpace, ' ') << setw(maxSpace) << convert.str()
		<< setw(maxSpace - 1) << getMoney();
}


void Custom::setVouder(double percent)
{
	this->percent = percent;
}