#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

//перечисление критериев сортировки
enum class SortType { Name, Category, Quantity, Date, Price, Percentage};

struct Node//элемент списка(товар)
{
public:
	bool toFile(fstream& file);//загрузка в файл
	bool fromFile(fstream& file);//загрузка товара из файла
	void show();//вывод в консоль
	void inputProduct();//ввод пользователем данных о товаре

	string name; //название товара
	string category; //категори€ товара
	int quantity; //кол-во
	int day; //день
	int month; //мес€ц
	int year; //год
	int price; //цена
	float percentage; //процент торговой надбавки
private:
	friend class List;//класс списка имеет доступ к приватным пол€м
	long long int next, prev;	//файловые указатели на следующий и предыдущий элементы в списке
};

class List//класс списка
{
public:
	List(); // онструктор
	~List(); // ƒеструктор

	int getSize() { return size; }	//получение размера списка
	//ƒобавление элемента в конец списка
	void add(string name, string category, int quantity, int day, int month, int year, int price, float percentage);
	//вставка в заданную позицию
	void insert(string name, string category, int quantity, int day, int month, int year, int price, float percentage, size_t index);
	//вставка с сохранением пор€дка
	void insertInOrder(string name, string category, int quantity, int day, int month, int year, int price, float percentage);
	//редактирование элемента в заданной позиции
	bool edit(string name, string category, int quantity, int day, int month, int year, int price, float percentage, size_t index);
	void show();//вывод списка в консоль
	long long int getNode(size_t index, Node& node);//получение элемента по индексу
	bool removeAt(size_t index);//удаление товара в заданной позиции

	void sort(SortType type);//сортировка списка
	void invoice();//составление фактуры
private:
	int size;	//размер списка
	fstream file;//св€занный со списком файл
};