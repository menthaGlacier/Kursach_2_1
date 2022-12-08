#pragma once

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

typedef unsigned int uint;

// ����� ������
class List {
public:
	// ����������� � ����������
	List();
	~List();

	// ������� � ����� � �� �������
	void insert(Train& _train);
	void insert(Train& _train, uint index);
	
	// �������� ���������� �������� � �� �������
	void remove();
	void remove(uint index);


	// ����� ������
	void print();
private:
	Node* head; // ��������� �� ������ �������
	Node* last; // ��������� �� ��������� �������
	uint size; // ������ ������
};