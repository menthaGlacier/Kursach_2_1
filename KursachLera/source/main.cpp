#include "../include/dependencies.h"
#include "../include/Train.h"
#include "../include/FileList.h"
#include "../include/Menu.h"

int main() {
	Menu menu;

	// Запускаем цикл бесконечного меню
	while(true) {
		menu.mainMenu();
	}

	return 0;
}
