#ifndef FILE_LIST_H
#define FILE_LIST_H

#include "dependencies.h"
#include "Node.h"

class FileList {
public:
	// Конструктор, принимающий имя файла
	FileList(const std::string& name);

	// Деструктор
	~FileList();

	// Метод для открытия файла
	void openFile(const std::string& name);

	// Метод для создания файла
	void createFile(const std::string& name);

	// Вставки
	void insert(const Train& data); // Вставка в конец
	void insert(const Train& data, unsigned int index); // По логическому номеру

	// Удаление
	void remove(); // Удаление с конца
	void remove(unsigned int index); // Удаление по логическому номеру

	// Сортировка
	void sort();

	// Поиск всех поездов, следующих до станции
	void find(unsigned int station);

	//
	void print();
private:
	std::string name; // Имя файла
	std::fstream file; // Файловый поток
	unsigned long int size; // Размер списка
	long long int first; // Позиция первого элемента списка
};

#endif /* FILE_LIST_H */
