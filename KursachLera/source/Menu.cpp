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
			input.clear(); // Очищаем строку ввода от прошлого ввода
			cin.clear(); // Очищаем поток ввода от мусора
			getline(cin, input); // Получаем ввод пользователя

			if (input == "1") {
				cout << "Введите имя файла: ";
				input.clear(); // Очищаем строку ввода от прошлого ввода
				cin.clear(); // Очищаем поток ввода от мусора
				getline(cin, input); // Получаем ввод пользователя
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

	while(true) {
		cout << "Ваш ввод: ";
		input.clear(); // Очищаем строку ввода от прошлого ввода
		cin.clear(); // Очищаем поток ввода от мусора
		getline(cin, input); // Получаем ввод пользователя

		if (input == "1") {
			cout << "Введите данные" << endl;
			Train train = inputTrain(); // Производимв ввод объекта
			
			cout << "Выберите действие:" << endl;
			cout << "1 -- Вставка в конец" << endl;
			cout << "2 -- Вставка по логическому номеру" << endl;
			
			while(true) {
				cout << "Ваш ввод: ";
				input.clear(); // Очищаем строку ввод от прошлого ввода
				cin.clear(); // Очищаем поток ввода от мусора
				getline(cin, input); // Получаем ввод пользователя

				if (input == "1") {
					list->insert(train); // Производим вставку в конец
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
				cout << "Ваш ввод: ";
				input.clear(); // Очищаем строку ввода от прошлого ввода
				cin.clear(); // Очищаем поток ввода от мусора
				getline(cin, input); // Получаем ввод пользователя

				if (input == "1") {
					list->deletion();
					break;
				} else if (input == "2") {
					cout << "Введите логический номер для удаления: ";
					input.clear(); // Очищаем строку ввода от прошлого ввода
					cin.clear(); // Очищаем поток ввода от мусора
					getline(cin, input); // Получаем ввод пользователя

					unsigned int index = stoul(input); // Переводим ввод в логический номер
					list->deletion(index); // Производим удаление по логическому номеру
					break;
				}
			}

			break;
		} else if (input == "3") {
			list->sort();
			break;
		} else if (input == "4") {
			Train train; // Объект для ввода
			cout << "Введите логический номер узла для обновления: ";
			input.clear(); // Очищаем строку ввода от прошлого ввода
			cin.clear(); // Очищаем поток ввода от мусора
			getline(cin, input); // Получаем ввод пользователя

			unsigned int index = stoul(input); // Переводим ввод в логический номер
			
			cout << "Введите данные" << endl;
			train = inputTrain(); // Производимв ввод объекта
			list->update(train, index); // Производим обновление элемента
			break;
		} else if (input == "5") {
			cout << "Выберите действие:" << endl;
			cout << "1 -- Полный просмотр списка" << endl;
			cout << "2 -- Постраничный просмотр" << endl;
			
			while(true) {
				cout << "Ваш ввод: ";
				input.clear(); // Очищаем строку ввода от прошлого ввода
				cin.clear(); // Очищаем поток ввода от мусора
				getline(cin, input); // Получаем ввод пользователя

				if (input == "1") {
					list->print();
					break;
				} else if (input == "2") {
					list->pageViewPrint();
					break;
				}
			}

			break;
		} else if (input == "6") {
			cout << "Введите станцию назначения: ";
			input.clear(); // Очищаем строку ввода от прошлого ввода
			cin.clear(); // Очищаем поток ввода от мусора
			getline(cin, input); // Получаем ввод пользователя
			list->find(stoul(input)); // Ищем все поезда, следующие до станции
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
	input.clear(); // Очищаем строку ввода от прошлого ввода
	cin.clear(); // Очищаем поток ввода от мусора
	getline(cin, input); // Получаем ввод пользователя
	train.setTrainNumber(stoul(input)); // Переводим ввод в число и присваивем

	cout << "Введите рабочие дни недели: ";
	input.clear(); // Очищаем строку ввода от прошлого ввода
	cin.clear(); // Очищаем поток ввода от мусора
	getline(cin, input); // Получаем ввод пользователя
	train.setDaysOfWeek(input); // Присваиваем строку
	
	cout << "Введите часы времени отправления: ";
	input.clear(); // Очищаем строку ввода от прошлого ввода
	cin.clear(); // Очищаем поток ввода от мусора
	getline(cin, input); // Получаем ввод пользователя
	train.setDepartureTimeHours(stoul(input)); // Переводим ввод в число и присваивем

	cout << "Введите минуты времени отправления: ";
	input.clear(); // Очищаем строку ввода от прошлого ввода
	cin.clear(); // Очищаем поток ввода от мусора
	getline(cin, input); // Получаем ввод пользователя
	train.setDepartureTimeMinutes(stoul(input)); // Переводим ввод в число и присваивем
	
	cout << "Введите часы времени в пути: ";
	input.clear(); // Очищаем строку ввода от прошлого ввода
	cin.clear(); // Очищаем поток ввода от мусора
	getline(cin, input); // Получаем ввод пользователя
	train.setTravelTimeHours(stoul(input)); // Переводим ввод в число и присваивем
	
	cout << "Введите минуты времени в пути: ";
	input.clear(); // Очищаем строку ввода от прошлого ввода
	cin.clear(); // Очищаем поток ввода от мусора
	getline(cin, input); // Получаем ввод пользователя
	train.setTravelTimeMinutes(stoul(input)); // Переводим ввод в число и присваивем
	
	cout << "Введите станцию отправления: ";
	input.clear(); // Очищаем строку ввода от прошлого ввода
	cin.clear(); // Очищаем поток ввода от мусора
	getline(cin, input); // Получаем ввод пользователя
	train.setDepartureStationNumber(stoul(input)); // Переводим ввод в число и присваивем
	
	cout << "Введите станцию назначения: ";
	input.clear(); // Очищаем строку ввода от прошлого ввода
	cin.clear(); // Очищаем поток ввода от мусора
	getline(cin, input); // Получаем ввод пользователя
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
