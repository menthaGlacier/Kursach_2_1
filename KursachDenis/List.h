#pragma once

#include "Header.h"
#include "Node.h"

class List {
public:
	List();
	~List();

	void insert(const Product& _data);
	void insert(const Product& _data, size_t index);
	void insort(ProductFieldName field, const Product& _data);
	void remove();
	void remove(size_t index);
	void find(ProductFieldName field, const Product& _data) const;
	Product* find(size_t index) const;

	//Сортировка
	void sort(ProductFieldName field, bool reverse = false);
	bool save(const std::string& file_name);
	bool load(const std::string& file_name);
	void output() const;
	size_t getSize() const;
private:
	Node* head, *last;
	size_t size;
};
