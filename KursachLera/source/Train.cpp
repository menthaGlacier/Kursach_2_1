#include "../include/Train.h"

// Конструктор по умолчанию
Train::Train() {
	setTrainNumber(0);
	setDaysOfWeek("");
	setDepartureTimeHours(0);
	setDepartureTimeMinutes(0);
	setTravelTimeHours(0);
	setTravelTimeMinutes(0);
	setDepartureStationNumber(0);
	setDestinationStationNumber(0);
}

// Конструктор по параметрам
Train::Train(unsigned int trainNumber, string daysOfWeek,
		unsigned int departureTimeHours, unsigned int departureTimeMinutes,
		unsigned int travelTimeHours, unsigned int travelTimeMinutes,
		unsigned int departureStationNumber, unsigned int destinationStationNumber,
		vector<unsigned int> transit) {
	setTrainNumber(trainNumber);
	setDaysOfWeek(daysOfWeek);
	setDepartureTimeHours(departureTimeHours);
	setDepartureTimeMinutes(departureTimeMinutes);
	setTravelTimeHours(travelTimeHours);
	setTravelTimeMinutes(travelTimeMinutes);
	setDepartureStationNumber(departureStationNumber);
	setDestinationStationNumber(destinationStationNumber);
	setTransit(transit);
}

// Конструктор копирования
Train::Train(const Train& train) {
	setTrainNumber(train.trainNumber);
	setDaysOfWeek(train.daysOfWeek);
	setDepartureTimeHours(train.departureTimeHours);
	setDepartureTimeMinutes(train.departureTimeMinutes);
	setTravelTimeHours(train.travelTimeHours);
	setTravelTimeMinutes(train.travelTimeMinutes);
	setDepartureStationNumber(train.departureStationNumber);
	setDestinationStationNumber(train.destinationStationNumber);
	setTransit(train.transit);
}

// Получить номер поезда
unsigned int Train::getTrainNumber() {
	return trainNumber;
}

// Получить дни недели отправления
string Train::getDaysOfWeek() {
	return daysOfWeek;
}

// Получить часы времени отправления
unsigned int Train::getDepartureTimeHours() {
	return departureTimeHours;
}

// Получить минуты времени отправления
unsigned int Train::getDepartureTimeMinutes() {
	return departureTimeMinutes;
}

// Получить часы времени в пути
unsigned int Train::getTravelTimeHours() {
	return travelTimeHours;
}

// Получить минуты времени пути
unsigned int Train::getTravelTimeMinutes() {
	return travelTimeMinutes;
}

// Получить номер станции отправки
unsigned int Train::getDepartureStationNumber() {
	return departureStationNumber;
}

// Получить номер станции назначения
unsigned int Train::getDestinationStationNumber() {
	return destinationStationNumber;
}

// Получить вектор промежуточных станций
vector<unsigned int> Train::getTransit() {
	return transit;
}

// Установить номер поезда
void Train::setTrainNumber(unsigned int trainNumber) {
	this->trainNumber = trainNumber;
}

// Установить дни недели отправления
void Train::setDaysOfWeek(string daysOfWeek) {
	this->daysOfWeek = daysOfWeek;
}

// Установить часы времени отправления
void Train::setDepartureTimeHours(unsigned int departureTimeHours) {
	// Часы не могут быть больше знечния в 23
	if (departureTimeHours > 23) {
		this->departureTimeHours = 23;
		return;
	}

	this->departureTimeHours = departureTimeHours;
}

// Установить минуты времени отправления
void Train::setDepartureTimeMinutes(unsigned int departureTimeMinutes) {
	// Минуты не могут превышать значение в 59
	if (departureTimeMinutes > 59) {
		this->departureTimeMinutes = 59;
		return;
	}

	this->departureTimeMinutes = departureTimeMinutes;
}

