#include "Announcement.h"

Announcement::Announcement()
{
	day = 0;
	month = 0;
	year = 0;
	number = 0;
	buy_sell = 1;
	next = -1;
}

void Announcement::setDate(unsigned short d, unsigned short m, unsigned short y)
{
	day = d;
	month = m;
	year = y;
}

void Announcement::setCategory(const string& c)
{
	category = c;
}

void Announcement::setBS(unsigned short bs)
{
	buy_sell = bs;
}

void Announcement::setAdText(const string& text)
{
	ad_text = text;
}
void Announcement::setNumber(unsigned long long num)
{
	number = num;
}

unsigned short Announcement::getMaxDay(unsigned short m, unsigned short y)
{
	unsigned short d_max;
	if (m == 2)	//если месяц февраль
	{
		if (y % 4 == 0) { d_max = 29; }	//если год високосный, то максимальный день 29
		else { d_max = 28; }	//иначе 28
	}
	//если месяц нечётный (до августа) или чётный (начиная с сентября) 
	else if ((m % 2 == 1 && m < 8) || (m % 2 == 0 && m >= 8)) { d_max = 31; }	//то максимальный день  31
	else { d_max = 30; }	//иначе 30
	return d_max;
}

bool Announcement::isDateCorrect(unsigned short d, unsigned short m, unsigned short y)
{
	//Проверка дня, месяца и года на соответствие пределам
	if (d > 0 && d <= 31 &&
		m > 0 && m <= 12 &&
		y >= 2000 && y <= 2022 &&
		d <= getMaxDay(m, y))
	{ return true; }
	else { return false; }
}

void Announcement::print() const
{
	cout
		<< "\n###Объявление от " << setfill('0')
		<< setw(2) << day << '.'
		<< setw(2) << month << '.' << setfill(' ')
		<< year
		<< "###\nРубрика: " << category
		<< ((buy_sell == '1') ? (" (покупка)") : (" (продажа)")) << endl
		<< ad_text
		<< "\nТелефон: " << number << endl;
}

bool Announcement::saveToFile(fstream& file)	//запись объявления в файл
{
	if (!file.is_open()) return false;	//если файл закрыт выходим с ошибкой
	file.clear();//очищение флагов состояния файлового потока
	//побайтово записываем в файл поля класса вершины списка
	//записываем численные значения
	file.write((const char*)&(next), sizeof(next));
	file.write((const char*)&(day), sizeof(day));
	file.write((const char*)&(month), sizeof(month));
	file.write((const char*)&(year), sizeof(year));
	file.write((const char*)&(buy_sell), sizeof(buy_sell));
	file.write((const char*)&(number), sizeof(number));

	//записываем сначала размер строки, затем саму строку
	size_t size = category.size();
	file.write((const char*)(&size), sizeof(size));
	if (size > 0) { file.write(category.c_str(), size); }

	size = ad_text.size();
	file.write((const char*)(&size), sizeof(size));
	if (size > 0) { file.write(ad_text.c_str(), ad_text.size()); }

	file.flush();//сбрасываем буфер потока в файл на диске
	if (file.fail())
	{
		file.clear();
		return false;//при сбое выходим с ошибкой
	}
	return true;
}

bool Announcement::loadFromFile(fstream& file)	//чтение вершины списка из файла
{
	if (!file.is_open()) return false;//если файл закрыт выходим с ошибкой
	file.clear();//очищение флагов состояния файлового потока 
	file.flush();//сбрасываем буфер потока в файл на диске
	//побайтово читаем из файла поля класса вершины списка
	file.read((char*)(&next), sizeof(next));
	file.read((char*)&(day), sizeof(day));
	file.read((char*)&(month), sizeof(month));
	file.read((char*)&(year), sizeof(year));
	file.read((char*)&(buy_sell), sizeof(buy_sell));
	file.read((char*)&(number), sizeof(number));

	size_t size = 0;
	file.read((char*)(&size), sizeof(size));//считываем размер строки
	if (size > 0)//если размер не нулевой
	{
		char* str = new char[size];//выделяем память строке
		file.read(str, size);//считываем строку
		category.assign(str, size);//присваиваем строке в классе
		delete[] str;//освобождаем память
	}

	size = 0;
	file.read((char*)(&size), sizeof(size));	//считываем размер строки
	if (size > 0)//если размер не нулевой
	{
		char* str = new char[size];//выделяем память строке
		file.read(str, size);//считываем строку
		ad_text.assign(str, size);//присваиваем строке в классе
		delete[] str;//освобождаем память
	}

	if (file.fail())
	{
		file.clear();
		return false;//при сбое  выходим с ошибкой
	}
	return true;
}

