#include "../include/Node.h"

// Получение размера файла
unsigned int Node::size() {
	return sizeof(next) + data.size();
}

// Оператор сравнение "больше"
bool Node::operator>(const Node& right) {
	return this->data > right.data;
}

// Оператор сравнения "меньше"
bool Node::operator<(const Node& right) {
	return this->data < right.data;
}

// Перегрузка оператора записи в файловый поток узла списка
std::fstream& operator<<(std::fstream& file, const Node& node) {
	// Записываем в файл позицию следующего элемента
	file.write(reinterpret_cast<const char*>(&node.next), sizeof(node.next));
	
	// Записываем в файл объект
	file << node.data;

	// Возвращаем файловый поток для продолжения операций над ним
	return file;
}

// Перегрузка оператора чтения из файлового потока узла списка
std::fstream& operator>>(std::fstream& file, Node& node) {
	// Читаем из файла позицию следующего элемента
	file.read(reinterpret_cast<char*>(&node.next), sizeof(node.next));

	// Читаем из файла объект
	file >> node.data;

	// Возвращаем файловый поток для продолжения операций над ним
	return file;
}
