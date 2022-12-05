#include "Node.h"

// Конструктор по параметру
Node::Node(Product& _data)
	: data(_data), prev(nullptr), next(nullptr) {}