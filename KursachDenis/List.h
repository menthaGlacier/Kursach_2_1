#pragma once

#include "Header.h"
#include "Node.h"

class List {
public:
	List(); //конструктор
	~List(); //деструктор

	void insert(const Product& _data); //вставка в конец
	void insert(const Product& _data, size_t index); //вставка в заданную позицию
	void insort(ProductFieldName field, const Product& _data); //вставка с сохранением порядка

	void remove(); //удаление последнего элемента
	void remove(size_t index); //удаление элемента по индексу

	void find(ProductFieldName field, const Product& _data) const; //поиск по критерию
	Product* find(size_t index) const; //поиск по индексу

	void sort(ProductFieldName field, bool reverse = false); //сортировка по критерию

	bool save(const std::string& file_name); //сохранение в файл
	bool load(const std::string& file_name); //загрузка из файла
	void output() const; //вывод списка в консоль

	size_t getSize() const; //получение размера
private:
	Node* head, *last; //указатель на первый и последний элемент
	size_t size; //размер списка
};
