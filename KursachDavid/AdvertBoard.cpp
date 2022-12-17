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
	{
		return;
	}

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
	// TODO
}

/* Вставка элемента с сохранением порядка */
void AdvertBoard::insort(const Advert& advert)
{
	// TODO
}

/* Удаление последнего элемента массива */
void AdvertBoard::remove()
{
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
	// TODO
}

/* Получение элемента через указатель */
Advert* AdvertBoard::operator[](int pos) const
{
	/* Нельзя обратиться к отрицательным или выходящим за размер элементам */
	if (pos < 0 || pos + 1 > size)
	{
		return nullptr;
	}

	/* Возвращаем элемент */
	return &(arr[pos]);
}

/* Поиск по заданной рубрике и по шаблону искомого слова в тексте объявления */
void AdvertBoard::find() const
{
	// TODO
}

/* Сортировка по дате подачи */
void AdvertBoard::sort()
{
	// TODO
}

/* Сохранение доски объявлений в файле */
void AdvertBoard::save(std::string file) const
{
	// TODO
}

/* Загрузка доски объявлений из файла */
void AdvertBoard::load(std::string file)
{
	// TODO
}

/* Вывод доски объявлений */
void AdvertBoard::output() const
{
	// TODO
}