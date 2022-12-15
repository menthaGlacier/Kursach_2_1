#include "Menu.h"

//запуск меню
void Menu::launch() {	
	while (true) {
		//доступные действия
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

		//получаем ввод от пользователя
		std::getline(std::cin, input_line);
		if (input_line.size() != 1) { 
			std::cout << "Wrong input" << std::endl; 
			continue;	//запрашиваем новый ввод если был введён не один символ
		}

		switch (input_line[0]) {
			case '1': {	//вывод списка в консоль
				warehouse.output();
				break;
			}
			case '2': {
				actionAdd();	//добавление товара
				break;
			}
			case '3': {
				actionRemove();	//удаление товара
				break;
			}
			case '4': {
				actionSort();	//сортировка
				break;
			}
			case '5': {
				actionSearch();	//поиск
				break;
			}
			case '6': {
				actionSave();	//сохранение в файл
				break;
			}
			case '7': {
				actionLoad();	//загрузка из файла
				break;
			}
			case '8': {
				actionInvoice();	//составление фактуры
				break;
			}
			case 'q':
			case 'Q': {
				return;	//выход из программы
			}
			default: {
				std::cout << "Unknown action" << std::endl;	
				break;//если был ввёден другой символ предлагаем выбрать заново
			}
		}
	}
}

void Menu::actionAdd() {	//добавление товара
	while (true) {
		std::cout <<
			"\n>>>>>>>>>>Where to add product:\n"
			"[1] Add to the end of list\n"
			"[2] Add to a specific position\n"
			"[3] Add a product keeping current order\n"
			"[B] Go back\n"
			"Choise: "
		<< std::flush;

		//получаем от пользователя ввод
		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;//запрашиваем новый ввод если был введён не один символ
		}

		switch (input_line[0]) {
			case '1': {	//вставка в конец
				//получаем от пользователя данные о товаре и вставляем в список
				warehouse.insert(inputProduct());	
				return;
			}
			case '2': {	//вставка в заданную позицию
				while (true) {
					size_t position;
					std::cout << "Enter position" << std::endl;	
					//запрашиваем у пользователя позицию
					try {
						std::getline(std::cin, input_line);
						position = std::stoul(input_line);	//преобразуем строку в число
					}
					catch (...) {	//обработка исключений, если строку не удалось преобразовать
						std::cout << "Error occured. Try again" << std::endl;
						continue;
					}
					//получаем от пользователя данные о товаре и вставляем на заданную позицию
					warehouse.insert(inputProduct(), position);
					return;
				}
			}
			case '3': {	//вставка с сохранением порядка
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
					//запрашиваем у пользователя, по какому критерию сохранять упорядоченность
					std::getline(std::cin, input_line);
					if (input_line.size() != 1) {
						std::cout << "Wrong input" << std::endl;
						continue;	//запрашиваем новый ввод если был введён не один символ
					}

					switch (input_line[0]) {
						//в зависимости от ввода, выбираем критерий и 
						//запрашиваем данные у пользователя о товаре
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
						case 'B': {	//возвращение назад в меню
							return;
						}
						default: {
							std::cout << "Unknown action" << std::endl;
							break;//если был введён другой символ, запрашиваем новый ввод
						}
					}
				}
				break;
			}
			case 'b':
			case 'B': {//возвращение назад в меню
				return;
			}
			default: {//если был введён другой символ, запрашиваем новый ввод
				std::cout << "Unknown action" << std::endl;
				break;
			}
		}
	}
}

void Menu::actionRemove() {	//удаление товара
	if (warehouse.getSize() == 0) {	//если список пуст, то выходим
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
		//получаем от пользователя ввод
		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;	//запрашиваем новый ввод если был введён не один символ
		}

		switch (input_line[0]) {
			case '1': {	//удаление последнего элемента
				warehouse.remove();
				return;
			}
			case '2': {	//удаление в заданной позиции
				while (true) {
					size_t position;
					std::cout << "Enter position" << std::endl;
					try {
						//получаем от пользователя ввод
						std::getline(std::cin, input_line);
						position = std::stoul(input_line);	//преобразовываем ввод в число
					}
					catch (...) {//если преобразование не удалось, обрабатываем исключение
						std::cout << "Error occured. Try again" << std::endl;
						continue;
					}
					if (position >= warehouse.getSize()) {
						//если полученная позиция не существует в списке
						//сообщаем об этом пользователю
						std::cout << "No element with such position" << std::endl;
					}
					else {//если элемент с полученным индексом есть, удаляем его
						warehouse.remove(position);
					}
					return;
				}
			}
			case 'b':
			case 'B': {	//возвращение назад в меню
				return;
			}
			default: {//если был введён другой символ, запрашиваем новый ввод
				std::cout << "Unknown action" << std::endl;
				break;
			}
		}
	}
}

