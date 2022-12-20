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

unsigned short Announcement::getMonthDayLimit(unsigned short m, unsigned short y)
{
	unsigned short limit_month_day;
	if (m == 2)	//если месяц февраль
	{
		if (y % 4 == 0)
			limit_month_day = 29;	//если год високосный, то максимальный день 29
		else
			limit_month_day = 28;	//иначе 28
	}
	//если месяц нечётный (до августа) или чётный (начиная с сентября) 
	else if ((m % 2 == 1 && m < 8) || (m % 2 == 0 && m >= 8))
		limit_month_day = 31;//то максимальный день  31
	else
		limit_month_day = 30; //иначе 30

	return limit_month_day;
}

bool Announcement::checkDate(unsigned short d, unsigned short m, unsigned short y)
{
	//Проверка дня, месяца и года на соответствие пределам
	if (d <= 0 || d > 31)
		return false;
	if (m <= 0 || m > 12)
		return false;
	if (y < 1970 || y > 2035 || d <= getMonthDayLimit(m, y))
		return false;
	return true;
}

void Announcement::print() const
{
	cout << "\n\tОбъявление от " << day << '.' << month << '.' << year;
	cout << "\n\tВ рубрике: " << category;
	if ((buy_sell == '1'))
		cout << " (покупка)";
	else
		cout << " (продажа)";
	cout << "\n\tТекст объявления: " << ad_text;
	cout << "\n\tКонтактный номер: " << number << endl;
}

bool Announcement::fileSave(fstream& f)	//запись объявления в файл
{
	if (!f.is_open())
		return false;	//если файл закрыт выходим с ошибкой

	f.clear();//очищение флагов состояния файлового потока
	//побайтово записываем в файл поля класса вершины списка
	//записываем численные значения
	f.write(reinterpret_cast<char*>(&next), sizeof(next));
	f.write(reinterpret_cast<char*>(&day), sizeof(day));
	f.write(reinterpret_cast<char*>(&month), sizeof(month));
	f.write(reinterpret_cast<char*>(&year), sizeof(year));
	f.write(reinterpret_cast<char*>(&buy_sell), sizeof(buy_sell));
	f.write(reinterpret_cast<char*>(&number), sizeof(number));

	//записываем сначала размер строки, затем саму строку
	unsigned int size = category.size();
	f.write(reinterpret_cast<char*>(&size), sizeof(size));
	if (size > 0)
		f.write(category.c_str(), size);

	size = ad_text.size();
	f.write(reinterpret_cast<char*>(&size), sizeof(size));
	
	if (size > 0)
		f.write(ad_text.c_str(), ad_text.size()); 

	f.flush();//сбрасываем буфер потока в файл на диске
	if (f.fail())
	{
		f.clear();
		return false;//при сбое выходим с ошибкой
	}

	return true;
}

bool Announcement::fileLoad(fstream& f)	//чтение вершины списка из файла
{
	if (!f.is_open()) return false;//если файл закрыт выходим с ошибкой
	f.clear();//очищение флагов состояния файлового потока 
	f.flush();//сбрасываем буфер потока в файл на диске
	//побайтово читаем из файла поля класса вершины списка
	f.read(reinterpret_cast<char*>(&next), sizeof(next));
	f.read((char*)&(day), sizeof(day));
	f.read((char*)&(month), sizeof(month));
	f.read((char*)&(year), sizeof(year));
	f.read((char*)&(buy_sell), sizeof(buy_sell));
	f.read((char*)&(number), sizeof(number));

	unsigned int size = 0;
	f.read(reinterpret_cast<char*>(&size), sizeof(size));//считываем размер строки
	if (size > 0)//если размер не нулевой
	{
		char* read_string = new char[size];//выделяем память строке
		f.read(read_string, size);//считываем строку
		category.assign(read_string, size);//присваиваем строке в классе
		delete[] read_string;//освобождаем память
	}

	size = 0;
	f.read(reinterpret_cast<char*>(&size), sizeof(size));	//считываем размер строки
	if (size > 0)//если размер не нулевой
	{
		char* read_string = new char[size];//выделяем память строке
		f.read(read_string, size);//считываем строку
		ad_text.assign(read_string, size);//присваиваем строке в классе
		delete[] read_string;//освобождаем память
	}

	if (f.fail())
	{
		f.clear();
		return false;//при сбое  выходим с ошибкой
	}

	return true;
}

bool Announcement::dateCheck(const string& date)
{
	if (date.size() < 10 || date.size() > 10)	//размер строки с датой в формате дд.мм.гггг = 10
		return false;

	unsigned short d = 0, m = 0, y = 0;
	for (unsigned int i = 0; i < date.size(); i++)	//преобразовываем символы в числа
	{
		if (i == 2 || i == 5)
			if (date[i] != '.') return false;
		else
		{
			if (date[i] < '0' || date[i] > '9')
				return false;

			if (i < 2)
				d = (d * 10 + date[i] - '0');
			else if (i < 5)
				m = (m * 10 + date[i] - '0');
			else
				y = (y * 10 + date[i] - '0');
		}
	}

	return checkDate(d, m, y);	//возвращаем результат проверки на валидность
}

bool Announcement::operator<(const Announcement& right) const
{
	if (year == right.year)
	{
		if (month == right.month)
			if (day < right.day)
				return true;
		else if (month < right.month)
			return true;
	}

	else if (year < right.year)
		return true;

	return false;
}

bool Announcement::operator>(const Announcement& right) const
{
	if (year == right.year)
	{
		if (month == right.month)
			if (day > right.day)
				return true;
		else if (month > right.month)
			return true;
	}
	else if (year > right.year)
		return true;

	return false;
}

void Announcement::inputAnnouncement(Announcement& elem)
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
			for (unsigned int i = 6; i < 10; i++)	//преобразовываем год
			{
				year = year * 10 + buffer[i] - '0';
			}
			elem.setDate(day, month, year);	//устанавливаем дату в элементе
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
			elem.setBS(choice);		//устанавливаем тип объявления в элементе
			break;
		}
		else { cout << "Неверный тип" << endl; }
		cin.ignore(1000, '\n');	//игнорируем лишние символы, оставшиеся в потоке
	}

	cout << "Введите рубрику объявления" << endl;
	cin.ignore(1000, '\n');
	getline(cin, buffer);

	elem.setCategory(buffer);

	while (true)	//устанавливаем номер телефона
	{
		cout << "Введите контактный номер (без 8)" << endl;
		unsigned long long number = 0;
		bool failed = false;
		cin >> buffer;
		for (unsigned int i = 0; i < buffer.size(); i++)	//преобразовываем полученные символы в числа
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
			elem.setNumber(number);	//устанавливаем номер
			break;
		}
	}

	cout << "Введите текст объявления" << endl;
	cin.ignore(1000, '\n');
	getline(cin, buffer);

	elem.setAdText(buffer);
}