#include "List.h"

void Node::inputProduct()//ввод данных о товаре
{ 
	for(;;)
	{
		cout << "Введите категорию" << endl;
		cin >> category;

		cout << "Введите название товара" << endl;
		cin >> name;

		cout << "Введите количество" << endl;
		cin >> quantity;

		cout << "Введите цену" << endl;
		cin >> price;

		cout << "Введите торговую надбавку" << endl;
		cin >> percentage;

		cout << "Введите день" << endl;
		cin >> day;

		cout << "Введите месяц" << endl;
		cin >> month;

		cout << "Введите год" << endl;
		cin >> year;

		//проверяем полученные данные
		if (quantity < 0 || price < 0 || percentage < 0
			|| year < 1900 || month < 1 || day < 1 || day > 31 || month > 12 || year > 2022)
		{
			cout << "Произошла ошибка" << endl;
			continue;
		}

		int maximum_day = 31;
		if (month == 2)
		{
			if (year % 4 == 0) 	//в феврале в високосный год 29 дней
			{
				maximum_day = 29;
			}
			else
			{
				maximum_day = 28;//в обычный год 28 дней
			}
		}
		else
			if ((month < 8 && month % 2 == 0)	//в чётные дни до августа 30 дней
			|| (month > 7 && month % 2 == 1)) //в нечётные дни после июля 30 дней
			{
				maximum_day= 30;
			}
		
		if (day > maximum_day)	//если день превосходит лимит
		{
			cout << "Произошла ошибка" << endl;
			continue;
		}

		cout << "\nВвёденный товар:\n";
		show();
		cout << "\n[1] - Подтвердить" << endl;

		int key = _getch();
		//запрашиваем подтверждение данных
		if (key == '1') return;
		else continue;//при отклонении повторяем ввод
	}
}

bool Node::toFile(fstream& file)	//запись вершины списка в файл
{
	if (!file.is_open()) return false;	//если файл закрыт выходим с ошибкой
	file.clear();//очищение флагов состояния файлового потока
	//побайтово записываем в файл поля класса вершины списка
	file.write((const char*)(&prev), sizeof(prev));	
	file.write((const char*)(&next), sizeof(next));
	file.write((const char*)(&quantity), sizeof(quantity));
	file.write((const char*)(&day), sizeof(day));
	file.write((const char*)(&month), sizeof(month));
	file.write((const char*)(&year), sizeof(year));
	file.write((const char*)(&price), sizeof(price));
	file.write((const char*)(&percentage), sizeof(percentage));


	size_t size = name.size();	//получаем размер строки с названием и записываем в файл по байтам размер
	file.write((const char*)(&size), sizeof(size));
	if (size > 0) file.write(name.c_str(), size);//если размер не нулевой записываем и саму строку

	size = category.size();	//получаем размер строки с категорией товара
	file.write((const char*)(&size), sizeof(size));//побайтово записываем размер строки
	if (size > 0) file.write(category.c_str(), size);//если размер не нулевой то записываем и саму строку

	file.flush();//сбрасываем буфер потока в файл на диске
	if (file.fail()) return false;//при сбое выходим с ошибкой
	return true;
}

bool Node::fromFile(fstream& file)	//чтение вершины списка из файла
{
	if (!file.is_open()) return false;//если файл закрыт выходим с ошибкой
	file.clear();//очищение флагов состояния файлового потока 
	file.flush();//сбрасываем буфер потока в файл на диске
	//побайтово читаем из файла поля класса вершины списка
	file.read((char*)(&prev), sizeof(prev));
	file.read((char*)(&next), sizeof(next));
	file.read((char*)(&quantity), sizeof(quantity));
	file.read((char*)(&day), sizeof(day));
	file.read((char*)(&month), sizeof(month));
	file.read((char*)(&year), sizeof(year));
	file.read((char*)(&price), sizeof(price));
	file.read((char*)(&percentage), sizeof(percentage));

	size_t size = 0;
	file.read((char*)(&size), sizeof(size));	//считываем размер строки
	if (size > 0)//если размер не нулевой
	{
		char* str = new char[size];//выделяем память строке
		file.read(str, size);//считываем строку
		name.assign(str, size);//присваиваем строке в классе
		delete[] str;//освобождаем память
	}

	size = 0;
	file.read((char*)(&size), sizeof(size));//считываем размер строки
	if (size > 0)//если размер не нулевой
	{
		char* str = new char[size];//выделяем память строке
		file.read(str, size);//считываем строку
		category.assign(str, size);//присваиваем строке в классе
		delete[] str;//освобождаем память
	}

	if (file.fail()) return false;//при сбое  выходим с ошибкой
	return true;
}

