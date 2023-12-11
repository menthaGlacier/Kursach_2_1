#include "../include/Menu.h"

// Конструктор по умолчанию
Menu::Menu() {
	this->list = nullptr;
}

// Деструктор
Menu::~Menu() {
	// Очищаем память, если у нас есть список
	if (list) {
		delete list;
	}
}

//
void Menu::mainMenu() {
	string input; // Строка для чтения ввода пользователя

	cout << "-------- Главное меню --------" << std::endl;

	// Если списка нет, даём пользователю его открыть или создать
	if (!list) {
		cout << "Выберите действие:" << endl;
		cout << "1 -- Открыть/создать файл" << endl;
		cout << "2 -- Закрыть программу" << endl;

		while (true) {
			cout << "Ваш ввод: ";
			cin.clear(); //
			getline(cin, input); //

			if (input == "1") {
				cout << "Введите имя файла: ";
				input.clear(); //
				cin.clear(); //
				getline(cin, input); //
				list = new FileList(input); // Создаем объект списка
				break;
			} else if (input == "2") {
				exit(0); // Завершаем программу
			}
		}
	}

	cout << "Выберите действие:" << endl;
	cout << "1 -- Вставка" << endl;
	cout << "2 -- Удаление" << endl;
	cout << "3 -- Сортировка" << endl;
	cout << "4 -- Изменить данные" << endl;
	cout << "5 -- Просмотр списка" << endl;
	cout << "6 -- Поиск поездов, следующих до станции" << endl;
	cout << "7 -- Закрыть программу" << endl;

	input.clear(); //
	cin.clear(); //
	while(true) {
		cout << "Ваш ввод: ";
		cin.clear(); //
		getline(cin, input); //

		if (input == "1") {
			Train train = inputTrain(); // Производимв ввод объекта
			cout << "Выберите действие:" << endl;
			cout << "1 -- Вставка в конец" << endl;
			cout << "2 -- Вставка по логическому номеру" << endl;
			
			while(true) {
				input.clear(); //
				cin.clear(); //
				getline(cin, input); //

				if (input == "1") {
					list->insert(train);
					break;
				} else if (input == "2") {
					unsigned int index = 0;

					cout << "Введите логический номер для вставки: ";
					input.clear(); // Очищаем строку ввода от прошлого ввода
					cin.clear(); // Очищаем поток ввода от мусора
					getline(cin, input); // Получаем ввод пользователя

					index = stoul(input); // Переводим ввод в логический номер для вставки
					list->insert(train, index); // Производим вставку по логическому номеру
					break;
				}
			}

			break;
		} else if (input == "2") { // FIXME
			cout << "Выберите действие:" << endl;
			cout << "1 -- Удаление с конца" << endl;
			cout << "2 -- Удаление по логическому номеру" << endl;
			
			while(true) {
				input.clear(); //
				cin.clear(); //
				getline(cin, input); //

				if (input == "1") {
					list->remove();
					break;
				} else if (input == "2") {
					unsigned int index = 0;

					cout << "Введите логический номер для вставки: ";
					input.clear(); //
					cin.clear(); //
					getline(cin, input); //

					index = stoul(input); // Переводим ввод в логический номер для удаления
					list->remove(index); // Производим удаление по логическому номеру
					break;
				}
			}
			break;
		} else if (input == "3") {
			break;
		} else if (input == "4") {
			break;
		} else if (input == "5") {
			list->print();
			break;
		} else if (input == "6") {
			cout << "Введите станцию назначения: ";
			input.clear(); //
			cin.clear(); //
			getline(cin, input); //

			list->find(stoul(input));
			break;
		} else if (input == "7") {
			exit(0); // Завершаем программу
		}
	}
}

// Ввод объекта
Train Menu::inputTrain() {
	Train train; // Обьект по умолчанию
	string input; // Строка для ввода

	cout << "Введите номер поезда: ";
	cin.clear(); //
	getline(cin, input); //
	train.setTrainNumber(stoul(input)); // Переводим ввод в число и присваивем

	cout << "Введите рабочие дни недели: ";
	cin.clear(); //
	getline(cin, input); //
	train.setDaysOfWeek(input); // Присваиваем строку
	
	cout << "Введите часы времени отправления: ";
	cin.clear(); //
	getline(cin, input); //
	train.setDepartureTimeHours(stoul(input)); // Переводим ввод в число и присваивем

	cout << "Введите минуты времени отправления: ";
	cin.clear(); //
	getline(cin, input); //
	train.setDepartureTimeMinutes(stoul(input)); // Переводим ввод в число и присваивем
	
	cout << "Введите часы времени в пути: ";
	cin.clear(); //
	getline(cin, input); //
	train.setTravelTimeHours(stoul(input)); // Переводим ввод в число и присваивем
	
	cout << "Введите минуты времени в пути: ";
	cin.clear(); //
	getline(cin, input); //
	train.setTravelTimeMinutes(stoul(input)); // Переводим ввод в число и присваивем
	
	cout << "Введите станцию отправления: ";
	cin.clear(); //
	getline(cin, input); //
	train.setDepartureStationNumber(stoul(input)); // Переводим ввод в число и присваивем
	
	cout << "Введите станцию назначения: ";
	cin.clear(); //
	getline(cin, input); //
	train.setDestinationStationNumber(stoul(input)); // Переводим ввод в число и присваивем

	int transitStation = 0; // Переменная для чтения ввода промежуточных станций
	cout << "Введите станции отправления разделенных пробелом" << endl;
	cout << "Ввод отрицательных значений завершит ввод" << endl;
	cout << "Ваш ввод: ";
	
	// В цикле читаем ввод пока не возникнет ошибка или пока не будет введено отрицательное число
	while (cin >> transitStation && transitStation > 0) {
		train.appendToTransit(transitStation); // Добавляем станцию в массив
	}

	// Возвращаем объект с заданными значениями
	return train;
}
