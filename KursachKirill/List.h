#pragma once

#include <iostream>
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

	// Сортировка списка
	void sort();

	// Вывод списка
	void print();
private:
	Node* head; // Указатель на первый элемент
	Node* last; // Указатель на последний элемент
	uint size; // Размер списка
};