#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <memory>
#include <Windows.h>
using namespace std;

class Book
{
private:
	string name;
	string type;
	string author;
	int ID;
	double price;
	string NXB;
	bool OnSell; // true: có thể bán(mua) và false: ngược lại
public:
	void init(string _name, string _type, string _author, int _ID, double _price, string _NXB, bool check);
	string getName();
	string getType();
	string getAuthor();
	int getID();
	int getCheckSell();
	double getPrice();
	string getNXB();
	void input();
	void setID(int _ID);
	void setPrice(double _price);
	
	bool is_sell();
	void OnSellMode();
	void OffSellMode();
	Book();
	~Book();
};

