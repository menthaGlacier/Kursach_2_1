#include "Announcement.h"

Announcement::Announcement()
{
	day = 0;
	month = 0;
	year = 0;
	number = 0;
	buy_sell = 1;
	next = -1;
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

unsigned short Announcement::getMonthDayLimit(unsigned short m, unsigned short y)
{
	unsigned short limit_month_day;
	if (m == 2)	//���� ����� �������
	{
		if (y % 4 == 0)
			limit_month_day = 29;	//���� ��� ����������, �� ������������ ���� 29
		else
			limit_month_day = 28;	//����� 28
	}
	//���� ����� �������� (�� �������) ��� ������ (������� � ��������) 
	else if ((m % 2 == 1 && m < 8) || (m % 2 == 0 && m >= 8))
		limit_month_day = 31;//�� ������������ ����  31
	else
		limit_month_day = 30; //����� 30

	return limit_month_day;
}

bool Announcement::checkDate(unsigned short d, unsigned short m, unsigned short y)
{
	//�������� ���, ������ � ���� �� ������������ ��������
	if (d <= 0 || d > 31)
		return false;
	if (m <= 0 || m > 12)
		return false;
	if (y < 1970 || y > 2035 || d <= getMonthDayLimit(m, y))
		return false;
	return true;
}

void Announcement::print() const
{
	cout << "\n\t���������� �� " << day << '.' << month << '.' << year;
	cout << "\n\t� �������: " << category;
	if ((buy_sell == '1'))
		cout << " (�������)";
	else
		cout << " (�������)";
	cout << "\n\t����� ����������: " << ad_text;
	cout << "\n\t���������� �����: " << number << endl;
}

bool Announcement::fileSave(fstream& f)	//������ ���������� � ����
{
	if (!f.is_open())
		return false;	//���� ���� ������ ������� � �������

	f.clear();//�������� ������ ��������� ��������� ������
	//��������� ���������� � ���� ���� ������ ������� ������
	//���������� ��������� ��������
	f.write(reinterpret_cast<char*>(&next), sizeof(next));
	f.write(reinterpret_cast<char*>(&day), sizeof(day));
	f.write(reinterpret_cast<char*>(&month), sizeof(month));
	f.write(reinterpret_cast<char*>(&year), sizeof(year));
	f.write(reinterpret_cast<char*>(&buy_sell), sizeof(buy_sell));
	f.write(reinterpret_cast<char*>(&number), sizeof(number));

	//���������� ������� ������ ������, ����� ���� ������
	unsigned int size = category.size();
	f.write(reinterpret_cast<char*>(&size), sizeof(size));
	if (size > 0)
		f.write(category.c_str(), size);

	size = ad_text.size();
	f.write(reinterpret_cast<char*>(&size), sizeof(size));
	
	if (size > 0)
		f.write(ad_text.c_str(), ad_text.size()); 

	f.flush();//���������� ����� ������ � ���� �� �����
	if (f.fail())
	{
		f.clear();
		return false;//��� ���� ������� � �������
	}

	return true;
}

bool Announcement::fileLoad(fstream& f)	//������ ������� ������ �� �����
{
	if (!f.is_open()) return false;//���� ���� ������ ������� � �������
	f.clear();//�������� ������ ��������� ��������� ������ 
	f.flush();//���������� ����� ������ � ���� �� �����
	//��������� ������ �� ����� ���� ������ ������� ������
	f.read(reinterpret_cast<char*>(&next), sizeof(next));
	f.read((char*)&(day), sizeof(day));
	f.read((char*)&(month), sizeof(month));
	f.read((char*)&(year), sizeof(year));
	f.read((char*)&(buy_sell), sizeof(buy_sell));
	f.read((char*)&(number), sizeof(number));

	unsigned int size = 0;
	f.read(reinterpret_cast<char*>(&size), sizeof(size));//��������� ������ ������
	if (size > 0)//���� ������ �� �������
	{
		char* read_string = new char[size];//�������� ������ ������
		f.read(read_string, size);//��������� ������
		category.assign(read_string, size);//����������� ������ � ������
		delete[] read_string;//����������� ������
	}

	size = 0;
	f.read(reinterpret_cast<char*>(&size), sizeof(size));	//��������� ������ ������
	if (size > 0)//���� ������ �� �������
	{
		char* read_string = new char[size];//�������� ������ ������
		f.read(read_string, size);//��������� ������
		ad_text.assign(read_string, size);//����������� ������ � ������
		delete[] read_string;//����������� ������
	}

	if (f.fail())
	{
		f.clear();
		return false;//��� ����  ������� � �������
	}

	return true;
}

bool Announcement::dateCheck(const string& date)
{
	if (date.size() < 10 || date.size() > 10)	//������ ������ � ����� � ������� ��.��.���� = 10
		return false;

	unsigned short d = 0, m = 0, y = 0;
	for (unsigned int i = 0; i < date.size(); i++)	//��������������� ������� � �����
	{
		if (i == 2 || i == 5)
			if (date[i] != '.') return false;
		else
		{
			if (date[i] < '0' || date[i] > '9')
				return false;

			if (i < 2)
				d = (d * 10 + date[i] - '0');
			else if (i < 5)
				m = (m * 10 + date[i] - '0');
			else
				y = (y * 10 + date[i] - '0');
		}
	}

	return checkDate(d, m, y);	//���������� ��������� �������� �� ����������
}

bool Announcement::operator<(const Announcement& right) const
{
	if (year == right.year)
	{
		if (month == right.month)
			if (day < right.day)
				return true;
		else if (month < right.month)
			return true;
	}

	else if (year < right.year)
		return true;

	return false;
}

bool Announcement::operator>(const Announcement& right) const
{
	if (year == right.year)
	{
		if (month == right.month)
			if (day > right.day)
				return true;
		else if (month > right.month)
			return true;
	}
	else if (year > right.year)
		return true;

	return false;
}

void Announcement::inputAnnouncement(Announcement& elem)
{
	string buffer;
	while (true)	//�������� ����
	{
		cout << "������� ���� (��.��.����)" << endl;
		cin >> buffer;

		if (!Announcement::dateCheck(buffer))	//������ �������� ����
		{
			cout << "�������� ����" << endl;
		}
		else	//���� �������� �������, ��������� ���� � �������
		{
			unsigned short day = (buffer[0] - '0') * 10 + (buffer[1] - '0');			//��������������� ���� � �����
			unsigned short month = (buffer[3] - '0') * 10 + (buffer[4] - '0');	//�� �������� � �����
			unsigned short year = 0;
			for (unsigned int i = 6; i < 10; i++)	//��������������� ���
			{
				year = year * 10 + buffer[i] - '0';
			}
			elem.setDate(day, month, year);	//������������� ���� � ��������
			break;
		}
	}

	while (true)	//�������� ��� ����������
	{
		cout
			<< "�������� ��� ����������:\n"
			<< "1. �����\n"
			<< "2. �������" << endl;

		char choice;
		cin >> choice;
		if (choice == '1' || choice == '2')	//���� ���� ��������
		{
			elem.setBS(choice);		//������������� ��� ���������� � ��������
			break;
		}
		else { cout << "�������� ���" << endl; }
		cin.ignore(1000, '\n');	//���������� ������ �������, ���������� � ������
	}

	cout << "������� ������� ����������" << endl;
	cin.ignore(1000, '\n');
	getline(cin, buffer);

	elem.setCategory(buffer);

	while (true)	//������������� ����� ��������
	{
		cout << "������� ���������� ����� (��� 8)" << endl;
		unsigned long long number = 0;
		bool failed = false;
		cin >> buffer;
		for (unsigned int i = 0; i < buffer.size(); i++)	//��������������� ���������� ������� � �����
		{
			if (buffer[i] >= '0' && buffer[i] <= '9')
			{
				number = number * 10 + buffer[i] - '0';
			}
			else		//���� ������ �� �����
			{
				cout << "�������� �����" << endl;
				failed = true;	//������������� ���� ������
				break;	//���������� ��������������
			}
		}
		if (failed == false)	//���� �� ���� �������� ������ ��� ��������������
		{
			elem.setNumber(number);	//������������� �����
			break;
		}
	}

	cout << "������� ����� ����������" << endl;
	cin.ignore(1000, '\n');
	getline(cin, buffer);

	elem.setAdText(buffer);
}