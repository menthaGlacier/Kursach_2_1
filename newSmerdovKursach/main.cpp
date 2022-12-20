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
			<< "4. Редактировать объявление в списке\n"
			<< "5. Поиск объявления по рубрике\n"
			<< "6. Поиск объявления по тексту\n"
			<< "7. Показать список объявлений\n"
			<< "8. Постраничный просмотр объявлений\n"
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
				new_element.inputAnnouncement(new_element);

				while (true)
				{
					cout
						<< "<<<Куда добавить объявление>>>\n"
						<< "1. Добавить объявление в конец списка\n"
						<< "2. Вставить объявление в заданную позицию списка\n"
						<< "3. Вставить объявление с сохранением порядка\n"
						<< "Выберите действие: " << flush;

					char choise;

					cin >> choise;	//получаем выбор от пользователя
					cout << endl;

					switch (choise)
					{
						case '1': 
						{
							list.add(new_element);
							break;
						}
						case '2':
						{
							cout << "Введите номер" << endl;
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
								list.insert(new_element, number - 1);	//вставляем в заданную позицию
								break;
							}
							break;
						}
						case '3':
						{
							list.insertInOrder(new_element);
							break;
						}
						default:
						{
							cout << "Неизвестное действие" << endl;
							continue;
						}
					}
					break;
				}
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
				if (failed == false && list.removeAt(index - 1) == true) { cout << "Объявление успешно удалено"; }
				else { cout << "Нет такого объявления"; }
				break;
			}

			case '4'://редактирование
			{
				cout << "Введите номер объявления" << endl;
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

				Announcement temp;
				if (failed == true || list.getNode(index-1, temp) == -1)
				{
					cout << "Нет такого объявления"; 
					break;
				}

				temp.inputAnnouncement(temp);//получаем ввод нового объявления
				//пытаемся отредактировать объявление
				if (list.edit(temp, index-1) == false) { cout << "Не удалось изменить" << endl; }
				else { cout << "Изменено" << endl; }
				break;
			}
			case '5':	//Поиск по рубрике
			{
				cout << "Введите рубрику для поиска: ";
				cin.ignore(1000, '\n');
				getline(cin, buffer);

				list.findCategory(buffer);
				break;
			}

			case '6':	//Поиск по тексту объявления
			{
				cout << "Введите текст для поиска: ";
				cin.ignore(1000, '\n');
				getline(cin, buffer);

				list.findText(buffer);
				break;
			}

			case '7':	//Вывод списка
			{
				list.out();
				break;
			}
			case '8'://просмотр постранично
			{
				size_t index = 1;
				Announcement temp;
				bool go_back = false;
				while (!go_back)
				{
					if (list.getSize() == 0)
					{
						cout << "Список пуст" << endl;
						break;
					}

					list.getNode(index - 1, temp);
					cout << "Текущее объявление №" << index << endl;
					temp.print();
					cout << endl;
					cout << "Выберите действие:" << endl;
					cout << "1. Следующее" << endl;
					cout << "2. Предыдущее" << endl;
					cout << "b. Возвращение в меню" << endl;

					char choise;

					cin >> choise;	//получаем выбор от пользователя
					cout << endl;
					switch (choise)
					{
						case '1'://следующий
						{
							if (index < list.getSize())
							{
								index++;
							}
							else
							{
								cout << "Последний элемент" << endl;
							}
							continue;
						}
						case '2'://предыдущий
						{
							if (index > 1)
							{
								index--;
							}
							else
							{
								cout << "Первый элемент" << endl;
							}
							continue;
						}
						case 'b'://возвращение назад
						{
							go_back = true;
							break;
						}
						default:	//Остальные символы не обрабатываются
						{
							cout << "Неизвестное действие" << endl;
							continue;
						}
					}
					break;
				}
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