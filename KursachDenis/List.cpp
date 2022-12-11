#include "List.h"

// ����������� ������� ������
List::List()
	: head(nullptr), last(nullptr), size(0) {}

// ����������
List::~List() {
	// ���� ������ ������ - �������
	if (size == 0) {
		return;
	}

	// ������� ������
	for (size_t i = 0; i < size; i++) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

// ������� � ����� ������
void List::insert(const Product& _data) {
	// ���� ������ ��� ������ - ��������� ������ �������
	if (size == 0) {
		head = new Node(_data);
		last = head;
		size = 1;
		return;
	}

	// ��������� ����� ������� � �����, ������������ ���������
	last->next = new Node(_data);
	last->next->prev = last;
	last = last->next;
	size++;
}

// ������� � ������ �� �������
void List::insert(const Product& _data, size_t index) {
	// ���� ������ ������ ��� ������ ������/����� ������� ������,
	// �� ���������� ����� ��� ������� � ����� ������
	if (size == 0 || index >= size) {
		this->insert(_data);
		return;
	}

	// ������� �� ������ �������
	if (index == 0) {
		head->prev = new Node(_data);
		head->prev->next = head;
		head = head->prev;
		size++;
		return;
	}

	// ������� �� ������� �����
	Node* tail = head->next;
	for (size_t i = 1; i < index; i++) {
		tail = tail->next;
	}

	// ��������� ����� ������� �� ������ �����, ������������ ���������
	Node* temp = new Node(_data);
	temp->next = tail;
	temp->prev = tail->prev;
	tail->prev->next = temp;
	tail->prev = temp;
	size++;
}

// �������� �������� � ����� ������
void List::remove() {
	// ���� ������ ������ - �������
	if (size == 0) {
		return;
	}

	// ���� head - ��������� �������, ������ ������ ������
	if (size == 1) {
		delete head;
		head = nullptr;
		last = nullptr;
		size = 0;
		return;
	}

	// ������� ��������� �������
	last = last->prev;
	delete last->next;
	last->next = nullptr;
	size--;
}

// �������� �������� �� �������
void List::remove(size_t index) {
	// ���� ������ ������, ������ � ����� ���������, ���� ������ ������/�����
	// ������� ���������� �������� ������,
	// ���������� ����� �������� �������� � ����� ������
	if (size <= 1 || index >= size - 1) {
		this->remove();
		return;
	}

	// �������� ������� ��������
	if (index == 0) {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		size--;
		return;
	}

	// ������� �� ������� ��������
	Node* tail = head->next;
	for (size_t i = 1; i < index; i++) {
		tail = tail->next;
	}

	// ������� ������� �� ������ �����, ������������ ���������
	tail->next->prev = tail->prev;
	tail->prev->next= tail->next;
	delete tail;
	size--;
}

//// ����� �������� �� ���� ����� ����
//Product* List::find(ProductFieldName field) const {
//
//}

// ����� �������� �� �������
Product* List::find(size_t index) const {
	// ���� ������ ���� - ���������� ������ nullptr
	if (size == 0) {
		return nullptr;
	}

	// ���� ������ ������ ������� ������, ���������� ��������� �������
	if (index + 1 > size) {
		return (last->data);
	}

	// ������� �� ������� �������� � ���������� ���
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

// ����� ������
void List::output() const {
	// ���� ������ ������ - �������� � �������
	if (size == 0) {
		std::cout << "List is empty" << std::endl;
		return;
	}

	// ������� ��� �������� ������
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