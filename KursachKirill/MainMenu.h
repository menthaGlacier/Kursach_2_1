#pragma once

#include <iostream>
#include <string>

#include "List.h"

using namespace std;

class MainMenu {
public:
	void start(); // ������ ����
private:
	void scheduleInsert(); // ���������� ��������
	void scheduleRemove(); // �������� ��������
	void schedulePrint(); // �����
	void scheduleSearch(); // ����� �� ���������
	void scheduleOrder(); // ��������������
	void scheduleSave(); // ���������� � �����
	void scheduleLoad(); // �������� �� �����
	Train enterTrain(); // ���� ��������

	List schedule; // ���������� �������
	string input; // ������ ��� ���������� �����
};
