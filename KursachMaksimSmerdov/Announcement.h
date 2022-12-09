#pragma once
#include "dependencies.h"
using namespace std;
class Announcement// Класс "обьявление"
{
	friend class List;
public:
	static bool dateCheck(const string& date);

	Announcement();

	void setDate(unsigned short d, unsigned short m, unsigned short y);
	void setCategory(const string& c);
	void setBS(unsigned short bs);
	void setAdText(const string& text);
	void setNumber(unsigned long long num);

	void print();
private:
	static bool isDateCorrect(unsigned short d, unsigned short m, unsigned short y);
	static unsigned short getMaxDay(unsigned short m, unsigned short y);

	unsigned short day, month, year,
		buy_sell;
	unsigned long long number;
	string category, ad_text;
	Announcement* next;
};