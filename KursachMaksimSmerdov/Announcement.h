#pragma once
#include "dependencies.h"
using namespace std;
class Announcement//  ласс "обь€вление"
{
	friend class List;	//даЄм доступ классу списка ко всем пол€м
public:
	static bool dateCheck(const string& date);	//метод проверки строки на возможность извлечени€ из неЄ даты

	Announcement();	//конструктор

	//сеттеры полей
	void setDate(unsigned short d, unsigned short m, unsigned short y);
	void setCategory(const string& c);
	void setBS(unsigned short bs);
	void setAdText(const string& text);
	void setNumber(unsigned long long num);

	void print();	//вывод элемента
private:
	//проверка даты на валидность
	static bool isDateCorrect(unsigned short d, unsigned short m, unsigned short y);

	//получение максимального дн€ дл€ заданного мес€ца и года
	static unsigned short getMaxDay(unsigned short m, unsigned short y);

	unsigned short day, month, year,	//дата
		buy_sell;	//категори€ (купл€/продажа)
	unsigned long long number;	//номер телефона
	string category, ad_text;	//название рубрики и текст объ€влени€
	Announcement* next;	//указатель на следующее объ€вление
};