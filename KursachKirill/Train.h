#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Train {
public:
	// Конструкторы
	Train();
	Train(int _trainNum, string _dayOfWeeks, int _startHour, int _startMinute,
		int _travelHours, int _travelMinutes, int _start, int _stop, vector<int> _transit);
	Train(const Train& copy);

	// Геттеры
	int getTrainNum();
	string getDayOfWeeks();
	int getStartHour();
	int getStartMinute();
	int getTravelHours();
	int getTravelMinutes();
	int getStart();
	int getStop();
	vector<int> getTransit();

	// Сеттеры
	void setTrainNum(int _trainNum);
	void setDayOfWeeks(string _dayOfWeeks);
	void setStartHour(int _startHour);
	void setStartMinute(int _startMinute);
	void setTravelHours(int _travelHours);
	void setTravelMinutes(int _travelMinutes);
	void setStart(int _start);
	void setStop(int _stop);
	void setTransit(vector<int> _transit);

	// Вывод
	void print();

	// Операторы
	Train& operator=(const Train& train);
	bool operator==(const Train& train);
	bool operator>(const Train& train);
	bool operator<(const Train& train);

private:
	int trainNum;
	string dayOfWeeks;
	int startHour, startMinute;
	int travelHours, travelMinutes;
	int start, stop;
	vector<int> transit;
};
