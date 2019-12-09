#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Admin.h"

class SystemLibrary
{
private:
	vector<Admin>lstAdmin;
	vector<Author> lstAuthor;
	vector<NXB>lstNXB;
	vector<Custom>lstCustom;
	vector<Book> lstBook;
	//shared_ptr <User> currentOnline;
	User* currentOnline;
public:
	static string convert_name_to_username(string name);

	void init_listbook();
	void init_list_admin();
	void init_list_custom();
	void init_list_NXB();
	void init_list_author();

	void add_list_NXB(Book& a);
	void add_list_author(Book& a);
	void add_detail(Book& a);

	void remove_detail(string nameBook);

	void add_author(string author);
	void add_NXB(string NXB);

	void remove_author(string author);	
	void remove_NXB(string NXB);


	void viewAllBook();
	void view_detail_authorBook(string author);
	void view_detail_NXBBook(string NXB);

	void view_all_Custom();
	void removeDetailCustom();

	void editPrice();

	bool login();
	void sign_up();
	void notification_type_login(); // thong bao quyen dang nhap: ADMIN, CUSTOM, AUTHOR, NXB

	void manageBookFollowAuthor();
	void manageBookFollowNXB();


	void allow_sell(string nameBook, bool check);
	void giftVoucher(string username);
	void chat();
	void notifate_to_all_custom();

	void ExportBilltoFile();
	void ExportListBooktoFile();
	void ExportListCustomtoFile();
	void ExportListAdmintoFile();
	void ExportAllMessage();

	void custom_loop();
	void admin_loop();
	void provider_loop();
	void main_loop();
	SystemLibrary();
	~SystemLibrary();
};

