#include "../include/FileList.h"

// Конструктор по параметрам для списка, где параметр - название файла
FileList::FileList(const string& name) {
	this->name = name;
	this->size = 0;
	this->first = 0;

	// Открываем/создаем файл с заданными именем
	openFile(name);

	// Читаем из файла размер списка и позицию первого узла
	file.read((char*)(&size), sizeof(size));
	file.read((char*)(&first), sizeof(first));
}

// Деструктор
FileList::~FileList() {
	// Закрываем файл, если он открыт
	if (file.is_open()) {
		file.close();
	}
}

// Открытие файла
void FileList::openFile(const string& name) {
	// Открываем файл с заданным именем в режиме бинарного файла для чтения и записи
	file.open(name, ios::binary | ios::in | ios::out);

	// Если файл не открылся, он, вероятно, не создан
	if (!file.is_open()) {
		// Создаем файл и открываем его для работы
		createFile(name);
		file.open(name, ios::binary | ios::in | ios::out);
	}
}

// Создание файла с заданным именем
void FileList::createFile(const string& name) {
	// Открытие в режими записи, если файла не существует, создаст его
	file.open(name, ios::binary | ios::out);
	if (!file.is_open()) {
		cout << "Не удалось создать файл" << endl;
		exit(0); // Завершаем программу
	}

	// Записываем в файл размер списка и позицию первого узла
	file.write((const char*)(&size), sizeof(size));
	file.write((const char*)(&first), sizeof(first));

	// Закрываем созданный файл для продолжения работы
	file.close();
}

// Вставка в конец списка
void FileList::insert(const Train& data) {
	// Временные переменные для хранения хвоста списка и его позиции
	Node tail;
	long long int tailPosition = -1;

	Node insert; // Новый узел, который мы будем вставлять
	long long int insertPosition = -1;
	insert.setNext(-1); // Следующего узла нет
	insert.setData(data); // Присваиваем объект

	// Если список пуст
	if (size == 0) {
		// Первый узел будет находиться после записей размера и позиции первого узла
		first = sizeof(size) + sizeof(first);
		file.seekg(first);
	} else {
		// Переходим на первый узел
		file.seekg(first);

		// Доходим до конца списка
		while (tail.getNext() != -1) {
			tailPosition = file.tellg(); // Сохраняем позицию начала очередного узла
			file >> tail; // Читаем очередной узел
			file.seekg(tail.getNext()); // Переходим на следующий узел
		}
	}

	// Очищаем поток от флага конца файла
	file.clear();

	file.seekg(0, ios::end); // Переходим в конец файла
	insertPosition = file.tellg(); // Сохраняем позицию нового узла
	file << insert; // Вставляем новый узел

	// Если список не был пуст
	if (tailPosition != -1) {
		// Переходим на хвост списка и перезаписываем указатель на позицию следующего узла
		file.seekg(tailPosition);
		tail.setNext(insertPosition);
		file << tail;
	}

	// Увеличиваем размер списка на единицу
	size++;

	// Переходим в начало файла и перезаписываем размер и позицию первого узла
	file.seekg(0);
	file.write((const char*)(&size), sizeof(size));
	file.write((const char*)(&first), sizeof(first));

	file.clear();
}

void FileList::insert(const Train& data, unsigned int index) {
	// Временные переменные для хранения хвоста списка и его позиции
	Node tail;
	long long int tailPosition = -1;

	Node insert; // Новый узел, который мы будем вставлять
	long long int insertPosition = -1;
	insert.setNext(-1); // Следующего узел неизвестен
	insert.setData(data); // Присваиваем объект

	// Если список пуст, либо индекс больше размера, вставляем в конец списка
	if (size == 0 || index >= size) {
		// Используем существующий метод вставки в конец и завершаем работу метода
		this->insert(data);
		return;
	}

	// Обрабатываем вставку на позицию первого узла
	if (index == 0) {
		file.seekg(first); // Переходим к текущему первому узлу
		tailPosition = file.tellg(); // Сохраняем его позицию
		insert.setNext(tailPosition); // Новый первый узел указывает на текущий
		file.seekg(0, ios::end); // Переходим в конец файла
		insertPosition = file.tellg(); // Сохраняем позицию для нового узла
		file << insert; // Записываем новый первый узел
		first = insertPosition; // Обновляем позицию первого узла
	} else {
		// Если вставка идёт на индекс 1, то хвостом будет первый узел
		if (index == 1) {
			file.seekg(first); // Переходим на первый узел
			tailPosition = file.tellg(); // Сохраняем позицию первого узла
			file >> tail; // Читаем первый узел
		} else {
			file.seekg(first); // Переходим на первый узел

			// Доходим до узла, предшествующего индексу позиции вставки
			for (unsigned int i = 0; i + 1 < index; i++) {
				tailPosition = file.tellg(); // Сохраняем позицию начала очередного узла
				file >> tail; // Читаем очередной узел
				file.seekg(tail.getNext()); // Переходим на следующий узел
			}
		}

		// Новый узел будет указывать на узел следующий за хвостом
		insert.setNext(tail.getNext());
		
		file.seekg(0, ios::end); // Переходим в конец файла
		insertPosition = file.tellg(); // Сохраняем позицию нового узла
		file << insert; // Вставляем новый узел

		file.clear(); // FIXME

		tail.setNext(insertPosition); // Хвост теперь указывает на новый узел
		file.seekg(tailPosition); // Переходим на позицию хвоста
		file << tail; // Перезаписываем хвост
	}

	file.clear(); // FIXME

	// Увеличиваем размер списка на единицу
	size++;

	// Переходим в начало файла и перезаписываем размер и позицию первого узла
	file.seekg(0);
	file.write((const char*)(&size), sizeof(size));
	file.write((const char*)(&first), sizeof(first));
}

