#pragma once

#include <iostream>
#include <string>

class Advert
{
private:
	bool buySell; /* �����-�������. ��������� false � true �������������� */
	std::string category; /* ������� */
	std::string adText; /* ����� ���������� */
	int year, month, day; /* ���� ������ */
	long long int number; /* ���������� ������� */

	friend class AdvertBoard; /* ������������� ����� ����� ���������� */
public:
	/* ������������ */
	Advert();
	Advert(bool bS, std::string cat, std::string ad,
		int y, int m, int d, long long int num);
	Advert(const Advert& advert);

	/* ��������� �������� */
	void setBuySell(bool bS);
	void setCategory(std::string cat);
	void setAdText(std::string ad);
	void setDate(int y, int m, int d);
	void setNumber(long long int num);

	/* ��������� �������� */
	bool getBuySell() const;
	std::string getCategory() const;
	std::string getAdText() const;
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	long long int getNumber() const;

	/* �������� ������ � ������ */
	bool operator<(const Advert& advert) const;
	bool operator>(const Advert& advert) const;

	/* ����� */
	void output() const;
};