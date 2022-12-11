#include "MainMenu.h"

void MainMenu::start() {
	while (true) {
		// Выводим список достпуныз действий
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

void MainMenu::scheduleInsert() {

}

void MainMenu::scheduleRemove() {

}

void MainMenu::schedulePrint() {

}

void MainMenu::scheduleSearch() {

}

void MainMenu::scheduleOrder() {

}

void MainMenu::scheduleSave() {
	cout << "Your file name: ";
	getline(cin, input);
	if (!schedule.save(input.c_str())) {
		cout << "Schedule was not saved in file" << endl;
	} else {
		cout << "Saved schedule in " << input << endl;
	}
}

void MainMenu::scheduleLoad() {
	cout << "Your file name: ";
	getline(cin, input);
	if (!schedule.load(input.c_str())) {
		cout << "Schedule was not loaded from file" << endl;
	} else {
		cout << "Load schedule from " << input << endl;
	}
}