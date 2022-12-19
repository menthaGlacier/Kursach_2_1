#include "Menu.h"

/* ����������� �� ��������� � ����� �������� ���� */
Menu::Menu()
{
	while (true)
	{
		/* ���� */
		std::cout << "Welcome to Main Menu" << std::endl;
		std::cout << "[P] Put on the new advert on the board" << std::endl;
		std::cout << "[R] Remove the advert on the board" << std::endl;
		std::cout << "[S] Save advert board in a file" << std::endl;
		std::cout << "[L] Load advert board from a file" << std::endl;
		std::cout << "[O] Sort the advert board" << std::endl;
		std::cout << "[F] Find advert on the board" << std::endl;
		std::cout << "[U] Output the advert board in console" << std::endl;
		std::cout << "[Q] Quit" << std::endl;

		/* �������� ����, ������������ ����� � ��������� */
		std::getline(std::cin, inputLine);
		if (inputLine.size() != 1)
			continue;

		/* �������� ��� ���������, ��� � �������� ������� */
		switch (inputLine[0])
		{
		default:
			std::cout << "Wrong input" << std::endl;
			continue;
		case 'P':
		case 'p':
			insertAct();
			break;
		case 'R':
		case 'r':
			removeAct();
			break;
		case 'S':
		case 's':
			saveAct();
			break;
		case 'L':
		case 'l':
			loadAct();
			break;
		case 'O':
		case 'o':
			sortAct();
			break;
		case 'F':
		case 'f':
			findAct();
			break;
		case 'U':
		case 'u':
			outputAct();
			break;
		case 'Q':
		case 'q':
			exit(0);
		}
	}
}

/* ���� ������ ���������� ��� ������� */
Advert Menu::newAdvert()
{
	/* ������� ������, ���� ����� ������������� ���� */
	/* ����� ������� ��������� ���������� ��� ����� ����, ����� � ��� */
	Advert newAdvert;
	int y, m, d;

	/* �������� ����, ������������ ����� � ��������� */
	/* ���� ����� ��������, ���������� ����������� �������� */
	std::cout << "Is it for [B] buying or [S] selling?" << std::endl;
	std::getline(std::cin, inputLine);
	if (inputLine.size() != 1)
		newAdvert.setBuySell(false);

	/* �������� ��� ���������, ��� � �������� ������� */
	switch (inputLine[0])
	{
	default:
		newAdvert.setBuySell(false);
	case 'B':
	case 'b':
		newAdvert.setBuySell(false);
		break;
	case 'S':
	case 's':
		newAdvert.setBuySell(true);
		break;
	}

	std::cout << "Enter category" << std::endl;
	std::getline(std::cin, inputLine);
	newAdvert.setCategory(inputLine);

	std::cout << "Enter advert text" << std::endl;
	std::getline(std::cin, inputLine);
	newAdvert.setAdText(inputLine);

	/* ������ ���, ����� � ���� �� �����������. �������� ����� � ����� ����� ��� */
	std::cout << "Enter year" << std::endl;
	std::getline(std::cin, inputLine);
	y = stoul(inputLine);

	std::cout << "Enter month" << std::endl;
	std::getline(std::cin, inputLine);
	m = stoul(inputLine);

	std::cout << "Enter day" << std::endl;
	std::getline(std::cin, inputLine);
	d = stoul(inputLine);
	newAdvert.setDate(y, m, d);

	std::cout << "Enter number" << std::endl;
	std::getline(std::cin, inputLine);
	newAdvert.setNumber(stoul(inputLine));

	/* ���������� �������� ������. ������������ ���� ����� ���������� �� ����������� */
	return newAdvert;
}

/* ������� ���������� � ����� ���������� */
void Menu::insertAct()
{
	std::cout << "[L] Put new advert to the end of a board" << std::endl;
	std::cout << "[I] Put new advert to the specific index on the board" << std::endl;
	std::cout << "[S] Put new advert with sort" << std::endl;
	while (true)
	{
		/* �������� ����, ������������ ����� � ��������� */
		std::getline(std::cin, inputLine);
		if (inputLine.size() != 1)
			continue;

		/* �������� ��� ���������, ��� � �������� ������� */
		switch (inputLine[0])
		{
		default:
			std::cout << "Wrong input" << std::endl;
			break;
		case 'L':
		case 'l':
			board.insert(newAdvert());
			return;
		case 'I':
		case 'i':
			while (true)
			{
				std::cout << "Enter index" << std::endl;
				std::getline(std::cin, inputLine);
				int index = stoul(inputLine);
				if (index + 1 > board.size || index < 0)
				{
					std::cout << "Index's not in board's range" << std::endl;
					break;
				}

				else
				{
					board.insert(newAdvert(), index);
					return;
				}
			}
		case 'S':
		case 's':
			board.insort(newAdvert());
			return;
		}
	}
}

/* �������� ���������� ���������� */
void Menu::removeAct()
{
	std::cout << "[L] Remove last advert from board" << std::endl;
	std::cout << "[I] Remove advert from board by index" << std::endl;
	while (true)
	{
		/* �������� ����, ������������ ����� � ��������� */
		std::getline(std::cin, inputLine);
		if (inputLine.size() != 1)
			continue;

		/* �������� ��� ���������, ��� � �������� ������� */
		switch (inputLine[0])
		{
		default:
			std::cout << "Wrong input" << std::endl;
			break;
		case 'L':
		case 'l':
			board.remove();
			return;
		case 'I':
		case 'i':
			while (true)
			{
				std::cout << "Enter index" << std::endl;
				std::getline(std::cin, inputLine);
				int index = stoul(inputLine);
				if (index + 1 > board.size || index < 0)
				{
					std::cout << "Index's not in board's range" << std::endl;
					break;
				}

				else
				{
					board.remove(index);
					return;
				}
			}
		}
	}
}

/* ���������� ����� ���������� � ���� */
void Menu::saveAct()
{
	std::cout << "Enter file name for saving" << std::endl;
	std::getline(std::cin, inputLine);
	if (board.save(inputLine))
		std::cout << "Saved" << std::endl;
	else
		std::cout << "Couldn't save" << std::endl;
}

/* �������� ����� ���������� �� ����� */
void Menu::loadAct()
{
	std::cout << "Enter file name for loading" << std::endl;
	std::getline(std::cin, inputLine);
	if (board.load(inputLine))
		std::cout << "Loaded" << std::endl;
	else
		std::cout << "Couldn't load" << std::endl;
}

/* ���������� ����� ���������� */
void Menu::sortAct()
{
	board.sort();
}

/* ����� ���������� � ����� */
void Menu::findAct()
{
	std::cout << "[C] Find adverts by category" << std::endl;
	std::cout << "[T] Find adverts by ad text" << std::endl;
	while (true)
	{
		/* �������� ����, ������������ ����� � ��������� */
		std::getline(std::cin, inputLine);
		if (inputLine.size() != 1)
			continue;

		/* �������� ��� ���������, ��� � �������� ������� */
		switch (inputLine[0])
		{
		default:
			std::cout << "Wrong input" << std::endl;
			break;
		case 'C':
		case 'c':
			std::cout << "Enter category" << std::endl;
			std::getline(std::cin, inputLine);
			board.findCategory(inputLine);
			return;
		case 'T':
		case 't':
			std::cout << "Enter ad text" << std::endl;
			std::getline(std::cin, inputLine);
			board.findAdText(inputLine);
			return;
		}
	}
}

/* ����� ����� ���������� � ������� */
void Menu::outputAct()
{
	board.output();
}