bool Announcement::dateCheck(const string& date)
{
	if (date.size() != 10)	//размер строки с датой в формате дд.мм.гггг = 10
	{
		return false;
	}

	unsigned short d = 0, m = 0, y = 0;
	for (size_t i = 0; i < date.size(); i++)	//преобразовываем символы в числа
	{
		if (i == 2 || i == 5)
		{
			if (date[i] != '.') return false;
		}
		else
		{
			if (date[i] < '0' || date[i] > '9') { return false; }

			if (i < 2)
			{
				d = d * 10 + date[i] - '0';
			}
			else if (i < 5)
			{
				m = m * 10 + date[i] - '0';
			}
			else
			{
				y = y * 10 + date[i] - '0';
			}
		}
	}

	return isDateCorrect(d, m, y);	//возвращаем результат проверки на валидность
}

bool Announcement::operator<(const Announcement& right) const
{
	if (year == right.year)
	{
		if (month == right.month)
		{
			if (day < right.day) { return true; }
		}
		else if (month < right.month) { return true; }
	}
	else if (year < right.year) { return true; }

	return false;
}

bool Announcement::operator>(const Announcement& right) const
{
	if (year == right.year)
	{
		if (month == right.month)
		{
			if (day > right.day) { return true; }
		}
		else if (month > right.month) { return true; }
	}
	else if (year > right.year) { return true; }

	return false;
}

void Announcement::inputAnnouncement(Announcement& new_element)
{
	string buffer;
	while (true)	//получаем дату
	{
		cout << "Введите дату (дд.мм.гггг)" << endl;
		cin >> buffer;

		if (!Announcement::dateCheck(buffer))	//делаем проверку даты
		{
			cout << "Неверная дата" << endl;
		}
		else	//если проверка успешна, добавляем дату в элемент
		{
			unsigned short day = (buffer[0] - '0') * 10 + (buffer[1] - '0');			//преобразовываем день и месяц
			unsigned short month = (buffer[3] - '0') * 10 + (buffer[4] - '0');	//из символов в числа
			unsigned short year = 0;
			for (size_t i = 6; i < 10; i++)	//преобразовываем год
			{
				year = year * 10 + buffer[i] - '0';
			}
			new_element.setDate(day, month, year);	//устанавливаем дату в элементе
			break;
		}
	}

	while (true)	//получаем тип объявления
	{
		cout
			<< "Выберите тип объявления:\n"
			<< "1. Купля\n"
			<< "2. Продажа" << endl;

		char choice;
		cin >> choice;
		if (choice == '1' || choice == '2')	//если ввод валидный
		{
			new_element.setBS(choice);		//устанавливаем тип объявления в элементе
			break;
		}
		else { cout << "Неверный тип" << endl; }
		cin.ignore(1000, '\n');	//игнорируем лишние символы, оставшиеся в потоке
	}

	cout << "Введите рубрику объявления" << endl;
	cin.ignore(1000, '\n');
	getline(cin, buffer);

	new_element.setCategory(buffer);

	while (true)	//устанавливаем номер телефона
	{
		cout << "Введите контактный номер (без 8)" << endl;
		unsigned long long number = 0;
		bool failed = false;
		cin >> buffer;
		for (size_t i = 0; i < buffer.size(); i++)	//преобразовываем полученные символы в числа
		{
			if (buffer[i] >= '0' && buffer[i] <= '9')
			{
				number = number * 10 + buffer[i] - '0';
			}
			else		//если символ не число
			{
				cout << "Неверный номер" << endl;
				failed = true;	//устанавливаем флаг ошибки
				break;	//прекращаем преобразование
			}
		}
		if (failed == false)	//если не была получена ошибка при преобразовании
		{
			new_element.setNumber(number);	//устанавливаем номер
			break;
		}
	}

	cout << "Введите текст объявления" << endl;
	cin.ignore(1000, '\n');
	getline(cin, buffer);

	new_element.setAdText(buffer);
}