// Установить часы времени в пути
void Train::setTravelTimeHours(unsigned int travelTimeHours) {
	// Часы не могут быть больше знечния в 23
	if (travelTimeHours > 23) {
		this->travelTimeHours = 23;
		return;
	}

	this->travelTimeHours = travelTimeHours;
}

// Установить минуты времени в пути
void Train::setTravelTimeMinutes(unsigned int travelTimeMinutes) {
	// Минуты не могут превышать значение в 59
	if (travelTimeMinutes > 59) {
		this->travelTimeMinutes = 59;
		return;
	}

	this->travelTimeMinutes = travelTimeMinutes;
}

// Установить номер станции отправки
void Train::setDepartureStationNumber(unsigned int departureStationNumber) {
	this->departureStationNumber = departureStationNumber;
}

// Установить номер станции назначения
void Train::setDestinationStationNumber(unsigned int destinationStationNumber) {
	this->destinationStationNumber = destinationStationNumber;
}

// Установить вектор промежуточных станций
void Train::setTransit(vector<unsigned int> transit) {
	this->transit = transit;
}

// Добавать станцию в вектор станций
void Train::appendToTransit(unsigned int station) {
	transit.push_back(station);
}

// Очистить вектор промежуточных станций
void Train::clearTransit() {
	transit.clear();
}

// Вывод
void Train::print() {
	cout << "Поезд №" << trainNumber << ":" << endl;
	cout << "\tДни недели отправления: " << daysOfWeek << endl;
	cout << "\tВремя отправления: " << departureTimeHours <<
		":" << departureTimeMinutes << endl;
	cout << "\tВремя в пути: " << travelTimeHours <<
		":" << travelTimeMinutes << endl;
	cout << "\tЕдет от станции " << departureStationNumber << 
		" до станции " << destinationStationNumber << endl;

	// Проходим по каждому элементу вектора с помощью цикла for для диапозона
	cout << "Промежуточные станции маршрута: ";
	for (unsigned int i : transit) {
		cout << i << " ";
	}

	cout << endl;
}

// Получить размер объекта
unsigned int Train::size() {
	unsigned int size = 0;

	// Считаем размер полей со статическим размером
	size += sizeof(trainNumber) + sizeof(departureTimeHours)
		+ sizeof(departureTimeMinutes) + sizeof(travelTimeHours)
		+ sizeof(travelTimeMinutes) + sizeof(departureStationNumber)
		+ sizeof(destinationStationNumber);

	// Добавляем размер полей с динмамическим размером
	size += daysOfWeek.size() + transit.size();

	return size;
}

// Присваивание
Train& Train::operator=(const Train& train) {
	// Проверяем, является ли объект тем же
	if (this == &train) {
		return *this;
	}

	setTrainNumber(train.trainNumber);
	setDaysOfWeek(train.daysOfWeek);
	setDepartureTimeHours(train.departureTimeHours);
	setDepartureTimeMinutes(train.departureTimeMinutes);
	setTravelTimeHours(train.travelTimeHours);
	setTravelTimeMinutes(train.travelTimeMinutes);
	setDepartureStationNumber(train.departureStationNumber);
	setDestinationStationNumber(train.destinationStationNumber);
	setTransit(train.transit);

	return *this;
}

// Равность
bool Train::operator==(const Train& train) {
	// Проверяем, равны ли поля между текущим и полученным объектом
	return (
		this->trainNumber != train.trainNumber &&
		this->daysOfWeek != train.daysOfWeek &&
		this->departureTimeHours != train.departureTimeHours &&
		this->departureTimeMinutes != train.departureTimeMinutes &&
		this->travelTimeHours != train.travelTimeHours &&
		this->travelTimeMinutes != train.travelTimeMinutes &&
		this->departureStationNumber != train.departureStationNumber &&
		this->destinationStationNumber != train.destinationStationNumber &&
		this->transit != train.transit
	);
}

// Больше
bool Train::operator>(const Train& train) {
	return this->trainNumber > train.trainNumber;
}

