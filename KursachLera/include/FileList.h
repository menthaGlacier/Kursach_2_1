#ifndef FILE_LIST_H
#define FILE_LIST_H

#include "dependencies.h"
#include "Node.h"

class FileList {
public:
	// Конструктор, принимающий имя файла
	FileList(const string& name);

	// Деструктор
	~FileList();

	// Метод для открытия файла
	void openFile(const string& name);

	// Метод для создания файла
	void createFile(const string& name);

	// Вставка
	void insert(const Train& data); // Вставка в конец
	void insert(const Train& data, unsigned int index); // По логическому номеру

	// Удаление
	void deletion(); // Удаление с конца
	void deletion(unsigned int index); // Удаление по логическому номеру

	// Обновить объект узла
	void update(const Train& data, unsigned int index);

	// Сортировка
	void sort();

	// Поиск всех поездов, следующих до станции
	void find(unsigned int station);

	// Вывод списка
	void print();

	// Постраничный просмотр списка
	void pageViewPrint();
private:
	string name; // Имя файла
	fstream file; // Файловый поток
	unsigned long int size; // Размер списка
	long long int first; // Позиция первого элемента списка
};

#endif /* FILE_LIST_H */
