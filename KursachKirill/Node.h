#pragma once

#include "Train.h"

// Класс узла списка
class Node {
public:
	// Конструктор по параметрам
	Node(Train& _train);
private:
	Train& train;
	Node* next;
	friend class List;
};