// Удаление узла с конца списка (НЕ ЗАКОНЧЕНО)
void FileList::deletion() {
	// Временные переменные для хранения хвоста списка и его позиции
	Node tail;
	long long int tailPosition = -1;

	Node insert; // Узел для вставки
	long long int insertPosition = -1;
	insert.setNext(-1);
	
	// Если список пуст, удаление не может быть осуществленно
	if (size == 0) {
		return;
	}

	// Если размер списка 1, удаление будет равноценно созданию нового пустого списка
	if (size == 1) {
		// Зануляем переменные
		size = 0;
		first = 0;

		// Производим создание нового файла с идентичным именем
		file.close(); // Закрываем текущий файл
		remove(name.c_str()); // Удаляем его
		openFile(name); // Создаем и открываем новый файл
		
		return;
	}

	// Создаем новый файл для списка, в который будет перемещен текущий
	fstream newList("new", ios::binary | ios::out);
	if (!newList.is_open()) {
		cout << "Не удалось создать файл" << endl;
		exit(0); // Завершаем программу
	}

	// Записываем в новый файл размер списка и позицию первого узла
	newList.write((const char*)(&size), sizeof(size));
	newList.write((const char*)(&first), sizeof(first));

	// Переходим в конец нового файла для записи узлов
	newList.seekg(0, ios::end);
	file.clear(); //FIXME

	file.seekg(first);
	insertPosition = newList.tellg();
	first = insertPosition;
	file >> insert;
	newList << insert;

	// да треш
	for (unsigned int i = 0; i < size + 1; i++) {
		tailPosition = insertPosition;
		tail = insert;
		file.seekg(0, ios::end);
		insertPosition = newList.tellg();
		file >> insert;
		
	}

	// FIXME ЗАКОНЧИТЬ!!!!
}

// Удаление узла по логическому номеру
void FileList::deletion(unsigned int index) {
	// начать и доделать лол
}

// Обновить объект узла
void FileList::update(const Train& data, unsigned int index) {
	// Временные переменные для хранения хвоста списка и его позиции
	Node tail;
	long long int tailPosition = -1;

	Node insert; // Новый узел, который мы будем вставлять
	long long int insertPosition = -1;
	insert.setNext(-1); // Следующего узел неизвестен

	// Логический номер не может быть больше размера списка
	if (index >= size) {
		cout << "Недопустимый логический номер" << endl;
		return;
	}

	file.seekg(first); // Переходим на начало списка

	// Если в списке только один узел, или надо обновить только первый, сразу перезаписываем его
	if (size == 1 || index == 0) {
		file >> insert;
		file.seekg(0, ios::end); // Переходим в конец файла
		insertPosition = file.tellg(); // Запоминаем позицию узла
		first = insertPosition; // Обновляем указатель на позицию первого узла
		insert.setData(data); // Присваиваем узлу объект
		file << insert; // Вставляем обновленный узел в конец файла
		
		// Переходим в начало файла и перезаписываем позицию первого узла
		file.seekg(0);
		file.write((const char*)(&size), sizeof(size));
		file.write((const char*)(&first), sizeof(first));
		return;
	}

	// Обрабатываем обновление второго узла
	if (index == 1) {
		file.seekg(first);
		tailPosition = file.tellg();
		file >> tail;
	} else {
		// Доходим до узла, предшествующего индексу позиции узла для обновления
		for (unsigned int i = 0; i + 1 < index; i++) {
			tailPosition = file.tellg(); // Сохраняем позицию начала очередного узла
			file >> tail; // Читаем очередной узел
			file.seekg(tail.getNext()); // Переходим на следующий узел
		}
	}

	file.seekg(tail.getNext()); // Переходим к изначальной версии объекта
	file >> insert; // Сохраняем данные, в том числе указатель на следующий узел
	insert.setData(data); // Присваиваем узлу объект
	file.seekg(0, ios::end); // Переходим в конец файла для записи
	insertPosition = file.tellg(); // Запоминаем позицию узла
	file << insert; // Вставляем обновленный объект в конец файла
	file.seekg(tailPosition); // Переходим на предыдущий элемент
	tail.setNext(insertPosition); // Обновляем указатель на следующий узел
	file << tail; // Перезаписываем узел
}

// Сортировка списка
void FileList::sort() {
	// начать и доделать часть 2 лол
}

// Поиск всех поездов, следующих до станции
void FileList::find(unsigned int station) {
	Node tail; // Хвост для обхода списка

	cout << "Все поезда следующие до станции " << station << ":" << endl;
	if (size == 0) {
		return;
	}

	file.seekg(first); // Переходим к первому узлу
	while (tail.getNext() != -1) {
		file >> tail;
		if (tail.getData().getDestinationStationNumber() == station) {
			tail.getData().print();
		}

		file.seekg(tail.getNext());
	}

	file.clear();
}

// Вывод списка
void FileList::print() {
	Node tail; // Хвост для обхода списка

	cout << "Движение поездов:" << endl;
	if (size == 0) {
		return;
	}

	file.seekg(first); // Переходим к первому узлу
	while (tail.getNext() != -1) {
		file >> tail;
		tail.getData().print();
		file.seekg(tail.getNext());
	}

	file.clear();
}

// Постраничный просмотр списка
void pageViewPrint() {

}
