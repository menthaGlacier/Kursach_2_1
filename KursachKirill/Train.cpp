#include "Train.h"

// Конструктор по умолчанию
Train::Train()
	: trainNum(0), dayOfWeeks(), startHour(0), startMinute(0), travelHours(0), travelMinutes(0), start(0), stop(0), transit() {
}

// Конструктор по параметрам
Train::Train(uint _trainNum, string _dayOfWeeks, uint _startHour, uint _startMinute,
	uint _travelHours, uint _travelMinutes, uint _start, uint _stop, vector<uint> _transit) {
	setTrainNum(_trainNum);
	setDayOfWeeks(_dayOfWeeks);
	setStartHour(_startHour);
	setStartMinute(_startMinute);
	setTravelHours(_travelHours);
	setTravelMinutes(_travelMinutes);
	setStart(_start);
	setStop(_stop);
	setTransit(_transit);
}

// Конструктор копирования
Train::Train(const Train& copy) {
	setTrainNum(copy.trainNum);
	setDayOfWeeks(copy.dayOfWeeks);
	setStartHour(copy.startHour);
	setStartMinute(copy.startMinute);
	setTravelHours(copy.travelHours);
	setTravelMinutes(copy.travelMinutes);
	setStart(copy.start);
	setStop(copy.stop);
	setTransit(copy.transit);
}

// Получение номера поезда
uint Train::getTrainNum() {
	return trainNum;
}

// Получение дней недели отправления
string Train::getDayOfWeeks() {
	return dayOfWeeks;
}

// Получение часа отправленя
uint Train::getStartHour() {
	return startHour;
}

// Получение минуты отправления
uint Train::getStartMinute() {
	return startMinute;
}

// Получение часов времени в пути
uint Train::getTravelHours() {
	return travelHours;
}

// Получение минут времени в пути
uint Train::getTravelMinutes() {
	return travelMinutes;
}

// Получение станции отправления
uint Train::getStart() {
	return start;
}

// Получение станции назначения
uint Train::getStop() {
	return stop;
}

// Получение промежуточных станций
vector<uint> Train::getTransit() {
	return transit;
}

// Установка номера поезда
void Train::setTrainNum(uint _trainNum) {
	trainNum = _trainNum;
}

// Установка дней недели отправления
void Train::setDayOfWeeks(string _dayOfWeeks) {
	dayOfWeeks = _dayOfWeeks;
}

// Установка часа отправленя
void Train::setStartHour(uint _startHour) {
	if (_startHour > 23) { // Час отправления не может превышать 23
		startHour = 23;
	}
	else {
		startHour = _startHour;
	}
}

// Установка минуты отправления
void Train::setStartMinute(uint _startMinute) {
	if (_startMinute > 59) { // Минута отправления не может превышать 59
		startMinute = 59;
	}
	else {
		startMinute = _startMinute;
	}
}

// Установка часов времени в пути
void Train::setTravelHours(uint _travelHours) {
	travelHours = _travelHours;
}

// Установка минут времени в пути
void Train::setTravelMinutes(uint _travelMinutes) {
	if (_travelMinutes > 59) { // Минуты пути не могут превышать 59
		travelMinutes = 59;
	}
	else {
		travelMinutes = _travelMinutes;
	}
}

// Установка станции отправления
void Train::setStart(uint _start) {
	start = _start;
}

// Установка станции назначения
void Train::setStop(uint _stop) {
	stop = _stop;
}

// Установка промежуточных станций
void Train::setTransit(vector<uint> _transit) {
	transit = _transit;
}

// Добавление промежуточной станций
void Train::appendTransit(uint _transit) {
	transit.push_back(_transit);
}

// Оператор присваивания
Train& Train::operator=(const Train& train) {
	// Копирование не нужно, если объекты одинаковы
	if (this == &train) {
		return *this;
	}

	// Копируем содержимое параметра
	setTrainNum(train.trainNum);
	setDayOfWeeks(train.dayOfWeeks);
	setStartHour(train.startHour);
	setStartMinute(train.startMinute);
	setTravelHours(train.travelHours);
	setTravelMinutes(train.travelMinutes);
	setStart(train.start);
	setStop(train.stop);
	setTransit(train.transit);
	return *this;
}

