#pragma once

#include <iostream>
#include <fstream>
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

	// ������� � �����, �� ������� � ����������� �������
	void insert(Train& _train);
	void insert(Train& _train, uint index);
	void insertOrdered(Train& _train);

	// �������� ���������� �������� � �� �������
	void remove();
	void remove(uint index);

	// ����� �������� �� ������ �����
	Train* search();

	// �������������� ������
	void order();

	// ����� ������
	void print();

	// ���������� � �������� ������ � � �� ��������� �����
	bool save(const char* fileName);
	bool load(const char* fileName);

	// ��������� ������� ������
	size_t getSize();
private:
	Node* head; // ��������� �� ������ �������
	Node* last; // ��������� �� ��������� �������
	uint size; // ������ ������
};