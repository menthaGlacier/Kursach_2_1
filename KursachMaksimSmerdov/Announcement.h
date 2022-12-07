#pragma once
#include <string>
using namespace std;
class Announcement// Класс "обьявление"
{
	friend class List;
public:
	static bool dateCheck(const string& date)
	{
		if (date.size() != 10)
		{
			return false;
		}

		unsigned short d = 0, m = 0, y = 0;
		for (size_t i = 0; i < date.size(); i++)
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

		return isDateCorrect(d, m, y);
	}

	Announcement();

	void setDate(unsigned short d, unsigned short m, unsigned short y);
	void setCategory(string c);
	void setBS(string bs);
	void setAdText(string text);
	void setNumber(unsigned long long num);
private:
	static bool isDateCorrect(unsigned short d, unsigned short m, unsigned short y);

	unsigned short day, month, year;
	string category, buy_sell, ad_text;
	unsigned long long number;
	Announcement* next;
};