#pragma once

#include <iostream>
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

	/* Поиск и сортировка */
	void find() const;
	void sort();

	/* Сохранение и загрузка из файла */
	void save(std::string file) const;
	void load(std::string file);

	/* Вывод */
	void output() const;
};
