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

	void findCategory(const string& ctgry);
	void findText(const string& text);

	void out();
	bool save(const string& filename);
	bool load(const string& filename);
private:
	Announcement* head;
};

