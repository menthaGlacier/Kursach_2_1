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

	// Вставка в конец и по индексу
	void insert(Train& _train);
	void insert(Train& _train, uint index);
	
	// Удаление последнего элемента и по индексу
	void remove();
	void remove(uint index);


	// Вывод списка
	void print();
private:
	Node* head; // Указатель на первый элемент
	Node* last; // Указатель на последний элемент
	uint size; // Размер списка
};