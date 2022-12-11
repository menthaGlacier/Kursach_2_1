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
	if (size == 0 || index >= size) {
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

// Поиск элемента по разным полям через меню
Train* find() {
	cout << "Select the field you want to find element by:" << endl;
	cout << "1 - Train number" << endl << "2 - Working day of weeks" << endl
		<< "3 - Departure time" << endl << "4 - Travel time" << endl
		<< "5 - Departure station" << endl << "6 - Destination station" << endl
		<< "7 - Transit stations" << endl;
	// TODO
	return nullptr; // DEBUG!!!

}

// Упорядочивание списка
void List::order() {
	// Используем пузырьковую сортировку
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

// Вывод списка
void List::print() {
	// Если список пустой - сообщаем и выходим
	if (size == 0) {
		cout << "List is empty" << endl;
		return;
	}

	// Выводим все элементы списка
	Node* tail = head;
	cout << "List:" << endl;
	for (uint i = 0; i < size; i++) {
		cout << "Element - " << i << "." << endl;
		tail->train->print();
		cout << endl;
		tail = tail->next;
	}
}

// Сохранение списка в бинарном файле
bool List::save(const char* fileName) {
	// Открываем файл в режиме бинарной записи и проверяем его
	fstream file(fileName, ios::out | ios::binary);
	if (!file.is_open()) {
		cout << "Fail to open file" << endl;
		return false;
	}

	// Пишем в файл до конца списка или до ошибки
	Node* tail = head;
	while (tail != nullptr && !file.fail()) {
		file << *(tail->train);
		tail = tail->next;
	}

	file.close();

	// Сообщаем о ошибке, если она произошла
	if (file.fail()) {
		cout << "Fail to write to file" << endl;
		return false;
	}

	return true;
}

// Загрузка списка из бинарного файла
bool List::load(const char* fileName) {
	// Открываем файл в режиме бинарного чтения и проверяем его
	fstream file(fileName, ios::in | ios::binary);
	if (!file.is_open()) {
		cout << "Fail to open file" << endl;
		return false;
	}

	// Очищаем список
	while (size != 0) {
		remove();
	}

	// Читаем файл до конца
	while(file.peek() != EOF) {
		Train readTrain;
		file >> readTrain;
		
		// Если была получена ошибка при чтении, завершаем программу
		if (file.fail()) {
			cout << "Fail to read from file" << endl;
			exit(-1);
		} else { // Иначе вставляем в элемент в список
			insert(readTrain);
		}
	}
}