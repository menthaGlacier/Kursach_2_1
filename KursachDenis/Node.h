#pragma once

#include "Header.h"
#include "Product.h"

// ����� ���� (��������) ������
class Node {
private:
	Node() = delete; // ����������� �� ��������� ��������
	Node(const Product& _data);//���������������� �����������
	~Node();//����������

	Product* data;//��������� �� �����
	Node* prev, *next;//��������� �� ���������� � ��������� �������
	friend class List;//����� ������ ����� ������ � ��������� ����� ��������
};
