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
		// Первый узел будет находиться в конце списка
		file.seekg(0, ios::end);
		first = file.tellg();
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
	file.seekg(0, ios::beg);
	file.write((const char*)(&size), sizeof(size));
	file.write((const char*)(&first), sizeof(first));

	file.flush();
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

		file.clear();

		tail.setNext(insertPosition); // Хвост теперь указывает на новый узел
		file.seekg(tailPosition); // Переходим на позицию хвоста
		file << tail; // Перезаписываем хвост
	}

	file.clear();

	// Увеличиваем размер списка на единицу
	size++;

	// Переходим в начало файла и перезаписываем размер и позицию первого узла
	file.seekg(0, ios::beg);
	file.write((const char*)(&size), sizeof(size));
	file.write((const char*)(&first), sizeof(first));
	file.flush();
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

	// Переходим в начало оригинального файла для чтения узлов
	file.seekg(first);
	
	// Переходим в конец нового файла для записи узлов
	newList.seekg(0, ios::end);

	// Переходим к первому узлу и сразу его записываем
	insertPosition = newList.tellg();
	first = insertPosition;
	file >> insert;
	newList << insert;

	// Читаем до конца списка
	while (true) {
		// Перекидываем узел записи в хвост
		tailPosition = insertPosition;
		tail = insert;

		// Переходим на следующий узел в файле чтения и в конец в файле записи
		file.seekg(tail.getNext());
		newList.seekg(0, ios::end);

		// Сохраняем позицию для записи и читаем очередной узел
		insertPosition = newList.tellg();
		file >> insert;

		// Если новый узел был конечным, пропускаем его запись и делаем
		// хвост последним узлом списка
		if (insert.getNext() == -1) {
			tail.setNext(-1);
			newList.seekg(tailPosition);
			newList << tail;
			break;
		}

		// Пишем в новый файл очередной узел
		newList << insert;

		// Перезаписываем хвост, чтобы он указывал на новый узел
		tail.setNext(insertPosition);
		newList.seekg(tailPosition);
		newList << tail;
	}

	file.clear();
	newList.clear();

	size--; // Размер списка уменьшается на единицу

	// Переходим в начало файла и перезаписываем размер и позицию первого узла
	newList.seekg(0, ios::beg);
	newList.write((const char*)(&size), sizeof(size));
	newList.write((const char*)(&first), sizeof(first));

	newList.clear();
	newList.flush();

	// Закрываем предыдущий и новый файл
	file.close();
	newList.close();

	// Удаляем старый файл и переименовываем новый в имя старого файла
	remove(name.c_str());
	rename("new", name.c_str());

	// Открываем новый файл для дальнейшей работы с ним
	file.open(name, ios::binary | ios::in | ios::out);
}

