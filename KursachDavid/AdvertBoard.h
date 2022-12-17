#pragma once

#include <iostream>
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

	/* ����� � ���������� */
	void find() const;
	void sort();

	/* ���������� � �������� �� ����� */
	void save(std::string file) const;
	void load(std::string file);

	/* ����� */
	void output() const;
};
