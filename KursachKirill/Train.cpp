#include "Train.h"

// ����������� �� ���������
Train::Train()
	: trainNum(-1), dayOfWeeks(), startHour(0), startMinute(0), travelHours(0), travelMinutes(0), start(-1), stop(-1), transit() {
}

// ����������� �� ����������
Train::Train(int _trainNum, string _dayOfWeeks, int _startHour, int _startMinute,
	int _travelHours, int _travelMinutes, int _start, int _stop, vector<int> _transit) {
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

//
int Train::getTrainNum() {
	return trainNum;
}

string Train::getDayOfWeeks() {
	return dayOfWeeks;
}

int Train::getStartHour() {
	return startHour;
}

int Train::getStartMinute() {
	return startMinute;
}

int Train::getTravelHours() {
	return travelHours;
}

int Train::getTravelMinutes() {
	return travelMinutes;
}

int Train::getStart() {
	return start;
}

int Train::getStop() {
	return stop;
}

vector<int> Train::getTransit() {
	return transit;
}

//
void Train::setTrainNum(int _trainNum) {

}

void Train::setDayOfWeeks(string _dayOfWeeks) {

}

void Train::setStartHour(int _startHour) {

}

void Train::setStartMinute(int _startMinute) {

}

void Train::setTravelHours(int _travelHours) {

}

void Train::setTravelMinutes(int _travelMinutes) {

}

void Train::setStart(int _start) {

}

void Train::setStop(int _stop) {

}

void Train::setTransit(vector<int> _transit) {

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