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

unsigned short Announcement::getMaxDay(unsigned short m, unsigned short y)
{
	unsigned short d_max;
	if (m == 2)	//���� ����� �������
	{
		if (y % 4 == 0) { d_max = 29; }	//���� ��� ����������, �� ������������ ���� 29
		else { d_max = 28; }	//����� 28
	}
	//���� ����� �������� (�� �������) ��� ������ (������� � ��������) 
	else if ((m % 2 == 1 && m < 8) || (m % 2 == 0 && m >= 8)) { d_max = 31; }	//�� ������������ ����  31
	else { d_max = 30; }	//����� 30
	return d_max;
}

bool Announcement::isDateCorrect(unsigned short d, unsigned short m, unsigned short y)
{
	//�������� ���, ������ � ���� �� ������������ ��������
	if (d > 0 && d <= 31 &&
		m > 0 && m <= 12 &&
		y >= 2000 && y <= 2022 &&
		d <= getMaxDay(m, y))
	{ return true; }
	else { return false; }
}

void Announcement::print() const
{
	cout
		<< "\n###���������� �� " << setfill('0')
		<< setw(2) << day << '.'
		<< setw(2) << month << '.' << setfill(' ')
		<< year
		<< "###\n�������: " << category
		<< ((buy_sell == '1') ? (" (�������)") : (" (�������)")) << endl
		<< ad_text
		<< "\n�������: " << number << endl;
}

bool Announcement::saveToFile(fstream& file)	//������ ���������� � ����
{
	if (!file.is_open()) return false;	//���� ���� ������ ������� � �������
	file.clear();//�������� ������ ��������� ��������� ������
	//��������� ���������� � ���� ���� ������ ������� ������
	//���������� ��������� ��������
	file.write((const char*)&(next), sizeof(next));
	file.write((const char*)&(day), sizeof(day));
	file.write((const char*)&(month), sizeof(month));
	file.write((const char*)&(year), sizeof(year));
	file.write((const char*)&(buy_sell), sizeof(buy_sell));
	file.write((const char*)&(number), sizeof(number));

	//���������� ������� ������ ������, ����� ���� ������
	size_t size = category.size();
	file.write((const char*)(&size), sizeof(size));
	if (size > 0) { file.write(category.c_str(), size); }

	size = ad_text.size();
	file.write((const char*)(&size), sizeof(size));
	if (size > 0) { file.write(ad_text.c_str(), ad_text.size()); }

	file.flush();//���������� ����� ������ � ���� �� �����
	if (file.fail())
	{
		file.clear();
		return false;//��� ���� ������� � �������
	}
	return true;
}

bool Announcement::loadFromFile(fstream& file)	//������ ������� ������ �� �����
{
	if (!file.is_open()) return false;//���� ���� ������ ������� � �������
	file.clear();//�������� ������ ��������� ��������� ������ 
	file.flush();//���������� ����� ������ � ���� �� �����
	//��������� ������ �� ����� ���� ������ ������� ������
	file.read((char*)(&next), sizeof(next));
	file.read((char*)&(day), sizeof(day));
	file.read((char*)&(month), sizeof(month));
	file.read((char*)&(year), sizeof(year));
	file.read((char*)&(buy_sell), sizeof(buy_sell));
	file.read((char*)&(number), sizeof(number));

	size_t size = 0;
	file.read((char*)(&size), sizeof(size));//��������� ������ ������
	if (size > 0)//���� ������ �� �������
	{
		char* str = new char[size];//�������� ������ ������
		file.read(str, size);//��������� ������
		category.assign(str, size);//����������� ������ � ������
		delete[] str;//����������� ������
	}

	size = 0;
	file.read((char*)(&size), sizeof(size));	//��������� ������ ������
	if (size > 0)//���� ������ �� �������
	{
		char* str = new char[size];//�������� ������ ������
		file.read(str, size);//��������� ������
		ad_text.assign(str, size);//����������� ������ � ������
		delete[] str;//����������� ������
	}

	if (file.fail())
	{
		file.clear();
		return false;//��� ����  ������� � �������
	}
	return true;
}

bool Announcement::dateCheck(const string& date)
{
	if (date.size() != 10)	//������ ������ � ����� � ������� ��.��.���� = 10
	{
		return false;
	}

	unsigned short d = 0, m = 0, y = 0;
	for (size_t i = 0; i < date.size(); i++)	//��������������� ������� � �����
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

	return isDateCorrect(d, m, y);	//���������� ��������� �������� �� ����������
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

void Announcement::inputAnnouncement(Announcement& new_element)
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
			for (size_t i = 6; i < 10; i++)	//��������������� ���
			{
				year = year * 10 + buffer[i] - '0';
			}
			new_element.setDate(day, month, year);	//������������� ���� � ��������
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
			new_element.setBS(choice);		//������������� ��� ���������� � ��������
			break;
		}
		else { cout << "�������� ���" << endl; }
		cin.ignore(1000, '\n');	//���������� ������ �������, ���������� � ������
	}

	cout << "������� ������� ����������" << endl;
	cin.ignore(1000, '\n');
	getline(cin, buffer);

	new_element.setCategory(buffer);

	while (true)	//������������� ����� ��������
	{
		cout << "������� ���������� ����� (��� 8)" << endl;
		unsigned long long number = 0;
		bool failed = false;
		cin >> buffer;
		for (size_t i = 0; i < buffer.size(); i++)	//��������������� ���������� ������� � �����
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
			new_element.setNumber(number);	//������������� �����
			break;
		}
	}

	cout << "������� ����� ����������" << endl;
	cin.ignore(1000, '\n');
	getline(cin, buffer);

	new_element.setAdText(buffer);
}