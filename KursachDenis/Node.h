#pragma once

#include "Header.h"
#include "Product.h"

// Класс узла (элемента) списка
class Node {
private:
	Node() = delete; // Конструктор по умолчанию запрещён
	Node(const Product& _data);//Инициализирующий конструктор

	Product* data;
	Node* prev, *next;
	friend class List;
};
