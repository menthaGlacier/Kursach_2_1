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

	// ����� ��������� �� ������� ����������
	void search(uint station);

	// �������������� ������
	void order();

	// ����� ������
	void print();

	// ���������� � �������� ������ � � �� ��������� �����
	bool save(const char* fileName);
	bool load(const char* fileName);

	// ��������� ������� ������
	uint getSize();

	// ��������� �����, ����������� ������� ���������
	class Iterator {
	public:
		// ������������
		Iterator(List& _list, uint _pos, bool isBegin);
		Iterator(const Iterator& other);

		// �������� ������������ � �������������
		Iterator& operator=(Iterator& other);
		Node* operator*();

		// �������� �������� ���������
		Iterator& operator++();
		Iterator operator++(int);

		// ��������� ���������
		bool operator==(const Iterator& other);
		bool operator!=(const Iterator& other);

		// ��������� �������� �������
		uint getPos();
	private:
		List& itrList; // ������, ������� ����� �������������
		Node* curNode; // ������� ������, �� ������� ��������� ��������
		uint pos; // �������, �� ������� ��������� �������� � ������
	};

	// �������� ��������� ����� � ������ c����� ��� ���������
	Iterator begin();
	Iterator end();
private:
	Node* head; // ��������� �� ������ �������
	Node* last; // ��������� �� ��������� �������
	uint size; // ������ ������

	friend class Iterator;
};