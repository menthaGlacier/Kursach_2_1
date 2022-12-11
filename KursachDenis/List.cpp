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
	if (size == 0 || index >= size) {
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

	// Доходим до нужного места
	Node* tail = head->next;
	for (size_t i = 1; i < index; i++) {
		tail = tail->next;
	}

	// Вставляем новый элемент на нужное место, перевязываем указатели
	Node* temp = new Node(_data);
	temp->next = tail;
	temp->prev = tail->prev;
	tail->prev->next = temp;
	tail->prev = temp;
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
	last = last->prev;
	delete last->next;
	last->next = nullptr;
	size--;
}

// Удаление элемента по индексу
void List::remove(size_t index) {
	// Если список пустой, только с одним элементом, либо индекс больше/равен
	// индексу последнего элемента списка,
	// используем метод удаления элемента в конце списка
	if (size <= 1 || index >= size - 1) {
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

	// Доходим до нужного элемента
	Node* tail = head->next;
	for (size_t i = 1; i < index; i++) {
		tail = tail->next;
	}

	// Удаляем элемент на нужном месте, перевязываем указатели
	tail->next->prev = tail->prev;
	tail->prev->next= tail->next;
	delete tail;
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

void List::sort(ProductFieldName field, bool reverse) {
	if (!head) { return; }

	Node* new_head = nullptr,
		* new_last = nullptr,	
		* begin = head;

	while (begin != nullptr) {
		Node* compared = begin,
		* current = begin->next;

		while (current != nullptr)	{
			bool do_swap = false;
			switch (field) {
			case ProductFieldName::Name: {
				if (current->data->getName() < compared->data->getName())
					do_swap = true;
				break;
			}
			case ProductFieldName::Category: {
				if (current->data->getCategory() < compared->data->getCategory())
					do_swap = true;
				break;
			}
			case ProductFieldName::Quantity: {
				if (current->data->getQuantity() < compared->data->getQuantity())
					do_swap = true;
				break;
			}
			case ProductFieldName::Price: {
				if (current->data->getPrice() < compared->data->getPrice())
					do_swap = true;
				break;
			}
			case ProductFieldName::Percentage: {
				if (current->data->getPercentage() < compared->data->getPercentage())
					do_swap = true;
				break;
			}
			case ProductFieldName::Date: {
				if (current->data->getYear() < compared->data->getYear())
					do_swap = true;
				else if (current->data->getYear() == compared->data->getYear())
					if (current->data->getMonth() < compared->data->getMonth())
						do_swap = true;
					else if (current->data->getMonth() == compared->data->getMonth())
						if (current->data->getDay() < compared->data->getDay())
							do_swap = true;
				break;
			}
			}

			if (do_swap && !reverse || !do_swap && reverse) {
				compared = current;
			}
			current = current->next;
		}

		if (compared == begin) {
			begin = begin->next;
			if (begin) begin->prev = nullptr;
		}	
		else {
			compared->prev->next = compared->next;
			if (compared->next) compared->next->prev = compared->prev;
		}

		compared->prev = new_last;
		compared->next = nullptr;
		if (new_last != nullptr)	{ new_last->next = compared; }
		else { new_head = compared; }
		new_last = compared;	
	}

	head = new_head;	
	last = new_last;
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
		std::cout << "\n--------------------------------------" << std::endl;
		tail = tail->next;
	}
}

size_t List::getSize() const {
	return size;
}