#include <iostream>

#include "Header.h"
#include "Product.h"
#include "List.h"
#include "Menu.h"

int main() {
	//Product prod1("Test1", "food", 909, 17, 0, 11, 10, 2007);
	//Product prod2("Test2", "goods", 0, 0, -1, 0, 0, 0);
	//Product prod3("Test3", "something idk", 11, 11.4, 11.11, 11, 11, 2011);

	//List list;
	//list.insert(prod3);
	//list.insert(prod1);
	//list.insert(prod2);
	//list.insert(prod3, 111);
	//list.output();

	//std::cout << std::endl << std::endl;
	//list.remove(3);
	//list.output();

	Menu menu;
	menu.launch();
	return 0;
}