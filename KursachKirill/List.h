#pragma once

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

typedef unsigned int uint;

// Класс списка
class List {
public:
	List();
	~List();

	void insert(Train& _train);
	void insert(Train& _train, uint index);

	void print();
private:
	Node* head;
	Node* last;
	uint size;
};