void Node::show()//вывод товара в консоль
{
	cout << "Категория: " << category 
		<< "\nНазвание: " << name 
		<< "\nКоличество: " << quantity 
		<< "\nДата:" << day << '.' << month << '.' << year 
		<< "\nЦена: " << price 
		<< "\nНадбавка: " << percentage;
}

List::List()	//конструктор списка
	: size(0)
{
	file.open("warehouse.bin", ios::in | ios::out | ios::binary);	//пытаемся открыть существующий файл 
	if (!file.is_open())	//если файл не открылся
	{
		file.open("warehouse.bin", ios::out);	//создаём файл
		if (!file.is_open())	//если создать файл не удалось аварийно выходим из программы
		{
			cout << "Не удалось открыть файл warehouse.bin" << endl;
			exit(-1);
		}
		file.close();	//закрываем файл
		file.open("warehouse.bin", ios::in | ios::out | ios::binary);	//открываем на двоичные чтение и запись
	}
	else
	{
		Node temp;
		while (temp.fromFile(file))	//проходим по списку в файле
		{
			size++;	//подсчитываем размер
			if (temp.next != -1) file.seekg(temp.next);
			else break;
		}
	}
}

List::~List()	//деструктор списка
{
	if (file.is_open()) file.close();	//если файл открыт, закрываем
}

//добавление товара в конец списка
void List::add(string name, string category, int quantity, int day, int month, int year, int price, float percentage)
{
	Node temp;
	long long int prev_pos = -1, cur_pos = 0;//файловый указатель на элемент перед новым и на новый
	file.seekg(cur_pos);	//переходим в начало файла

	while (temp.fromFile(file))	//проходим до последнего элемента, считывая его
	{
		prev_pos = cur_pos;
		cur_pos = temp.next;
		if (cur_pos == -1) break;
		file.seekg(cur_pos);
	}

	file.seekg(0, ios::end);	//переходим в конец файла
	cur_pos = file.tellg();	//запоминаем текущую позицию в файле
	//инициализируем поля новой вершины списка
	temp.prev = prev_pos;
	temp.next = -1;
	temp.name = name;
	temp.category = category;
	temp.quantity = quantity;
	temp.day = day;
	temp.month = month;
	temp.year = year;
	temp.price = price;
	temp.percentage = percentage;

	if (prev_pos != -1)	//если перед новой вершиной есть элементы
	{
		//переходим к месту в файле, где хранится файловый указатель 
		//на следующий элемент у элемента перед новым
		file.seekg(prev_pos + sizeof(long long int));
		file.write((const char*)(&cur_pos), sizeof(cur_pos));//записываем файловый указатель на новую вершину
	}
	file.seekg(cur_pos);//переходим в позицию новой вершины
	temp.toFile(file);//записываем вершину
	size++;//увеличиваем размер списка
	file.flush();//сохраняем изменения в файле на диск
}

