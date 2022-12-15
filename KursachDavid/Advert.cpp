#include "Advert.h"

/* */
Advert::Advert()
{
	buySell = false;
	year = 2000;
	month = 1;
	day = 1;
	number = 0;
}

/* */
Advert::Advert(bool bS, std::string cat, std::string ad,
	int y, int m, int d, long long int num)
{
	setBuySell(bS);
	setCategory(cat);
	setAdText(ad);
	setDate(y, m, d);
	setNumber(num);
}

/* */
Advert::Advert(const Advert& advert)
{
	setBuySell(advert.buySell);
	setCategory(advert.category);
	setAdText(advert.adText);
	setDate(advert.year, advert.month, advert.day);
	setNumber(advert.number);
}

/* */
void Advert::setBuySell(bool bS)
{
	buySell = bS;
}

/* */
void Advert::setCategory(std::string cat)
{
	category = cat;
}

/* */
void Advert::setAdText(std::string ad)
{
	adText = ad;
}

/* */
void Advert::setDate(int y, int m, int d)
{
	/* */
	if (year >= 2000 || year <= 2030)
		year = y;
	else
		year = 2000;

	/* */
	if (month >= 1 || month <= 12)
		month = m;
	else
		month = 1;

	/* */
	if (day >= 1 || day <= 30)
		day = d;
	else
		day = 1;
}

/* */
void Advert::setNumber(long long int num)
{
	/* */
	if (num < 0)
		number = num * -1;
	else
		number = num;
}

/* */
bool Advert::getBuySell() const
{
	return buySell;
}

/* */
std::string Advert::getCategory() const
{
	return category;
}

/* */
std::string Advert::getAdText() const
{
	return adText;
}

/* */
int Advert::getYear() const
{
	return year;
}


/* */
int Advert::getMonth() const
{
	return month;
}

/* */
int Advert::getDay() const
{
	return day;
}

/* */
long long int Advert::getNumber() const
{
	return number;
}

/* */
void Advert::output() const
{
	std::cout << "AD from " << year << "." << month << "." << day << std::endl
		<< "In category: " << category << std::endl
		<< "to " << (buySell ? "sell " : "buy ") << std::endl
		<< "Ad text: " << adText << std::endl
		<< "Contact: " << number << std::endl;
}