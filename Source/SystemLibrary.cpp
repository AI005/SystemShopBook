#include "SystemLibrary.h"

SystemLibrary::SystemLibrary()
{
	init_listbook();
	init_list_admin();
	init_list_custom();
	init_list_NXB();
	init_list_author();
}


SystemLibrary::~SystemLibrary()
{
}

string SystemLibrary::convert_name_to_username(string name)
{
	string a;
	for (auto letter : name) {
		if (letter != ' ') {
			a.push_back(letter);
		}
	}
	return a;
}

void SystemLibrary::init_list_NXB()
{
	fstream f_lstNXB;
	string name, username, password;
	f_lstNXB.open("login\\listNXB.txt", ios::in);
	int i = 0;
	NXB item;
	while (!f_lstNXB.eof()) {
		getline(f_lstNXB, name, ',');
		getline(f_lstNXB, username, ',');
		getline(f_lstNXB, password);
		if (name != "")
			item.init(name, username, password);
		lstNXB.push_back(item);
	}
	f_lstNXB.close();

	for (auto& a : lstBook) {
		add_list_NXB(a);
	}
}


void SystemLibrary::init_list_author()
{
	fstream f_lstAuthor;
	string name, username, password;
	f_lstAuthor.open("login\\listAuthor.txt", ios::in);
	int i = 0;
	Author item;
	while (!f_lstAuthor.eof()) {
		getline(f_lstAuthor, name, ',');
		getline(f_lstAuthor, username, ',');
		getline(f_lstAuthor, password);
		if (name != "")
			item.init(name, username, password);
		lstAuthor.push_back(item);
	}
	f_lstAuthor.close();

	for (auto& a : lstBook) {
		add_list_author(a);
	}
}

void SystemLibrary::init_list_admin()
{
	fstream f_lstAdmin;
	string name, username, password;
	f_lstAdmin.open("login\\listAdmin.txt", ios::in);
	lstAdmin.resize(2);
	int i = 0;
	while (!f_lstAdmin.eof()) {
		getline(f_lstAdmin, name, ',');
		getline(f_lstAdmin, username, ',');
		getline(f_lstAdmin, password);
		if(name != "")
		    lstAdmin[i++].Custom::init(name, username, password);
	}
	f_lstAdmin.close();
}

void SystemLibrary::init_list_custom()
{
	string name, username, password;
	const int MAXLENGTH = 100;
	fstream f_lstUser;
	f_lstUser.open("login\\listUser.txt", ios::in);
	char c;
	Custom item;
	while (!f_lstUser.eof())
	{
		getline(f_lstUser, name, ',');
		getline(f_lstUser, username, ',');
		getline(f_lstUser, password);
		item.User::init(name, username, password);
		lstCustom.push_back(item);
	}
	f_lstUser.close();
}

void SystemLibrary::init_listbook()
{
	string name, type, author, price, NXB;
	int check;

	fstream f_lstBook("listBook.txt", ios::in);
	int i = 1;
	char c;
	Book item;
	while (!f_lstBook.eof()) {
		getline(f_lstBook, name, ',');
		if (name == "")
			break;
		getline(f_lstBook, type, ',');
		getline(f_lstBook, author, ',');
		getline(f_lstBook, price, ',');
		getline(f_lstBook, NXB, ',');
		f_lstBook >> check;
		c = f_lstBook.get();
		item.init(name, type, author, i++, (double)stof(price), NXB, check);
		lstBook.push_back(item);
	}
}

void SystemLibrary::add_list_NXB(Book& a)
{
	int Flag = -1;
	for (int i = 0; i < lstNXB.size(); ++i) {
		if (a.getNXB() == lstNXB[i].getName()) {
			Flag = i;
			break;
		}
	}
	if (Flag == -1) {
		lstNXB.resize(lstNXB.size() + 1);
		lstNXB.back().setName(a.getNXB());
		lstNXB.back().add_detail(a);
	}
	else {
		lstNXB[Flag].add_detail(a);
	}
}

