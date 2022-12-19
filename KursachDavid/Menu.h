#pragma once

#include "AdvertBoard.h"

/* Класс меню для работы с доской объявлений */
class Menu
{
private:
	/* Доска объявлений и строка для ввода */
	AdvertBoard board;
	std::string inputLine;

	/* Метод ввода нового элемента для вставок */
	Advert newAdvert();
	
	/* Пункты меню */
	void insertAct();
	void removeAct();
	void saveAct();
	void loadAct();
	void sortAct();
	void findAct();
	void outputAct();
public:
	/* Конструктор по умолчанию */
	Menu();
};
