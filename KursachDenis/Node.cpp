#include "Node.h"

//����������� �� ���������
Node::Node()
	: data(nullptr), prev(nullptr), next(nullptr) {}

// ����������� �� ���������
Node::Node(const Product& _data)
	: data(nullptr), prev(nullptr), next(nullptr) {
	data = new Product(_data);
}