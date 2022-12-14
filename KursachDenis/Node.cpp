#include "Node.h"

//  онструктор по параметру
Node::Node(const Product& _data)
	: data(nullptr), prev(nullptr), next(nullptr) {
	data = new Product(_data);//выдел€ем пам€ть дл€ товара
}

Node::~Node() {//деструктор
	if (data) delete data;//освобождаем пам€ть
}