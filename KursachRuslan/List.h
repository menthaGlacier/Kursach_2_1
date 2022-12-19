#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

//������������ ��������� ����������
enum class SortType { Name, Category, Quantity, Date, Price, Percentage};

struct Node//������� ������(�����)
{
public:
	bool toFile(fstream& file);//�������� � ����
	bool fromFile(fstream& file);//�������� ������ �� �����
	void show();//����� � �������
	void inputProduct();//���� ������������� ������ � ������

	string name; //�������� ������
	string category; //��������� ������
	int quantity; //���-��
	int day; //����
	int month; //�����
	int year; //���
	int price; //����
	float percentage; //������� �������� ��������
private:
	friend class List;//����� ������ ����� ������ � ��������� �����
	long long int next, prev;	//�������� ��������� �� ��������� � ���������� �������� � ������
};

class List//����� ������
{
public:
	List(); //�����������
	~List(); // ����������

	int getSize() { return size; }	//��������� ������� ������
	//���������� �������� � ����� ������
	void add(string name, string category, int quantity, int day, int month, int year, int price, float percentage);
	//������� � �������� �������
	void insert(string name, string category, int quantity, int day, int month, int year, int price, float percentage, size_t index);
	//������� � ����������� �������
	void insertInOrder(string name, string category, int quantity, int day, int month, int year, int price, float percentage);
	//�������������� �������� � �������� �������
	bool edit(string name, string category, int quantity, int day, int month, int year, int price, float percentage, size_t index);
	void show();//����� ������ � �������
	long long int getNode(size_t index, Node& node);//��������� �������� �� �������
	bool removeAt(size_t index);//�������� ������ � �������� �������

	void sort(SortType type);//���������� ������
	void invoice();//����������� �������
private:
	int size;	//������ ������
	fstream file;//��������� �� ������� ����
};