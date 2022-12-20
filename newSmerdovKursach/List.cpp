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
		Announcement tmp;
		while (tmp.fileLoad(file))	//проходим по списку в файле
		{
			size++;	//подсчитываем размер
			if (tmp.next != -1) file.seekg(tmp.next);
			else break;
		}
	}
}

List::~List()	//деструктор списка
{
	if (file.is_open()) file.close();	//если файл открыт, закрываем
}

//добавление товара в конец списка
void List::add(Announcement& elem)
{
	Announcement tmp;
	long long int prev_pos = -1, cur_pos = 0;//файловый указатель на элемент перед новым и на новый
	file.seekg(cur_pos);	//переходим в начало файла

	while (tmp.fileLoad(file))	//проходим до последнего элемента, считывая его
	{
		prev_pos = cur_pos;
		cur_pos = tmp.next;
		if (cur_pos == -1)
			break;
		file.seekg(cur_pos);
	}

	file.clear();
	file.seekg(0, ios::end);	//переходим в конец файла
	cur_pos = file.tellg();	//запоминаем текущую позицию в файле
	elem.next = -1;

	if (prev_pos != -1)	//если перед новой вершиной есть элементы
	{
		//переходим к месту в файле, где хранится файловый указатель 
		//на следующий элемент у элемента перед новым
		file.seekg(prev_pos);
		file.write(reinterpret_cast<char*>(&cur_pos), sizeof(cur_pos));//записываем файловый указатель на новую вершину
		file.seekg(cur_pos);//переходим в позицию новой вершины
	}
	elem.fileSave(file);//записываем вершину
	size++;//увеличиваем размер списка
	file.flush();//сохраняем изменения в файле на диск
}

//вставка товара по индексу
void List::insert(Announcement& elem, unsigned int pos)
{
	if (pos >= size)	//вставка в конец
	{
		add(elem);
		return;
	}
	
	if (pos == 0)	//вставка в начало
	{
		long long int prev_pos = 0, next_pos = -1;
		fstream temp_file("tmp.bin", ios::out | ios::binary);//создаём временный файл
		//инициализируем новую вершину
		elem.next = -1;
		elem.fileSave(temp_file);//записываем во временный файл

		next_pos = temp_file.tellg();//записываем в файловый указатель позицию для следующего элемента
		file.seekg(0);//перемещаемся в начало старого файла
		Announcement tmp;
		for (unsigned int i = 0; i < size; i++)//проходим по старому списку
		{
			tmp.fileLoad(file);//загружаем вершину из старого файла
			tmp.next = -1;
			tmp.fileSave(temp_file);//записываем вершину во временный файл

			//связываем предыдущий элемент с последним
			temp_file.seekg(prev_pos);
			temp_file.write(reinterpret_cast<char*>(&next_pos), sizeof(next_pos));

			prev_pos = next_pos;
			temp_file.seekg(0, ios::end);	//переходим в конец временного файла и смещаем указатели
			next_pos = temp_file.tellg();
		}
		file.close();//закрываем файлы
		temp_file.close();
		remove("board.bin");//удаляем старый файл
		rename("tmp.bin", "board.bin");//переименовываем временный файл
		file.open("board.bin", ios::in | ios::out | ios::binary);//делаем его основным
		size++;//увеличиваем размер списка
		return;
	}

	long long int prev_pos = -1, next_pos = 0;
	file.seekg(next_pos);//переходим в начало файла
	Announcement tmp;
	for (unsigned int i = 0; i < pos; i++)//проходим до нужного индекса
	{
		file.seekg(next_pos);//переходим к следующему файлу
		tmp.fileLoad(file);//загружаем из файла товар
		prev_pos = next_pos;//смещаем указатели
		next_pos = tmp.next;
	}

	file.seekg(0, ios::end);//переходим к концу файла
	long long int cur_pos = file.tellg();	//сохраняем позицию нового элемента
	elem.next = next_pos;
	elem.fileSave(file);//загружаем новую вершину в файл

	file.seekg(prev_pos);//связываем предыдущий элемент с новым
	file.write(reinterpret_cast<char*>(&cur_pos), sizeof(cur_pos));

	file.flush();//сохраняем изменения в файле на диск
	size++;//увеличиваем размер списка
}

