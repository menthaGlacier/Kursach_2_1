#pragma once

#include "Train.h"

// ����� ���� ������
class Node {
public:
	// ����������� �� ����������
	Node(Train& _train);
private:
	Train& train;
	Node* next;
	friend class List;
};