//вставка товара по индексу
void List::insert(string name, string category, int quantity, int day, int month, int year, int price, float percentage, size_t index)
{
	if (index >= size)	//вставка в конец
	{
		add(name, category, quantity, day, month, year, price, percentage);
		return;
	}

	Node temp;
	
	if (index == 0)	//вставка в начало
	{
		long long int prev_pos = 0, next_pos = -1;
		fstream temp_file("temp.bin", ios::out | ios::binary);//создаём временный файл
		//инициализируем новую вершину
		temp.prev = -1;
		temp.next = -1;
		temp.name = name;
		temp.category = category;
		temp.quantity = quantity;
		temp.day = day;
		temp.month = month;
		temp.year = year;
		temp.price = price;
		temp.percentage = percentage;
		temp.toFile(temp_file);//записываем во временный файл

		next_pos = temp_file.tellg();//записываем в файловый указатель позицию для следующего элемента
		file.seekg(0);//перемещаемся в начало старого файла
		for (size_t i = 0; i < size; i++)//проходим по старому списку
		{
			temp.fromFile(file);//загружаем вершину из старого файла
			temp.prev = prev_pos;//связываем её с предыдущей вершиной, записанной во временный файл
			temp.next = -1;

			temp.toFile(temp_file);//записываем вершину во временный файл

			//связываем предыдущий элемент с последним
			temp_file.seekg(prev_pos + sizeof(next_pos));
			temp_file.write((const char*)(&next_pos), sizeof(next_pos));

			prev_pos = next_pos;
			temp_file.seekg(0, ios::end);	//переходим в конец временного файла и смещаем указатели
			next_pos = temp_file.tellg();
		}
		file.close();//закрываем файлы
		temp_file.close();
		remove("warehouse.bin");//удаляем старый файл
		rename("temp.bin", "warehouse.bin");//переименовываем временный файл
		file.open("warehouse.bin", ios::in | ios::out | ios::binary);//делаем его основным
		size++;//увеличиваем размер списка
		return;
	}

	long long int prev_pos = -1, next_pos = 0;
	file.seekg(next_pos);//переходим в начало файла
	for (size_t i = 0; i < index; i++)//проходим до нужного индекса
	{
		file.seekg(next_pos);//переходим к следующему файлу
		temp.fromFile(file);//загружаем из файла товар
		prev_pos = next_pos;//смещаем указатели
		next_pos = temp.next;
	}

	file.seekg(0, ios::end);//переходим к концу файла
	long long int cur_pos = file.tellg();	//сохраняем позицию нового элемента
	//инициализируем новую вершину
	temp.prev = prev_pos;
	temp.next = next_pos;
	temp.name = name;
	temp.category = category;
	temp.quantity = quantity;
	temp.day = day;
	temp.month = month;
	temp.year = year;
	temp.price = price;
	temp.percentage = percentage;
	temp.toFile(file);//загружаем новую вершину в файл

	file.seekg(prev_pos + sizeof(next_pos));//связываем предыдущий элемент с новым
	file.write((const char*)(&cur_pos), sizeof(cur_pos));

	file.seekg(next_pos);//связываем следующий элемент с новым
	file.write((const char*)(&cur_pos), sizeof(cur_pos));

	file.flush();//сохраняем изменения в файле на диск
	size++;//увеличиваем размер списка
}

bool List::removeAt(size_t index)	//удаление в заданной позиции
{
	if (index >= size) return false; //если нет такого индекса то выходим не удаляя элементы

	long long int last = -1, prev = -1;
	Node temp;
	fstream temp_file("temp.bin", ios::out | ios::binary);//создаём временный файл
	file.seekg(0);//переходим в начало старого файла
	for (size_t i = 0; i < size; i++) //проходим по списку
	{
		temp.fromFile(file);//считываем элемент
		if (i == index)//если индекс совпадает с удаляемым, то пропускаем его
		{
			if (temp.next != -1) file.seekg(temp.next);
			continue;
		}
		//иначе добавляем элемент в новый файл
		temp_file.seekg(0, ios::end);
		last = temp_file.tellg();
		temp.prev = prev;
		temp.next = -1;
		temp.toFile(temp_file);
		
		if (prev != -1)//связываем последний добавленный с новым
		{
			temp_file.seekg(prev + sizeof(prev));
			temp_file.write((const char*)(&last), sizeof(last));
		}
		prev = last;//смещаем указатель
	}
	//закрываем файлы
	file.close();
	temp_file.close();
	//удаляем старый файл, делаем новый основным
	remove("warehouse.bin");
	rename("temp.bin", "warehouse.bin");
	file.open("warehouse.bin", ios::in | ios::out | ios::binary);
	size--;
	return true;
}

