#include "List.h"

// 
List::List()
	: head(nullptr), last(nullptr), size(0) {
}

// 
List::~List() {
	// ���� ������ ������ - �������
	if (size == 0) {
		return;
	}

	// ������� ������
	for (uint i = 0; i < size; i++) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

// ������� � ����� ������
void List::insert(Train& _train) {
	// ���� ������ ��� ������ - ��������� ������ �������
	if (size == 0) {
		head = new Node(_train);
		last = head;
		size++;
		return;
	}

	// ��������� ����� ������� � �����
	last->next = new Node(_train);
	last = last->next;
	size++;
}

// ������� � ������ �� �������
void List::insert(Train& _train, uint index) {
	// ���� ������ ������ ��� ������ ������/����� ������� ������
	// �� ����������� ����� ��� ������� � ����� ������
	if (size == 0 || index + 1 >= size) {
		this->insert(_train);
		return;
	}

	// ������� �� ������ �������
	if (index == 0) {
		Node* temp = head;
		head = new Node(_train);
		head->next = temp;
		size++;
		return;
	}

	// ������� �� ��������, ����������� ����� ������
	Node* tail = head;
	for (uint i = 0; i + 1 < index; i++) {
		tail = tail->next;
	}

	// ��������� ����� ������� �� ������ �����
	Node* temp = tail->next;
	tail->next = new Node(_train);
	tail->next->next = temp;
	size++;
}


// ����� ������
void List::print() {
	// ���� ������ ������ - �������� � �������
	if (size == 0) {
		cout << "List is empty" << std::endl;
		return;
	}

	// ������� ��� �������� ������
	Node* tail = head;
	std::cout << "List:" << std::endl;
	for (uint i = 0; i < size; i++) {
		cout << "Element" << i << " ";
		tail->train.print();
		cout << endl;
		tail = tail->next;
	}
}