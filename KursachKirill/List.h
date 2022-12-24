#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

typedef unsigned int uint;

// Класс списка
class List {
public:
	// Конструктор и деструктор
	List();
	~List();

	// Вставка в конец, по индексу и сохранением порядка
	void insert(Train& _train);
	void insert(Train& _train, uint index);
	void insertOrdered(Train& _train);

	// Удаление последнего элемента и по индексу
	void remove();
	void remove(uint index);

	// Поиск элементов по станции назначения
	void search(uint station);

	// Упорядочивание списка
	void order();

	// Вывод списка
	void print();

	// Сохранение и загрузка списка в и из бинарного файла
	bool save(const char* fileName);
	bool load(const char* fileName);

	// Получение размера списка
	uint getSize();

	// Вложенный класс, реализующий функции итератора
	class Iterator {
	public:
		// Конструкторы
		Iterator(List& _list, uint _pos, bool isBegin);
		Iterator(const Iterator& other);

		// Операции присваивания и разыменования
		Iterator& operator=(Iterator& other);
		Node* operator*();

		// Операции итерации итератора
		Iterator& operator++();
		Iterator operator++(int);

		// Операторы сравнения
		bool operator==(const Iterator& other);
		bool operator!=(const Iterator& other);

		// Получение значение позиции
		uint getPos();
	private:
		List& itrList; // Список, который будет итерироваться
		Node* curNode; // Элемент списка, на котором находится итератор
		uint pos; // Позиция, на которой находится итератор в списке
	};

	// Операции получения конца и начала cписка для итератора
	Iterator begin();
	Iterator end();
private:
	Node* head; // Указатель на первый элемент
	Node* last; // Указатель на последний элемент
	uint size; // Размер списка

	friend class Iterator;
};