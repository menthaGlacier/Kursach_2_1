#include "List.h"

// Конструктор по умолчанию
List::List()
	: head(nullptr), last(nullptr), size(0) {
}

// Деструктор
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
	// Если список пуст или индекс больше или равен размеру списка
	// то используем метод вставки в конец списка
	if (size == 0 || index + 1 >= size) {
		insert(_train);
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

// Вставка с сохранением порядка
void List::insertOrdered(Train& _train) {
	// Вставляем элемент в конец
	insert(_train);

	// Сортируем список
	sort();
}

// Удаление с конца списка
void List::remove() {
	// Выходим при пустом списке
	if (size == 0) {
		return;
	}

	// Удаляем первый элемент, если он единственный
	if (size == 1) {
		delete head;
		head = nullptr;
		size--;
		return;
	}

	// Доходим до предпоследнего элемента
	Node* tail = head;
	while (tail->next != last) {
		tail = tail->next;
	}

	// Удаляем последний элемент
	tail->next = nullptr;
	delete last;
	last = tail;
	size--;
}

// Удаление по индексу
void List::remove(uint index) {
	// Если список пуст, список имеет один элемент, либо индекс больше
	// или равен размеру списка то используем метод удаления с конца списка
	if (size == 0 || size == 1 || index + 1 >= size) {
		remove();
		return;
	}

	// Удаление с первой позиции
	if (index == 0) {
		// Удаляем первый элемент
		Node* temp = head->next;
		delete head;
		head = temp;
		size--;
		return;
	}

	// Доходим до элемента, предыдущего перед нужным
	Node* tail = head;
	for (uint i = 0; i + 1 < index; i++) {
		tail = tail->next;
	}

	// Удаляем элемент
	Node* temp = tail->next->next;
	delete tail->next;
	tail->next = temp;
	size--;
}

void List::sort() {

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