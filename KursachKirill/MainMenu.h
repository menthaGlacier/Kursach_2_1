#pragma once

#include <iostream>
#include <string>

#include "List.h"

using namespace std;

class MainMenu
{
public:
	void start(); // Запуск меню
private:
	void scheduleInsert(); // Добавление элемента
	void scheduleRemove(); // Удаление элемента
	void schedulePrint(); // Вывод
	void scheduleSearch(); // Поиск по параметру
	void scheduleOrder(); // Упорядочивание
	void scheduleSave(); // Сохранение в файле
	void scheduleLoad(); // Загрузка из файла

	List schedule; // Расписание поездов
	string input; // Строка для считывания ввода
};
