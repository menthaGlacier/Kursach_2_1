#include "List.h"

// Конструктор пустого списка
List::List()
	: head(nullptr), last(nullptr), size(0) {}

// Деструктор
List::~List() {
	// Если список пустой - выходим
	if (size == 0) {
		return;
	}

	// Очищаем список
	for (size_t i = 0; i < size; i++) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

// Вставка в конец списка
void List::insert(const Product& _data) {
	// Если список был пустым - вставляем первый элемент
	if (size == 0) {
		head = new Node(_data);
		last = head;
		size = 1;
		return;
	}

	// Вставляем новый элемент в конец, перевязываем указатели
	last->next = new Node(_data);
	last->next->prev = last;
	last = last->next;
	size++;
}

// Вставка в список по индексу
void List::insert(const Product& _data, size_t index) {
	// Если список пустой или индекс больше/равен размеру списка,
	// то используем метод для вставки в конец списка
	if (size == 0 || index + 1 >= size) //TODO fails on index == -1{
		this->insert(_data);
		return;
	}

	// Вставка на первую позицию
	if (index == 0) {
		head->prev = new Node(_data);
		head->prev->next = head;
		head = head->prev;
		size++;
		return;
	}

	// Доходим до элемента, предыдущего перед нужным
	Node* tail = head;
	for (size_t i = 0; i + 1 < index; i++) {
		tail = tail->next;
	}

	// Вставляем новый элемент на нужное место, перевязываем указатели
	Node* temp = new Node(_data);
	temp->next = tail->next;
	temp->prev = tail;
	tail->next->prev = temp;
	tail->next = temp;
	size++;
}

// Удаление элемента с конца списка
void List::remove() {
	// Если список пустой - выходим
	if (size == 0) {
		return;
	}

	// Если head - последний элемент, делаем список пустым
	if (size == 1) {
		delete head;
		head = nullptr;
		last = nullptr;
		size = 0;
		return;
	}

	// Удаляем последний элемент
	Node* temp = last;
	last = last->prev;
	delete temp;
	size--;
}

// Удаление элемента по индексу
void List::remove(size_t index) {
	// Если список пустой, только с одним элементом, либо индекс больше/равен
	// размеру списка, используем метод удаления элемента в конце списка
	if (size == 0 || size == 1 || index + 1 >= size) {
		this->remove();
		return;
	}
	
	// Удаление первого элемента
	if (index == 0) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		size--;
		return;
	}

	// Доходим до элемента, предыдущего перед нужным
	Node* tail = head;
	for (size_t i = 0; i + 1 < index; i++) {
		tail = tail->next;
	}

	// Удаляем элемент на нужном месте, перевязываем указатели
	Node* temp = tail->next;
	tail->next = tail->next->next;
	tail->next->prev = tail;
	delete temp;
	size--;
}

//// Поиск элемента по полю через меню
//Product* List::find(ProductFieldName field) const {
//
//}

// Поиск элемента по индексу
Product* List::find(size_t index) const {
	// Если список пуст - возвращаем пустой nullptr
	if (size == 0) {
		return nullptr;
	}

	// Если индекс больше размера списка, возвращаем последний элемент
	if (index + 1 > size) {
		return (last->data);
	}

	// Доходим до нужного элемента и возвращаем его
	Node* tail = head;
	for (size_t i = 0; i < index; i++) {
		tail = tail->next;
	}

	return (tail->data);
}

// Вывод списка
void List::output() const {
	// Если список пустой - сообщаем и выходим
	if (size == 0) {
		std::cout << "List is empty" << std::endl;
		return;
	}

	// Выводим все элементы списка
	Node* tail = head;
	std::cout << "List:" << std::endl;
	for (size_t i = 0; i < size; i++) {
		std::cout << "#" << i << " ";
		tail->data->output();
		std::cout << "--------------------------------------" << std::endl;
		tail = tail->next;
	}
}

size_t List::getSize() const {
	return size;
}