void SystemLibrary::add_list_author(Book& a)
{
	int Flag = -1;
	for (int i = 0; i < lstAuthor.size(); ++i) {
		if (a.getAuthor() == lstAuthor[i].getName()) {
			Flag = i;
			break;
		}
	}
	if (Flag == -1) {
		lstAuthor.resize(lstAuthor.size() + 1);
		lstAuthor.back().setName(a.getAuthor());
		lstAuthor.back().add_detail(a);
	}
	else {
		lstAuthor[Flag].add_detail(a);
	}
}


void SystemLibrary::add_detail(Book& a)
{
	fstream f_lstBook("listBook.txt", ios::out);
	f_lstBook << endl << a.getName() << ',' << a.getType() << ',' << a.getAuthor() << ',' << a.getPrice() << ',' << a.getNXB();
	f_lstBook.close();

	lstBook.push_back(a);
	add_list_author(a);
	add_list_NXB(a);
}

void SystemLibrary::add_book_by_provider()
{
	Book newBook;
	newBook.input();
	newBook.setID(lstBook.size() + 1);
	if ((currentOnline->getType() == PUBLISHING && currentOnline->getName() == newBook.getNXB())
		|| 
		(currentOnline->getType() == AUTHOR && currentOnline->getName() == newBook.getAuthor()))
	{
		add_detail(newBook);
	}
	else
	{
		if (currentOnline->getType() == PUBLISHING)    cout << "\nWrong NXB";
		else                                           cout << "\nWrong Author";
	}
}

void SystemLibrary::remove_detail(string nameBook)
{
	for (auto&a : lstAuthor) {
		if (a.remove_detail(nameBook))
			break;
	}

	for (auto&a : lstNXB) {
		if (a.remove_detail(nameBook))
			break;
	}

	for (int i = 0; i < lstBook.size(); ++i) {
		if (lstBook[i].getName() == nameBook) {
			lstBook.erase(lstBook.begin() + i);
			break;
		}
	}
}

void SystemLibrary::remove_detailBook_by_Provider()
{
	Book *item = NULL;
	string namebook;
	cin.ignore(256, '\n');    cout << "\nname's book: ";    getline(cin, namebook);
	for (auto& a : lstBook) {
		if (a.getName() == namebook) {
			item = &a;
			break;
		}
	}
	if (item == NULL) {
		cout << "\nthis book is not exist on list";
	}
	else
	{
		remove_detail(namebook);
	}
}


void SystemLibrary::add_author(string author)
{
	for (auto a : lstAuthor) {
		if (a.getName() == author)
		{
			cout << "author has exist";
			return;
		}
	}
	lstAuthor.resize(lstAuthor.size() + 1);
	lstAuthor.back().setName(author);
}

void SystemLibrary::add_NXB(string NXB)
{
	for (auto a : lstNXB) {
		if (a.getName() == NXB)
		{
			cout << "NXB has exist";
			return;
		}
	}
	lstNXB.resize(lstNXB.size() + 1);
	lstNXB.back().setName(NXB);
}

void SystemLibrary::remove_author(string author)
{
	for (int i = 0; i < lstBook.size(); ++i) {
		if (lstBook[i].getAuthor() == author) {
			remove_detail(lstBook[i].getName());
			i--;
		}
	}
	for (int i = 0; i < lstAuthor.size(); ++i) {
		if (lstAuthor[i].getName() == author) {
			lstAuthor.erase(lstAuthor.begin() + i);
			break;
		}
	}
	for (int i = 0; i < lstBook.size(); ++i) {
		lstBook[i].setID(i + 1);
	}
	init_list_author();
	init_list_NXB();
}

void SystemLibrary::remove_NXB(string NXB)
{
	for (int i = 0; i < lstBook.size(); ++i) {
		if (lstBook[i].getNXB() == NXB) {
			remove_detail(lstBook[i].getName());
			i--;
		}
	}
	for (int i = 0; i < lstNXB.size(); ++i) {
		if (lstNXB[i].getName() == NXB) {
			lstNXB.erase(lstNXB.begin() + i);
			break;
		}
	}
	for (int i = 0; i < lstBook.size(); ++i) {
		lstBook[i].setID(i + 1);
	}
	init_list_author();
	init_list_NXB();
}

