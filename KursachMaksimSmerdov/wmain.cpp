#include "dependencies.h"
#include "Announcement.h"
#include "List.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");	//устанавливаем русскую локаль и кодировку символов
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List list;	//создаём список
	bool should_close = false;	//переменная, обозначающая выход из программы при значении true
	string buffer;
	while (!should_close)
	{
		system("cls");	//очищаем экран

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
			<< "q. Выход\n"
			<< "Выберите действие: " << flush;
		char choise;

		cin >> choise;	//получаем выбор от пользователя
		cout << endl;

		switch (choise)
		{
		case '1':		//добавление объявления
		{
			Announcement new_element;	//добавляемый элемент
			while (true)	//получаем дату
			{
				cout << "Введите дату (дд.мм.гггг)" << endl;
				cin >> buffer;	

				if (!Announcement::dateCheck(buffer))	//делаем проверку даты
				{
					cout << "Неверная дата" << endl;
				}
				else	//если проверка успешна, добавляем дату в элемент
				{
					unsigned short day = (buffer[0] - '0') * 10 + (buffer[1] - '0');			//преобразовываем день и месяц
					unsigned short month = (buffer[3] - '0') * 10 + (buffer[4] - '0');	//из символов в числа
					unsigned short year = 0;
					for (size_t i = 6; i < 10; i++)	//преобразовываем год
					{
						year = year * 10 + buffer[i] - '0';
					}
					new_element.setDate(day, month, year);	//устанавливаем дату в элементе
					break;
				}
			}

			while (true)	//получаем тип объявления
			{
				cout
					<< "Выберите тип объявления:\n"
					<< "1. Купля\n"
					<< "2. Продажа" << endl;

				char choice;
				cin >> choice;
				if (choice == '1' || choice == '2')	//если ввод валидный
				{
					new_element.setBS(choice);		//устанавливаем тип объявления в элементе
					break;
				}
				else { cout << "Неверный тип" << endl; }
				cin.ignore(1000, '\n');	//игнорируем лишние символы, оставшиеся в потоке
			}

			cout << "Введите рубрику объявления" << endl;
			cin.ignore(1000, '\n');
			getline(cin, buffer);
			
			new_element.setCategory(buffer);

			while (true)	//устанавливаем номер телефона
			{
				cout << "Введите контактный номер (без 8)" << endl;
				unsigned long long number = 0;
				bool failed = false;
				cin >> buffer;
				for (size_t i = 0; i < buffer.size(); i++)	//преобразовываем полученные символы в числа
				{
					if (buffer[i] >= '0' && buffer[i] <= '9')
					{
						number = number * 10 + buffer[i] - '0';
					}
					else		//если символ не число
					{
						cout << "Неверный номер" << endl;
						failed = true;	//устанавливаем флаг ошибки
						break;	//прекращаем преобразование
					}
				}
				if (failed == false)	//если не была получена ошибка при преобразовании
				{
					new_element.setNumber(number);	//устанавливаем номер
					break;
				}
			}

			cout << "Введите текст объявления" << endl;
			cin.ignore(1000, '\n');
			getline(cin, buffer);
			
			new_element.setAdText(buffer);

			list.add(new_element);
			break;
		}

		case '2':	//Сортировка списка
		{
			list.sort();
			cout << "Список отсортирован" << endl;
			break;
		}

		case '3':	//Удаление объявления
		{
			cout << "Введите номер объявления: ";
			size_t index = 0;
			bool failed = false;
			cin >> buffer;	//получаем строку от пользователя
			for (size_t i = 0; i < buffer.size(); i++)	//преобразовываем строку в число
			{
				if (buffer[i] >= '0' && buffer[i] <= '9')
				{
					index = index * 10 + buffer[i] - '0';
				}
				else		//если символ не число
				{
					cout << "Неверный номер" << endl;
					failed = true;	//устанавливаем флаг ошибки
					break;	//завершаем преобразование
				}
			}
			//если успешно получено число и существует элемент с таким индексом, то удаляем его
			if (failed == false && list.del(index-1) == true) { cout << "Объявление успешно удалено"; }
			else { cout << "Нет такого объявления"; }
			break;
		}

		case '4':	//Поиск по рубрике
		{
			cout << "Введите рубрику для поиска: ";
			cin.ignore(1000, '\n');
			getline(cin, buffer);
			
			list.findCategory(buffer);
			break;
		}

		case '5':	//Поиск по тексту объявления
		{
			cout << "Введите текст для поиска: ";
			cin.ignore(1000, '\n');
			getline(cin, buffer);
			
			list.findText(buffer);	
			break;
		}

		case '6':	//Вывод списка
		{
			list.out();
			break;
		}

		case '7':	//Сохранение в файл
		{
			cout << "Введите название файла для сохранеия" << endl;
			cin.ignore(1000, '\n');
			getline(cin, buffer);
			
			if (list.save(buffer) == false) { cout << "Произошла ошибка при сохранении" << endl; }
			else { cout << "Список сохранён в файл " << buffer << endl; }
			break;
		}

		case '8':	//Загрузка из файла
		{
			cout << "Введите название файла для сохранеия" << endl;
			cin.ignore(1000, '\n');
			getline(cin, buffer);
			
			if (list.load(buffer) == false) { cout << "Произошла ошибка при загрузке" << endl; }
			else { cout << "Список из файла " << buffer << " успешно загружен"<< endl; }
			break;
		}

		case '9':	//Очистка списка
		{
			list.clear();
			cout << "Список очищен" << endl;
			break;
		}

		case 'q':	//Выход
		{
			should_close = true;
			break;
		}

		default:	//Остальные символы не обрабатываются
		{
			cout << "Неизвестное действие" << endl;
		}
		}

		if (!should_close)
		{
			cin.unget();
			cin.ignore(1000, '\n');
			cout << "\n\n\n";
			system("pause");
		}
	}
}