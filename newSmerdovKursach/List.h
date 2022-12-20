#pragma once
#include "dependencies.h"
#include "Announcement.h"
using namespace std;

class List//����� ������
{
public:
	List(); //�����������
	~List(); // ����������

	int getSize() { return size; }	//��������� ������� ������
	void add(Announcement& new_element);		//���������� �������� � ����� ������
	void insert(Announcement& new_element, size_t index);	//������� � �������� �������
	void insertInOrder(Announcement& new_element);//������� � ����������� �������
	bool edit(Announcement& changed_element, size_t index);//�������������� �������� � �������� �������
	void out();//����� ������ � �������
	long long int getNode(size_t index, Announcement& element);//��������� �������� �� �������
	bool removeAt(size_t index);//�������� ������ � �������� �������
	void findCategory(const string& ctgry);	//����� �� �������
	void findText(const string& text);	//����� �� ������ ����������
	void sort();//���������� ������

private:
	int size;	//������ ������
	fstream file;//��������� �� ������� ����
};