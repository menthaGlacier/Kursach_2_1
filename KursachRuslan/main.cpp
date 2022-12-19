#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include "List.h"
using namespace std;

void menu(List& list)
{
	char key;	//���������� ������ ��������
	for (;;)	//����������� ����
	{
		cout << "\n";
		cout << "�������� ��������:" << endl;
		cout << "[1] - �������� �����" << endl;
		cout << "[2] - �������������" << endl; 
		cout << "[3] - ��������������" << endl; 
		cout << "[4] - ��������" << endl; 
		cout << "[5] - ������������ ��������" << endl;
		cout << "[6] - �������� ������" << endl;
		cout << "[7] - ��������� ������� � ������� �����" << endl;
		cout << "[ ] - �����\n" << endl;

		key = _getch();	//�������� ����� ��������
		switch (key)
		{
		case '1'://����������
		{
			Node temp;
			temp.inputProduct();	//�������� �����
			for (;;)
			{
				cout << "���� �������� �������?" << endl;
				cout << "[1] - � �����" << endl;
				cout << "[2] - � �������� �������" << endl;
				cout << "[3] - �������� � ����������� �������" << endl;
				key = _getch();//�������� ����� ��������
				switch (key)
				{
				case '1':	//������� � �����
					list.add(temp.name, temp.category, temp.quantity, temp.day, temp.month, temp.year, temp.price, temp.percentage);
					break;
				case '2':	//������� � �������� �������
				{
					size_t position;
					cout << "������� ������" << endl;
					cin >> position;
					list.insert(temp.name, temp.category, temp.quantity, temp.day, temp.month, temp.year, temp.price, temp.percentage, position);
					break;
				}
				case '3'://������� � ����������� ������� (�� �������� ������)
					list.insertInOrder(temp.name, temp.category, temp.quantity, temp.day, temp.month, temp.year, temp.price, temp.percentage);
					break;
				default://�� ������, ���� �������� ������� ��������, ������������ � �������
					cout << "Error: �������� ����������� � �������!" << endl;
					continue;
				}
				break;
			}
			break;
		}
		case '2':	//����������
		{
			cout << "�������� ��� ����������: " << endl;
			cout << "[1] - �� ���������" << endl;
			cout << "[2] - �� ��������" << endl;
			cout << "[3] - �� ����" << endl;
			cout << "[4] - �� ����" << endl;
			cout << "[5] - �� ����������" << endl;
			cout << "[6] - �� ��������" << endl;

			key = _getch();//�������� ����� ��������
			switch (key)
			{
			case '1'://�� ���������
			{
				list.sort(SortType::Category);
				break;
			}
			case '2'://�� ��������
			{
				list.sort(SortType::Name);
				break;
			}
			case '3'://�� ����
			{
				list.sort(SortType::Date);
				break;
			}
			case '4'://�� ����
			{
				list.sort(SortType::Price);
				break;
			}
			case '5'://�� ����������
			{
				list.sort(SortType::Quantity);
				break;
			}
			case '6'://�� ��������
			{
				list.sort(SortType::Percentage);
				break;
			}
			default://�� ������, ���� �������� ������� ��������, ������������ � �������
				cout << "Error: �������� ����������� � �������!" << endl;
				break;
			}
			break;
		}
		case '3':	//��������������
		{
			cout << "������� ������ ��������" << endl;
			size_t index;
			Node temp;
			cin >> index;	//�������� ������ ������ ��� ���������
			if (list.getNode(index, temp) == -1)	//�������� �������� ����� �� �������� �������
			{
				cout << "�� ���������� ��������" << endl;
				break;
			}

			temp.inputProduct();//�������� ���� ������ ������
			//�������� ��������������� �����
			if (list.edit(
				temp.name, temp.category, temp.quantity,
				temp.day, temp.month, temp.year,
				temp.price, temp.percentage, index) == false) cout << "�� ������� ��������" << endl;
			else cout << "��������" << endl;
			break;
		}
		case '4': //��������
		{
			cout << "������� ������ ��������" << endl;
			size_t index;
			cin >> index;//�������� ������ ������ ��� ��������
			//�������� ������� ����� � �������
			if (list.removeAt(index) == false) cout << "�� ������� �������" << endl;
			else cout << "�������" << endl;
			break;
		}
		case '5':
		{
			size_t index = 0;
			Node product;
			for (;;)
			{
				if (list.getSize() == 0)
				{
					cout << "������ ����" << endl;
					break;
				}

				list.getNode(index, product);
				cout << "������� ����� �" << index << endl;
				product.show();
				cout << endl;
				cout << "�������� ��������:" << endl;
				cout << "[1] - ��������� �����" << endl;
				cout << "[2] - ���������� �����" << endl;
				cout << "[3] - ��������������" << endl;
				cout << "[4] - ��������" << endl;
				key = _getch();	//�������� ����� ��������
				switch (key)
				{
				case '1'://���������
				{
					if (index + 1 < list.getSize())
					{
						index++;
					}
					else
					{
						cout << "��������� �������" << endl;
					}
					break;
				}
				case '2'://����������
				{
					if (index > 0)
					{
						index--;
					}
					else
					{
						cout << "������ �������" << endl;
					}
					break;
				}
				case '3'://��������������
				{
					Node temp;
					temp.inputProduct();//�������� ���� ������ ������
					//�������� ��������������� �����
					if (list.edit(
						temp.name, temp.category, temp.quantity,
						temp.day, temp.month, temp.year,
						temp.price, temp.percentage, index) == false) cout << "�� ������� ��������" << endl;
					else cout << "��������" << endl;
					break;
				}
				case '4': //��������
				{
					if (list.removeAt(index) == false) cout << "�� ������� �������" << endl;
					else cout << "�������" << endl;
					break;
				}
				}
			}
			break;
		}
		case '6'://����������� ����� ������
			list.show();
			cout << "\n���������� ��������� � ������: " << list.getSize() << endl;
			break;
		case '7'://����������� ������� � ������� ������� �� ������
			list.invoice();
			break;
		case ' ':
			exit(0);
		default: //�� ������, ���� �������� ������� ��������, ������������ � �������
			cout << "Error: �������� ����������� � �������!" << endl;
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("color 2"); //������ ��������� ����� ������ � �������
	cout << "\t\t\t\t\tCourse paper, made by Kuvandykov R. \n" << endl; //��������� ������

	List list; //�������� ������
	menu(list);//������ ����
	return 0;
}