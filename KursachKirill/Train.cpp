#include "Train.h"

// ����������� �� ���������
Train::Train()
	: trainNum(0), dayOfWeeks(), startHour(0), startMinute(0), travelHours(0), travelMinutes(0), start(0), stop(0), transit() {
}

// ����������� �� ����������
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

// ����������� �����������
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

// ��������� ������ ������
uint Train::getTrainNum() {
	return trainNum;
}

// ��������� ���� ������ �����������
string Train::getDayOfWeeks() {
	return dayOfWeeks;
}

// ��������� ���� ����������
uint Train::getStartHour() {
	return startHour;
}

// ��������� ������ �����������
uint Train::getStartMinute() {
	return startMinute;
}

// ��������� ����� ������� � ����
uint Train::getTravelHours() {
	return travelHours;
}

// ��������� ����� ������� � ����
uint Train::getTravelMinutes() {
	return travelMinutes;
}

// ��������� ������� �����������
uint Train::getStart() {
	return start;
}

// ��������� ������� ����������
uint Train::getStop() {
	return stop;
}

// ��������� ������������� �������
vector<uint> Train::getTransit() {
	return transit;
}

// ��������� ������ ������
void Train::setTrainNum(uint _trainNum) {
	trainNum = _trainNum;
}

// ��������� ���� ������ �����������
void Train::setDayOfWeeks(string _dayOfWeeks) {
	dayOfWeeks = _dayOfWeeks;
}

// ��������� ���� ����������
void Train::setStartHour(uint _startHour) {
	if (_startHour > 23) { // ��� ����������� �� ����� ��������� 23
		startHour = 23;
	}
	else {
		startHour = _startHour;
	}
}

// ��������� ������ �����������
void Train::setStartMinute(uint _startMinute) {
	if (_startMinute > 59) { // ������ ����������� �� ����� ��������� 59
		startMinute = 59;
	}
	else {
		startMinute = _startMinute;
	}
}

// ��������� ����� ������� � ����
void Train::setTravelHours(uint _travelHours) {
	travelHours = _travelHours;
}

// ��������� ����� ������� � ����
void Train::setTravelMinutes(uint _travelMinutes) {
	if (_travelMinutes > 59) { // ������ ���� �� ����� ��������� 59
		travelMinutes = 59;
	}
	else {
		travelMinutes = _travelMinutes;
	}
}

// ��������� ������� �����������
void Train::setStart(uint _start) {
	start = _start;
}

// ��������� ������� ����������
void Train::setStop(uint _stop) {
	stop = _stop;
}

// ��������� ������������� �������
void Train::setTransit(vector<uint> _transit) {
	transit = _transit;
}

// ���������� ������������� �������
void Train::appendTransit(uint _transit) {
	transit.push_back(_transit);
}

// �������� ������������
Train& Train::operator=(const Train& train) {
	// ���� ������� ���������, ����������� �� ���������
	if (this == &train) {
		return *this;
	}

	// ����� �������� ���������� _product � ������
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

// �����
void Train::print() {
	cout << "Train number #" << trainNum << endl;
	cout << "Working day of weeks:" << dayOfWeeks << endl;
	cout << "Departure time - " << startHour << ":" << startMinute << endl;
	cout << "Travel time - " << travelHours << ":" << travelMinutes << endl;
	cout << "Main route " << start << " -> " << stop << endl;

	cout << "Transit stations: ";
	for (const uint it : transit) { // ����� ������� ����� ��������
		cout << it << " ";
	}

	cout << endl;
}

// �������� ��������� "�����"
bool Train::operator==(const Train& train) {
	// ���� �����-���� ���� �� ��������� � ������������ - ������� �� �����
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

// �������� ��������� "������"
bool Train::operator>(const Train& train) {
	// ��������� ��� �� ���� "������������ ������"
	if (this->trainNum > train.trainNum) {
		return true;
	}

	return false;
}

// �������� ��������� "������"
bool Train::operator<(const Train& train) {
	// ��������� ��� �� ���� "������������ ������"
	if (this->trainNum < train.trainNum) {
		return true;
	}

	return false;
}