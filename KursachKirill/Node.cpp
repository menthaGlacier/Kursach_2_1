#include "Node.h"

// ����������� �� ���������
Node::Node()
	: train(nullptr), next(nullptr) {
	train = new Train();
}

// ����������� � ����������
Node::Node(Train& _train)
	: train(nullptr), next(nullptr) {
	train = new Train(_train);
	next = nullptr;
}

// ����������
Node::~Node() {
	if (train) {
		delete train;
	}
}