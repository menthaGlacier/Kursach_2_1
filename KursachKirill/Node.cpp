#include "Node.h"

// Конструктор по умолчанию
Node::Node()
	: train(nullptr), next(nullptr) {
	train = new Train();
}

// Конструктор с параметром
Node::Node(Train& _train)
	: train(nullptr), next(nullptr) {
	train = new Train(_train);
	next = nullptr;
}

// Деструктор
Node::~Node() {
	if (train) {
		delete train;
	}
}