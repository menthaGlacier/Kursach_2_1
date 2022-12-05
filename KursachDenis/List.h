#pragma once

#include "Header.h"
#include "Node.h"

class List {
public:
	List();
	~List();

	void insert(Product& _data);
	void insert(Product& _data, size_t index);
	void remove();
	void remove(size_t index);
	Product* find(ProductFieldName field) const;
	Product* find(size_t index) const;
	void output() const;
	size_t getSize() const;
private:
	Node* head, *last;
	size_t size;
};
