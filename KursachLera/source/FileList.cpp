#include "../include/FileList.h"

// Конструктор по параметрам для списка, где параметр - название файла
FileList::FileList(const std::string& name) {
	this->name = name;
	this->size = 0;
	this->first = 0;

	// Открываем/создаем файл с заданными именем
	openFile(name);

	// Читаем из файла размер списка и позицию первого узла
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	file.read(reinterpret_cast<char*>(&first), sizeof(first));
}

// Деструктор
FileList::~FileList() {
	// Закрываем файл, если он открыт
	if (file.is_open()) {
		file.close();
	}
}

// Открытие файла
void FileList::openFile(const std::string& name) {
	// Открываем файл с заданным именем в режиме бинарного файла для чтения и записи
	file.open(name, std::ios::binary | std::ios::in | std::ios::out);

	// Если файл не открылся, он, вероятно, не создан
	if (!file.is_open()) {
		// Создаем файл и открываем его для работы
		createFile(name);
		file.open(name, std::ios::binary | std::ios::in | std::ios::out);
	}
}

// Создание файла с заданным именем
void FileList::createFile(const std::string& name) {
	// Открытие в режими записи, если файла не существует, создаст его
	file.open(name, std::ios::binary | std::ios::out);
	if (!file.is_open()) {
		std::cout << "Не удалось создать файл" << std::endl;
		exit(0); // Завершаем программу
	}

	// Записываем в файл размер списка и позицию первого узла
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	file.write(reinterpret_cast<const char*>(&first), sizeof(first));

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

	file.seekg(0, std::ios::end); // Переходим в конец файла
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
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	file.write(reinterpret_cast<const char*>(&first), sizeof(first));

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
		file.seekg(0, std::ios::end); // Переходим в конец файла
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
		
		file.seekg(0, std::ios::end); // Переходим в конец файла
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
	file.write(reinterpret_cast<const char*>(&size), sizeof(size));
	file.write(reinterpret_cast<const char*>(&first), sizeof(first));
}

//
void FileList::remove() {
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
		std::remove(name.c_str()); // Удаляем его
		openFile(name); // Создаем и открываем новый файл
		
		return;
	}

	//
	std::fstream newList("new", std::ios::binary | std::ios::out);
	if (!newList.is_open()) {
		std::cout << "Не удалось создать файл" << std::endl;
		exit(0); // Завершаем программу
	}

	// Записываем в новый файл размер списка и позицию первого узла
	newList.write((const char*)(&size), sizeof(size));
	newList.write((const char*)(&first), sizeof(first));

	// Переходим в конец нового файла для записи узлов
	newList.seekg(0, std::ios::end);
	file.clear(); //FIXME

	file.seekg(first);
	insertPosition = newList.tellg();
	first = insertPosition;
	file >> insert;
	newList << insert;

	//
	for (unsigned int i = 0; i < size + 1; i++) {
		tailPosition = insertPosition;
		tail = insert;
		file.seekg(0, std::ios::end);
		insertPosition = newList.tellg();
		file >> insert;
		
	}

	// LOL SAID ME
	// LMAO
	// FIXME FINISH THIS!!!!
}

// Поиск всех поездов, следующих до станции
void FileList::find(unsigned int station) {
	Node tail; // Хвост для обхода списка

	std::cout << "Все поезда следующие до станции " << station << ":" << std::endl;
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

//
void FileList::print() {
	Node tail; // Хвост для обхода списка

	std::cout << "Движение поездов:" << std::endl;
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
