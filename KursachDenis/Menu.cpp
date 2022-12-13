#include "Menu.h"

void Menu::launch() {
	while (true) {
		std::cout <<
			"\n>>>>>>>>>>Available actions:\n"
			"[1] Show product list\n"
			"[2] Add new product to list\n"
			"[3] Delete product from list\n"
			"[4] Sort list\n"
			"[5] Search in list\n"
			"[6] Save list to file\n"
			"[7] Load list from file\n"
			"[8] Calculate invoice\n"
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
			case '8': {
				actionInvoice();
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
			"\n>>>>>>>>>>Where to add product:\n"
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
			case '3': {
				while (true) {
					std::cout <<
						"\n>>>>>>>>>>Insort by:\n"
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
			"\n>>>>>>>>>>Where to delete product:\n"
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
			"\n>>>>>>>>>>Sort:\n"
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
				"\n>>>>>>>>>>Sort by:\n"
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
			"\n>>>>>>>>>>Search for:\n"
			"[1] Product name\n"
			"[2] Category\n"
			"[3] Quantity\n"
			"[4] Date\n"
			"[5] Price\n"
			"[6] Markup percentage\n"
			"[7] Index\n"
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
				std::cout << "Enter product name" << std::endl;
				std::getline(std::cin, input_line);
				Product product;
				product.setName(input_line);
				warehouse.find(ProductFieldName::Name, product);
				return;
			}

			case '2': {
				std::cout << "Enter product category" << std::endl;
				std::getline(std::cin, input_line);
				Product product;
				product.setCategory(input_line);
				warehouse.find(ProductFieldName::Category, product);
				return;
			}

			case '3': {
				try {
					std::cout << "Enter product quantity" << std::endl;
					std::getline(std::cin, input_line);
					size_t quantity = std::stoul(input_line);

					Product product;
					product.setQuantity(quantity);

					std::cout <<
						"\n>>>>>>>>>>Confirm quantity:\n"
						<< product.getQuantity() <<
						"\n[1] Yes"
						"\n[2] No"
						"\nChoise: "
					<< std::flush;

					while (true) {
						std::getline(std::cin, input_line);
						if (input_line.size() == 1) {
							if (input_line[0] == '1') {
								warehouse.find(ProductFieldName::Quantity, product);
								return;
							}
							else if (input_line[0] == '2') { break; }
						}
					}
				}
				catch (...) {
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}

			case '4': {
				try {
					std::cout << "Enter day" << std::endl;
					std::getline(std::cin, input_line);
					size_t day = std::stoul(input_line);

					std::cout << "Enter month" << std::endl;
					std::getline(std::cin, input_line);
					size_t month = std::stoul(input_line);

					std::cout << "Enter year" << std::endl;
					std::getline(std::cin, input_line);
					size_t year = std::stoul(input_line);

					Product product;
					product.setDate(day, month, year);

					std::cout <<
						"\n>>>>>>>>>>Confirm date:\n"
						<< product.getDay() << '.' << product.getMonth() << '.' << product.getYear() <<
						"\n[1] Yes"
						"\n[2] No"
						"\nChoise: "
					<< std::flush;

					while (true) {
						std::getline(std::cin, input_line);
						if (input_line.size() == 1) {
							if (input_line[0] == '1') {
								warehouse.find(ProductFieldName::Date, product);
								return;
							}
							else if (input_line[0] == '2') { break; }
						}
					}
				}
				catch (...) {
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}

			case '5': {
				try {
					std::cout << "Enter product price" << std::endl;
					std::getline(std::cin, input_line);
					double price = std::stod(input_line);

					Product product;
					product.setPrice(price);

					std::cout <<
						"\n>>>>>>>>>>Confirm price:\n"
						<< product.getPrice() <<
						"\n[1] Yes"
						"\n[2] No"
						"\nChoise: "
					<< std::flush;

					while (true) {
						std::getline(std::cin, input_line);
						if (input_line.size() == 1) {
							if (input_line[0] == '1') {
								warehouse.find(ProductFieldName::Price, product);
								return;
							}
							else if (input_line[0] == '2') { break; }
						}
					}
				}
				catch (...) {
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}

			case '6': {
				try {
					std::cout << "Enter markup percentage" << std::endl;
					std::getline(std::cin, input_line);
					double percentage = std::stod(input_line);

					Product product;
					product.setPercentage(percentage);

					std::cout <<
						"\n>>>>>>>>>>Confirm markup:\n"
						<< product.getPercentage() <<
						"\n[1] Yes"
						"\n[2] No"
						"\nChoise: "
						<< std::flush;

					while (true) {
						std::getline(std::cin, input_line);
						if (input_line.size() == 1) {
							if (input_line[0] == '1') {
								warehouse.find(ProductFieldName::Percentage, product);
								return;
							}
							else if (input_line[0] == '2') { break; }
						}
					}
				}
				catch (...) {
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}

			case '7': {
				std::cout << "Enter position" << std::endl;
				try {
					std::getline(std::cin, input_line);
					size_t position = std::stoul(input_line);

					if (position >= warehouse.getSize()) {
						std::cout << "No element with such position" << std::endl;
					}
					else {
						std::cout << "#" << position << " ";
						warehouse.find(position)->output();
						std::cout << std::endl;
					}
					return;
				}
				catch (...) {
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}
			case 'b':
			case 'B': {
				return;
			}
		}
	}
}

void Menu::actionSave() {
	std::cout << "Enter filename" << std::endl;
	std::getline(std::cin, input_line);
	if (!warehouse.save(input_line)) {
		std::cout << "Error occured while saving" << std::endl;
	} else {
		std::cout << "Saved successfully" << std::endl;
	}
}

void Menu::actionLoad() {
	std::cout << "Enter filename" << std::endl;
	std::getline(std::cin, input_line);
	if (!warehouse.load(input_line)) {
		std::cout << "Error occured while loading" << std::endl;
	}
	else {
		std::cout << "Loaded successfully" << std::endl;
	}
}

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
			"\n>>>>>>>>>>Confirm product:\n"
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

void Menu::actionInvoice()
{
	if (warehouse.getSize() == 0) {
		std::cout << "List is empty" << std::endl;
		return;
	}

	List invoice;
	for (size_t i = 0; i < warehouse.getSize(); i++) {
		Product* product = warehouse.find(i);
		invoice.insert(*product);
		invoice.find(i)->setQuantity(0);
	}
	size_t index = 0;
	Product* warehouse_product = warehouse.find(index),
		* invoice_product = invoice.find(index);

	while (true) {
		std::cout <<
			"\nCurrent product:"
			"\n#" << index << " " << *warehouse_product << 
			"\n[1] Next product"
			"\n[2] Previous product"
			"\n[3] Add to invoice"
			"\n[4] Remove from invoice"
			"\n[5] Show current invoice"
			"\n[6] Sell and go back"
		<<std::endl;

		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;
		}

		switch (input_line[0]) {
			case '1': {
				if (warehouse.getSize() == index + 1) {
					index = 0;
				} else {
					index++;
				}

				warehouse_product = warehouse.find(index);
				invoice_product = invoice.find(index);
				continue;
			}
			case '2': {
				if (index == 0) {
					index = warehouse.getSize() - 1;
				} else {
					index--;
				}

				warehouse_product = warehouse.find(index);
				invoice_product = invoice.find(index);
				continue;
			}
			case '3': {
				std::cout << "Enter amount" << std::endl;
				std::getline(std::cin, input_line);

				try {
					size_t amount = std::stoul(input_line);

					if (amount > warehouse_product->getQuantity()) {
						std::cout << "There's not such amount of product in warehouse" << std::endl;
					} else {
						warehouse_product->setQuantity(warehouse_product->getQuantity() - amount);
						invoice_product->setQuantity(invoice_product->getQuantity() + amount);
					}
				}
				catch (...) {
					std::cout << "Error occured. Try again" << std::endl;
				}

				continue;
			}
			case '4': {
				std::cout << "Enter amount" << std::endl;
				std::getline(std::cin, input_line);

				try {
					size_t amount = std::stoul(input_line);

					if (amount > invoice_product->getQuantity()) {
						std::cout << "There's not such amount of product in invoice" << std::endl;
					}
					else {
						warehouse_product->setQuantity(warehouse_product->getQuantity() + amount);
						invoice_product->setQuantity(invoice_product->getQuantity() - amount);
					}
				}
				catch (...) {
					std::cout << "Error occured. Try again" << std::endl;
				}

				continue;
			}

			case '5':
			case '6': {
				double sum = 0.0, sum_no_mk = 0.0;
				for (size_t i = 0; i < invoice.getSize(); i++) {
					Product* product = invoice.find(i);
					double price = product->getPrice(),
						percentage = product->getPercentage(),
						quantity = (double) product->getQuantity();

					sum += quantity * price * (percentage + 100.0) / 100.0;
					sum_no_mk += quantity * price;
				}
				std::cout << "\nCurrent invoice:\n";
				invoice.output();

				if (sum_no_mk == 0.0) std::cout << "\nTotal sum: 0.0" << std::endl;
				else {
					std::cout <<
						"\nTotal sum: " << sum <<
						"\nSum without markup: " << sum_no_mk <<
						"\nTotal markup percentage: " << sum / sum_no_mk * 100.0
					<< std::endl;
				}

				if (input_line[0] == '6') { return; }
			}
		}
	}
}