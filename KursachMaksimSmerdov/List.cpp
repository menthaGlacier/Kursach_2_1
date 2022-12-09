#include "list.h"

List::List()
{
	head = nullptr;
}

List::~List()
{
	while (head)
	{
		Announcement* to_delete = head;
		head = head->next;
		delete to_delete;
	}
}

void List::add(const Announcement& entry, size_t index)
{
	Announcement* left = nullptr,
		*middle = new Announcement(entry),
		* right = head;
	for (size_t i = 0; i < index && right; i++)
	{
		left = right;
		right = right->next;
	}

	if (left) { left->next = middle; }
	else { head = middle; }
	middle->next = right;
}

bool List::del(size_t index)
{
	Announcement* left = nullptr,
		* to_delete = head;

	for (size_t i = 0; i < index; i++)
	{
		if (to_delete == nullptr) { return false; }
		left = to_delete;
		to_delete = to_delete->next;
	}

	if (to_delete)
	{
		if (left != nullptr) { left->next = to_delete->next; }
		else { head = head->next; }
		delete to_delete;
		return true;
	}
	return false;
}

void List::clear()
{
	while (head != nullptr)
	{
		Announcement* next = head->next;
		delete head;
		head = next;
	}
}

void List::sort()
{
	if (!head) { return; }
	Announcement* new_head = nullptr,
		* sorted = nullptr,
		* start = head;

	while (start != nullptr)
	{
		Announcement* minimal = start,  *min_prev = nullptr,
			*current_prev = start, *current = start->next;
		while (current != nullptr)
		{
			bool do_swap = false;
			if (current->year == minimal->year)
			{
				if (current->month == minimal->month)
				{
					if (current->day < minimal->day) { do_swap = true; }
				}
				else if (current->month < minimal->month) { do_swap = true; }
			}
			else if (current->year < minimal->year) { do_swap = true; }

			if (do_swap == true)
			{
				minimal = current;
				min_prev = current_prev;
			}
			current_prev = current;
			current = current->next;
		}
		if (minimal == start) { start = start->next; }
		else { min_prev->next = minimal->next; 	}

		if (sorted != nullptr) sorted->next = minimal;
		sorted = minimal;
		if (new_head == nullptr) {new_head = minimal; }
	}
	
	if (sorted) { sorted->next = nullptr; }
	head = new_head;
}

void List::findCategory(const string& ctgry)
{
	Announcement* pointer = head;
	bool found = false;
	cout << "Найденные объявления в рубрике" << ctgry << ':' << endl;
	while (pointer != nullptr)
	{
		if (pointer->category == ctgry)
		{
			pointer->print();
			found = true;
		}
	}
	if (found == false) { cout << "Не найдено ни одного объявления" << endl; }
}

void List::findText(const string& text)
{
	Announcement* pointer = head;
	bool found = false;
	cout << "Найденные объявления, содержащие в тексте" << text << ':' << endl;
	while (pointer != nullptr)
	{
		if (pointer->ad_text.find(text) != string::npos)
		{
			pointer->print();
			found = true;
		}
	}
	if (found == false) { cout << "Не найдено ни одного объявления" << endl; }
}

void List::out()
{
	Announcement* pointer = head;
	cout << "Список объявлений:";
	if (head == nullptr) { cout << " пуст." << endl; }
	while (pointer != nullptr)
	{
		pointer->print();
		pointer = pointer->next;
	}
}

bool List::save(const string& filename)
{
	fstream file(filename, ios::out | ios::binary);
	if (!file.is_open()) { return false; }

	Announcement* pointer = head;
	while (pointer != nullptr && file.fail() == false)
	{
		file.write((const char*)&(pointer->day), sizeof(pointer->day));
		file.write((const char*)&(pointer->month), sizeof(pointer->month));
		file.write((const char*)&(pointer->year), sizeof(pointer->year));
		file.write((const char*)&(pointer->buy_sell), sizeof(pointer->buy_sell));
		file.write((const char*)&(pointer->number), sizeof(pointer->number));

		size_t size = pointer->category.size();
		file.write((const char*)(&size), sizeof(size));
		file.write(pointer->category.c_str(), size);

		size = pointer->ad_text.size();
		file.write((const char*)(&size), sizeof(size));
		file.write(pointer->ad_text.c_str(), pointer->ad_text.size());

		pointer = pointer->next;
	}
	file.close();
	if (file.fail()) { return false; }
	return true;
}

bool List::load(const string& filename)
{
	fstream file(filename, ios::in | ios::binary);
	if (!file.is_open()) { return false; }

	Announcement* new_head = nullptr, * pointer = nullptr;
	while (file.peek() != EOF)
	{
		Announcement* new_element = new Announcement;
		file.read((char*)&(new_element->day), sizeof(new_element->day));
		file.read((char*)&(new_element->month), sizeof(new_element->month));
		file.read((char*)&(new_element->year), sizeof(new_element->year));
		file.read((char*)&(new_element->buy_sell), sizeof(new_element->buy_sell));
		file.read((char*)&(new_element->number), sizeof(new_element->number));

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

		if (file.fail() == true)
		{
			delete new_element;
			while (new_head)
			{
				pointer = new_head;
				new_head = new_head->next;
				delete pointer;
			}
			file.close();
			return false;
		}
		else
		{
			if (pointer != nullptr) pointer->next = new_element;
			pointer = new_element;
			pointer->next = nullptr;
			if (new_head == nullptr) new_head = pointer;
		}
	}

	file.close();
	clear();
	head = new_head;
	return true;
}