#pragma once

#include <iostream>
#include <fstream>
#include "Advert.h"

/* ����� ����������, ������������� ����� ������ */
class AdvertBoard
{
private:
	Advert* arr; /* ������ ��������� */
	int size, capacity; /* ������ � ����������� ������� */

	/* ��������� ������ ������ � ����� � ����� �������� */
	void updateArray();

public:
	/* ������������ */
	AdvertBoard();
	AdvertBoard(int cap);

	/* ���������� */
	~AdvertBoard();

	/* ������� ��������� */
	void insert(const Advert& advert);
	void insert(const Advert& advert, int pos);
	void insort(const Advert& advert);

	/* ���������� ��������� */
	void remove();
	void remove(int pos);

	/* ��������� �������� */
	Advert* operator[](int pos) const;

	/* ������ � ���������� */
	void findCategory(const std::string cat) const;
	void findAdText(const std::string ad) const;
	void sort();

	/* ���������� � �������� �� ����� */
	bool save(std::string file) const;
	bool load(std::string file);

	/* ����� */
	void output() const;
};
