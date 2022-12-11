#include "Menu.h"

void Menu::launch() {
	while (true) {
		std::cout <<
			">>>>>>>>>>Available actions:\n"
			"[1] Show product list\n"
			"[2] Add new product to list\n"
			"[3] Delete product from list\n"
			"[4] Sort list\n"
			"[5] Search in list\n"
			"[6] Save list to file\n"
			"[7] Load list from file\n"
			"[Q] Quit\n"
			"Choise: "
		<< std::flush;

		std::getline(std::cin, input_line);
		if (input_line.size() != 1) { 
			std::cout << "Wrong input" << std::endl; 
			continue;
		}

		switch (input_line[0]) {
			case '1': {
				warehouse.output();
				break;
			}
			case '2': {
				actionAdd();
				break;
			}
			case '3': {
				actionRemove();
				break;
			}
			case '4': {
				actionSort();
				break;
			}
			case '5': {
				actionSearch();
				break;
			}
			case '6': {
				actionSave();
				break;
			}
			case '7': {
				actionLoad();
				break;
			}
			case 'q':
			case 'Q': {
				return;
			}
			default: {
				std::cout << "Unknown action" << std::endl;
				break;
			}
		}
	}


}

void Menu::actionAdd() {
	while (true) {
		std::cout <<
			">>>>>>>>>>Where to add product:\n"
			"[1] Add to the end of list\n"
			"[2] Add to a specific position\n"
			"[3] Add a product keeping current order\n"
			"[B] Go back\n"
			"Choise: "
		<< std::flush;

		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;
		}

		switch (input_line[0]) {
			case '1': {
				warehouse.insert(inputProduct());
				return;
			}
			case '2': {
				while (true) {
					size_t position;
					std::cout << "Enter position" << std::endl;
					try {
						std::getline(std::cin, input_line);
						position = std::stoul(input_line);
					}
					catch (...) {
						std::cout << "Error occured. Try again" << std::endl;
						continue;
					}

					warehouse.insert(inputProduct(), position);
					return;
				}
			}
			case '3': {//TODO INSORT
				while (true) {
					std::cout <<
						">>>>>>>>>>Insort by:\n"
						"[1] Product name\n"
						"[2] Category\n"
						"[3] Quantity\n"
						"[4] Date\n"
						"[5] Price\n"
						"[6] Markup percentage\n"
						"[B] Go back\n"
						"Choise: "
						<< std::flush;

					std::getline(std::cin, input_line);
					if (input_line.size() != 1) {
						std::cout << "Wrong input" << std::endl;
						continue;
					}

					switch (input_line[0]) {
						case '1': {
							warehouse.insort(ProductFieldName::Name, inputProduct());
							return;
						}
						case '2': {
							warehouse.insort(ProductFieldName::Category, inputProduct());
							return;
						}
						case '3': {
							warehouse.insort(ProductFieldName::Quantity, inputProduct());
							return;
						}
						case '4': {
							warehouse.insort(ProductFieldName::Date, inputProduct());
							return;
						}
						case '5': {
							warehouse.insort(ProductFieldName::Price, inputProduct());
							return;
						}
						case '6': {
							warehouse.insort(ProductFieldName::Percentage, inputProduct());
							return;
						}
						case 'b':
						case 'B': {
							return;
						}
						default: {
							std::cout << "Unknown action" << std::endl;
							break;
						}
					}
				}
				break;
			}
			case 'b':
			case 'B': {
				return;
			}
			default: {
				std::cout << "Unknown action" << std::endl;
				break;
			}
		}
	}
}

void Menu::actionRemove() {
	if (warehouse.getSize() == 0) {
		std::cout << "List is empty" << std::endl;
		return;
	}

	while (true) {
		std::cout <<
			">>>>>>>>>>Where to delete product:\n"
			"[1] Delete last in the list\n"
			"[2] Delete product in a specific position\n"
			"[B] Go back\n"
			"Choise: "
		<< std::flush;

		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;
		}

		switch (input_line[0]) {
			case '1': {
				warehouse.remove();
				return;
			}
			case '2': {
				while (true) {
					size_t position;
					std::cout << "Enter position" << std::endl;
					try {
						std::getline(std::cin, input_line);
						position = std::stoul(input_line);
					}
					catch (...) {
						std::cout << "Error occured. Try again" << std::endl;
						continue;
					}
					if (position >= warehouse.getSize()) {
						std::cout << "No element with such position" << std::endl;
					}
					else {
						warehouse.remove(position);
					}
					return;
				}
			}
			case 'b':
			case 'B': {
				return;
			}
			default: {
				std::cout << "Unknown action" << std::endl;
				break;
			}
		}
	}
}

