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
	void add(Announcement& elem);		//���������� �������� � ����� ������
	void insert(Announcement& elem, unsigned int pos);	//������� � �������� �������
	void insertInOrder(Announcement& elem);//������� � ����������� �������
	bool edit(Announcement& elem, unsigned int pos);//�������������� �������� � �������� �������
	void out();//����� ������ � �������
	long long int getNode(unsigned int pos, Announcement& element);//��������� �������� �� �������
	bool removeAt(unsigned int pos);//�������� ������ � �������� �������
	void findCategory(const string& ctgry);	//����� �� �������
	void findText(const string& text);	//����� �� ������ ����������
	void sort();//���������� ������

private:
	int size;	//������ ������
	fstream file;//��������� �� ������� ����
};