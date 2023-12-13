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

	// Геттеры
	string getName();
	fstream getFile();
	unsigned long int getSize();
	long long int getFirst();

	// Вложенный класс итератора
	class Iterator {
	public:
		Iterator(FileList* list, long long int startPosition) {
			this->list = list;
			this->currentPosition = startPosition;
		}

		Iterator& operator++() {
			Node node;
			list->file >> node; // Читаем узел
			list->file.clear(); // Очищаем флаги файла
			list->file.seekg(node.getNext()); // Переходим на следующий элемент
			currentPosition = list->file.tellg(); // Запоминаем текущую позицию
			return *this;
		}

		// Перегрузка постфиксного инкремента
		Iterator operator++(int) {
			Iterator temp = *this; // Сохраняем предыдущее состояние итератора
			++(*this); // Продвигаем его
			return temp; // Возвращаем сохраненное состояние
		}

		// Перегрузка оператора "равно"
		bool operator==(const Iterator& iter) {
			return currentPosition == iter.currentPosition;
		}

		// Перегрузка оператор "не равно"
		bool operator!=(const Iterator& iter) {
			return currentPosition != iter.currentPosition;
		}

		// Перегрузка разыменования итератора возвращает объект
		Train operator*() {
			Node node;
			long long int pos = list->file.tellg(); // Запоминаем позицию узла
			list->file >> node; // Читаем узел
			list->file.clear(); // Очищаем флаги файла
			list->file.seekg(pos); // Возвращаемся на позицию узла
			return node.getData(); // Возвращаем объект
		}

	private:
		FileList* list; // Список по которому идёт итерация
		long long int currentPosition; // Текущая позиция в файле
	};

	// Получить итератор на начало списка
	Iterator begin() {
		return Iterator(this, first);
	}

	// Получить итератор на конец списка
	Iterator end() {
		return Iterator(this, -1);
	}
private:
	string name; // Имя файла
	fstream file; // Файловый поток
	unsigned long int size; // Размер списка
	long long int first; // Позиция первого элемента списка
};

#endif /* FILE_LIST_H */