void SystemLibrary::editBookbyAdmin()
{
	string namebook;
	cin.ignore(256, '\n');    cout << "\nName book: ";    getline(cin, namebook);
	int pos;
	for (pos = 0; pos < lstBook.size(); pos++)
	{
		if (lstBook[pos].getName() == namebook) {
			break;
		}
		pos++;
	}
	if (pos == lstBook.size())    cout << "\nthisbook is not exist";
	else {
		lstBook[pos].editBook();
	}
}

void SystemLibrary::editBookbyProvider()
{
	string namebook;
	cin.ignore(256, '\n');    cout << "\nName book: ";    getline(cin, namebook);
	try {
		Book item = currentOnline->editBook(namebook);
		int pos;
		for (pos = 0; pos < lstBook.size(); pos++)
		{
			if (lstBook[pos].getName() == namebook) {
				break;
			}
			pos++;
		}
		lstBook[pos] = item;
	}
	catch(string error) {
		cout << error;
	}
}


void SystemLibrary::viewAllBook()
{
	struct INFORMATION
	{
		string name;
		int length;
	};
	vector<INFORMATION>info{ {"Name", 5}, {"Type", 3}, {"Author", 4}, {"ID", 1}, {"Price", 2}, {"NXB", 3}, {"Sell", 1} };
	int n = info.size();
	int minSpace = 5;
	int Width = 0;
	for (auto a : info) { Width += a.length; }
	Width = Width * minSpace + 2;

	cout << string(Width, '_') << endl;
	cout << "|";
	for (auto a : info) {
		cout << setw(minSpace * a.length) << a.name + " |";
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

//void SystemLibrary::viewAllBookByCustom()
//{
//	struct INFORMATION
//	{
//		string name;
//		int length;
//	};
//	vector<INFORMATION>info{ {"Name", 5}, {"Type", 3}, {"Author", 4}, {"ID", 1}, {"Price", 2}, {"NXB", 3}};
//	int n = info.size();
//	int minSpace = 5;
//	int Width = 0;
//	for (auto a : info) { Width += a.length; }
//	Width = Width * minSpace + 2;
//
//	cout << string(Width, '_') << endl;
//	cout << "|";
//	for (auto a : info) {
//		cout << setw(minSpace * a.length) << a.name + " |";
//	}
//	cout << endl << string(Width, '-') << endl;
//
//	ostringstream convert;
//	for (auto a : lstBook) {
//		if (a.getCheckSell() == true) {
//			cout << "|";
//			cout << setw(minSpace * info[0].length) << a.getName() + " |";
//			cout << setw(minSpace * info[1].length) << a.getType() + " |";
//			cout << setw(minSpace * info[2].length) << a.getAuthor() + " |";
//
//			convert << a.getID() << " |";
//			cout << setw(minSpace * info[3].length) << convert.str();
//			convert.str("");
//
//			convert << a.getPrice() << " |";
//			cout << setw(minSpace * info[4].length) << convert.str();
//			convert.str("");
//
//			cout << setw(minSpace * info[5].length) << a.getNXB() + " |";
//			cout << endl << string(Width, '-') << endl;
//		}
//	}
//}

void SystemLibrary::view_detail_authorBook(string author)
{
	int pos = -1;
	for (int i = 0; i < lstAuthor.size(); ++i) {
		if (lstAuthor[i].getName() == author) {
			pos = i;
			break;
		}
	}
	if (pos == -1) {
		cout << "this Author no exist in list";
	}
	else {
		lstAuthor[pos].view_lstBook();
	}
}

void SystemLibrary::view_detail_NXBBook(string NXB)
{
	int pos = -1;
	for (int i = 0; i < lstNXB.size(); ++i) {
		if (lstNXB[i].getName() == NXB) {
			pos = i;
			break;
		}
	}
	if (pos == -1) {
		cout << "this NXB no exist in list";
	}
	else {
		lstNXB[pos].view_lstBook();
	}
}

void SystemLibrary::ExportBilltoFile()
{
	fstream fileBill;
	fileBill.open("bill.txt", ios::app);

	time_t currentTime = time(0);
	fileBill << "\n\n-----" << ctime(&currentTime) << "-----\n";
	for (auto &a : lstCustom) {
		if (a.Bill.size() != 0) {
			fileBill << endl << a.getName() << ", username: " << a.getUsername() << endl;
			for (auto x : a.Bill) {
				fileBill
					<< x.book.getName() << "\t|Price:" << x.book.getPrice() << "\t|Amount: " << x.amount << "\t|Money: "
					<< x.amount * x.book.getPrice() << endl;
			}
			fileBill <<"Sale" <<a.getVoucher() * 100 << "%, " <<"TOTAL: " << a.getMoney() << endl;
		}
	}
	fileBill.close();
}

void SystemLibrary::ExportListBooktoFile()
{
	fstream f_lstBook;
	f_lstBook.open("listBook.txt", ios::trunc | ios::out);
	for (int i = 0; i < lstBook.size(); ++i) {
		f_lstBook << lstBook[i].getName() << ',';
		f_lstBook << lstBook[i].getType() << ',';
		f_lstBook << lstBook[i].getAuthor() << ',';
		f_lstBook << lstBook[i].getPrice() << ',';
		f_lstBook << lstBook[i].getNXB() << ',';
		f_lstBook << (int)lstBook[i].getCheckSell();
		if(i <= lstBook.size() - 1)    f_lstBook << endl;
	}
	f_lstBook.close();
}

void SystemLibrary::ExportListCustomtoFile()
{
	fstream f_lstCustom;
	f_lstCustom.open("login\\listUser.txt", ios::trunc | ios::out);
	for (int i = 0; i < lstCustom.size(); ++i) {
		f_lstCustom << lstCustom[i].getName() << ',';
		f_lstCustom << lstCustom[i].getUsername() << ',';
		f_lstCustom << lstCustom[i].getPassword();
		if (i < lstCustom.size() - 1) f_lstCustom << endl;
	}
	f_lstCustom.close();
}

void  SystemLibrary::ExportListAdmintoFile()
{
	fstream f_lstAdmin;
	f_lstAdmin.open("login\\listAdmin.txt", ios::trunc | ios::out);
	for (int i = 0; i < lstAdmin.size(); i++) {
		f_lstAdmin << lstAdmin[i].getName() << ',';
		f_lstAdmin << lstAdmin[i].getUsername() << ',';
		f_lstAdmin << lstAdmin[i].getPassword();
		if (i < lstAdmin.size() - 1) f_lstAdmin << endl;
	}
	f_lstAdmin.close();
}	

void SystemLibrary::ExportListAuthortoFile()
{
	fstream f_lstAuthor;
	f_lstAuthor.open("login\\listAuthor.txt", ios::trunc | ios::out);
	for (int i = 0; i < lstAuthor.size(); i++) {
		f_lstAuthor << lstAuthor[i].getName() << ',';
		f_lstAuthor << lstAuthor[i].getUsername() << ',';
		f_lstAuthor << lstAuthor[i].getPassword();
		if (i < lstAuthor.size() - 1) f_lstAuthor << endl;
	}
	f_lstAuthor.close();
}

void SystemLibrary::ExportListNXBtoFile()
{
	fstream f_lstNXB;
	f_lstNXB.open("login\\listNXB.txt", ios::trunc | ios::out);
	for (int i = 0; i < lstNXB.size(); i++) {
		f_lstNXB << lstNXB[i].getName() << ',';
		f_lstNXB << lstNXB[i].getUsername() << ',';
		f_lstNXB << lstNXB[i].getPassword();
		if (i < lstNXB.size() - 1) f_lstNXB << endl;
	}
	f_lstNXB.close();
}

void SystemLibrary::ExportAllMessage()
{
	for (auto &a : lstCustom) {
		fstream f_r, f_s;
		f_r.open(a.message.filename_r, ios::trunc | ios::out);
		f_s.open(a.message.filename_s, ios::trunc | ios::out);
		for (auto &stc : a.message.receive)
			f_r << stc << endl;
		for (auto &stc : a.message.send)
			f_s << stc << endl;
		f_s.close();
		f_r.close();
	}

	for (auto &a : lstAdmin) {
		fstream f_r, f_s;
		f_r.open(a.message.filename_r, ios::trunc | ios::out);
		f_s.open(a.message.filename_s, ios::trunc | ios::out);
		for (auto &stc : a.message.receive)
			f_r << stc << endl;
		for (auto &stc : a.message.send)
			f_s << stc << endl;
		f_s.close();
		f_r.close();
	}

	for (auto &a : lstAuthor) {
		fstream f_r, f_s;
		f_r.open(a.message.filename_r, ios::trunc | ios::out);
		f_s.open(a.message.filename_s, ios::trunc | ios::out);
		for (auto &stc : a.message.receive)
			f_r << stc << endl;
		for (auto &stc : a.message.send)
			f_s << stc << endl;
		f_s.close();
		f_r.close();
	}

	for (auto &a : lstNXB) {
		fstream f_r, f_s;
		f_r.open(a.message.filename_r, ios::trunc | ios::out);
		f_s.open(a.message.filename_s, ios::trunc | ios::out);
		for (auto &stc : a.message.receive)
			f_r << stc << endl;
		for (auto &stc : a.message.send)
			f_s << stc << endl;
		f_s.close();
		f_r.close();
	}
}
void SystemLibrary::view_all_Custom()
{
	for (auto a : lstCustom) {
		cout << "\n\n\nName: " << a.getName();
		cout << "\nUsername: " << a.getUsername();
		cout << "\nPassword: " << a.getPassword() << endl;
		a.viewBill();
	}
}

void SystemLibrary::removeDetailCustom()
{
	int pos;
	for (int i = 0; i < lstCustom.size(); ++i) {
		cout << i << ". " << lstCustom[i].getUsername() << endl;
	}
	cout << "\n\nInpute the positive'User to remove: ";
	cin >> pos;
	if (pos >= 0 && pos < lstCustom.size()) {
		lstCustom.erase(lstCustom.begin() + pos);
	}
	else {
		cout << "\nERROR POSITIVE";
	}
}

void SystemLibrary::editPrice()
{
	string namebook;
	cout << "Name's Book that you wanna edit price: ";
	cin.ignore(256, '\n');	getline(cin, namebook);

	int Flag = 0;
	double newPrice;
	Book item;
	for (auto& a : lstBook) {
		if (a.getName() == namebook) {
			cout << "\nOld Price: " << a.getPrice();
			cout << "\nNew Price: ";	cin >> newPrice;
			a.setPrice(newPrice);
			Flag = 1;
			item = a;
			break;
		}
	}
}

bool SystemLibrary::login()
{
	string username, password;
	cin.ignore(256, '\n');
	cout << "\nusername: "; getline(cin, username);
	cout << "password: ";
	char c;
	do {
		c = _getch();
		if (c == 13)
			break;
		if (c == 8 && !password.empty()) {
			password.pop_back();
			cout << "\b \b";
		}
		else if (c != 8) {
			cout << '*';
			password.push_back(c);
		}
	} while (true);

	for (auto& a: lstCustom)
		if (a.getUsername() == username && a.getPassword() == password) {
			currentOnline = &a;
			return true;
		}

	for (auto &a : lstAdmin)
		if (a.Custom::getUsername() == username && a.Custom::getPassword() == password) {
			currentOnline = &a;
			return true;
		}

	for (auto& a : lstAuthor)
		if (a.getUsername() == username && a.getPassword() == password) {
			currentOnline = &a;
			return true;
		}

	for (auto& a : lstNXB)
		if (a.getUsername() == username && a.getPassword() == password) {
			currentOnline = &a;
			return true;
		}

	return false;
}

void SystemLibrary::sign_up()
{
	string name, username, password;
	cin.ignore(256, '\n');
	cout << "name: ";		getline(cin, name);
	cout << "username: ";	getline(cin, username);
	cout << "password: ";	getline(cin, password);

	for (auto &a : lstCustom) {
		if (a.getUsername() == username) {
			cout << "username has exist";
			return;
		}
	}

	for (auto &a : lstAuthor) {
		if (a.getUsername() == username) {
			cout << "username has exist";
			return;
		}
	}

	for (auto &a : lstNXB) {
		if (a.getUsername() == username) {
			cout << "username has exist";
			return;
		}
	}

	for (auto &a : lstAdmin) {
		if (a.NXB::getUsername() == username) {
			cout << "username has exist";
			return;
		}
	}

	lstCustom.push_back(Custom(name, username, password, CUSTOM));
}


void SystemLibrary::notification_type_login()
{
	switch (currentOnline->getType())
	{
	case CUSTOM:
		cout << "\nHELLO CUSTOM\n";
		cout << currentOnline->getName();
		break;
	case AUTHOR:
		cout << "\nHELLO AUTHOR\n";
		currentOnline->getName();
		break;
	case PUBLISHING:
		cout << "\nHELLO NXB\n";
		currentOnline->getName();
		break;
	case ADMIN:
		cout << "\nHELLO ADMIN\n";
		currentOnline->getName();
		break;
	default:
		break;
	}
	Sleep(1000);
}


void SystemLibrary::manageBookFollowAuthor()
{
	int select;
	string nameAuthor;
	int pos;
	do
	{
		system("cls");
		cout << "---list Author---";
		for (int i = 0; i < lstAuthor.size(); ++i) {
			cout << endl << i << ". " << lstAuthor[i].getName();
		}
		cout << "\n----------------------" << endl;
		cout
			<< "\n1. Add author"
			<< "\n2. Remove author"
			<< "\n3. view detail author"
			<< "\n0. exit"
			<< "\nSelect: ";
		cin >> select;

		switch (select)
		{
		case 0:
			return;

		case 1:
			cin.ignore(256, '\n');
			cout << "new name author: ";
			getline(cin, nameAuthor);
			add_author(nameAuthor);
			break;

		case 2:
			cin.ignore(256, '\n');
			cout << "name author: ";
			getline(cin, nameAuthor);
			remove_author(nameAuthor);
			break;

		case 3:
			cout << "input positive of list: ";
			cin >> pos;
			if (pos >= 0 && pos < lstAuthor.size()) {
				lstAuthor[pos].view_lstBook();
			}
			else {
				cout << "error pos";
			}
			break;

		default:
			break;
		}
		cout << endl;	system("pause");
	} while (true);
}

void SystemLibrary::manageBookFollowNXB()
{
	int select;
	string nameNXB;
	int pos;
	do
	{
		system("cls");
		cout << "---list NXB---";
		for (int i = 0; i < lstNXB.size(); ++i) {
			cout << endl << i << ". " << lstNXB[i].getName();
		}
		cout << "\n----------------------" << endl;
		cout
			<< "\n1. Add NXB"
			<< "\n2. Remove NXB"
			<< "\n3. view detail NXB"
			<< "\n0. exit"
			<< "\nSelect: ";
		cin >> select;

		switch (select)
		{
		case 0:
			return;

		case 1:
			cin.ignore(256, '\n');
			cout << "new name NXB: ";
			getline(cin, nameNXB);
			add_NXB(nameNXB);
			break;

		case 2:
			cin.ignore(256, '\n');
			cout << "name NXB: ";
			getline(cin, nameNXB);
			remove_NXB(nameNXB);
			break;

		case 3:
			cout << "input positive of list: ";
			cin >> pos;
			if (pos >= 0 && pos < lstNXB.size()) {
				lstNXB[pos].view_lstBook();
			}
			else {
				cout << "error pos";
			}
			break;

		default:
			break;
		}
		cout << endl;	system("pause");
	} while (true);
}


void SystemLibrary::allow_sell(string nameBook, bool check)
{
	for (auto& a : lstBook) {
		if (a.getName() == nameBook)
		{
			if (check == true) a.OnSellMode();
			else               a.OffSellMode();
		}
	}
}

void SystemLibrary::giftVoucher(string username)
{
	double voucher;
	bool Flag = false;
	for (auto& a : lstCustom) {
		if (a.getUsername() == username) {
			cout << "\nSale(80%: 0.8): ";    cin >> voucher;
			a.setVouder(voucher);
			Flag = true;
			return;
		}
	}
	if (Flag == false) {
		cout << "\nusername is not exist";
	}
}

void SystemLibrary::notifate_to_all_custom()
{
	string text;
	cin.ignore(256, '\n');    cout << "content: ";       getline(cin, text);

	for (auto& a : lstCustom) {
			currentOnline->Send(&a, text);
	}

	for (auto& a : lstAuthor) {
			currentOnline->Send(&a, text);
	}

	for (auto& a : lstNXB) {
			currentOnline->Send(&a, text);
	}
}

void SystemLibrary::chat()
{
	string username;
	cin.ignore(256, '\n');
	cout << "\nUsername: ";    getline(cin, username);
	string text;
	cout << "content: ";       getline(cin, text);

	for (auto& a : lstCustom) {
		if (a.getUsername() == username) {
			currentOnline->Send(&a, text);
			return;
		}
	}


	for (auto& a : lstAdmin) {
		if (a.getUsername() == username) {
			currentOnline->Send(&a, text);
			return;
		}
	}


	for (auto& a : lstNXB) {
		if (a.getUsername() == username) {
			currentOnline->Send(&a, text);
			return;
		}
	}


	for (auto& a : lstAuthor) {
		if (a.getUsername() == username) {
			currentOnline->Send(&a, text);
			return;
		}
	}

	cout << "\nthis username is not exist";
}

void SystemLibrary::custom_loop()
{
	int select;
	string newPassword;
	do
	{
		system("cls");
		cout
			<< "\n1. View all Book"
			<< "\n2. Buy book"
			<< "\n3. View Bill"
			<< "\n4. Edit Bill"
			<< "\n5. Change password"
			<< "\n6. Voucher"
			<< "\n7. Logout"
			<< "\n8. View message received"
			<< "\n9. View message sended"
			<< "\n10. Send message"
			<< "\n0. Exit"
			<< "\nSelect: ";    cin >> select;
		switch (select) {
		case 0:
		case 7:
			currentOnline = NULL;
			return;
		case 1:
			system("cls");
			currentOnline->view_list_book(lstBook);
			break;
		case 2:
			currentOnline->buy(lstBook);
			break;
		case 3:
			cout << currentOnline->getUsername() << endl;
			currentOnline->viewBill();
			break;
		case 4:
			currentOnline->edit_Bill();
			break;
		case 5:
			cin.ignore(256, '\n');
			cout << "new Password: ";    getline(cin, newPassword);
			currentOnline->changePassword(newPassword);
			break;
		case 6:
			cout << "Voucher: " << currentOnline->getVoucher() * 100 << "%";
			break;
		case 8:
			currentOnline->ViewHistoryReceiveMes();
			break;
		case 9:
			currentOnline->ViewHistorySendMes();
			break;
		case 10:
			chat();
			break;
		default:
			break;
		}
		cout << endl;    system("pause");
	} while (true);
}

void SystemLibrary::admin_loop()
{
	int select;
	string newPassword, nameBook, nameUser;
	Book newBook;
	do
	{
		system("cls");
		cout
			<< "\n1. View all list book"
			<< "\n2. manage book follow author"
			<< "\n3. manage book follow NXB"
			<< "\n4. View all custom"
			<< "\n5. Add detail book"
			<< "\n6. Remove detail book"
			<< "\n7. Remove a Custom"
			<< "\n8. Edit Book"
			<< "\n9. Change Password"
			<< "\n10. Gift voucher for custom"
			<< "\n11. View message received"
			<< "\n12. View message sended"
			<< "\n13. Send message"
			<< "\n14. Send notifation to all custom"
			<< "\n0. EXIT"
			<< "\nSelect: ";    cin >> select;
		switch (select) {
		case 0:
			currentOnline = NULL;
			return;
		case 1:
			system("cls");
			viewAllBook();
			break;
		case 2:
			manageBookFollowAuthor();
			break;
		case 3:
			manageBookFollowNXB();
			break;
		case 4:
			view_all_Custom();
			break;
		case 5:
			newBook.input();
			newBook.setID(lstBook.size() + 1);
			add_detail(newBook);
			break;
			break;
		case 6:
			cin.ignore(256, '\n');
			cout << "enter name book: ";	getline(cin, nameBook);
			remove_detail(nameBook);
			break;
		case 7:
			system("cls");
			removeDetailCustom();
			break;
		case 8:
			system("cls");
			viewAllBook();
			editBookbyAdmin();
			break;
		case 9:
			cin.ignore(256, '\n');
			cout << "\nNew password: ";    getline(cin, newPassword);
			currentOnline->changePassword(newPassword);
			break;
		case 10:
			cin.ignore(256, '\n');
			cout << "\nusername: ";    getline(cin, nameUser);
			giftVoucher(nameUser);
			break;
		case 11:
			currentOnline->ViewHistoryReceiveMes();
			break;
		case 12:
			currentOnline->ViewHistorySendMes();
			break;
		case 13:
			chat();
			break;
		case 14:
			notifate_to_all_custom();
			break;
		default:
			break;
		}
		cout << endl;    system("pause");
	} while (true);
}

void SystemLibrary::provider_loop()
{
	int select;
	string namebook, newPassword;
	bool check;

	do
	{
		system("cls");
		cout
			<< "\n1. View list book"
			<< "\n2. allow to sell book"
			<< "\n3. change password"
			<< "\n4. View message received"
			<< "\n5. View message sended"
			<< "\n6. Send message"
			<< "\n7. Edit book"
			<< "\n8. Remove a book"
			<< "\n9. Add a book"
			<< "\n0. Exit"
			<< "\nSelect: ";    cin >> select;
		switch (select) {
		case 1:
			system("cls");
			currentOnline->view_lstBook();
			break;
		case 2:
			cin.ignore(256, '\n');
			cout << "\nnamebook: ";    getline(cin, namebook);
			cout
				<< "\nAllow sell"
				<< "\n1. Yes"
				<< "\nAny. No"
				<< "\nSelect: ";    cin >> select;
			if (select == 1)    check = true;
			else                check = false;
			if (currentOnline->allow_sell(namebook, check))
				allow_sell(namebook, check);
			else
				cout << "\mthis book is not on list";
			break;
		case 3:
			cin.ignore(256, '\n');
			cout << "\nNew password: ";    getline(cin, newPassword);
			currentOnline->changePassword(newPassword);
			break;
		case 4:
			currentOnline->ViewHistoryReceiveMes();
			break;
		case 5:
			currentOnline->ViewHistorySendMes();
			break;
		case 6:
			chat();
			break;
		case 7:
			editBookbyProvider();
			break;
		case 8:
			remove_detailBook_by_Provider();
			break;
		case 9:
			add_book_by_provider();
			break;
		case 0:
			currentOnline = NULL;
			return;
		default:
			break;
		}
		cout << endl;    system("pause");
	} while (true);
}

void SystemLibrary::main_loop()
{
	int select;
	do
	{
		system("cls");
		cout
			<< "\n1. LOGIN"
			<< "\n2. SIGN-UP"
			<< "\n0. EXIT"
			<< "\nSelect: ";    cin >> select;
		if (select == 0)
		{
			ExportBilltoFile();
			ExportListBooktoFile();
			ExportListCustomtoFile();
			ExportListAdmintoFile();
			ExportListAuthortoFile();
			ExportListNXBtoFile();
			ExportAllMessage();
			return;
		}
		else if (select == 1)
		{
			if (login() == false) {
				cout << "\n Wrong Account";
			}
			else {
				notification_type_login();
				switch (SystemLibrary::currentOnline->getType())
				{
				case CUSTOM:
					custom_loop();
					break;
				case ADMIN:
					admin_loop();
					break;

				case AUTHOR:
				case PUBLISHING:
					provider_loop();
					break;

				default:
					break;
				}
			}
		}
		else if (select == 2)
		{
			sign_up();
		}
		cout << endl;    system("pause");
	} while (true);
}