#pragma once

#include "Train.h"

// Класс узла списка
class Node {
public:
	// Конструкторы и деструктор
	Node();
	Node(Train& _train);
	~Node();
private:
	Train* train;
	Node* next;
	friend class List;
};