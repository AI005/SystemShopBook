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
	void add_book_by_provider(); // thêm sách theo quyền của tác giả và NXB

	void remove_detail(string nameBook);
	void remove_detailBook_by_Provider(); // xóa sách theo quyền của tác giả & NXB
	void add_author(string author);
	void add_NXB(string NXB);

	void remove_author(string author);	
	void remove_NXB(string NXB);

	void editBookbyAdmin();    // sửa sách theo quyền của admin
	void editBookbyProvider(); // sửa sách theo quyền của tác giả & NXB

	void viewAllBook();         // Xem sách theo quyền của admin
	//void viewAllBookByCustom(); // xem sách theo quyền của khách hàng
	void view_detail_authorBook(string author); 
	void view_detail_NXBBook(string NXB);

	void view_all_Custom();
	void removeDetailCustom();

	void editPrice();

	bool login();
	void sign_up(); 
	void notification_type_login(); // thong bao quyen dang nhap: ADMIN, CUSTOM, AUTHOR, NXB

	void manageBookFollowAuthor(); //Quản lí sách theo tác giả (quyền của admin)
	void manageBookFollowNXB();    //Quản lí sách theo NXB     (quyền của admin)


	void allow_sell(string nameBook, bool check); // cho phép quyển sách có được bán không(quyền của NXB & tác giả)
	void giftVoucher(string username); // Tặng voucher khuyến mãi cho một khách hàng
	void chat();                  // currentOnline Chat với người khác
	void notifate_to_all_custom();// Admin đang online thông báo cho tất cả khách hàng

	void ExportBilltoFile();      // Xuất Hóa đơn ra file
	void ExportListBooktoFile();  // Xuất danh sách sách ra file
	void ExportListCustomtoFile();// Xuất danh sách thông tin khách hàng ra file
	void ExportListAdmintoFile(); // Xuât danh sách thông tin admin ra file
	void ExportListAuthortoFile();// Xuất danh sách tác giả ra file
	void ExportListNXBtoFile();   // Xuất danh sách NXB ra file
	void ExportAllMessage();      // Xuất tất cả tin nhắn ra file

	void custom_loop();           // Hệ thống của khách hàng
	void admin_loop();            // Hệ thống của admin
	void provider_loop();         // Hệ thống của tác giả & NXB
	void main_loop();             // Hệ thống chính
	SystemLibrary();
	~SystemLibrary();
};

