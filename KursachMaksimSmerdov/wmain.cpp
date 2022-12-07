#include "dependencies.h"
//#include "Announcement.h"
#include "List.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List list;
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
				buffer.clear();
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
				cout << "Выберите тип объявления (куплю/продам)" << std::endl;
				buffer.clear();
				cin >> buffer;
				if (buffer != "куплю" && buffer != "продам")
				{
					cout << "Неверный тип" << endl;
				}
				else
				{
					new_element.setBS(buffer);
					break;
				}
			}

			cout << "Введите рубрику объявления" << endl;
			buffer.clear();
			cin >> buffer;
			new_element.setCategory(buffer);

			cout << "Введите контактный номер (без 8)" << endl;
			unsigned long long number;
			cin >> number;
			new_element.setNumber(number);

			cout << "Введите текст объявления" << endl;
			buffer.clear();
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
			if (list.del(index-1) == true) { cout << "Объявление спешно удалено"; }
			else { cout << "Нет такого объявления"; }
			break;
		}

		case 4:
		{
			break;
		}

		case 5:
		{
			break;
		}

		case 6:
		{
			list.out();
			break;
		}

		case 7:
		{
			break;
		}

		case 8:
		{
			break;
		}

		case 9:
		{
			list.clear();
			break;
		}

		case 10:
		{
			should_close = true;
			break;
		}

		default:
		{

		}
		}

		cout << "\n\n\n";
		system("pause");
	}
}