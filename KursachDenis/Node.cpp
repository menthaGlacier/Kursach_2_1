#include "Node.h"

// ����������� �� ���������
Node::Node(Product& _data)
	: data(_data), prev(nullptr), next(nullptr) {}