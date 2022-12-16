#include "Advert.h"

/* Конструктор по умолчанию */
Advert::Advert()
{
	buySell = false;
	year = 2000;
	month = 1;
	day = 1;
	number = 0;
}

/* Конструктор по параметрам */
Advert::Advert(bool bS, std::string cat, std::string ad,
	int y, int m, int d, long long int num)
{
	/* Установка значений через сеттеры для корректности значений */
	setBuySell(bS);
	setCategory(cat);
	setAdText(ad);
	setDate(y, m, d);
	setNumber(num);
}

/* Конструктор копирования */
Advert::Advert(const Advert& advert)
{
	/* Установка значений через сеттеры для корректности значений */
	setBuySell(advert.buySell);
	setCategory(advert.category);
	setAdText(advert.adText);
	setDate(advert.year, advert.month, advert.day);
	setNumber(advert.number);
}

/* Установка значения "купли-продажи" */
void Advert::setBuySell(bool bS)
{
	buySell = bS;
}

/* Установка значения рубрики */
void Advert::setCategory(std::string cat)
{
	category = cat;
}

/* Установка значения текста объявления */
void Advert::setAdText(std::string ad)
{
	adText = ad;
}

/* Установка значения даты подачи */
void Advert::setDate(int y, int m, int d)
{
	/* Год должен быть в пределах [2000, 2030] */
	if (year >= 2000 || year <= 2030)
		year = y;
	else
		year = 2000;

	/* Месяц должен быть в пределах [1, 12] */
	if (month >= 1 || month <= 12)
		month = m;
	else
		month = 1;

	/* День должен быть в пределах [1, 31] */
	if (day >= 1 || day <= 31)
		day = d;
	else
		day = 1;
}

/* Установка значения контактного номера */
void Advert::setNumber(long long int num)
{
	/* Если номер отрицательный, приводим его к положительному значению */
	if (num < 0)
		number = num * -1;
	else
		number = num;
}

/* Получения значения "купли-продажи" */
bool Advert::getBuySell() const
{
	return buySell;
}

/* Получения значения рубрики */
std::string Advert::getCategory() const
{
	return category;
}

/* Получения значения текста объявления */
std::string Advert::getAdText() const
{
	return adText;
}

/* Получение значения года подачи */
int Advert::getYear() const
{
	return year;
}

/* Получения значения месяц подачи */
int Advert::getMonth() const
{
	return month;
}

/* Получение значения дня подачи */
int Advert::getDay() const
{
	return day;
}

/* Получения значения контактного номера */
long long int Advert::getNumber() const
{
	return number;
}

/* Оператор меньше */
bool Advert::operator<(const Advert& advert) const
{
	if (year == advert.year)
	{
		if (month == advert.month)
			if (day < advert.day)
				return true;

		else if (month < advert.month)
			return true; 
	}

	else if (year < advert.year)
		return true;

	return false;
}

/* Оператор больше */
bool Advert::operator>(const Advert& advert) const
{
	if (year == advert.year)
	{
		if (month == advert.month)
			if (day > advert.day)
				return true;
		else if (month > advert.month)
			return true;
	}

	else if (year > advert.year)
		return true;

	return false;
}

/* Вывод объявления */
void Advert::output() const
{
	std::cout << "AD from " << year << "." << month << "." << day << std::endl
		<< "In category: " << category << std::endl
		<< "to " << (buySell ? "sell " : "buy ") << std::endl
		<< "Ad text: " << adText << std::endl
		<< "Contact: " << number << std::endl;
}