// Меньше
bool Train::operator<(const Train& train) {
	return this->trainNumber < train.trainNumber;
}

// Перегрузка оператора записи в файловый поток объекта
fstream& operator<<(fstream& file, const Train& train) {
	// Запись в файл переменных со статическим размером
	file.write((const char*)(&train.trainNumber), sizeof(train.trainNumber));
	file.write((const char*)(&train.departureTimeHours), sizeof(train.departureTimeHours));
	file.write((const char*)(&train.departureTimeMinutes), sizeof(train.departureTimeMinutes));
	file.write((const char*)(&train.travelTimeHours), sizeof(train.travelTimeHours));
	file.write((const char*)(&train.travelTimeMinutes), sizeof(train.travelTimeMinutes));
	file.write((const char*)(&train.departureStationNumber), sizeof(train.departureStationNumber));
	file.write((const char*)(&train.destinationStationNumber), sizeof(train.destinationStationNumber));

	// Сначала записываем в файл размер строки
	unsigned int stringSize = train.daysOfWeek.size();
	file.write((const char*)(&stringSize), sizeof(stringSize));

	// Если размер строки равен 0, нет смысла что-то записывать. Иначе делаем запись
	if (stringSize > 0) {
		// Записываем содержимое строки, переводя string в си-строку
		file.write(train.daysOfWeek.c_str(), stringSize);
	}

	// Аналогично записываем сначала размер вектора
	unsigned int vectorSize = train.transit.size();
	file.write((const char*)(&vectorSize), sizeof(vectorSize));

	// Проходим по каждому элементу вектора с помощью цикла for для диапозона
	for (unsigned int i : train.transit) {
		// Записываем очередной элемент вектора в файл
		file.write((const char*)(&i), sizeof(i));
	}

	// Возвращаем файловый поток для продолжения операций над ним
	return file;
}

// Перегрузка оператора чтения из файлового потока объекта
fstream& operator>>(fstream& file, Train& train) {
	// Читаем из файла переменные со статическим размером
	file.read((char*)(&train.trainNumber), sizeof(train.trainNumber));
	file.read((char*)(&train.departureTimeHours), sizeof(train.departureTimeHours));
	file.read((char*)(&train.departureTimeMinutes), sizeof(train.departureTimeMinutes));
	file.read((char*)(&train.travelTimeHours), sizeof(train.travelTimeHours));
	file.read((char*)(&train.travelTimeMinutes), sizeof(train.travelTimeMinutes));
	file.read((char*)(&train.departureStationNumber), sizeof(train.departureStationNumber));
	file.read((char*)(&train.destinationStationNumber), sizeof(train.destinationStationNumber));

	// Читаем размер строки
	unsigned int stringSize = 0;
	file.read((char*)(&stringSize), sizeof(stringSize));

	// Если строка имеет размер больше 0, читаем её содержимое
	if (stringSize > 0) {
		// Строка, в которую будет записана прочтенная строка
		char* fileString = new char[stringSize + 1];

		// Читаем строку с прочтенным ранее размером
		file.read(fileString, stringSize);
		fileString[stringSize] = '\0';

		// Создаем из си-строки string строку и передаем её объекту
		string str(fileString);
		train.setDaysOfWeek(str);

		// Освобождаем память
		delete[] fileString;
	}

	// Очищаем вектор промежуточных станций
	train.clearTransit();

	// Переменная, в которую будут записываться прочтенные промежуточные станции
	unsigned int station = 0;

	// Читаем размер вектор и начинаем чтения кол-во станций по длине вектора
	unsigned int vectorSize = 0;
	file.read((char*)(&vectorSize), sizeof(vectorSize));
	for (unsigned int i = 0; i < vectorSize; i++) {
		// Читаем промежуточную станцию и добавляем её в вектор
		file.read((char*)(&station), sizeof(station));
		train.appendToTransit(station);
	}

	// Возвращаем файловый поток для продолжения операций над ним
	return file;

}
