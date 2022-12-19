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
	char key;	//переменная выбора действий
	for (;;)	//бесконечный цикл
	{
		cout << "\n";
		cout << "Выберите действие:" << endl;
		cout << "[1] - Добавить товар" << endl;
		cout << "[2] - Отсортировать" << endl; 
		cout << "[3] - Редактирование" << endl; 
		cout << "[4] - Удаление" << endl; 
		cout << "[5] - Постраничный просмотр" << endl;
		cout << "[6] - Показать список" << endl;
		cout << "[7] - Составить фактуру и продать товар" << endl;
		cout << "[ ] - Выход\n" << endl;

		key = _getch();	//получаем выбор действия
		switch (key)
		{
		case '1'://добавление
		{
			Node temp;
			temp.inputProduct();	//получаем товар
			for (;;)
			{
				cout << "Куда добавить элемент?" << endl;
				cout << "[1] - В конец" << endl;
				cout << "[2] - В заданную позицию" << endl;
				cout << "[3] - Вставить с сохранением порядка" << endl;
				key = _getch();//получаем выбор действия
				switch (key)
				{
				case '1':	//вставка в конец
					list.add(temp.name, temp.category, temp.quantity, temp.day, temp.month, temp.year, temp.price, temp.percentage);
					break;
				case '2':	//вставка в заданную позицию
				{
					size_t position;
					cout << "Введите индекс" << endl;
					cin >> position;
					list.insert(temp.name, temp.category, temp.quantity, temp.day, temp.month, temp.year, temp.price, temp.percentage, position);
					break;
				}
				case '3'://вставка с сохранением порядка (по названию товара)
					list.insertInOrder(temp.name, temp.category, temp.quantity, temp.day, temp.month, temp.year, temp.price, temp.percentage);
					break;
				default://на случай, если пытаются выбрать действие, отсутсвующее в перечне
					cout << "Error: действие отсутствует в перечне!" << endl;
					continue;
				}
				break;
			}
			break;
		}
		case '2':	//сортировка
		{
			cout << "Выберите тип сортировки: " << endl;
			cout << "[1] - По категории" << endl;
			cout << "[2] - По названию" << endl;
			cout << "[3] - По дате" << endl;
			cout << "[4] - По цене" << endl;
			cout << "[5] - По количеству" << endl;
			cout << "[6] - По надбавке" << endl;

			key = _getch();//получаем выбор действия
			switch (key)
			{
			case '1'://по категории
			{
				list.sort(SortType::Category);
				break;
			}
			case '2'://по названию
			{
				list.sort(SortType::Name);
				break;
			}
			case '3'://по дате
			{
				list.sort(SortType::Date);
				break;
			}
			case '4'://по цене
			{
				list.sort(SortType::Price);
				break;
			}
			case '5'://по количеству
			{
				list.sort(SortType::Quantity);
				break;
			}
			case '6'://по надбавке
			{
				list.sort(SortType::Percentage);
				break;
			}
			default://на случай, если пытаются выбрать действие, отсутсвующее в перечне
				cout << "Error: действие отсутствует в перечне!" << endl;
				break;
			}
			break;
		}
		case '3':	//редактирование
		{
			cout << "Введите индекс элемента" << endl;
			size_t index;
			Node temp;
			cin >> index;	//получаем индекс товара для изменения
			if (list.getNode(index, temp) == -1)	//пытаемся получить товар по заданной позиции
			{
				cout << "Не существует элемента" << endl;
				break;
			}

			temp.inputProduct();//получаем ввод нового товара
			//пытаемся отредактировать товар
			if (list.edit(
				temp.name, temp.category, temp.quantity,
				temp.day, temp.month, temp.year,
				temp.price, temp.percentage, index) == false) cout << "Не удалось изменить" << endl;
			else cout << "Изменено" << endl;
			break;
		}
		case '4': //удаление
		{
			cout << "Введите индекс элемента" << endl;
			size_t index;
			cin >> index;//получаем индекс товара для удаления
			//пытаемся удалить товар с позиции
			if (list.removeAt(index) == false) cout << "Не удалось удалить" << endl;
			else cout << "Удалено" << endl;
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
					cout << "Список пуст" << endl;
					break;
				}

				list.getNode(index, product);
				cout << "Текущий товар №" << index << endl;
				product.show();
				cout << endl;
				cout << "Выберите действие:" << endl;
				cout << "[1] - Следующий товар" << endl;
				cout << "[2] - Предыдущий товар" << endl;
				cout << "[3] - Редактирование" << endl;
				cout << "[4] - Удаление" << endl;
				key = _getch();	//получаем выбор действия
				switch (key)
				{
				case '1'://следующий
				{
					if (index + 1 < list.getSize())
					{
						index++;
					}
					else
					{
						cout << "Последний элемент" << endl;
					}
					break;
				}
				case '2'://предыдущий
				{
					if (index > 0)
					{
						index--;
					}
					else
					{
						cout << "Первый элемент" << endl;
					}
					break;
				}
				case '3'://редактирование
				{
					Node temp;
					temp.inputProduct();//получаем ввод нового товара
					//пытаемся отредактировать товар
					if (list.edit(
						temp.name, temp.category, temp.quantity,
						temp.day, temp.month, temp.year,
						temp.price, temp.percentage, index) == false) cout << "Не удалось изменить" << endl;
					else cout << "Изменено" << endl;
					break;
				}
				case '4': //удаление
				{
					if (list.removeAt(index) == false) cout << "Не удалось удалить" << endl;
					else cout << "Удалено" << endl;
					break;
				}
				}
			}
			break;
		}
		case '6'://отображение всего списка
			list.show();
			cout << "\nКоличество элементов в списке: " << list.getSize() << endl;
			break;
		case '7'://составление фактуры и продажа товаров со склада
			list.invoice();
			break;
		case ' ':
			exit(0);
		default: //на случай, если пытаются выбрать действие, отсутсвующее в перечне
			cout << "Error: действие отсутствует в перечне!" << endl;
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("color 2"); //просто изменение цвета текста в консоли
	cout << "\t\t\t\t\tCourse paper, made by Kuvandykov R. \n" << endl; //заголовок работы

	List list; //Создание списка
	menu(list);//запуск меню
	return 0;
}