#include "Node.h"

//Конструктор по умолчанию
Node::Node()
	: data(nullptr), prev(nullptr), next(nullptr) {}

// Конструктор по параметру
Node::Node(const Product& _data)
	: data(nullptr), prev(nullptr), next(nullptr) {
	data = new Product(_data);
}