long long int List::getNode(size_t index, Node& node)	//получение элемента по индексу
{
	if (index >= size) return -1;	//если нет элемента возвращаем несуществующий файловый указатель

	long long int pos = 0;
	file.seekg(pos);	//переходим в начало файла
	for (size_t i = 0; i < size; i++)	//проходим по списку
	{
		node.fromFile(file);	//загружаем вершину из файла
		if (i == index)	//если индекс совпадает с нужным
		{
			break;//выходим из цикла
		}

		pos = node.next;	//переходим в к следующему элементу
		file.seekg(node.next);
	}
	return pos; //возвращаем файловый указатель
}

//редактирование элемента по индексу
bool List::edit(string name, string category, int quantity, int day, int month, int year, int price, float percentage, size_t index)
{
	Node temp;
	long long int pos = getNode(index, temp);//получаем элемент по индексу
	if (pos == -1) return false;//если элемент не получен выходим с ошибкой

	if (temp.name.size() + temp.category.size() == name.size() + category.size())	//если размер записи в файле не изменится
	{
		file.seekg(pos);	//переходим по файловому указателю
		temp.name = name;
		temp.category = category;
		temp.quantity = quantity;
		temp.day = day;
		temp.month = month;
		temp.year = year;
		temp.price = price;
		temp.percentage = percentage;
		temp.toFile(file);//перезаписываем данные
		return true;
	}
	//если размер записи отличается
	removeAt(index);//удаляем старый элемент
	insert(name, category, quantity, day, month, year, price, percentage, index);//вставляем новый
	return true;
}

void List::show()//вывод списка в консоль
{
	file.seekg(0);//переходим в начало файла

	Node temp;
	cout << "Список: " << endl;
	while (temp.fromFile(file))//загружаем элементы из файла
	{
		temp.show();//выводим в консоль элемент
		cout << endl << endl;
		if (temp.next == -1) break;
		file.seekg(temp.next);//переходим к следующему элементу
	}
}

//вставка с сохранением порядка
void List::insertInOrder(string name, string category, int quantity, int day, int month, int year, int price, float percentage)
{
	if (size == 0)//если список пуст
	{
		//просто вставляем элемент
		add(name, category, quantity, day, month, year, price, percentage);
		return;
	}

	Node temp;
	for (size_t i = 0; i < size; i++)//проходим по списку
	{
		getNode(i, temp);//получаем элемент по индексу
		if (temp.name >= name)//если название товара в алфавитном порядке после нового
		{
			insert(name, category, quantity, day, month, year, price, percentage, i);//вставляем на это место новый элемент
			return;
		}
	}
	//если дошли до конца списка вставляем в конец списка новый элемент
	add(name, category, quantity, day, month, year, price, percentage);
}

