#include "Node.h"

// ����������� �� ���������
Node::Node(const Product& _data)
	: data(nullptr), prev(nullptr), next(nullptr) {
	data = new Product(_data);
}