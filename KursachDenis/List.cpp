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

void List::insort(ProductFieldName field, const Product& _data)
{
	if (size <= 1) {
		this->insert(_data);
		return;
	}

	bool reverse = false;
	switch (field) {
		case ProductFieldName::Name: {
			if (head->data->getName() > head->next->data->getName()) {
				reverse = true;
			}
			break;
		}
		case ProductFieldName::Category: {
			if (head->data->getCategory() > head->next->data->getCategory()) {
				reverse = true;
			}
			break;
		}
		case ProductFieldName::Quantity: {
			if (head->data->getQuantity() > head->next->data->getQuantity()) {
				reverse = true;
			}
			break;
		}
		case ProductFieldName::Price: {
			if (head->data->getPrice() > head->next->data->getPrice()) {
				reverse = true;
			}
			break;
		}
		case ProductFieldName::Percentage: {
			if (head->data->getPercentage() > head->next->data->getPercentage()) {
				reverse = true;
			}
			break;
		}
		case ProductFieldName::Date: {
			if (head->data->getYear() > head->next->data->getYear())
				reverse = true;
			else 	if (head->data->getYear() == head->next->data->getYear())
				if (head->data->getMonth() > head->next->data->getMonth())
					reverse = true;
				else if (head->data->getMonth() == head->next->data->getMonth())
					if (head->data->getDay() > head->next->data->getDay())
						reverse = true;
			break;
		}
	}

	Node* compared = head, * temp = new Node(_data);

	while (compared != nullptr) {
		bool found = false;
		switch (field) {
			case ProductFieldName::Name: {
				if (!reverse) {
					if (_data.getName() < compared->data->getName()) {
						found = true; }
				} else {
					if (_data.getName() > compared->data->getName()) {
						found = true; }
				}
				break;
			}
			case ProductFieldName::Category: {
				if (!reverse) {
					if (_data.getCategory() < compared->data->getCategory()) {
						found = true;
					}
				}
				else {
					if (_data.getCategory() > compared->data->getCategory()) {
						found = true;
					}
				}
				break;
			}
			case ProductFieldName::Quantity: {
				if (!reverse) {
					if (_data.getQuantity() < compared->data->getQuantity()) {
						found = true;
					}
				}
				else {
					if (_data.getQuantity() > compared->data->getQuantity()) {
						found = true;
					}
				}
				break;
			}
			case ProductFieldName::Price: {
				if (!reverse) {
					if (_data.getPrice() < compared->data->getPrice()) {
						found = true;
					}
				}
				else {
					if (_data.getPrice() > compared->data->getPrice()) {
						found = true;
					}
				}
				break;
			}
			case ProductFieldName::Percentage: {
				if (!reverse) {
					if (_data.getPercentage() < compared->data->getPercentage()) {
						found = true;
					}
				}
				else {
					if (_data.getPercentage() > compared->data->getPercentage()) {
						found = true;
					}
				}
				break;
			}
			case ProductFieldName::Date: {
				if (!reverse) {
					if (_data.getYear() < compared->data->getYear())
						found = true;
					else 	if (_data.getYear() == compared->data->getYear())
						if (_data.getMonth() < compared->data->getMonth())
							found = true;
						else if (_data.getMonth() == compared->data->getMonth())
							if (_data.getDay() < compared->data->getDay())
								found = true;
				} else {
					if (_data.getYear() > compared->data->getYear())
						found = true;
					else 	if (_data.getYear() == compared->data->getYear())
						if (_data.getMonth() > compared->data->getMonth())
							found = true;
						else if (_data.getMonth() == compared->data->getMonth())
							if (_data.getDay() > compared->data->getDay())
								found = true;
				}
				break;
			}
		}
		if (found) { break; }
		compared = compared->next;
	}

	if (compared != nullptr) {
		if (compared->prev) compared->prev->next = temp;
		temp->prev = compared->prev;
		temp->next = compared;
		compared->prev = temp;
		if (compared == head) head = temp;
	} else {
		last->next = temp;
		temp->prev = last;
		temp->next = nullptr;
		last = temp;
	}
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

// Поиск элемента по полю через меню
void List::find(ProductFieldName field, const Product& _data) const {
	Node* current = head;
	for (size_t i = 0; current != nullptr; i++, current = current->next) {
		switch (field) {
		case ProductFieldName::Name:
			if (current->data->getName() == _data.getName()) {
				std::cout << "#" << i << " ";
				current->data->output();
				std::cout << std::endl;
			}
			break;
		case ProductFieldName::Category:
			if (current->data->getCategory() == _data.getCategory()) {
				std::cout << "#" << i << " ";
				current->data->output();
				std::cout << std::endl;
			}
			break;
		case ProductFieldName::Quantity:
			if (current->data->getQuantity() == _data.getQuantity()) {
				std::cout << "#" << i << " ";
				current->data->output();
				std::cout << std::endl;
			}
			break;
		case ProductFieldName::Price:
			if (current->data->getPrice() == _data.getPrice()) {
				std::cout << "#" << i << " ";
				current->data->output();
				std::cout << std::endl;
			}
			break;
		case ProductFieldName::Percentage:
			if (current->data->getPercentage() == _data.getPercentage()) {
				std::cout << "#" << i << " ";
				current->data->output();
				std::cout << std::endl;
			}
			break;
		case ProductFieldName::Date:
			if ((current->data->getDay() == _data.getDay())
				&& (current->data->getMonth() == _data.getMonth())
				&& (current->data->getYear() == _data.getYear())) {
				std::cout << "#" << i << " ";
				current->data->output();
				std::cout << std::endl;
			}
			break;
		}

	}
}

// Поиск элемента по индексу
Product* List::find(size_t index) const {
	// Если список пуст - возвращаем пустой nullptr
	if (size == 0 || index >= size) {
		return nullptr;
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

bool List::save(const std::string& file_name)
{
	std::fstream file(file_name, std::ios::binary | std::ios::out);
	if (!file.is_open()) { return false; }

	for (Node* loading = head; loading != nullptr; loading = loading->next)
	{
		std::string str = loading->data->getName();
		size_t size_value = str.size();

		file.write(reinterpret_cast<const char*>(&size_value), sizeof(size_value));
		file.write(str.c_str(), size_value);

		str = loading->data->getCategory();
		size_value = str.size();

		file.write(reinterpret_cast<const char*>(&size_value), sizeof(size_value));
		file.write(str.c_str(), size_value);

		size_value = loading->data->getQuantity();
		file.write(reinterpret_cast<const char*>(&size_value), sizeof(size_value));

		size_value = loading->data->getDay();
		file.write(reinterpret_cast<const char*>(&size_value), sizeof(size_value));

		size_value = loading->data->getMonth();
		file.write(reinterpret_cast<const char*>(&size_value), sizeof(size_value));

		size_value = loading->data->getYear();
		file.write(reinterpret_cast<const char*>(&size_value), sizeof(size_value));

		double double_value = loading->data->getPrice();
		file.write(reinterpret_cast<const char*>(&double_value), sizeof(double_value));

		double_value = loading->data->getPercentage();
		file.write(reinterpret_cast<const char*>(&double_value), sizeof(double_value));
	}
	file.close();
	return true;
}

bool List::load(const std::string& file_name)
{
	std::fstream file(file_name, std::ios::binary | std::ios::in);
	if (!file.is_open()) { return false; }

	for (size_t i = 0; i < size; i++) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	size = 0;
	head = nullptr;
	last = nullptr;

	while(file.peek() != EOF && file.fail() != true)
	{
		std::string name, category;
		size_t quantity, day, month, year;
		size_t str_size;
		double price, percentage;

		file.read(reinterpret_cast<char*>(&str_size), sizeof(str_size));
		if (str_size > 0) {
			char* temp = new char[str_size];
			file.read(temp, str_size);
			name.assign(temp, str_size);
			delete[] temp;
		}

		file.read(reinterpret_cast<char*>(&str_size), sizeof(str_size));
		if (str_size > 0) {
			char* temp = new char[str_size];
			file.read(temp, str_size);
			category.assign(temp, str_size);
			delete[] temp;
		}

		file.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
		file.read(reinterpret_cast<char*>(&day), sizeof(day));
		file.read(reinterpret_cast<char*>(&month), sizeof(month));
		file.read(reinterpret_cast<char*>(&year), sizeof(year));
		file.read(reinterpret_cast<char*>(&price), sizeof(price));
		file.read(reinterpret_cast<char*>(&percentage), sizeof(percentage));
		
		if (file.fail() == true) {
			for (size_t i = 0; i < size; i++) {
				Node* temp = head;
				head = head->next;
				delete temp;
			}
			size = 0;
			head = nullptr;
			last = nullptr;
			return false;
		}
		if (last) {
			last->next = new Node(Product(name, category, quantity, price, percentage, day, month, year));
			last->next->prev = last;
			last = last->next;
		}
		else {
			last = new Node(Product(name, category, quantity, price, percentage, day, month, year));
			head = last;
		}
		size++;
	}

	file.close();
	return true;
}

size_t List::getSize() const {
	return size;
}