void List::sort(SortType type)//сортировка
{
	if (size <= 1) return;	//если элементов меньше двух выходим

	long long int first_pos = 0;	//указатель на первый элемент
	for (size_t i = 1; i < size; i++)	//проходим количество итераций меньше чем размер на 1
	{
		file.seekg(first_pos);	//переходим к первому элементу
		for (size_t j = 0; j < size - i; j++)//проходим по неотсортированной части
		{
			//получаем два элемента (левый и правый)
			long long int pos1 = file.tellg();	
			Node temp1, temp2;
			temp1.fromFile(file);
			file.seekg(temp1.next);

			long long int pos2 = file.tellg();
			temp2.fromFile(file);

			//сравниваем элементы по заданному критерию
			if ((type == SortType::Category && temp1.category > temp2.category)
				|| (type == SortType::Name && temp1.name > temp2.name)
				|| (type == SortType::Percentage && temp1.percentage > temp2.percentage)
				|| (type == SortType::Price && temp1.price > temp2.price)
				|| (type == SortType::Quantity && temp1.quantity > temp2.quantity)
				|| (type == SortType::Date && (temp1.year > temp2.year 
					|| (temp1.year == temp2.year && (temp1.month > temp2.month 
						|| (temp1.month == temp2.month && temp1.day > temp2.day))))))
			{
				if (temp1.prev != -1)//если левый элемент не первый в списке
				{
					file.seekg(temp1.prev + sizeof(pos2));//связываем его предыдущий элемент с правым элементом
					file.write((const char*)(&pos2), sizeof(pos2));
				}
				else//в ином случае заменяем файловый указатель на первый элемент на правый элемент
				{
					first_pos = pos2;
				}

				if (temp2.next != -1)//если правый элемент не последний в списке
				{
					file.seekg(temp2.next);//связываем следующий за ним элемент с левым элементом
					file.write((const char*)(&pos1), sizeof(pos1));
				}
				//перевязываем указатели двух сравниваемых элементов
				file.seekg(pos1);
				file.write((const char*)(&pos2), sizeof(pos2));
				file.write((const char*)(&temp2.next), sizeof(temp2.next));

				file.seekg(pos2);
				file.write((const char*)(&temp1.prev), sizeof(temp1.prev));
				file.write((const char*)(&pos1), sizeof(pos1));

				file.seekg(pos1);//переходим к следующему элементу
			}
			else file.seekg(pos2);//переходим к следующему элементу
		}
	}

	Node first, temp;
	long long int file_pos = getNode(0, first);//файловый указатель для движения по старому файлу
	size_t index = 0;
	while (first.prev != -1) //находим первый элемент в списке
	{
		file_pos = first.prev;//перемещаемся к предыдущим элементам
		file.seekg(first.prev);
		first.fromFile(file);
		index++;//считаем индекс элемента, который стоит первым в файле
	}

	if (index != 0)	//если индекс не нулевой(то есть первый в файле элемент - не первый в списке)
	{
		fstream temp_file("temp.bin", ios::binary | ios::out);//создаём временный файл

		long long int temp_pos = -1;
		for (size_t i = 0; i < size; i++)//проходим по списку и копируем элементы в новый файл
		{
			file.seekg(file_pos);	//перемещаемся к следующему элементу в старом файле
			temp.fromFile(file);	//считываем элемент
			file_pos = temp.next;	//смещаем указатель на следующий элемент

			temp.prev = temp_pos;	//сохраняем в считанном элементе указатель на предыдущий элемент
			temp.next = -1;	//за новым элементом нет следующего
			temp_pos = temp_file.tellg();	//сохраняем текущую позицию в новом файле как предыдущюю для следующего элемента
			temp.toFile(temp_file); //сохраняем новый элемент в новом файле

			if (temp.prev != -1)	//если есть предыдущий элемент
			{
				temp_file.seekg(temp.prev + sizeof(temp_pos));	//смещаемся к указателю на следующий элемент предыдущего элемента
				temp_file.write((const char*)(&temp_pos), sizeof(temp_pos));	//устанавливаем указатель на новый элемент
			}
			temp_file.seekg(0, ios::end);
		}
		//закрываем файлы
		file.close();
		temp_file.close();
		//удаляем старый файл, новый делаем основным
		remove("warehouse.bin");
		rename("temp.bin", "warehouse.bin");

		file.open("warehouse.bin", ios::in | ios::out | ios::binary);
	}
}

void List::invoice() //фактура
{
	int total_sum = 0, total_quantity = 0;
	float total_percentage = 0.f;

	long long int position = 0;
	
	for (size_t i = 0; i < size; i++)//проходим по списку
	{
		file.seekg(position);
		Node temp;
		temp.fromFile(file);//загружаем элемент

		total_sum += temp.price * temp.quantity;//прибавляем сумму
		total_quantity += temp.quantity;//прибавляем количество
		total_percentage += temp.percentage;//прибавялем надбавку

		file.seekg(position);//переходим к началу элемента
		temp.quantity = 0;//меняем количество на ноль
		temp.toFile(file);//обновляем элемент

		position = temp.next;//переходим к следующему элементу
	}
	//выводим подсчёты
	cout << "Итоговая сумма: " << total_sum << endl;
	cout << "Итоговая надбавка: " << total_percentage<< endl;
	cout << "Общее количество: " << total_quantity << endl;
}