void Menu::actionSort()	//сортировка
{
	//переменная, обозначающая сортировку по возрастанию или по убыванию
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

		//получаем от пользователя ввод
		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;	//запрашиваем новый ввод если был введён не один символ
		}

		switch (input_line[0]) {
			case '1': { //сортировка по возрастанию
				reverse = false;
				break;
			}
			case '2': {	//сортировка по убыванию
				reverse = true;
				break;
			}
			case 'b':
			case 'B': {	//возвращение назад в меню
				return;
			}
			default: {	//если был введён другой символ, запрашиваем новый ввод
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

			//получаем от пользователя ввод
			std::getline(std::cin, input_line);
			if (input_line.size() != 1) {
				std::cout << "Wrong input" << std::endl;
				continue;	//запрашиваем новый ввод если был введён не один символ
			}

			switch (input_line[0]) {
				//в зависимости от сортируем по заданному полю
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
				case 'B': {	//возврат назад в меню
					return;
				}
				default: {//если был введён другой символ, запрашиваем новый ввод
					std::cout << "Unknown action" << std::endl;
					break;
				}
			}
		}
	}
}

void Menu::actionSearch() {	//поиск
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

		//получаем от пользователя ввод
		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;	//запрашиваем новый ввод если был введён не один символ
		}

		switch (input_line[0]) {
			case '1': {	//поиск по названию
				std::cout << "Enter product name" << std::endl;
				std::getline(std::cin, input_line);	//получаем от пользователя название продукта
				Product product;
				product.setName(input_line);
				warehouse.find(ProductFieldName::Name, product);//ищем в списке продукт с заданным названием
				return;
			}

			case '2': {//поиск по категории
				std::cout << "Enter product category" << std::endl;
				std::getline(std::cin, input_line);//получаем от пользователя категорию продукта
				Product product;
				product.setCategory(input_line);
				warehouse.find(ProductFieldName::Category, product);//ищем в списке продукт с заданной категории
				return;
			}

			case '3': {//поиск по количеству
				try {
					std::cout << "Enter product quantity" << std::endl;
					std::getline(std::cin, input_line);//получаем от пользователя количество продукта
					size_t quantity = std::stoul(input_line);	//преобразовываем строку в число

					Product product;
					product.setQuantity(quantity);

					//запрашиваем подтверждение количества для поиска
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
								//выполняем поиск по количеству
								warehouse.find(ProductFieldName::Quantity, product);
								return;
							}
							else if (input_line[0] == '2') { break; }
						}
					}
				}
				catch (...) {//если преобразование строки не удалось обрабатываем исключение
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}

			case '4': {//поиск по дате
				try {
					std::cout << "Enter day" << std::endl;
					std::getline(std::cin, input_line);	//получаем от пользователя день
					size_t day = std::stoul(input_line);	//преобразовываем день в число

					std::cout << "Enter month" << std::endl;
					std::getline(std::cin, input_line);//получаем от пользователя месяц
					size_t month = std::stoul(input_line);//преобразовываем месяц в число

					std::cout << "Enter year" << std::endl;
					std::getline(std::cin, input_line);//получаем от пользователя год
					size_t year = std::stoul(input_line);//преобразовываем год в число

					Product product;
					product.setDate(day, month, year);

					//запрашиваем подтверждение даты
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
								//ищем по дате
								warehouse.find(ProductFieldName::Date, product);
								return;
							}
							else if (input_line[0] == '2') { break; }
						}
					}
				}
				catch (...) {//если преобразование строки не удалось обрабатываем исключение
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}

			case '5': {//поиск по стоимости
				try {
					std::cout << "Enter product price" << std::endl;
					std::getline(std::cin, input_line);	//получаем от пользователя стоимость
					double price = std::stod(input_line);//преобразуем строку в число

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
								//ищем по стоимости
								warehouse.find(ProductFieldName::Price, product);
								return;
							}
							else if (input_line[0] == '2') { break; }
						}
					}
				}
				catch (...) {//если преобразование строки не удалось обрабатываем исключение
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}

			case '6': {//поиск по торговой надбавке
				try {
					std::cout << "Enter markup percentage" << std::endl;
					std::getline(std::cin, input_line);//получаем от пользователя процент
					double percentage = std::stod(input_line);//преобразуем строку в число

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
								//ищем товар по надбавке
								warehouse.find(ProductFieldName::Percentage, product);
								return;
							}
							else if (input_line[0] == '2') { break; }
						}
					}
				}
				catch (...) {//если преобразование строки не удалось обрабатываем исключение
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}

			case '7': {//поиск по индексу
				std::cout << "Enter position" << std::endl;
				try {
					std::getline(std::cin, input_line);//получаем ввод индекса
					size_t position = std::stoul(input_line);	//преобразовываем строку в число

					if (position >= warehouse.getSize()) {	//если индекс выходит за пределы списка
						//сообщаем пользователю
						std::cout << "No element with such position" << std::endl;
					}
					else {
						std::cout << "#" << position << " ";	//если список содержит нужный элемент, выводим его
						warehouse.find(position)->output();
						std::cout << std::endl;
					}
					return;
				}
				catch (...) {	//если преобразование строки не удалось обрабатываем исключение
					std::cout << "Error occured. Try again" << std::endl;
					continue;
				}
			}
			case 'b':
			case 'B': {//возвращение назад в меню
				return;
			}
		}
	}
}