// Вывод
void Train::print() {
	cout << "Train number #" << trainNum << endl;
	cout << "Working day of weeks: " << dayOfWeeks << endl;
	cout << "Departure time - " << startHour << ":" << startMinute << endl;
	cout << "Travel time - " << travelHours << ":" << travelMinutes << endl;
	cout << "Main route " << start << " -> " << stop << endl;

	cout << "Transit stations: ";
	for (const uint it : transit) { // Вывод вектора через итератор
		cout << it << " ";
	}

	cout << endl;
}

// Оператор равности
bool Train::operator==(const Train& train) {
	// Объекты не равны, если есть отличия в каких-либо полях
	if (this->trainNum != train.trainNum
		|| this->dayOfWeeks != train.dayOfWeeks
		|| this->startHour != train.startHour
		|| this->startMinute != train.startMinute
		|| this->travelMinutes != train.travelMinutes
		|| this->travelHours != train.travelHours
		|| this->travelMinutes != train.travelMinutes
		|| this->start != train.start
		|| this->stop != train.stop
		|| this->transit != train.transit) {
		return false;
	}

	return true;
}

// Оператор больше
bool Train::operator>(const Train& train) {
	// Сравнение по номеру поезда
	if (this->trainNum > train.trainNum) {
		return true;
	}

	return false;
}

// Оператор меньше
bool Train::operator<(const Train& train) {
	// Сравнение по номеру поезда
	if (this->trainNum < train.trainNum) {
		return true;
	}

	return false;
}

// Оператор записи в файл
fstream& operator<<(fstream& file, const Train& train) {
	// Записывем все простые элементы
	file.write((const char*)(&train.trainNum), sizeof(train.trainNum));
	file.write((const char*)(&train.startHour), sizeof(train.startHour));
	file.write((const char*)(&train.startMinute), sizeof(train.startMinute));
	file.write((const char*)(&train.travelHours), sizeof(train.travelHours));
	file.write((const char*)(&train.travelMinutes), sizeof(train.travelMinutes));
	file.write((const char*)(&train.start), sizeof(train.start));
	file.write((const char*)(&train.stop), sizeof(train.stop));

	// Записываем размер строки, затем её текст
	uint strSize = train.dayOfWeeks.size();
	file.write((const char*)(&strSize), sizeof(strSize));
	if (strSize > 0) {
		file.write(train.dayOfWeeks.c_str(), strSize);
	}

	// Записываем размер вектора, затем его элементы
	uint vecSize = train.transit.size();
	file.write((const char*)(&vecSize), sizeof(vecSize));
	for (uint i : train.transit) {
		file.write((const char*)(&i), sizeof(i));
	}

	return file;
}

// Оператор чтения с файла
fstream& operator>>(fstream& file, Train& train) {
	// Считываем все простые элементы
	file.read((char*)(&train.trainNum), sizeof(train.trainNum));
	file.read((char*)(&train.startHour), sizeof(train.startHour));
	file.read((char*)(&train.startMinute), sizeof(train.startMinute));
	file.read((char*)(&train.travelHours), sizeof(train.travelHours));
	file.read((char*)(&train.travelMinutes), sizeof(train.travelMinutes));
	file.read((char*)(&train.start), sizeof(train.start));
	file.read((char*)(&train.stop), sizeof(train.stop));

	// Считываем размер строки, затем её текст
	uint strSize = 0;
	file.read((char*)(&strSize), sizeof(strSize));
	if (strSize > 0) {
		char* tempStr = new char[strSize];
		file.read(tempStr, strSize);
		train.dayOfWeeks.assign(tempStr, strSize);
		delete[] tempStr;
	}

	// Очищаем вектор, считываем из файла размер вектора, затем его элементы
	train.transit.clear();
	uint vecSize = 0, tempUint;
	file.read((char*)(&vecSize), sizeof(vecSize));
	for (uint i = 0; i < vecSize; i++) {
		file.read((char*)(&tempUint), sizeof(tempUint));
		train.appendTransit(tempUint);
	}

	return file;
}