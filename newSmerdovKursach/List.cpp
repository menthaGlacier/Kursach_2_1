#include "List.h"

List::List() //конструктор пустого списка
{
	size = 0;
	file.open("FILE.bin", ios::in | ios::out | ios::binary);
	//проверяем, открыт ли файл
	if (!file.is_open())
	{
		//если нет, то создаем
		file.open("FILE.bin", ios::out);
		if (!file.is_open())
		{
			//выходим, если файл не создался
			cout << "Не удалось открыть файл FILE.bin" << endl;
			exit(-1);
		}
		file.close(); //закрываем
		file.open("FILE.bin", ios::in | ios::out | ios::binary);
	}
	else
	{
		//загружаем содержимое
		Announcement tmp; //временный объект
		while (tmp.fileLoad(file))
		{
			//считаем размер
			size++;
			if (tmp.next != -1)
				file.seekg(tmp.next);
			else
				break;
		}
	}
}

List::~List() //деструктор
{
	//закрываем открытый файл
	if (file.is_open())
		file.close();
}

//добавление в конец
void List::add(Announcement& elem)
{
	Announcement tmp;
	long long int old_pos = -1, this_pos = 0;// указатели на элемент предыдущий и новый
	//начало файла
	file.seekg(this_pos);

	//читаем файл
	while (tmp.fileLoad(file))
	{
		old_pos = this_pos;
		this_pos = tmp.next;
		if (this_pos == -1)
			break;
		file.seekg(this_pos);
	}

	file.clear(); //чистим
	file.seekg(0, ios::end); //конец
	this_pos = file.tellg();
	elem.next = -1;

	//если перед новой вершиной есть элементы
	if (old_pos != -1)
	{
		file.seekg(old_pos);
		file.write(reinterpret_cast<char*>(&this_pos), sizeof(this_pos));//записываем файловый указатель на новую вершину
		file.seekg(this_pos);//переходим в позицию новой вершины
	}

	elem.fileSave(file);//записываем вершину
	size++;
	file.flush();//сохраняем изменения
}

//вставка по индексу
void List::insert(Announcement& elem, unsigned int pos)
{
	//если позиция больше, вставляем в конец файла
	if (pos >= size)
	{
		add(elem);
		return;
	}
	
	//если позиция = начало
	if (pos == 0)
	{
		long long int old_pos = 0, next_pos = -1;
		fstream tmpf("TMP.bin", ios::out | ios::binary);//создаём буфер файл
		elem.next = -1;
		elem.fileSave(tmpf);// пишем в буфер

		//записываем позицию для следующего элемента
		next_pos = tmpf.tellg();
		file.seekg(0);//перемещаемся в начало файла
		Announcement tmp; //временный объект
		for (unsigned int i = 0; i < size; i++)
		{
			//записываем из старого файла в буфер
			tmp.fileLoad(file);
			tmp.next = -1;
			tmp.fileSave(tmpf);

			//связываем предыдущий элемент с последним
			tmpf.seekg(old_pos);
			tmpf.write(reinterpret_cast<char*>(&next_pos), sizeof(next_pos));

			old_pos = next_pos;
			tmpf.seekg(0, ios::end);	//переходим в конец временного файла и смещаем указатели
			next_pos = tmpf.tellg();
		}
		file.close();//закрываем файлы
		tmpf.close();
		remove("FILE.bin");//удаляем старый файл
		rename("TMP.bin", "FILE.bin");//переименовываем временный файл
		file.open("FILE.bin", ios::in | ios::out | ios::binary);//делаем его основным
		size++;//увеличиваем размер списка
		return;
	}

	long long int old_pos = -1, next_pos = 0;
	file.seekg(next_pos);//переходим в начало файла
	Announcement tmp;
	for (unsigned int i = 0; i < pos; i++)//проходим до нужного индекса
	{
		file.seekg(next_pos);//переходим к следующему файлу
		tmp.fileLoad(file);//загружаем из файла товар
		old_pos = next_pos;//смещаем указатели
		next_pos = tmp.next;
	}

	file.seekg(0, ios::end);//переходим к концу файла
	long long int this_pos = file.tellg();	//сохраняем позицию нового элемента
	elem.next = next_pos;
	elem.fileSave(file);//загружаем новую вершину в файл

	file.seekg(old_pos);//связываем предыдущий элемент с новым
	file.write(reinterpret_cast<char*>(&this_pos), sizeof(this_pos));

	file.flush();//сохраняем изменения в файле на диск
	size++;//увеличиваем размер списка
}