bool List::removeAt(unsigned int pos)	//удаление в заданной позиции
{
	if (pos >= size) return false; //если нет такого индекса то выходим не удаляя элементы

	long long int last = -1, prev = -1;
	Announcement tmp;
	fstream temp_file("tmp.bin", ios::out | ios::binary);//создаём временный файл
	file.seekg(0);//переходим в начало старого файла
	for (unsigned int i = 0; i < size; i++) //проходим по списку
	{
		tmp.fileLoad(file);//считываем элемент
		if (i == pos)//если индекс совпадает с удаляемым, то пропускаем его
		{
			if (tmp.next != -1)
				file.seekg(tmp.next);
			continue;
		}
		//иначе добавляем элемент в новый файл
		temp_file.seekg(0, ios::end);
		last = temp_file.tellg();
		tmp.next = -1;
		tmp.fileSave(temp_file);
		
		if (prev != -1)//связываем последний добавленный с новым
		{
			temp_file.seekg(prev);
			temp_file.write(reinterpret_cast<char*>(&last), sizeof(last));
		}
		prev = last;//смещаем указатель
	}
	//закрываем файлы
	file.close();
	temp_file.close();
	//удаляем старый файл, делаем новый основным
	remove("board.bin");
	rename("tmp.bin", "board.bin");
	file.open("board.bin", ios::in | ios::out | ios::binary);
	size--;
	return true;
}

long long int List::getNode(unsigned int pos, Announcement& node)	//получение элемента по индексу
{
	if (pos >= size)
		return -1;	//если нет элемента возвращаем несуществующий файловый указатель
	long long int pos = 0;
	file.seekg(pos);	//переходим в начало файла
	for (unsigned int i = 0; i < size; i++)	//проходим по списку
	{
		node.fileLoad(file);	//загружаем вершину из файла
		if (i == pos)	//если индекс совпадает с нужным
			break;//выходим из цикла

		pos = node.next;	//переходим в к следующему элементу
		file.seekg(node.next);
	}
	return pos; //возвращаем файловый указатель
}

//редактирование элемента по индексу
bool List::edit(Announcement& elem, unsigned int pos)
{
	long long int pos = -1;
	Announcement tmp;
	pos = getNode(pos, tmp);//получаем элемент по индексу
	if (pos == -1)
		return false;//если элемент не получен выходим с ошибкой

	if ((tmp.ad_text.size() + tmp.category.size()) ==
		(elem.ad_text.size() + elem.category.size()))	//если размер записи в файле не изменится
	{
		file.seekg(pos);	//переходим по файловому указателю
		elem.next = tmp.next;
		elem.fileSave(file);//перезаписываем данные
		return true;
	}
	//если размер записи отличается
	removeAt(pos);//удаляем старый элемент
	insert(elem, pos);//вставляем новый
	return true;
}

void List::out()//вывод списка в консоль
{
	cout << "Список объявлений: ";
	Announcement tmp;
	file.seekg(0);//переходим в начало файла
	if (size == 0)
		cout << "Не имеет элементов" << endl;
	else {
		while (tmp.fileLoad(file))//загружаем элементы из файла
		{
			tmp.print();//выводим в консоль элемент
			cout << "------------------------------------------------------" << endl;;
			if (tmp.next == -1)
				break;
			file.seekg(tmp.next);//переходим к следующему элементу
		}
	}
}

//вставка с сохранением порядка
void List::insertInOrder(Announcement& elem)
{
	if (size == 0)//если список пуст
	{
		//просто вставляем элемент
		add(elem);
		return;
	}

	Announcement tmp;
	for (unsigned int i = 0; i < size; i++)//проходим по списку
	{
		getNode(i, tmp);//получаем элемент по индексу
		if (elem < tmp)//если название товара в алфавитном порядке после нового
		{
			insert(elem, i);//вставляем на это место новый элемент
			return;
		}
	}
	//если дошли до конца списка вставляем в конец списка новый элемент
	add(elem);
}

