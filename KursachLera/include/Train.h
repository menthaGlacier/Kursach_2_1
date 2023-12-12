#ifndef TRAIN_H
#define TRAIN_H

#include "dependencies.h"

class Train {
public:
	// Конструкторы
	Train(); // Конструктор по умолчанию
	Train(unsigned int trainNumber, string daysOfWeek,
			unsigned int departureTimeHours, unsigned int departureTimeMinutes,
			unsigned int travelTimeHours, unsigned int travelTimeMinutes,
			unsigned int departureStationNumber,
			unsigned int destinationStationNumber,
			vector<unsigned int> transit); // Конструктор по параметрам
	Train(const Train& train); // Конструктор копирования

	// Геттеры
	unsigned int getTrainNumber();
	string getDaysOfWeek();
	unsigned int getDepartureTimeHours();
	unsigned int getDepartureTimeMinutes();
	unsigned int getTravelTimeHours();
	unsigned int getTravelTimeMinutes();
	unsigned int getDepartureStationNumber();
	unsigned int getDestinationStationNumber();
	vector<unsigned int> getTransit();

	// Сеттеры
	void setTrainNumber(unsigned int trainNumber);
	void setDaysOfWeek(string daysOfWeek);
	void setDepartureTimeHours(unsigned int departureTimeHours);
	void setDepartureTimeMinutes(unsigned int departureTimeMinutes);
	void setTravelTimeHours(unsigned int travelTimeHours);
	void setTravelTimeMinutes(unsigned int travelTimeMinutes);
	void setDepartureStationNumber(unsigned int departureStationNumber);
	void setDestinationStationNumber(unsigned int destinationStationNumber);
	void setTransit(vector<unsigned int> transit);

	// Добавление станции в вектор промежуточных станций
	void appendToTransit(unsigned int station);

	// Очистка вектор промежуточных станций
	void clearTransit();

	// Вывод
	void print();

	// Получить размер объекта
	unsigned int size();

	// Перегрузки операторов
	Train& operator=(const Train& train); // Присваивание
	bool operator==(const Train& train); // Равность
	bool operator>(const Train& train); // Больше
	bool operator<(const Train& train); // Меньше

	friend fstream& operator<<(fstream& file, const Train& train); // Запись в поток
	friend fstream& operator>>(fstream& file, Train& train); // Чтение из потока
private:
	unsigned int trainNumber; // Номер поезда
	string daysOfWeek; // Дни недели отправления
	unsigned int departureTimeHours; // Время отправления (часы)
	unsigned int departureTimeMinutes; // Время отправления (минуты)
	unsigned int travelTimeHours; // Время в пути (часы)
	unsigned int travelTimeMinutes; // Время в пути (минуты)
	unsigned int departureStationNumber; // Номер станции отправления
	unsigned int destinationStationNumber; // Номер станции назначения
	vector<unsigned int> transit; // Промежуточные станции
};

#endif /* TRAIN_H */
