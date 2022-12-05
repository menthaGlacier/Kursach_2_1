#pragma once

#include "Header.h"
#include "Product.h"

// Класс узла (элемента) списка
class Node {
public:
	Node() = delete; // Конструктор по умолчанию запрещен
	Node(Product& _data);
private:
	Product& data;
	Node* prev, *next;
	friend class List;
};
