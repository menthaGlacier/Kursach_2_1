#pragma once
#include "dependencies.h"
#include "Announcement.h"
using namespace std;

class List//класс списка
{
public:
	List(); //Конструктор
	~List(); // Деструктор

	int getSize() { return size; }	//получение размера списка
	void add(Announcement& new_element);		//Добавление элемента в конец списка
	void insert(Announcement& new_element, size_t index);	//вставка в заданную позицию
	void insertInOrder(Announcement& new_element);//вставка с сохранением порядка
	bool edit(Announcement& changed_element, size_t index);//редактирование элемента в заданной позиции
	void out();//вывод списка в консоль
	long long int getNode(size_t index, Announcement& element);//получение элемента по индексу
	bool removeAt(size_t index);//удаление товара в заданной позиции
	void findCategory(const string& ctgry);	//поиск по рубрике
	void findText(const string& text);	//поиск по тексту объявления
	void sort();//сортировка списка

private:
	int size;	//размер списка
	fstream file;//связанный со списком файл
};