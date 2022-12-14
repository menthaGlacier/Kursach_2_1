#pragma once

#include "Header.h"
#include "Product.h"

// Класс узла (элемента) списка
class Node {
private:
	Node() = delete; // Конструктор по умолчанию запрещён
	Node(const Product& _data);//Инициализирующий конструктор
	~Node();//деструктор

	Product* data;//указатель на товар
	Node* prev, *next;//указатели на предыдущий и следующий элемент
	friend class List;//класс списка имеет доступ к приватным полям элемента
};