void Menu::actionSave() { //сохранение в файл
	std::cout << "Enter filename" << std::endl;
	std::getline(std::cin, input_line);	//получаем ввод названия файла
	if (!warehouse.save(input_line)) {//пытаемся сохранить в файл и сообщаем о результате
		std::cout << "Error occured while saving" << std::endl;
	} else {
		std::cout << "Saved successfully" << std::endl;
	}
}

void Menu::actionLoad() {
	std::cout << "Enter filename" << std::endl;
	std::getline(std::cin, input_line);//получаем ввод названия файла
	if (!warehouse.load(input_line)) {//загружаем список из файла
		std::cout << "Error occured while loading" << std::endl;
	}
	else {
		std::cout << "Loaded successfully" << std::endl;
	}
}

Product Menu::inputProduct() { //ввод данных о товаре
	std::string name, category;
	size_t quantity, day, month, year;
	double price, percentage;

	while (true) {
		try {
			//получение названия категории
			std::cout << "Enter product category" << std::endl;
			std::getline(std::cin, category);
			//получение названия товара
			std::cout << "Enter product name" << std::endl;
			std::getline(std::cin, name);
			//получения количества
			std::cout << "Enter product quantity" << std::endl;
			std::getline(std::cin, input_line);
			quantity = std::stoul(input_line);
			//получение стоимости
			std::cout << "Enter product price" << std::endl;
			std::getline(std::cin, input_line);
			price = std::stod(input_line);
			//получение процента надбавки
			std::cout << "Enter markup percentage" << std::endl;
			std::getline(std::cin, input_line);
			percentage = std::stod(input_line);
			//получение дня
			std::cout << "Enter day" << std::endl;
			std::getline(std::cin, input_line);
			day = std::stoul(input_line);
			//получение месяца
			std::cout << "Enter month" << std::endl;
			std::getline(std::cin, input_line);
			month = std::stoul(input_line);
			//получение года
			std::cout << "Enter year" << std::endl;
			std::getline(std::cin, input_line);
			year = std::stoul(input_line);
		}
		catch (...) {//если одно из преобразований строки в число не удалось, обрабатываем исключение
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
		//запрашиваем подтверждение данных
		while (true) {
			std::getline(std::cin, input_line);
			if (input_line.size() == 1) {
				if (input_line[0] == '1') {//при подтверждении возвращаем товар
					return product; }
				else if (input_line[0] == '2') { break; }
			}
		}
	}
}

void Menu::actionInvoice()	//составление фактуры
{
	if (warehouse.getSize() == 0) {//если список пуст выходим из метода
		std::cout << "List is empty" << std::endl;
		return;
	}

	List invoice;//список фактуры
	for (size_t i = 0; i < warehouse.getSize(); i++) {//копируем список товаров со склада
		Product* product = warehouse.find(i);
		invoice.insert(*product);
		invoice.find(i)->setQuantity(0);	//устанавливаем количество товара в фактуре ноль
	}
	size_t index = 0;//текущий индекс товара
	Product* warehouse_product = warehouse.find(index),	//текущий товар в складе
		* invoice_product = invoice.find(index);	//текущий товар в фактуре

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

		//получаем от пользователя ввод
		std::getline(std::cin, input_line);
		if (input_line.size() != 1) {
			std::cout << "Wrong input" << std::endl;
			continue;	//запрашиваем новый ввод если был введён не один символ
		}

		switch (input_line[0]) {
			case '1': {//переход к следующему товару
				if (warehouse.getSize() == index + 1) {
					index = 0;
				} else {
					index++;
				}

				//меняем указатели на текущие товары
				warehouse_product = warehouse.find(index);
				invoice_product = invoice.find(index);
				continue;
			}
			case '2': {//переход к предыдущему товару
				if (index == 0) {
					index = warehouse.getSize() - 1;
				} else {
					index--;
				}

				//меняем указатели на текущие товары
				warehouse_product = warehouse.find(index);
				invoice_product = invoice.find(index);
				continue;
			}
			case '3': {//добавление товара в фактуру
				std::cout << "Enter amount" << std::endl;
				std::getline(std::cin, input_line);//получаем от пользователя количество

				try {
					size_t amount = std::stoul(input_line);//преобразовываем строку в число

					if (amount > warehouse_product->getQuantity()) {	//если количество превышает количество на складе
						std::cout << "There's not such amount of product in warehouse" << std::endl;	//сообщаем в консоль
					} else {//в ином случае убираем товар со склада и добавляем в фактуру
						warehouse_product->setQuantity(warehouse_product->getQuantity() - amount);
						invoice_product->setQuantity(invoice_product->getQuantity() + amount);
					}
				}
				catch (...) {//если преобразование строки в число не удалось, обрабатываем исключение
					std::cout << "Error occured. Try again" << std::endl;
				}

				continue;
			}
			case '4': {//возвращение товара из фактуры на склад
				std::cout << "Enter amount" << std::endl;
				std::getline(std::cin, input_line);//получаем количество

				try {
					size_t amount = std::stoul(input_line);//преобразовываем строку в число

					if (amount > invoice_product->getQuantity()) {//если указанное количество превышает количество в фактуре
						std::cout << "There's not such amount of product in invoice" << std::endl;	//сообщаем в консоль
					} else {	// в ином случае убираем товар из фактуры и возвращаем на склад
						warehouse_product->setQuantity(warehouse_product->getQuantity() + amount);
						invoice_product->setQuantity(invoice_product->getQuantity() - amount);
					}
				}
				catch (...) {//если преобразование строки в число не удалось, обрабатываем исключение
					std::cout << "Error occured. Try again" << std::endl;
				}

				continue;
			}

			case '5':
			case '6': {//вывод фактуры (+ продажа и возращение)
				double sum = 0.0, sum_no_mk = 0.0;
				//получаем итоговые суммы по фактуре
				for (size_t i = 0; i < invoice.getSize(); i++) {
					Product* product = invoice.find(i);
					double price = product->getPrice(),
						percentage = product->getPercentage(),
						quantity = (double) product->getQuantity();

					sum += quantity * price * (percentage + 100.0) / 100.0;
					sum_no_mk += quantity * price;
				}
				//выводим фактуру
				std::cout << "\nCurrent invoice:\n";
				invoice.output();
				//выводим стоимость и торговую надбавку
				if (sum_no_mk == 0.0) std::cout << "\nTotal sum: 0.0" << std::endl;
				else {
					std::cout <<
						"\nTotal sum: " << sum <<
						"\nSum without markup: " << sum_no_mk <<
						"\nTotal markup percentage: " << sum / sum_no_mk * 100.0
					<< std::endl;
				}

				if (input_line[0] == '6') { return; }//если указано вернуться - возвращаем
			}
		}
	}
}