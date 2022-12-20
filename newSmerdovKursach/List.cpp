#include "List.h"

List::List()	//конструктор списка
	: size(0)
{
	file.open("board.bin", ios::in | ios::out | ios::binary);	//пытаемся открыть существующий файл 
	if (!file.is_open())	//если файл не открылся
	{
		file.open("board.bin", ios::out);	//создаём файл
		if (!file.is_open())	//если создать файл не удалось аварийно выходим из программы
		{
			cout << "Не удалось открыть файл board.bin" << endl;
			exit(-1);
		}
		file.close();	//закрываем файл
		file.open("board.bin", ios::in | ios::out | ios::binary);	//открываем на двоичные чтение и запись
	}
	else
	{
		Announcement temp;
		while (temp.loadFromFile(file))	//проходим по списку в файле
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
void List::add(Announcement& new_element)
{
	Announcement temp;
	long long int prev_pos = -1, cur_pos = 0;//файловый указатель на элемент перед новым и на новый
	file.seekg(cur_pos);	//переходим в начало файла

	while (temp.loadFromFile(file))	//проходим до последнего элемента, считывая его
	{
		prev_pos = cur_pos;
		cur_pos = temp.next;
		if (cur_pos == -1) break;
		file.seekg(cur_pos);
	}

	file.clear();
	file.seekg(0, ios::end);	//переходим в конец файла
	cur_pos = file.tellg();	//запоминаем текущую позицию в файле
	new_element.next = -1;

	if (prev_pos != -1)	//если перед новой вершиной есть элементы
	{
		//переходим к месту в файле, где хранится файловый указатель 
		//на следующий элемент у элемента перед новым
		file.seekg(prev_pos);
		file.write((const char*)(&cur_pos), sizeof(cur_pos));//записываем файловый указатель на новую вершину
		file.seekg(cur_pos);//переходим в позицию новой вершины
	}
	new_element.saveToFile(file);//записываем вершину
	size++;//увеличиваем размер списка
	file.flush();//сохраняем изменения в файле на диск
}

//вставка товара по индексу
void List::insert(Announcement& new_element, size_t index)
{
	if (index >= size)	//вставка в конец
	{
		add(new_element);
		return;
	}
	
	if (index == 0)	//вставка в начало
	{
		long long int prev_pos = 0, next_pos = -1;
		fstream temp_file("temp.bin", ios::out | ios::binary);//создаём временный файл
		//инициализируем новую вершину
		new_element.next = -1;
		new_element.saveToFile(temp_file);//записываем во временный файл

		next_pos = temp_file.tellg();//записываем в файловый указатель позицию для следующего элемента
		file.seekg(0);//перемещаемся в начало старого файла
		Announcement temp;
		for (size_t i = 0; i < size; i++)//проходим по старому списку
		{
			temp.loadFromFile(file);//загружаем вершину из старого файла
			temp.next = -1;

			temp.saveToFile(temp_file);//записываем вершину во временный файл

			//связываем предыдущий элемент с последним
			temp_file.seekg(prev_pos);
			temp_file.write((const char*)(&next_pos), sizeof(next_pos));

			prev_pos = next_pos;
			temp_file.seekg(0, ios::end);	//переходим в конец временного файла и смещаем указатели
			next_pos = temp_file.tellg();
		}
		file.close();//закрываем файлы
		temp_file.close();
		remove("board.bin");//удаляем старый файл
		rename("temp.bin", "board.bin");//переименовываем временный файл
		file.open("board.bin", ios::in | ios::out | ios::binary);//делаем его основным
		size++;//увеличиваем размер списка
		return;
	}

	long long int prev_pos = -1, next_pos = 0;
	file.seekg(next_pos);//переходим в начало файла
	Announcement temp;
	for (size_t i = 0; i < index; i++)//проходим до нужного индекса
	{
		file.seekg(next_pos);//переходим к следующему файлу
		temp.loadFromFile(file);//загружаем из файла товар
		prev_pos = next_pos;//смещаем указатели
		next_pos = temp.next;
	}

	file.seekg(0, ios::end);//переходим к концу файла
	long long int cur_pos = file.tellg();	//сохраняем позицию нового элемента
	new_element.next = next_pos;
	new_element.saveToFile(file);//загружаем новую вершину в файл

	file.seekg(prev_pos);//связываем предыдущий элемент с новым
	file.write((const char*)(&cur_pos), sizeof(cur_pos));

	file.flush();//сохраняем изменения в файле на диск
	size++;//увеличиваем размер списка
}

bool List::removeAt(size_t index)	//удаление в заданной позиции
{
	if (index >= size) return false; //если нет такого индекса то выходим не удаляя элементы

	long long int last = -1, prev = -1;
	Announcement temp;
	fstream temp_file("temp.bin", ios::out | ios::binary);//создаём временный файл
	file.seekg(0);//переходим в начало старого файла
	for (size_t i = 0; i < size; i++) //проходим по списку
	{
		temp.loadFromFile(file);//считываем элемент
		if (i == index)//если индекс совпадает с удаляемым, то пропускаем его
		{
			if (temp.next != -1) file.seekg(temp.next);
			continue;
		}
		//иначе добавляем элемент в новый файл
		temp_file.seekg(0, ios::end);
		last = temp_file.tellg();
		temp.next = -1;
		temp.saveToFile(temp_file);
		
		if (prev != -1)//связываем последний добавленный с новым
		{
			temp_file.seekg(prev);
			temp_file.write((const char*)(&last), sizeof(last));
		}
		prev = last;//смещаем указатель
	}
	//закрываем файлы
	file.close();
	temp_file.close();
	//удаляем старый файл, делаем новый основным
	remove("board.bin");
	rename("temp.bin", "board.bin");
	file.open("board.bin", ios::in | ios::out | ios::binary);
	size--;
	return true;
}

long long int List::getNode(size_t index, Announcement& node)	//получение элемента по индексу
{
	if (index >= size) return -1;	//если нет элемента возвращаем несуществующий файловый указатель

	long long int pos = 0;
	file.seekg(pos);	//переходим в начало файла
	for (size_t i = 0; i < size; i++)	//проходим по списку
	{
		node.loadFromFile(file);	//загружаем вершину из файла
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
bool List::edit(Announcement& changed_element, size_t index)
{
	Announcement temp;
	long long int pos = getNode(index, temp);//получаем элемент по индексу
	if (pos == -1) return false;//если элемент не получен выходим с ошибкой

	if (temp.ad_text.size() + temp.category.size() == changed_element.ad_text.size() + changed_element.category.size())	//если размер записи в файле не изменится
	{
		file.seekg(pos);	//переходим по файловому указателю
		changed_element.next = temp.next;
		changed_element.saveToFile(file);//перезаписываем данные
		return true;
	}
	//если размер записи отличается
	removeAt(index);//удаляем старый элемент
	insert(changed_element, index);//вставляем новый
	return true;
}

void List::out()//вывод списка в консоль
{
	file.seekg(0);//переходим в начало файла

	Announcement temp;
	cout << "Список объявлений:";
	if (size == 0) { cout << " пуст." << endl; return; }
	while (temp.loadFromFile(file))//загружаем элементы из файла
	{
		temp.print();//выводим в консоль элемент
		cout << endl;
		if (temp.next == -1) break;
		file.seekg(temp.next);//переходим к следующему элементу
	}
}

//вставка с сохранением порядка
void List::insertInOrder(Announcement& new_element)
{
	if (size == 0)//если список пуст
	{
		//просто вставляем элемент
		add(new_element);
		return;
	}

	Announcement temp;
	for (size_t i = 0; i < size; i++)//проходим по списку
	{
		getNode(i, temp);//получаем элемент по индексу
		if (new_element < temp)//если название товара в алфавитном порядке после нового
		{
			insert(new_element, i);//вставляем на это место новый элемент
			return;
		}
	}
	//если дошли до конца списка вставляем в конец списка новый элемент
	add(new_element);
}

void List::findCategory(const string& ctgry)	//поиск по рубрике
{
	Announcement temp;	
	bool found = false;
	cout << "Найденные объявления в рубрике " << ctgry << ':' << endl;
	file.seekg(0);
	while (temp.loadFromFile(file))	//проходим до конца списка
	{
		if (temp.category == ctgry)	//если рубрика текущего элемента совпадает
		{
			temp.print();	//выводим элемент
			found = true;
		}
	}
	if (found == false) { cout << "Не найдено ни одного объявления" << endl; }
}

void List::findText(const string& text)	//поиск по тексту объявления
{
	Announcement temp;
	bool found = false;
	cout << "Найденные объявления, содержащие в тексте " << text << ':' << endl;
	file.seekg(0);
	while (temp.loadFromFile(file))	//проходим до конца списка
	{
		if (temp.ad_text.find(text) != string::npos)	//если в тексте найдено совпадение
		{
			temp.print();	//выводим элемент
			found = true;
		}
	}
	if (found == false) { cout << "Не найдено ни одного объявления" << endl; }
}

void List::sort()//сортировка
{
	if (size <= 1) return;	//если элементов меньше двух выходим

	long long int first_pos = 0;	//указатель на первый элемент
	for (size_t i = 1; i < size; i++)	//проходим количество итераций меньше чем размер на 1
	{
		file.seekg(first_pos);	//переходим к первому элементу
		long long int prev = -1;
		for (size_t j = 0; j < size - i; j++)//проходим по неотсортированной части
		{
			//получаем два элемента (левый и правый)
			long long int pos1 = file.tellg();	
			Announcement temp1, temp2;
			temp1.loadFromFile(file);
			file.seekg(temp1.next);

			long long int pos2 = file.tellg();
			temp2.loadFromFile(file);

			//сравниваем элементы
			if (temp1 > temp2)
			{
				if (pos1 != first_pos)//если левый элемент не первый в списке
				{
					file.seekg(prev);//связываем его предыдущий элемент с правым элементом
					file.write((const char*)(&pos2), sizeof(pos2));
				}
				else//в ином случае заменяем файловый указатель на первый элемент на правый элемент
				{
					first_pos = pos2;
				}

				//перевязываем указатели двух сравниваемых элементов
				file.seekg(pos1);
				file.write((const char*)(&temp2.next), sizeof(temp2.next));

				file.seekg(pos2);
				file.write((const char*)(&pos1), sizeof(pos1));

				file.seekg(pos1);//переходим к следующему элементу
				prev = pos2;
			}
			else
			{
				file.seekg(pos2);//переходим к следующему элементу
				prev = pos1;
			}
		}
	}

	if (first_pos != 0)
	{
		Announcement temp;
		fstream temp_file("temp.bin", ios::binary | ios::out);//создаём временный файл
		long long int temp_pos = -1, file_pos = first_pos, prev = -1;

		for (size_t i = 0; i < size; i++)//проходим по списку и копируем элементы в новый файл
		{
			file.seekg(file_pos);	//перемещаемся к следующему элементу в старом файле
			temp.loadFromFile(file);	//считываем элемент
			file_pos = temp.next;	//сохраняем указатель на следующий элемент

			temp.next = -1;	//за новым элементом нет следующего
			temp_pos = temp_file.tellg();	//сохраняем текущую позицию в новом файле как предыдущую для следующего элемента
			temp.saveToFile(temp_file); //сохраняем новый элемент в новом файле

			if (prev != -1)	//если есть предыдущий элемент
			{
				temp_file.seekg(prev);	//смещаемся к предыдущему элементу
				temp_file.write((const char*)(&temp_pos), sizeof(temp_pos));	//устанавливаем указатель на новый элемент
			}
			prev = temp_pos;	//сохраняем в считанном элементе указатель на предыдущий элемент
			temp_file.seekg(0, ios::end);
		}
		//закрываем файлы
		file.close();
		temp_file.close();
		//удаляем старый файл, новый делаем основным
		remove("board.bin");
		rename("temp.bin", "board.bin");

		file.open("board.bin", ios::in | ios::out | ios::binary);
	}
}