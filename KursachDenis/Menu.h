#pragma once
#include "Header.h"
#include "List.h"

class Menu {
public:
	void launch();	//метод запуска
private:
	void actionAdd();	//добавление товара на склад
	void actionRemove();	//удаление товара со склада
	void actionSort();	//сортировка товаров
	void actionSearch();	//поиск товара
	void actionSave();	//сохранение списка в файл
	void actionLoad();	//загрузка списка из файла
	void actionInvoice();	//составление фактуры

	Product inputProduct();	//метод ввода данных о товаре

	List warehouse;	//список товаров на складе
	std::string input_line;	//строка для обработки ввода
};