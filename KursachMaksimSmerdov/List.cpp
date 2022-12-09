#include "List.h"

List::List()
{
	head = nullptr;
}

List::~List()
{
	clear();
}

void List::add(const Announcement& entry, size_t index)
{
	Announcement* left = nullptr,	//указатель на элемент перед добавляемым
		*middle = new Announcement(entry),	//указатель на добавляемый элемент
		* right = head;	//указатель на элемент после добавляемого
	for (size_t i = 0; i < index && right; i++)	//перемещаемся либо до конца списка, либо до нужного места
	{
		left = right;
		right = right->next;
	}

	if (left) { left->next = middle; }	//если есть элемент слева, то связываем его с добавляемым
	else { head = middle; }	//иначе добавляемый элемент становится первым в списке
	middle->next = right;	//связываем добавляемый элемент с тем, что справа от него
}

bool List::del(size_t index)
{
	Announcement* left = nullptr,	//указатель на элемент слева от удаляемого
		* to_delete = head;	//указатель на удаляемый элемент

	for (size_t i = 0; i < index; i++)	//перемещаемся до нужного места
	{
		if (to_delete == nullptr) { return false; }	//если нужного элемента нет, то выходим из метода
		left = to_delete;
		to_delete = to_delete->next;
	}

	if (to_delete)	//если существует элемент по нужному индексу
	{
		//перевязываем указатель его предыдущего элемента, если он есть
		if (left != nullptr) { left->next = to_delete->next; }
		else { head = head->next; }	//иначе смещаем указатель на первый элемент
		delete to_delete;	//удаляем элемент
		return true;	//удаление успешно
	}
	return false;	
}

void List::clear()
{
	while (head != nullptr)	//пока остались элементы
	{
		Announcement* to_delete = head;	//выбираем головной элемент для удаления
		head = head->next;	//смещаем головной элемент
		delete to_delete;	//удаляем элемент
	}
}

void List::sort()	//сортировка выборкой по дате
{
	if (!head) { return; }	//если список пуст выходим

	Announcement* new_head = nullptr,		//указатель на новый головной элемент
		* sorted = nullptr,	//указатель на последний отсортированный элемент
		* start = head;	//начало для цикла

	while (start != nullptr)	//проходим по старому списку, пока он не опустеет
	{
		Announcement* minimal = start,  *min_prev = nullptr,	//указатель на минимальный элемент и его предыдущий
			*current_prev = start, *current = start->next;	//указатель на текущий элемент и его предыдущий

		while (current != nullptr)	//доходим до конца списка
		{
			if (*current < *minimal)	//если текущий элемент меньше минимального
			{
				minimal = current;		//меняем минимальный элемент
				min_prev = current_prev;	//и его предыдущий
			}

			current_prev = current;	
			current = current->next;//переходим к следующему элементу
		}

		if (minimal == start) { start = start->next; }	//если минимальный элемент первый в старом списке, то смещаем начало
		else { min_prev->next = minimal->next; }	//иначе перевязываем указатели, исключая минимальный элемент

		if (sorted != nullptr) sorted->next = minimal;	//если новый список не пустой, то связываем последний элемент с новым
		sorted = minimal;	//смещаем указатель на последний  отсортированный элемент
		if (new_head == nullptr) {new_head = minimal; }	//если новый список пустой, то устанавливаем головной элемент
	}
	
	if (sorted) { sorted->next = nullptr; }	//если новый список не пустой, то зануляем указатель на следующий элемент у последнего
	head = new_head;	//меняем указатель на первый элемент в списке
}

void List::findCategory(const string& ctgry)	//поиск по рубрике
{
	Announcement* pointer = head;	//итерирующий указатель
	bool found = false;
	cout << "Найденные объявления в рубрике " << ctgry << ':' << endl;
	while (pointer != nullptr)	//проходим до конца списка
	{
		if (pointer->category == ctgry)	//если рубрика текущего элемента совпадает
		{
			pointer->print();	//выводим элемент
			found = true;
		}
		pointer = pointer->next;
	}
	if (found == false) { cout << "Не найдено ни одного объявления" << endl; }
}

