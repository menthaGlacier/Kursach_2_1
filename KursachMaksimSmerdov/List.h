#pragma once
#include "dependencies.h"
#include "Announcement.h"
using namespace std;

class List
{
public:
	List();	//конструктор
	~List();	//деструктор

	void add(const Announcement& entry, size_t index = -1);		//добавление элемента в список
	bool del(size_t index);	//удаление по индексу
	void clear();	//очистка списка

	void sort();	//сортировка по дате

	void findCategory(const string& ctgry);	//поиск по рубрике
	void findText(const string& text);	//поиск по тексту объ€влени€

	void out();	//вывод списка
	bool save(const string& filename);	//сохранение в файл
	bool load(const string& filename);	//загрузка из файла
private:
	Announcement* head;	//указатель на первый элемент
};

