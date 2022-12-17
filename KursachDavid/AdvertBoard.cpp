#include "AdvertBoard.h"

/* Пересоздаение массив под новую вместимость */
void AdvertBoard::updateArray()
{
	/* Сохраняем старый массив, создаем новый */
	Advert* pastArray = arr;
	arr = new Advert[capacity];

	/* Проверяем, пуст ли предыдущий массив */
	if (pastArray != nullptr)
	{
		/* Копируем элементы из устаревшего в новый массив */
		for (int i = 0; i < size; i++)
			arr[i] = pastArray[i];

		/* Очищаем устаревший массив */
		delete[] pastArray;
	}
}

/* Конструктор по умолчанию */
AdvertBoard::AdvertBoard()
{
	arr = nullptr;
	size = 0;
	capacity = 0;
}

/* Конструктор с заданной вместимостью */
AdvertBoard::AdvertBoard(int cap)
{
	/* Указанная вместимость не может быть меньше или равна нулю */
	if (cap <= 0)
		return;

	/* Создаем массив с данной вместимостью */
	/* Массив остаётся изначально пуст, т.е. его размер равен 0 */
	arr = new Advert[cap];
	size = 0;
	capacity = cap;
}

/* Деструктор */
AdvertBoard::~AdvertBoard()
{
	/* Освобождаем память, использованную для массива */
	delete[] arr;
}

/* Вставка элемента в конец массива */
void AdvertBoard::insert(const Advert& advert)
{
	/* Проверяем, полон ли массив */
	if (size == capacity)
	{
		/* Если изначально массив был пуст, делаем его вместимость 2 */
		/* Иначе расширяем его вместимость в два раза */
		if (capacity == 0)
			capacity = 2;
		else
			capacity *= 2;

		/* Изменяем массив */
		updateArray();
	}

	/* Производим вставку, инкрементируем значение размера */
	arr[size++] = Advert(advert);
}

/* Вставка элемента в нужную позицию */
void AdvertBoard::insert(const Advert& advert, int pos)
{
	/* Нельзя обратиться к отрицательным или выходящим за размер элементам */
	if (pos < 0 || pos + 1 > size)
		return;

	/* Проверяем, полон ли массив */
	if (size == capacity)
	{
		/* Если изначально массив был пуст, делаем его вместимость 2 */
		/* Иначе расширяем его вместимость в два раза */
		if (capacity == 0)
			capacity = 2;
		else
			capacity *= 2;

		/* Изменяем массив */
		updateArray();
	}

	/* Сдвигаем все элементы массива вправо */
	Advert temp = arr[pos];
	for (int i = pos; i < size; i++)
	{
		arr[i] = temp;
		temp = arr[i + 1];
		arr[i + 1] = arr[i];
	}

	/* Вставляем элемент на нужную позицию, увеличиваем размер */
	arr[pos] = advert;
	size++;
}

/* Вставка элемента с сохранением порядка */
void AdvertBoard::insort(const Advert& advert)
{
	/* Вставка с сохранением порядк есть вставка с сортировкой */
	/* Применим метод вставки в конец и метод сортировки массива */
	insert(advert);
	sort();
}

/* Удаление последнего элемента массива */
void AdvertBoard::remove()
{
	/* Если размер массива равен единице, то удаление элемента равно очищению */
	if (size == 1)
	{
		delete arr;
		size = 0;
		capacity = 0;
		return;
	}

	/* Провекра на пустой массив */
	if (size > 0)
	{
		/* Делаем бывший последний элемент пустым, уменьшаем размер массива */
		arr[--size] = Advert();

		/* Дополнительно, сокращаем вместимость вдвое при необходимости */
		/* Необходимость, когда размер меньше вместимость в более чем два раза */
		if ((capacity * 0.5) > size)
		{
			/* Сокращаем вместимость вдвое, изменяем массив */
			capacity /= 2;
			updateArray();
		}
	}
}

/* Удаление элемента в нужной позиции */
void AdvertBoard::remove(int pos)
{
	/* Нельзя обратиться к отрицательным или выходящим за размер элементам */
	if (pos < 0 || pos + 1 > size)
		return;

	/* Используем обработку этого случая из метода удаления последнего элемента */
	if (size == 1)
		remove();

	/* Провекра на пустой массив */
	if (size > 0)
	{
		/* Делаем сдвиг массива влево для удаления элемента */
		for (int i = pos; i < size - 1; i++)
			arr[i] = arr[i + 1];

		/* Теперь последний элемент является лишним */
		/* Удаляем его с помощью метода удаления последнего элемента */
		remove();
	}
}

/* Получение элемента через указатель */
Advert* AdvertBoard::operator[](int pos) const
{
	/* Нельзя обратиться к отрицательным или выходящим за размер элементам */
	if (pos < 0 || pos + 1 > size)
		return nullptr;

	/* Возвращаем элемент */
	return &(arr[pos]);
}

/* Поиск по заданной рубрике */
void AdvertBoard::findCategory(const std::string cat) const
{
	std::cout << "Search results:" << std::endl;

	/* Проходимся по всей доске объявлений */
	for (int i = 0; i < size; i++)
	{
		/* Если найдено совпадение, выводим позицию объявления и его само */
		if (arr[i].category.find(cat) != std::string::npos)
		{
			std::cout << "At #" << i << "pos" << std::endl;
			arr[i].output();
		}
	}
}

