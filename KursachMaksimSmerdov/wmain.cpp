#include "dependencies.h"
#include "Announcement.h"
#include "List.h"

using namespace std;

#define TEST1											\
Announcement ann;																					\
\
ann.setCategory(string("1"));																		\
ann.setBS(1);																\
ann.setAdText(string("1"));													\
ann.setNumber(1);													\
\
ann.setDate(3, 3, 2003);				\
list.add(ann);										\
\
ann.setDate(2, 2, 2002);				\
list.add(ann);										\
\
ann.setDate(1,1,2001);										\
list.add(ann);									\

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	List list;
	TEST1

	{ cout << "Test1 failed" << endl; }
	bool should_close = false;
	while (!should_close)
	{
		system("cls");

		cout
			<< "<<<Список доступных действий>>>\n"
			<< "1. Добавить объявление в список\n"
			<< "2. Отсортировать объявления по дате\n"
			<< "3. Удалить объявление из списка\n"
			<< "4. Поиск объявления по рубрике\n"
			<< "5. Поиск объявления по тексту\n"
			<< "6. Показать список объявлений\n"
			<< "7. Сохранить список в файл\n"
			<< "8. Загрузить список из файла\n"
			<< "9. Очистить список\n"
			<< "10. Выход\n"
			<< "Выберите действие: " << flush;
		int choise;

		cin >> choise;
		cout << endl;

		switch (choise)
		{
		case 1:
		{
			bool result = false;
			string buffer;
			Announcement new_element;
			while (true)
			{
				cout << "Введите дату (дд.мм.гггг)" << endl;
				cin >> buffer;

				if (!Announcement::dateCheck(buffer))
				{
					cout << "Неверная дата" << endl;
				}
				else
				{
					unsigned short day = (buffer[0] - '0') * 10 + (buffer[1] - '0');
					unsigned short month = (buffer[3] - '0') * 10 + (buffer[4] - '0');
					unsigned short year = 0;
					for (size_t i = 6; i < 10; i++)
					{
						year = year * 10 + buffer[i] - '0';
					}
					new_element.setDate(day, month, year);
					break;
				}
			}

			while (true)
			{
				cout
					<< "Выберите тип объявления:\n"
					<< "1. Купля\n"
					<< "2. Продажа" << endl;

				unsigned short choice;
				cin >> choice;
				if (choice == 1 || choice == 2)
				{
					new_element.setBS(choice);
					break;
				}
				else { cout << "Неверный тип" << endl; }
			}

			cout << "Введите рубрику объявления" << endl;
			cin >> buffer;
			new_element.setCategory(buffer);

			while (true)
			{
				cout << "Введите контактный номер (без 8)" << endl;
				unsigned long long number = 0;
				bool failed = false;
				cin >> buffer;
				for (size_t i = 0; i < buffer.size(); i++)
				{
					if (buffer[i] >= '0' && buffer[i] <= '9')
					{
						number = number * 10 + buffer[i] - '0';
					}
					else
					{
						cout << "Неверный номер" << endl;
						failed = true;
						break;
					}
				}
				if (failed == false)
				{
					new_element.setNumber(number);
					break;
				}
			}

			cout << "Введите текст объявления" << endl;
			cin >> buffer;
			new_element.setAdText(buffer);

			list.add(new_element);
			break;
		}

		case 2:
		{
			list.sort();
			cout << "Список отсортирован" << endl;
			break;
		}

		case 3:
		{
			cout << "Введите номер объявления: ";
			size_t index;
			cin >> index;
			if (list.del(index-1) == true) { cout << "Объявление успешно удалено"; }
			else { cout << "Нет такого объявления"; }
			break;
		}

		case 4:
		{
			cout << "Введите рубрику для поиска: ";
			string buffer;
			cin >> buffer;
			list.findCategory(buffer);
			break;
		}

		case 5:
		{
			cout << "Введите текст для поиска: ";
			string buffer;
			cin >> buffer;
			list.findText(buffer);
			break;
		}

		case 6:
		{
			list.out();
			break;
		}

		case 7:
		{
			cout << "Введите название файла для сохранеия" << endl;
			string buffer;
			cin >> buffer;
			if (list.save(buffer) == false) { cout << "Произошла ошибка при сохранении" << endl; }
			else { cout << "Список сохранён в файл " << buffer << endl; }
			break;
		}

		case 8:
		{
			cout << "Введите название файла для сохранеия" << endl;
			string buffer;
			cin >> buffer;
			if (list.load(buffer) == false) { cout << "Произошла ошибка при загрузке" << endl; }
			else { cout << "Список из файла " << buffer << " успешно загружен"<< endl; }
			break;
		}

		case 9:
		{
			list.clear();
			cout << "Список очищен" << endl;
			break;
		}

		case 10:
		{
			should_close = true;
			break;
		}

		default:
		{
			cout << "Неизвестное действие" << endl;
		}
		}
		
		if (!should_close)
		{
			cout << "\n\n\n";
			system("pause");
		}
	}
}