void List::findText(const string& text)	//поиск по тексту объявления
{
	Announcement* pointer = head;//итерирующий указатель
	bool found = false;
	cout << "Найденные объявления, содержащие в тексте " << text << ':' << endl;
	while (pointer != nullptr)//проходим до конца списка
	{
		if (pointer->ad_text.find(text) != string::npos) //если в тексте найдено совпадение
		{
			pointer->print();//выводим элемент
			found = true;
		}
		pointer = pointer->next;
	}
	if (found == false) { cout << "Не найдено ни одного объявления" << endl; }
}

void List::out()	//вывод списка
{
	Announcement* pointer = head;
	cout << "Список объявлений:";
	if (head == nullptr) { cout << " пуст." << endl; }
	while (pointer != nullptr)	//проходим по списку
	{
		pointer->print();	//выводим элемент
		pointer = pointer->next;	//переходим к следующему
	}
}

bool List::save(const string& filename)
{
	fstream file(filename, ios::out | ios::binary);	//открываем в режиме записи бинарный файл
	if (!file.is_open()) { return false; }	//если открыть не удалось, выходим с ошибкой

	Announcement* pointer = head;
	while (pointer != nullptr && file.fail() == false)	//проходим по списку до конца, либо до получения ошибки
	{
		//записываем численные значения
		file.write((const char*)&(pointer->day), sizeof(pointer->day));	
		file.write((const char*)&(pointer->month), sizeof(pointer->month));
		file.write((const char*)&(pointer->year), sizeof(pointer->year));
		file.write((const char*)&(pointer->buy_sell), sizeof(pointer->buy_sell));
		file.write((const char*)&(pointer->number), sizeof(pointer->number));

		//записываем сначала размер строки, затем саму строку
		size_t size = pointer->category.size();
		file.write((const char*)(&size), sizeof(size));
		if (size > 0) { file.write(pointer->category.c_str(), size); }

		size = pointer->ad_text.size();
		file.write((const char*)(&size), sizeof(size));
		if (size > 0) { file.write(pointer->ad_text.c_str(), pointer->ad_text.size()); }

		pointer = pointer->next;	//переходим к следующему элементу
	}

	file.close();	//закрываем файл
	if (file.fail()) { return false; }	//если получена ошибка, сообщаем
	return true;
}

bool List::load(const string& filename)
{
	fstream file(filename, ios::in | ios::binary);	//открываем бинарный файл в режиме чтения
	if (!file.is_open()) { return false; }	//если файл не открылся, выходим с ошибкой

	Announcement* new_head = nullptr, * pointer = nullptr;	//указатели на первый и последний элемент нового списка
	while (file.peek() != EOF)	//проходим до конца файла
	{
		Announcement* new_element = new Announcement;	//выделяем память для нового элемента
		//читаем численные значения
		file.read((char*)&(new_element->day), sizeof(new_element->day));	
		file.read((char*)&(new_element->month), sizeof(new_element->month));
		file.read((char*)&(new_element->year), sizeof(new_element->year));
		file.read((char*)&(new_element->buy_sell), sizeof(new_element->buy_sell));
		file.read((char*)&(new_element->number), sizeof(new_element->number));

		//читаем сначала размеры строк, затем сами строки
		size_t size = 0;
		file.read((char*)(&size), sizeof(size));
		if (size > 0)
		{
			char* str = new char[size];
			file.read(str, size);
			new_element->category.assign(str, size);
			delete[] str;
		}

		size = 0;
		file.read((char*)(&size), sizeof(size));
		if (size > 0)
		{
			char* str = new char[size];
			file.read(str, size);
			new_element->ad_text.assign(str, size);
			delete[] str;
		}

		//если получена ошибка
		if (file.fail() == true)
		{
			delete new_element;	//освобождаем память последнего элмента
			while (new_head)	//очищаем считанный список
			{
				pointer = new_head;
				new_head = new_head->next;
				delete pointer;
			}
			file.close();	//закрываем файл
			return false;	//выходим с ошибкой
		}
		else
		{
			if (pointer != nullptr) { pointer->next = new_element; }	//добавляем элемент в конец списка
			pointer = new_element;	//смещаем указатель на последний элемент
			pointer->next = nullptr;
			if (new_head == nullptr) new_head = pointer;	//если список был пуст, устанавливаем головной указатель
		}
	}

	file.close();	//закрываем файл
	clear();	//очищаем текущий список
	head = new_head;	//устанавливаем новый
	return true;
}