void List::findCategory(const string& ctgry)	//поиск по рубрике
{
	Announcement tmp;	
	bool found = false;
	cout << "Найденные объявления в рубрике " << ctgry << ':' << endl;
	file.seekg(0);
	while (tmp.fileLoad(file))	//проходим до конца списка
	{
		if (tmp.category == ctgry)	//если рубрика текущего элемента совпадает
		{
			tmp.print();	//выводим элемент
			found = true;
		}
	}
	if (found == false) { cout << "Не найдено ни одного объявления" << endl; }
}

void List::findText(const string& text)	//поиск по тексту объявления
{
	Announcement tmp;
	bool found = false;
	cout << "Найденные объявления, содержащие в тексте " << text << ':' << endl;
	file.seekg(0);
	while (tmp.fileLoad(file))	//проходим до конца списка
	{
		if (tmp.ad_text.find(text) != string::npos)	//если в тексте найдено совпадение
		{
			tmp.print();	//выводим элемент
			found = true;
		}
	}
	if (found == false) { cout << "Не найдено ни одного объявления" << endl; }
}

void List::sort()//сортировка
{
	if (size <= 1) return;	//если элементов меньше двух выходим

	long long int first_pos = 0;	//указатель на первый элемент
	for (unsigned int i = 1; i < size; i++)	//проходим количество итераций меньше чем размер на 1
	{
		file.seekg(first_pos);	//переходим к первому элементу
		long long int prev = -1;
		for (unsigned int j = 0; j < size - i; j++)//проходим по неотсортированной части
		{
			//получаем два элемента (левый и правый)
			long long int pos1 = file.tellg();	
			Announcement temp1, temp2;
			temp1.fileLoad(file);
			file.seekg(temp1.next);

			long long int pos2 = file.tellg();
			temp2.fileLoad(file);

			//сравниваем элементы
			if (temp1 > temp2)
			{
				if (pos1 != first_pos)//если левый элемент не первый в списке
				{
					file.seekg(prev);//связываем его предыдущий элемент с правым элементом
					file.write(reinterpret_cast<char*>(&pos2), sizeof(pos2));
				}
				else//в ином случае заменяем файловый указатель на первый элемент на правый элемент
				{
					first_pos = pos2;
				}

				//перевязываем указатели двух сравниваемых элементов
				file.seekg(pos1);
				file.write(reinterpret_cast<char*>(&temp2.next), sizeof(temp2.next));

				file.seekg(pos2);
				file.write(reinterpret_cast<char*>(&pos1), sizeof(pos1));

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
		Announcement tmp;
		fstream temp_file("tmp.bin", ios::binary | ios::out);//создаём временный файл
		long long int temp_pos = -1, file_pos = first_pos, prev = -1;

		for (unsigned int i = 0; i < size; i++)//проходим по списку и копируем элементы в новый файл
		{
			file.seekg(file_pos);	//перемещаемся к следующему элементу в старом файле
			tmp.fileLoad(file);	//считываем элемент
			file_pos = tmp.next;	//сохраняем указатель на следующий элемент

			tmp.next = -1;	//за новым элементом нет следующего
			temp_pos = temp_file.tellg();	//сохраняем текущую позицию в новом файле как предыдущую для следующего элемента
			tmp.fileSave(temp_file); //сохраняем новый элемент в новом файле

			if (prev != -1)	//если есть предыдущий элемент
			{
				temp_file.seekg(prev);	//смещаемся к предыдущему элементу
				temp_file.write(reinterpret_cast<char*>(&temp_pos), sizeof(temp_pos));	//устанавливаем указатель на новый элемент
			}
			prev = temp_pos;	//сохраняем в считанном элементе указатель на предыдущий элемент
			temp_file.seekg(0, ios::end);
		}
		//закрываем файлы
		file.close();
		temp_file.close();
		//удаляем старый файл, новый делаем основным
		remove("board.bin");
		rename("tmp.bin", "board.bin");

		file.open("board.bin", ios::in | ios::out | ios::binary);
	}
}