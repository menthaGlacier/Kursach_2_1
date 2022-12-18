#include "Menu.h"

/*  */
Menu::Menu()
{
	// TODO
		// SUCK
}

/* ¬вод нового оюъ€влени€ дл€ вставки */
Advert& Menu::newAdvert()
{
	// TODO
		// SQUEEZE
}

/* */
void Menu::insertAct()
{
	// TODO
		// BANG
}

/* */
void Menu::removeAct()
{
	// TODO
		// BLOW
}

/*  */
void Menu::saveAct()
{
	std::cout << "Input file name for saving" << std::endl;
	std::cout << "Input: ";
	std::getline(std::cin, inputLine);
	if (board.save(inputLine))
		std::cout << "Saved" << std::endl;
	else
		std::cout << "Couldn't save" << std::endl;
}

/*  */
void Menu::loadAct()
{
	std::cout << "Input file name for loading" << std::endl;
	std::cout << "Input: ";
	std::getline(std::cin, inputLine);
	if (board.load(inputLine))
		std::cout << "Loaded" << std::endl;
	else
		std::cout << "Couldn't load" << std::endl;
}

/*  */
void Menu::sortAct()
{

}

/*  */
void Menu::findAct()
{
	board.findCategory();
	board.findAdText();
}

/*  */
void Menu::outputAct()
{
	board.output();
}