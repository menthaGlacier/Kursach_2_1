#include "List.h"

// 
List::List()
	: head(nullptr), last(nullptr), size(0) {
}

// 
List::~List() {
	// Если список пустой - выходим
	if (size == 0) {
		return;
	}

	// Очищаем список
	for (uint i = 0; i < size; i++) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

// Вставка в конец списка
void List::insert(Train& _train) {
	// Если список был пустым - вставляем первый элемент
	if (size == 0) {
		head = new Node(_train);
		last = head;
		size++;
		return;
	}

	// Вставляем новый элемент в конец
	last->next = new Node(_train);
	last = last->next;
	size++;
}

// Вставка в список по индексу
void List::insert(Train& _train, uint index) {
	// Если список пустой или индекс больше/равен размеру списка
	// то исплользуем метод для вставки в конец списка
	if (size == 0 || index + 1 >= size) {
		this->insert(_train);
		return;
	}

	// Вставка на первую позицию
	if (index == 0) {
		Node* temp = head;
		head = new Node(_train);
		head->next = temp;
		size++;
		return;
	}

	// Доходим до элемента, предыдущего перед нужным
	Node* tail = head;
	for (uint i = 0; i + 1 < index; i++) {
		tail = tail->next;
	}

	// Вставляем новый элемент на нужное место
	Node* temp = tail->next;
	tail->next = new Node(_train);
	tail->next->next = temp;
	size++;
}


// Вывод списка
void List::print() {
	// Если список пустой - сообщаем и выходим
	if (size == 0) {
		cout << "List is empty" << std::endl;
		return;
	}

	// Выводим все элементы списка
	Node* tail = head;
	std::cout << "List:" << std::endl;
	for (uint i = 0; i < size; i++) {
		cout << "Element" << i << " ";
		tail->train.print();
		cout << endl;
		tail = tail->next;
	}
}