// Удаление узла по логическому номеру
void FileList::deletion(unsigned int index) {
	// Временные переменные для хранения хвоста списка и его позиции
	Node tail;
	long long int tailPosition = -1;

	Node insert; // Узел для вставки
	long long int insertPosition = -1;
	insert.setNext(-1);
	
	// Если список пуст, имеет размер 1 или индекс больше или равен размеру списка
	// используем существующий метод удаление с конца для обработки этих случаев
	if (size == 0 || size == 1 || index + 1 >= size) {
		this->deletion();
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

	// Переходим в начало оригинального файла для чтения узлов
	file.seekg(first);
	
	// Переходим в конец нового файла для записи узлов
	newList.seekg(0, ios::end);

	// Переходим к первому узлу и сразу его записываем
	insertPosition = newList.tellg();
	first = insertPosition;
	file >> insert;
	
	// Если удаляется первый узел, пропускаем его и переходим к следующему
	if (index == 0) {
		file.seekg(insert.getNext());
		file >> insert;
	}

	newList << insert;

	unsigned int i = 1;

	// Читаем до конца списка
	while (insert.getNext() != -1) {
		// Перекидываем узел записи в хвост
		tailPosition = insertPosition;
		tail = insert;

		// Переходим на следующий узел в файле чтения и в конец в файле записи
		file.seekg(tail.getNext());
		newList.seekg(0, ios::end);

		// Сохраняем позицию для записи и читаем очередной узел
		insertPosition = newList.tellg();
		file >> insert;

		// Если очередной узел - требуемый узел для удаления, пропускаем его
		if (i == index) {
			file.seekg(insert.getNext());
			file >> insert;
		}

		// Пишем в новый файл очередной узел
		newList << insert;

		// Перезаписываем хвост, чтобы он указывал на новый узел
		tail.setNext(insertPosition);
		newList.seekg(tailPosition);
		newList << tail;

		i++;
	}

	file.clear();
	newList.clear();

	size--; // Размер списка уменьшается на единицу

	// Переходим в начало файла и перезаписываем размер и позицию первого узла
	newList.seekg(0, ios::beg);
	newList.write((const char*)(&size), sizeof(size));
	newList.write((const char*)(&first), sizeof(first));

	newList.clear();
	newList.flush();

	// Закрываем предыдущий и новый файл
	file.close();
	newList.close();

	// Удаляем старый файл и переименовываем новый в имя старого файла
	remove(name.c_str());
	rename("new", name.c_str());

	// Открываем новый файл для дальнейшей работы с ним
	file.open(name, ios::binary | ios::in | ios::out);
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
		file.seekg(0, ios::beg);
		file.write((const char*)(&size), sizeof(size));
		file.write((const char*)(&first), sizeof(first));

		file.clear();
		file.flush();
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
	file.seekg(tailPosition); // Переходим на предыдущий узел
	tail.setNext(insertPosition); // Обновляем указатель на следующий узел
	file << tail; // Перезаписываем узел
}

// Сортировка списка
void FileList::sort() {
	Node tail; // Узел, предшествующий левом
	Node left; // Левый узел
	Node right; // Правый узел

	long long int tailPosition;
	long long int leftPosition;
	long long int rightPosition;

	if (size < 2) {
		cout << "Недостаточно узлов для сортировки" << endl;
		return;
	}

	// Если в списке всего два узла, их сразу же можно отсортировать
	if (size == 2) {
		file.seekg(first);
		leftPosition = file.tellg(); // Запоминаем позицию левого узла
		file >> left; // Читаем его
		file.seekg(left.getNext()); // Переходим к следующему, правому узлу
		rightPosition = file.tellg(); // Также запоминаем позицию правого узла
		file >> right; // Также читаем его

		// Сравниваем узлы и производим перестановку, если условие для сортировки подходит
		if (left > right) {
			// Теперь левый узел указывает туда, куда указывал правый
			// А правый узел указывает на позицию левого узла
			left.setNext(right.getNext());
			right.setNext(leftPosition);

			// Перезаписываем указатели в списке
			file.seekg(leftPosition);
			file << left;
			file.seekg(rightPosition);
			file << right;

			// Обновляем позицию первого узла
			first = rightPosition;

			// Переходим в начало файла и обновляем данные списка
			file.seekg(0, ios::beg);
			file.write((const char*)(&size), sizeof(size));
			file.write((const char*)(&first), sizeof(first));

			file.clear();
			file.flush();
		}

		return;
	}

	// Используем обычную сортировку пузырьком
	for (unsigned int i = 0; i < size; i++) {
		file.seekg(first); // Переходим на первый узел
		rightPosition = file.tellg(); // Запоминаем его позицию
		file >> right; // Читаем первый узел
		file.seekg(right.getNext()); // Переходим на следующий 

		// Выполняем обход до конца списка
		while (right.getNext() != -1) {
			// Перекидываем все узлы
			tailPosition = leftPosition;
			tail = left;
			leftPosition = rightPosition;
			left = right;
			rightPosition = file.tellg();
			file >> right;

			// Если узел слева имеет номер поезда больше, чем узел справа, выполняем перестановку
			if (left > right) {
				// Если узел слева был первым, обновляем указатель на первый узел
				if (leftPosition == first) {
					first = rightPosition;
				}

				// Теперь левый узел указывает туда, куда указывал правый
				// А правый узел указывает на позицию левого узла
				left.setNext(right.getNext());
				right.setNext(leftPosition);

				// Перезаписываем указатели в списке
				file.seekg(leftPosition);
				file << left;
				file.seekg(rightPosition);
				file << right;

				// Т.к. узлы поменялись местами, обмениваемся данными
				Node temp(left);
				unsigned int tempPosition = leftPosition;
				left = right;
				leftPosition = rightPosition;
				right = temp;
				rightPosition = tempPosition;

				// Если узел слева не был первым, надо обновить узел перед ним
				if (leftPosition != first) {
					// Перезаписываем указатель, чтобы он указывал на переставленный узел
					tail.setNext(leftPosition);
					file.seekg(tailPosition);
					file << tail;
				}
			}

			// Переходим на следующий узел
			file.seekg(right.getNext());
			file.clear();
		}

		file.clear();
	}

	file.clear();

	// Переходим в начало файла и обновляем данные списка
	file.seekg(0, ios::beg);
	file.write((const char*)(&size), sizeof(size));
	file.write((const char*)(&first), sizeof(first));

	file.clear();
	file.flush();
}

// Поиск всех поездов, следующих до станции
void FileList::find(unsigned int station) {
	Node tail; // Хвост для обхода списка

	cout << "Все поезда следующие до станции " << station << ":" << endl;
	if (size == 0) {
		return;
	}

	file.seekg(first); // Переходим к первому узлу
	while(tail.getNext() != -1) {
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
	cout << "-------------------------------------------" << endl;
	
	// Если список пуст, вывод не может быть осуществлён
	if (size == 0) {
		return;
	}

	// Проходим по списку с помощью итератора
	for (Iterator iter = begin(); iter != end(); iter++) {
		Train train = *iter; // Получаем объект из итератора
		train.print(); // Выводим его
		cout << "-------------------------------------------" << endl;
	}

	file.clear();
}

// Постраничный просмотр списка
void FileList::pageViewPrint() {
	Node tail;

	unsigned int page = 1; // "Страница" просмотра
	unsigned int nodePerPage = 4; // Количество узлов на страницу

	cout << "Движение поездов:" << endl;
	
	// Если список пуст, просмотр не может быть осуществлён
	if (size == 0) {
		return;
	}

	file.seekg(first); // Переходим к первому узлу
	while (tail.getNext() != -1) {
		cout << "Страница №" << page << endl;
		for (unsigned int i = 0; i < nodePerPage && tail.getNext() != -1; i++) {
			file >> tail;
			tail.getData().print();
			file.seekg(tail.getNext());
		}

		cout << "Нажмите Enter для следующей страницы...";
		cin.get();
		page++;
	}
}