void Menu::actionSort()
{
	bool reverse = false;
	while (true)
	{
		std::cout <<
			">>>>>>>>>>Sort:\n"
			"[1] In ascending order\n"
			"[2] In descending order\n"
			"[B] Go back\n"
			"Choise: "
			<< std::flush;

		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;
		}

		switch (input_line[0]) {
			case '1': {
				reverse = false;
				break;
			}
			case '2': {
				reverse = true;
				break;
			}
			case 'b':
			case 'B': {
				return;
			}
			default: {
				std::cout << "Unknown action" << std::endl;
				continue;
			}
		}

		while (true) {
			std::cout <<
				">>>>>>>>>>Sort by:\n"
				"[1] Product name\n"
				"[2] Category\n"
				"[3] Quantity\n"
				"[4] Date\n"
				"[5] Price\n"
				"[6] Markup percentage\n"
				"[B] Go back\n"
				"Choise: "
				<< std::flush;

			std::getline(std::cin, input_line);
			if (input_line.size() != 1) {
				std::cout << "Wrong input" << std::endl;
				continue;
			}

			switch (input_line[0]) {
				case '1': {
					warehouse.sort(ProductFieldName::Name, reverse);
					return;
				}
				case '2': {
					warehouse.sort(ProductFieldName::Category, reverse);
					return;
				}
				case '3': {
					warehouse.sort(ProductFieldName::Quantity, reverse);
					return;
				}
				case '4': {
					warehouse.sort(ProductFieldName::Date, reverse);
					return;
				}
				case '5': {
					warehouse.sort(ProductFieldName::Price, reverse);
					return;
				}
				case '6': {
					warehouse.sort(ProductFieldName::Percentage, reverse);
					return;
				}
				case 'b':
				case 'B': {
					return;
				}
				default: {
					std::cout << "Unknown action" << std::endl;
					break;
				}
			}
		}
	}
}

void Menu::actionSearch() {
	while (true) {
		std::cout <<
			">>>>>>>>>>Search for:\n"
			"[1] Product name\n"
			"[2] Category\n"
			"[3] Quantity\n"
			"[4] Date\n"
			"[5] Price\n"
			"[6] Markup percentage\n"
			"[B] Go back\n"
			"Choise: "
		<< std::flush;

		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;
		}
	}
}

void Menu::actionSave()
{}

void Menu::actionLoad()
{}

Product Menu::inputProduct() {
	std::string name, category;
	size_t quantity, day, month, year;
	double price, percentage;

	while (true) {
		try {
			std::cout << "Enter product category" << std::endl;
			std::getline(std::cin, category);

			std::cout << "Enter product name" << std::endl;
			std::getline(std::cin, name);

			std::cout << "Enter product quantity" << std::endl;
			std::getline(std::cin, input_line);
			quantity = std::stoul(input_line);

			std::cout << "Enter product price" << std::endl;
			std::getline(std::cin, input_line);
			price = std::stod(input_line);

			std::cout << "Enter markup percentage" << std::endl;
			std::getline(std::cin, input_line);
			percentage = std::stod(input_line);

			std::cout << "Enter day" << std::endl;
			std::getline(std::cin, input_line);
			day = std::stoul(input_line);

			std::cout << "Enter month" << std::endl;
			std::getline(std::cin, input_line);
			month = std::stoul(input_line);

			std::cout << "Enter year" << std::endl;
			std::getline(std::cin, input_line);
			year = std::stoul(input_line);
		}
		catch (...) {
			std::cout << "Error occured. Try again" << std::endl;
			continue;
		}

		Product product(name, category, quantity, price, percentage, day, month, year);
		std::cout <<
			">>>>>>>>>>Confirm product:\n"
			<< product <<			
			"\n[1] Yes"
			"\n[2] No"
			"\nChoise: "
		<< std::flush;

		while (true) {
			std::getline(std::cin, input_line);
			if (input_line.size() == 1) {
				if (input_line[0] == '1') {
					return product; }
				else if (input_line[0] == '2') { break; }
			}
		}
	}
}