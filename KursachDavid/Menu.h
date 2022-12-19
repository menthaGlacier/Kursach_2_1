#pragma once

#include "AdvertBoard.h"

/* ����� ���� ��� ������ � ������ ���������� */
class Menu
{
private:
	/* ����� ���������� � ������ ��� ����� */
	AdvertBoard board;
	std::string inputLine;

	/* ����� ����� ������ �������� ��� ������� */
	Advert newAdvert();
	
	/* ������ ���� */
	void insertAct();
	void removeAct();
	void saveAct();
	void loadAct();
	void sortAct();
	void findAct();
	void outputAct();
public:
	/* ����������� �� ��������� */
	Menu();
};
