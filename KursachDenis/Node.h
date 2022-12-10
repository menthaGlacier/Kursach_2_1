#pragma once

#include "Header.h"
#include "Product.h"

// Класс узла (элемента) списка
class Node {
public:
	Node(); // Конструктор по умолчанию
	Node(const Product& _data);//Инициализирующий конструктор
private:
	Product* data;
	Node* prev, *next;
	friend class List;
};