/* Поиск по шаблону искомого слова в тексте объявления */
void AdvertBoard::findAdText(const std::string ad) const
{
	std::cout << "Search results:" << std::endl;
	
	/* Проходимся по всей доске объявлений */
	for (int i = 0; i < size; i++)
	{
		/* Если найдено совпадение, выводим позицию объявления и его само */
		if (arr[i].adText.find(ad) != std::string::npos)
		{
			std::cout << "At #" << i << "pos" << std::endl;
			arr[i].output();
		}
	}
}

/* Сортировка по дате подачи */
void AdvertBoard::sort()
{
	/* Используем пузырьковую сортировку */
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[i] > arr[i])
			{
				Advert temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
}

/* Сохранение доски объявлений в файле */
bool AdvertBoard::save(std::string file) const
{
	/* Открываем файл в режими записи в бинарный файл */
	/* Также проверяем, был ли открыт файл */
	std::fstream fl(file, std::ios::out | std::ios::binary);
	if (fl.is_open() == false)
		return false;

	/* Записываем размер массива, если он не пуст */
	if (size > 0)
		fl.write((const char*)(&size), sizeof(size));

	/* Проходим по всему массиву, либо до получения ошибки */
	for (int i = 0; i < size && fl.fail() == false; i++)
	{
		/* Сначала записываем данные фиксированного размера */
		fl.write((const char*)(&arr[i].buySell), sizeof(arr[i].buySell));
		fl.write((const char*)(&arr[i].year), sizeof(arr[i].year));
		fl.write((const char*)(&arr[i].month), sizeof(arr[i].month));
		fl.write((const char*)(&arr[i].day), sizeof(arr[i].day));
		fl.write((const char*)(&arr[i].number), sizeof(arr[i].number));

		/* Далее записываем строки */
		/* Записываем размер строк, затем текст строки */
		/* Если строка пуста, запись текста не производится */
		int strSize = arr[i].category.size();
		fl.write((const char*)(&strSize), sizeof(strSize));
		if (strSize > 0)
			fl.write(arr[i].category.c_str(), strSize);

		strSize = arr[i].adText.size();
		fl.write((const char*)(&strSize), sizeof(strSize));
		if (strSize > 0)
			fl.write(arr[i].adText.c_str(), strSize);
	}

	/* Закрываем файл и возвращаем false, если была обнаружена ошибка */
	fl.close();
	if (fl.fail())
		return false;
	else
		return true;
}

/* Загрузка доски объявлений из файла */
bool AdvertBoard::load(std::string file)
{
	/* Открываем файл в режими чтения в бинарный файл */
	/* Также проверяем, был ли открыт файл */
	std::fstream fl(file, std::ios::in | std::ios::binary);
	if (fl.is_open() == false)
		return false;

	/* Читаем записанную вместимость и создаем массив для чтения */
	int arrCapacity = 0, arrSize = 0;
	fl.read((char*)(&arrCapacity), sizeof(arrCapacity));
	Advert* tempArr = new Advert[arrCapacity];

	/* Читаем по размеру записанного массива, либо до конца файла */
	for (int i = 0; i < arrCapacity && fl.peek() != EOF; i++)
	{
		/* Временный объект для чтения */
		Advert temp;

		/* Сначала считываем данные фиксированного размера */
		fl.read((char*)(&temp.buySell), sizeof(temp.buySell));
		fl.read((char*)(&temp.year), sizeof(temp.year));
		fl.read((char*)(&temp.month), sizeof(temp.month));
		fl.read((char*)(&temp.day), sizeof(temp.day));
		fl.read((char*)(&temp.number), sizeof(temp.number));

		/* Далее читаем строки */
		/* Читаем размер строк, затем текст строки */
		/* Для чтения будет использовать временный буфер */
		/* Если строка пуста, чтение текста не производится */
		int strSize = 0;
		fl.read((char*)(&strSize), sizeof(strSize));
		if (strSize > 0)
		{
			/* Читаем, записываем в строку, очищаем память буфера */
			char* strBuffer = new char[strSize];
			fl.read(strBuffer, strSize);
			temp.category.assign(strBuffer, strSize);
			delete[] strBuffer;
		}

		strSize = 0;
		fl.read((char*)(&strSize), sizeof(strSize));
		if (strSize > 0)
		{
			/* Читаем, записываем в строку, очищаем память буфера */
			char* strBuffer = new char[strSize];
			fl.read(strBuffer, strSize);
			temp.adText.assign(strBuffer, strSize);
			delete[] strBuffer;
		}

		/* Записываем в массив прочтенное объявление */
		tempArr[i] = temp;
		arrSize++;
	}

	/* Закрываем файл */
	fl.close();
	
	/* Возвращаем false и очищаем память, если была обнаружена ошибка */
	/* Иначе заменяем существующий массив доски объявления новым */
	if (fl.fail())
	{
		delete[] tempArr;
		return false;
	}

	else
	{
		/* Очищаем существующий массив, если он не пуст */
		if (arr)
			delete arr;

		capacity = arrCapacity;
		size = arrSize;
		arr = tempArr;
		return true;
	}
}

/* Вывод доски объявлений */
void AdvertBoard::output() const
{
	std::cout << "Advert board:" << std::endl;

	/* Последовательно выводим все элементы массива */
	for (int i = 0; i < size; i++)
	{
		std::cout << "Advert #" << i << std::endl;
		arr[i].output();
	}
}