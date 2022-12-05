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
void List::insert(Product& _data) {
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
void List::insert(Product& _data, size_t index) {
	// ���� ������ ������ ��� ������ ������ ������� ������
	// �� ����������� ����� ��� ������� � ����� ������
	if (size == 0 || index + 1 > size) {
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

	// ������� �� ��������, ����������� ����� ������
	Node* tail = head;
	for (size_t i = 0; i + 1 < index; i++) { // �������� ������� �����
		tail = tail->next;
	}

	// ��������� ����� ������� �� ������ �����, ������������ ���������
	Node* temp = new Node(_data);
	temp->next = tail->next;
	temp->prev = tail;
	tail->next->prev = temp;
	tail->next = temp;
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
	Node* temp = last;
	last = last->prev;
	delete temp;
	size--;
}

// �������� �������� �� �������
void List::remove(size_t index) {
	// ���� ������ ������ ��� ������ � ����� ���������
	// ���������� ����� �������� �������� � ����� ������
	if (size == 0 || size == 1) {
		this->remove();
		return;
	}

	// �������� ������� ��������
	if (index == 1) {
		Node* temp = head->next;
		delete head;
		head = temp;
		size--;

		// ������������ ��������� ��� ���������� �����������
		Node* tail = head;
		for (size_t i = 1; i < size; i++)
		{
			tail = tail->next;
		}

		tail->next = head;
		return;
	}

	// ������� �� index-1 ��������
	Node* tail = head;
	for (size_t i = 1; i + 1 < index; i++)
	{
		tail = tail->next;
	}

	Node* temp = tail->next->next;
	delete tail->next;
	tail->next = temp;
	size--;
}

// ����� �������� �� ���� ����� ����
Product* List::find() const {

}

// ����� �������� �� �������
Product* List::find(size_t index) const {
	// ���� ������ ���� - ���������� ������ nullptr
	if (size == 0) {
		return nullptr;
	}

	// ���� ������ ������ ������� ������, ���������� ��������� �������
	if (index + 1 > size) {
		return &(last->data);
	}

	// ������� �� ������� �������� � ���������� ���
	Node* tail = head;
	for (size_t i = 0; i < index; i++) { // ���������, ������������ �������� ������
		tail = tail->next;
	}

	return &(tail->data);
}

// ����� ������
void List::output() const {
	// ���� ������ ������ - �������� � �������
	if (size == 0) {
		std::cout << "List is empty" << std::endl;
		return;
	}

	// ������� �������� ������
	std::cout << "List:" << std::endl;
	Node* tail = head;
	for (size_t i = 0; i < size; i++) { // ����� �������� �� ������ tail != last
		std::cout << "#" << i << " ";
		tail->data.output();
		tail = tail->next;
	}
}

size_t List::getSize() const {
	return size;
}