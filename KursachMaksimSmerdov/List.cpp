#include "list.h"

List::List()
{
	head = nullptr;
}

List::~List()
{

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

}

void List::findCategory(string)
{

}

void List::findText(string)
{

}

void List::out()
{
	Announcement* pointer = head;
	cout << "Список объявлений:";
	if (head == nullptr) { cout << " пуст." << endl; }
	while (pointer != nullptr)
	{
		cout
			<< "\n###Объявление от "
			<< pointer->day << '.' << pointer->month << '.' << pointer->year
			<< "###\nРубрика: " << pointer->category
			<< ((pointer->buy_sell == "куплю") ? (" (покупка)") : (" (продажа)")) << endl
			<< pointer->ad_text
			<< "\nТелефон: " << pointer->number << endl;
		pointer = pointer->next;
	}
}

void List::save()
{

}

void List::load()
{

}