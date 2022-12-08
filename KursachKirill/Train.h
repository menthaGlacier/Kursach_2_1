#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;

class Train {
public:
	// ������������
	Train();
	Train(uint _trainNum, string _dayOfWeeks, uint _startHour, uint _startMinute,
		uint _travelHours, uint _travelMinutes, uint _start, uint _stop, vector<uint> _transit);
	Train(const Train& copy);

	// �������
	uint getTrainNum();
	string getDayOfWeeks();
	uint getStartHour();
	uint getStartMinute();
	uint getTravelHours();
	uint getTravelMinutes();
	uint getStart();
	uint getStop();
	vector<uint> getTransit();

	// �������
	void setTrainNum(uint _trainNum);
	void setDayOfWeeks(string _dayOfWeeks);
	void setStartHour(uint _startHour);
	void setStartMinute(uint _startMinute);
	void setTravelHours(uint _travelHours);
	void setTravelMinutes(uint _travelMinutes);
	void setStart(uint _start);
	void setStop(uint _stop);
	void setTransit(vector<uint> _transit);
	void appendTransit(uint _transit);

	// �����
	void print();

	// ���������
	Train& operator=(const Train& train);
	bool operator==(const Train& train);
	bool operator>(const Train& train);
	bool operator<(const Train& train);

private:
	uint trainNum;
	string dayOfWeeks;
	uint startHour, startMinute;
	uint travelHours, travelMinutes;
	uint start, stop;
	vector<uint> transit;
};
