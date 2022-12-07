#include "Announcement.h"

Announcement::Announcement()
{
	day = 0;
	month = 0;
	year = 0;
	number = 0;
	next = nullptr;
}

void Announcement::setDate(unsigned short d, unsigned short m, unsigned short y)
{
	day = d;
	month = m;
	year = y;
}

void Announcement::setCategory(string c)
{
	category = c;
}

void Announcement::setBS(string bs)
{
	buy_sell = bs;
}

void Announcement::setAdText(string text)
{
	ad_text = text;
}
void Announcement::setNumber(unsigned long long num)
{
	number = num;
}



bool Announcement::isDateCorrect(unsigned short d, unsigned short m, unsigned short y)
{
	if (d <= 31 && m <= 12 && y >= 2000 && y <= 2022)
	{
		unsigned short d_max;
		if (m == 2) 
		{
			if (y % 4 == 0) { d_max = 29; }
			else { d_max = 28; }
		}
		else if ((m % 2 == 1 && m < 8) || (m % 2 == 0 && m >= 8)) { d_max = 31; }
		else { d_max = 30; }

		if (d < d_max) return true;
	}
	return false;
}