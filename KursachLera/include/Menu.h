#ifndef MENU_H
#define MENU_H

#include "dependencies.h"
#include "FileList.h"

class Menu {
public:
	Menu(); // Конструктор по умолчанию
	~Menu(); // Деструктор
	void mainMenu(); // Главное меню
	Train inputTrain(); // Ввод объекта
private:
	FileList* list;
};

#endif /* MENU_H */
