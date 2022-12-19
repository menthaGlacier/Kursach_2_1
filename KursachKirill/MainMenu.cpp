#include "MainMenu.h"

// Запуск меню
void MainMenu::start() {
	while (true) {
		// Выводим список достпуных действий
		cout << "-------------Menu-------------" << endl;
		cout << "1 - Add a train to the schedule list" << endl
			<< "2 - Remove a train from the schedule list" << endl
			<< "3 - Print schedule list" << endl
			<< "4 - Search in schedule list" << endl
			<< "5 - Order schedule list" << endl
			<< "6 - Save schedule list to file" << endl
			<< "7 - Load schedule list from file" << endl
			<< "8 - Exit the program" << endl;
		cout << "Input: ";

		// Получаем ввод и проверяем его
		getline(cin, input);
		if (input.length() != 1) {
			cout << "Unknown input. Repeat" << endl;
			continue;
		}

		switch (input[0]) {
		case '1':
			scheduleInsert();
			break;
		case '2':
			scheduleRemove();
			break;
		case '3':
			schedulePrint();
			break;
		case '4':
			scheduleSearch();
			break;
		case '5':
			scheduleOrder();
			break;
		case '6':
			scheduleSave();
			break;
		case '7':
			scheduleLoad();
			break;
		case '8':
			return;
		default:
			cout << "Unknown action" << endl;
			continue;
		}
	}
}

// Операция вставки элемента в расписание
void MainMenu::scheduleInsert() {
	// Выводим список достпуных действий
	cout << "1 - Add at the end" << endl
		<< "2 - Add into pos" << endl
		<< "3 - Add keeping order" << endl;
	cout << "Input: ";

	Train inputTrain;
	while (true) {
		// Получаем ввод и проверяем его
		getline(cin, input);
		if (input.length() != 1) {
			cout << "Unknown input. Repeat" << endl;
			continue;
		}

		switch (input[0]) {
		case '1':
			inputTrain = enterTrain();
			schedule.insert(inputTrain);
			return;
		case '2':
			while (true) {
				cout << "Enter pos" << endl;
				getline(cin, input);
				uint pos = stoul(input);

				if (pos >= schedule.getSize()) {
					cout << "Input is incorrect" << endl;
				} else {
					inputTrain = enterTrain();
					schedule.insert(inputTrain, pos);
					return;
				}
			}

			break;
		case '3':
			inputTrain = enterTrain();
			schedule.insertOrdered(inputTrain);
		default:
			std::cout << "Unknown action" << std::endl;
			break;
		}
	}
}

// Операция удаления элемента из расписания
void MainMenu::scheduleRemove() {
	// Выводим список достпуных действий
	cout << "1 - Remove from the end" << endl
		<< "2 - Remove from pos" << endl;
	cout << "Input: ";

	while (true) {
		// Получаем ввод и проверяем его
		getline(cin, input);
		if (input.length() != 1) {
			cout << "Unknown input. Repeat" << endl;
			continue;
		}
	}

	switch (input[0]) {
	case '1':
		schedule.remove();
		return;
	case '2':
		while (true) {
			cout << "Enter pos" << endl;
			getline(cin, input);
			uint pos = stoul(input);

			if (pos >= schedule.getSize()) {
				cout << "Input is incorrect" << endl;
			} else {
				schedule.remove(pos);
				return;
			}
		}
	default:
		std::cout << "Unknown action" << std::endl;
		break;
	}
}

// Операция вывода расписания
void MainMenu::schedulePrint() {
	schedule.print();
}

// Операция поиска
void MainMenu::scheduleSearch() {
	cout << "Enter destination station to perform search: " << endl;
	getline(cin, input);
	uint searchStation = stoul(input);
	schedule.search(searchStation);
}

// Операция упорядочивания расписания
void MainMenu::scheduleOrder() {
	schedule.order();
}

// Операция сохранения расписания в бинарный файл
void MainMenu::scheduleSave() {
	cout << "Your file name: ";
	getline(cin, input);
	if (!schedule.save(input.c_str())) {
		cout << "Schedule was not saved in file" << endl;
	} else {
		cout << "Saved schedule in " << input << endl;
	}
}

// Операция загрузки расписания из двоичного файла
void MainMenu::scheduleLoad() {
	cout << "Your file name: ";
	getline(cin, input);
	if (!schedule.load(input.c_str())) {
		cout << "Schedule was not loaded from file" << endl;
	} else {
		cout << "Load schedule from " << input << endl;
	}
}

// Операция ввода расписания
Train MainMenu::enterTrain() {
	uint trainNum;
	string dayOfWeeks;
	uint startHour, startMinute;
	uint travelHours, travelMinutes;
	uint start, stop;
	vector<uint> transit;
	uint tempTransit;

	cout << "Any wrong input will be changes to defaults" << endl;
	while (true) {
		cout << "Enter train number" << endl;
		getline(cin, input);
		trainNum = std::stoul(input);

		cout << "Enter working day of weeks" << endl;
		getline(cin, input);
		dayOfWeeks = input;

		cout << "Enter departure hour" << endl;
		getline(cin, input);
		startHour = stoul(input);

		cout << "Enter departure minute" << endl;
		getline(cin, input);
		startMinute = stoul(input);

		cout << "Enter travel hours" << endl;
		getline(cin, input);
		travelHours = stoul(input);

		cout << "Enter travel minutes" << endl;
		getline(cin, input);
		travelMinutes = stoul(input);

		cout << "Enter departure station" << endl;
		getline(cin, input);
		start = stoul(input);

		cout << "Enter destination station" << endl;
		getline(cin, input);
		stop = stoul(input);

		cout << "Enter transit stations (0 to end)" << endl;
		while (cin >> tempTransit && tempTransit != 0) {
			transit.push_back(tempTransit);
		}

		return Train (trainNum, dayOfWeeks, startHour, startMinute,
			travelHours, travelMinutes, start, stop, transit);
	}
}