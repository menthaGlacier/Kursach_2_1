#include "Announcement.h"

Announcement::Announcement()
{
	day = 0;
	month = 0;
	year = 0;
	number = 0;
	buy_sell = 1;
	next = nullptr;
}

void Announcement::setDate(unsigned short d, unsigned short m, unsigned short y)
{
	day = d;
	month = m;
	year = y;
}

void Announcement::setCategory(const string& c)
{
	category = c;
}

void Announcement::setBS(unsigned short bs)
{
	buy_sell = bs;
}

void Announcement::setAdText(const string& text)
{
	ad_text = text;
}
void Announcement::setNumber(unsigned long long num)
{
	number = num;
}

unsigned short Announcement::getMaxDay(unsigned short m, unsigned short y)
{
	unsigned short d_max;
	if (m == 2)	//если мес€ц февраль
	{
		if (y % 4 == 0) { d_max = 29; }	//если год високосный, то максимальный день 29
		else { d_max = 28; }	//иначе 28
	}
	//если мес€ц нечЄтный (до августа) или чЄтный (начина€ с сент€бр€) 
	else if ((m % 2 == 1 && m < 8) || (m % 2 == 0 && m >= 8)) { d_max = 31; }	//то максимальный день  31
	else { d_max = 30; }	//иначе 30
	return d_max;
}

bool Announcement::isDateCorrect(unsigned short d, unsigned short m, unsigned short y)
{
	//ѕроверка дн€, мес€ца и года на соответствие пределам
	if (d > 0 && d <= 31 &&
		m > 0 && m <= 12 &&
		y >= 2000 && y <= 2022 &&
		d < getMaxDay(m, y))
	{ return true; }
	else { return false; }
}

void Announcement::print() const
{
	cout
		<< "\n###ќбъ€вление от " << setfill('0')
		<< setw(2) << day << '.'
		<< setw(2) << month << '.' << setfill(' ')
		<< year
		<< "###\n–убрика: " << category
		<< ((buy_sell == 1) ? (" (покупка)") : (" (продажа)")) << endl
		<< ad_text
		<< "\n“елефон: " << number << endl;
}

bool Announcement::dateCheck(const string& date)
{
	if (date.size() != 10)	//размер строки с датой в формате дд.мм.гггг = 10
	{
		return false;
	}

	unsigned short d = 0, m = 0, y = 0;
	for (size_t i = 0; i < date.size(); i++)	//преобразовываем символы в числа
	{
		if (i == 2 || i == 5)
		{
			if (date[i] != '.') return false;
		}
		else
		{
			if (date[i] < '0' || date[i] > '9') { return false; }

			if (i < 2)
			{
				d = d * 10 + date[i] - '0';
			}
			else if (i < 5)
			{
				m = m * 10 + date[i] - '0';
			}
			else
			{
				y = y * 10 + date[i] - '0';
			}
		}
	}

	return isDateCorrect(d, m, y);	//возвращаем результат проверки на валидность
}

bool Announcement::operator<(const Announcement& right) const
{
	if (year == right.year)
	{
		if (month == right.month)
		{
			if (day < right.day) { return true; }
		}
		else if (month < right.month) { return true; }
	}
	else if (year < right.year) { return true; }

	return false;
}

bool Announcement::operator>(const Announcement& right) const
{
	if (year == right.year)
	{
		if (month == right.month)
		{
			if (day > right.day) { return true; }
		}
		else if (month > right.month) { return true; }
	}
	else if (year > right.year) { return true; }

	return false;
}