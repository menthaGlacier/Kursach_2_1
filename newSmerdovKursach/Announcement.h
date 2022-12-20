#pragma once
#include "dependencies.h"
using namespace std;
class Announcement//  ласс "обь€вление"
{
	friend class List;	//даЄм доступ классу списка ко всем пол€м
public:
	static bool dateCheck(const string& date);	//метод проверки строки на возможность извлечени€ из неЄ даты
	static void inputAnnouncement(Announcement& elem);

	Announcement();	//конструктор

	//сеттеры полей
	void setDate(unsigned short d, unsigned short m, unsigned short y);
	void setCategory(const string& c);
	void setBS(unsigned short bs);
	void setAdText(const string& text);
	void setNumber(unsigned long long num);

	void print() const;	//вывод элемента
	bool fileSave(fstream& f);
	bool fileLoad(fstream& f);

	bool operator<(const Announcement& right) const;
	bool operator>(const Announcement& right) const;
private:
	//проверка даты на валидность
	static bool checkDate(unsigned short d, unsigned short m, unsigned short y);

	//получение максимального дн€ дл€ заданного мес€ца и года
	static unsigned short getMonthDayLimit(unsigned short m, unsigned short y);

	unsigned short day, month, year,	//дата
		buy_sell;	//категори€ (купл€/продажа)
	unsigned long long number;	//номер телефона
	string category, ad_text;	//название рубрики и текст объ€влени€
	long long int next;	//файловый указатель на следующее объ€вление
};