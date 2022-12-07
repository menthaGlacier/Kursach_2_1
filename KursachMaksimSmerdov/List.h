#pragma once
#include "dependencies.h"
#include "Announcement.h"
using namespace std;

class List
{
public:
	List();
	~List();

	void add(const Announcement& entry, size_t index = -1);
	bool del(size_t index);
	void clear();

	void sort();

	void findCategory(string);
	void findText(string);

	void out();
	void save();
	void load();
private:
	Announcement* head;
};

