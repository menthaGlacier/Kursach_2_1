#pragma once

#include <iostream>
#include <string>

class Advert
{
private:
	bool buySell; /* Купля-продажа. Принимает false и true соответственно */
	std::string category; /* Рубрика */
	std::string adText; /* Текст объявления */
	int year, month, day; /* Дата подачи */
	long long int number; /* Контактный телефон */

	friend class Array; // Дружественный класс массива */
public:
	/* Конструкторы */
	Advert();
	Advert(bool bS, std::string cat, std::string ad,
		int y, int m, int d, long long int num);
	Advert(const Advert& advert);

	/* Установка значений */
	void setBuySell(bool bS);
	void setCategory(std::string cat);
	void setAdText(std::string ad);
	void setDate(int y, int m, int d);
	void setNumber(long long int num);

	/* Получение значений */
	bool getBuySell() const;
	std::string getCategory() const;
	std::string getAdText() const;
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	long long int getNumber() const;

	/* Вывод */
	void output() const;

	/* Оператор меньше и больше */
	bool operator<(const Advert& right) const;
	bool operator>(const Advert& right) const;
};