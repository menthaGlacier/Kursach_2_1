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
	void add(Announcement& elem);		//Добавление элемента в конец списка
	void insert(Announcement& elem, unsigned int pos);	//вставка в заданную позицию
	void insertInOrder(Announcement& elem);//вставка с сохранением порядка
	bool edit(Announcement& elem, unsigned int pos);//редактирование элемента в заданной позиции
	void out();//вывод списка в консоль
	long long int getNode(unsigned int pos, Announcement& element);//получение элемента по индексу
	bool removeAt(unsigned int pos);//удаление товара в заданной позиции
	void findCategory(const string& ctgry);	//поиск по рубрике
	void findText(const string& text);	//поиск по тексту объявления
	void sort();//сортировка списка

private:
	int size;	//размер списка
	fstream file;//связанный со списком файл
};