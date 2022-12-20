#pragma once
#include "dependencies.h"
using namespace std;
class Announcement// ����� "����������"
{
	friend class List;	//��� ������ ������ ������ �� ���� �����
public:
	static bool dateCheck(const string& date);	//����� �������� ������ �� ����������� ���������� �� �� ����
	static void inputAnnouncement(Announcement& elem);

	Announcement();	//�����������

	//������� �����
	void setDate(unsigned short d, unsigned short m, unsigned short y);
	void setCategory(const string& c);
	void setBS(unsigned short bs);
	void setAdText(const string& text);
	void setNumber(unsigned long long num);

	void print() const;	//����� ��������
	bool fileSave(fstream& f);
	bool fileLoad(fstream& f);

	bool operator<(const Announcement& right) const;
	bool operator>(const Announcement& right) const;
private:
	//�������� ���� �� ����������
	static bool checkDate(unsigned short d, unsigned short m, unsigned short y);

	//��������� ������������� ��� ��� ��������� ������ � ����
	static unsigned short getMonthDayLimit(unsigned short m, unsigned short y);

	unsigned short day, month, year,	//����
		buy_sell;	//��������� (�����/�������)
	unsigned long long number;	//����� ��������
	string category, ad_text;	//�������� ������� � ����� ����������
	long long int next;	//�������� ��������� �� ��������� ����������
};