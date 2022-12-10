#pragma once

#include "Train.h"

// ����� ���� ������
class Node {
public:
	// ������������ � ����������
	Node();
	Node(Train& _train);
	~Node();
private:
	Train* train;
	Node* next;
	friend class List;
};