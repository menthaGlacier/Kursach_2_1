#pragma once

#include "Header.h"
#include "Product.h"

// ����� ���� (��������) ������
class Node {
public:
	Node(); // ����������� �� ���������
	Node(const Product& _data);//���������������� �����������
private:
	Product* data;
	Node* prev, *next;
	friend class List;
};
