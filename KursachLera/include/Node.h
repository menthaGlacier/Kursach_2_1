#ifndef NODE_H
#define NODE_H

#include "dependencies.h"
#include "Train.h"

// Класс для узла списка
class Node {
public:
	// Конструктор по умолчанию
	Node();

	// Геттеры
	long long int getNext();
	Train getData();

	// Сеттеры
	void setNext(long long next);
	void setData(const Train& data);

	// Записать узел в файл
	void write(std::fstream& file);
	
	// Прочесть узел из файла
	void read(std::fstream& file);

	// Получить размер узла
	unsigned int size();

	// Перегрузка операторов
	bool operator>(const Node& right); // Оператор "больше"
	bool operator<(const Node& right); // Оператор "меньше"

	friend std::fstream& operator<<(std::fstream& file, const Node& node); // Запись в поток
	friend std::fstream& operator>>(std::fstream& file, Node& node); // Чтение из потока
private:
	long long int next; // Позиция следующего элемента в файле
	Train data; // Данные узла
};

#endif /* NODE_H */