bool List::removeByIndex(unsigned int pos)	//удаление в заданной позиции
{
	if (pos >= size)
		return false; //если нет такого индекса то выходим не удаляя элементы

	long long int last = -1, prev = -1;
	Announcement tmp;
	fstream tmpf("TMP.bin", ios::out | ios::binary);//создаём временный файл
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
		tmpf.seekg(0, ios::end);
		last = tmpf.tellg();
		tmp.next = -1;
		tmp.fileSave(tmpf);
		
		if (prev != -1)//связываем последний добавленный с новым
		{
			tmpf.seekg(prev);
			tmpf.write(reinterpret_cast<char*>(&last), sizeof(last));
		}
		prev = last;//смещаем указатель
	}
	//закрываем файлы
	file.close();
	tmpf.close();
	//удаляем старый файл, делаем новый основным
	remove("FILE.bin");
	rename("TMP.bin", "FILE.bin");
	file.open("FILE.bin", ios::in | ios::out | ios::binary);
	size--;
	return true;
}

long long int List::getNode(unsigned int pos, Announcement& node)	//получение элемента по индексу
{
	if (pos >= size)
		return -1;	//если нет элемента возвращаем несуществующий файловый указатель
	long long int tpos = 0;
	file.seekg(tpos);	//переходим в начало файла
	for (unsigned int i = 0; i < size; i++)	//проходим по списку
	{
		node.fileLoad(file);	//загружаем вершину из файла
		if (i == pos)	//если индекс совпадает с нужным
			break;//выходим из цикла

		tpos = node.next;	//переходим в к следующему элементу
		file.seekg(node.next);
	}
	return tpos; //возвращаем файловый указатель
}

//изменение элемента
bool List::edit(Announcement& elem, unsigned int pos)
{
	long long int tpos = -1;
	Announcement tmp;
	tpos = getNode(pos, tmp);//получаем элемент 
	if (tpos == -1)
		return false;//выходим с ошибкой, если нет данного элемента

	if ((tmp.ad_text.size() + tmp.category.size()) ==
		(elem.ad_text.size() + elem.category.size()))
	{
		file.seekg(tpos);	//переходим по файловому указателю
		elem.next = tmp.next;
		elem.fileSave(file);//перезаписываем данные
		return true;
	}
	//если размер записи отличается
	removeByIndex(pos);//удаляем старый элемент
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

void List::sort()//сортировка пузырьком
{
	//завершаем, если список имеет один или менее элемент
	if (size <= 1)
		return;

	//первый элемент
	long long int first_pos = 0;
	//проходим по файлу
	for (unsigned int i = 1; i < size; i++)
	{
		file.seekg(first_pos);	//переходим к первому элементу
		long long int prev = -1;
		for (unsigned int j = 0; j < size - i; j++)
		{
			//получаем левый и правый элементы
			long long int pos1 = file.tellg();	
			Announcement temp1, temp2;
			temp1.fileLoad(file);
			file.seekg(temp1.next);

			long long int pos2 = file.tellg();
			temp2.fileLoad(file);

			//сравниваем элементы
			if (temp1 > temp2)
			{
				//если левый элемент не первый в списке, то связываем его левый с правым элементом
				if (pos1 != first_pos)
				{
					file.seekg(prev);
					file.write(reinterpret_cast<char*>(&pos2), sizeof(pos2));
				}
				//иначе заменяем указатель на правый элемент
				else
					first_pos = pos2;

				//меняем указатели объектов
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
		Announcement tmp; //временный объект
		fstream tmpf("TMP.bin", ios::binary | ios::out);//создаём временный файл
		long long int temp_pos = -1, file_pos = first_pos, prev = -1;

		for (unsigned int i = 0; i < size; i++)
		{
			//перемещаемся к следующему элементу и читаем его
			file.seekg(file_pos);
			tmp.fileLoad(file);
			//запишем указатель на следующий элемент
			file_pos = tmp.next;

			//новый элемент не имеет продолжения
			tmp.next = -1;
			//сохраняем текущую позицию в файле как предыдущую для следующего элемента
			temp_pos = tmpf.tellg();
			tmp.fileSave(tmpf);

			//если предыдущий элемент существует, то смещаемся к нему
			if (prev != -1)
			{
				tmpf.seekg(prev);
				//устанавливаем указатель на новый элемент
				tmpf.write(reinterpret_cast<char*>(&temp_pos), sizeof(temp_pos));
			}

			//сохраняем в элементе указатель на предыдущий элемент
			prev = temp_pos;
			tmpf.seekg(0, ios::end);
		}
		//закрываем файлы
		//делаем буфер основным файлом
		file.close();
		tmpf.close();
		remove("FILE.bin");
		rename("TMP.bin", "FILE.bin");
		file.open("FILE.bin", ios::in | ios::out | ios::binary);
	}
}