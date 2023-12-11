#ifndef MENU_H
#define MENU_H

#include "dependencies.h"
#include "FileList.h"

class Menu {
public:
	Menu(); //
	~Menu(); //
	void mainMenu(); //
	Train inputTrain();
private:
	FileList* list;
	bool isOpen;
};

#endif /* MENU_H */
