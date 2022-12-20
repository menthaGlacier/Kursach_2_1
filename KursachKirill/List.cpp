#include "List.h"

// ����������� �� ���������
List::List()
	: head(nullptr), last(nullptr), size(0) {
}

// ����������
List::~List() {
	// ���� ������ ������ - �������
	if (size == 0) {
		return;
	}

	// ������� ������
	//for (uint i = 0; i < size; i++) {
	//	Node* temp = head;
	//	head = head->next;
	//	delete temp;
	//}

	for (List::Iterator it = begin(); it != end(); it++) {
		Node* temp = *it;
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
	// ���� ������ ���� ��� ������ ������ ��� ����� ������� ������
	// �� ���������� ����� ������� � ����� ������
	if (size == 0 || index >= size) {
		insert(_train);
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

// ������� � ����������� �������
void List::insertOrdered(Train& _train) {
	// ��������� ������� � �����
	insert(_train);

	// ��������� ������
	order();
}

// �������� � ����� ������
void List::remove() {
	// ������� ��� ������ ������
	if (size == 0) {
		return;
	}

	// ������� ������ �������, ���� �� ������������
	if (size == 1) {
		delete head;
		head = nullptr;
		size--;
		return;
	}

	// ������� �� �������������� ��������
	Node* tail = head;
	while (tail->next != last) {
		tail = tail->next;
	}

	// ������� ��������� �������
	tail->next = nullptr;
	delete last;
	last = tail;
	size--;
}

// �������� �� �������
void List::remove(uint index) {
	// ���� ������ ����, ������ ����� ���� �������, ���� ������ ������
	// ��� ����� ������� ������ �� ���������� ����� �������� � ����� ������
	if (size == 0 || size == 1 || index + 1 >= size) {
		remove();
		return;
	}

	// �������� � ������ �������
	if (index == 0) {
		// ������� ������ �������
		Node* temp = head->next;
		delete head;
		head = temp;
		size--;
		return;
	}

	// ������� �� ��������, ����������� ����� ������
	Node* tail = head;
	for (uint i = 0; i + 1 < index; i++) {
		tail = tail->next;
	}

	// ������� �������
	Node* temp = tail->next->next;
	delete tail->next;
	tail->next = temp;
	size--;
}

// ����� ��������� �� ������� ����������
void List::search(uint station) {
	cout << "Search:" << endl;
	//Node* tail = head;
	//for (uint i = 0; i < size; i++) {
	//	if (tail->train->getStop() == station) {
	//		cout << "Found at position " << i << endl;
	//		tail->train->print();
	//	}
	//	
	//	tail = tail->next;
	//}

	for (List::Iterator it = begin(); it != end(); it++) {
		if ((*it)->train->getStop() == station) {
			cout << "Found at position " << it.getPos() << endl;
			(*it)->train->print();
			cout << endl;
		}
	}
}

// �������������� ������
void List::order() {
	// ���������� ����������� ����������
	for (uint i = 0; i < size; i++) {
		Node* tail = head;
		for (uint j = i + 1; j < size; j++) {
			if (tail->train > tail->next->train) {
				Node* temp = tail->next;
				tail->next = temp->next;
				temp->next = tail;
				if (tail == head) {
					head = temp;
				}

				tail = temp;
			}

			tail = tail->next;
		}
	}
}

// ����� ������
void List::print() {
	// ���� ������ ������ - �������� � �������
	if (size == 0) {
		cout << "List is empty" << endl;
		return;
	}

	// ������� ��� �������� ������
	//Node* tail = head;
	//cout << "List:" << endl;
	//for (uint i = 0; i < size; i++) {
	//	cout << "Element - " << i << "." << endl;
	//	tail->train->print();
	//	cout << endl;
	//	tail = tail->next;
	//}

	for (List::Iterator it = begin(); it != end(); it++) {
		cout << "Element " << it.getPos() << "." << endl;
		(*it)->train->print();
		cout << endl;
	}
}

// ���������� ������ � �������� �����
bool List::save(const char* fileName) {
	// ��������� ���� � ������ �������� ������ � ��������� ���
	fstream file(fileName, ios::out | ios::binary);
	if (!file.is_open()) {
		cout << "Fail to open file" << endl;
		return false;
	}

	// ����� � ���� �� ����� ������ ��� �� ������
	//Node* tail = head;
	//while (tail != nullptr && !file.fail()) {
	//	file << *(tail->train);
	//	tail = tail->next;
	//}

	for (List::Iterator it = begin(); it != end() && !file.fail(); it++) {
		file << (*it)->train;
	}

	file.close();

	// �������� � ������, ���� ��� ���������
	if (file.fail()) {
		cout << "Fail to write to file" << endl;
		return false;
	}

	return true;
}

// �������� ������ �� ��������� �����
bool List::load(const char* fileName) {
	// ��������� ���� � ������ ��������� ������ � ��������� ���
	fstream file(fileName, ios::in | ios::binary);
	if (!file.is_open()) {
		cout << "Fail to open file" << endl;
		return false;
	}

	// ������� ������
	while (size != 0) {
		remove();
	}

	// ������ ���� �� �����
	while(file.peek() != EOF) {
		Train readTrain;
		file >> readTrain;
		
		// ���� ���� �������� ������ ��� ������, ��������� ���������
		if (file.fail()) {
			cout << "Fail to read from file" << endl;
			exit(-1);
		} else { // ����� ��������� � ������� � ������
			insert(readTrain);
		}
	}

	return true;
}

// ��������� ������� ������
uint List::getSize() {
	return size;
}

// ����������� �� ����������
List::Iterator::Iterator(List& _list, uint _pos)
	: itrList(_list), curNode(nullptr), pos(_pos) {
	// ���� ������� ������ ��� ����� �������, �������� �������� �� ������� � ����� ���������� �������� ������
	if (pos + 1 >= itrList.size) {
		pos = itrList.size;
		curNode = itrList.last->next;
	} else if (pos != 0) { // ����� ������ �� ������� ��������
		curNode = itrList.head;
		for (uint i = 0; i < pos; i++) {
			curNode = curNode->next;
		}
	} else { // ����� �������� ����� �� ������ �������� ������
		curNode = itrList.head;
	}
}

// ����������� �����������
List::Iterator::Iterator(const List::Iterator& other)
	: itrList(other.itrList), pos(other.pos) {
}

// �������� ������������
List::Iterator& List::Iterator::operator=(List::Iterator& other) {
	itrList = other.itrList;
	curNode = other.curNode;
	pos = other.pos;
	return *this;
}

// �������� �������������
Node* List::Iterator::operator*() {
	return curNode;
}

// ������������ ���������
List::Iterator& List::Iterator::operator++() {
	if (pos != itrList.size) {
		curNode = curNode->next;
		pos++;
	}

	return *this;
}

// ������������� ���������
List::Iterator List::Iterator::operator++(int) {
	Iterator temp(*this);
	++(*this);
	return temp;
}

// ��������� ��������
bool List::Iterator::operator==(const List::Iterator& other) {
	if ((&itrList == &(other.itrList))
		&& (curNode == other.curNode)
		&& (pos == other.pos)) {
		return true;
	} else {
		return false;
	}
}

// ��������� ����������
bool List::Iterator::operator!=(const List::Iterator& other) {
	return !(*this == other); // ����������� �������������� ��������
}

// �������� ������� ���������
uint List::Iterator::getPos() {
	return pos;
}

// ��������� ������ ������ ��� ���������
List::Iterator List::begin() {
	return List::Iterator(*this, 0);
}

// ��������� ����� ������ ��� ���������
List::Iterator List::end() {
	return List::Iterator(*this, this->size);
}