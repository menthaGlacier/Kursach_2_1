#pragma once

#include <iostream>
#include <fstream>
#include "Advert.h"

/* Доска объявлений, реализованная через массив */
class AdvertBoard
{
private:
	Advert* arr; /* Массив элементов */
	int size, capacity; /* Размер и вместимость массива */

	/* Переводим старый массив в новый с новым размером */
	void updateArray();

public:
	/* Конструкторы */
	AdvertBoard();
	AdvertBoard(int cap);

	/* Деструктор */
	~AdvertBoard();

	/* Вставка элементов */
	void insert(const Advert& advert);
	void insert(const Advert& advert, int pos);
	void insort(const Advert& advert);

	/* Извлечение элементов */
	void remove();
	void remove(int pos);

	/* Получение элемента */
	Advert* operator[](int pos) const;

	/* Поиски и сортировка */
	void findCategory(const std::string cat) const;
	void findAdText(const std::string ad) const;
	void sort();

	/* Сохранение и загрузка из файла */
	bool save(std::string file) const;
	bool load(std::string file);

	/* Вывод */
	void output() const;
};
