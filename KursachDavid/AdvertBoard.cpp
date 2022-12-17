#include "AdvertBoard.h"

/* ������������� ������ ��� ����� ����������� */
void AdvertBoard::updateArray()
{
	/* ��������� ������ ������, ������� ����� */
	Advert* pastArray = arr;
	arr = new Advert[capacity];

	/* ���������, ���� �� ���������� ������ */
	if (pastArray != nullptr)
	{
		/* �������� �������� �� ����������� � ����� ������ */
		for (int i = 0; i < size; i++)
			arr[i] = pastArray[i];

		/* ������� ���������� ������ */
		delete[] pastArray;
	}
}

/* ����������� �� ��������� */
AdvertBoard::AdvertBoard()
{
	arr = nullptr;
	size = 0;
	capacity = 0;
}

/* ����������� � �������� ������������ */
AdvertBoard::AdvertBoard(int cap)
{
	/* ��������� ����������� �� ����� ���� ������ ��� ����� ���� */
	if (cap <= 0)
		return;

	/* ������� ������ � ������ ������������ */
	/* ������ ������� ���������� ����, �.�. ��� ������ ����� 0 */
	arr = new Advert[cap];
	size = 0;
	capacity = cap;
}

/* ���������� */
AdvertBoard::~AdvertBoard()
{
	/* ����������� ������, �������������� ��� ������� */
	delete[] arr;
}

/* ������� �������� � ����� ������� */
void AdvertBoard::insert(const Advert& advert)
{
	/* ���������, ����� �� ������ */
	if (size == capacity)
	{
		/* ���� ���������� ������ ��� ����, ������ ��� ����������� 2 */
		/* ����� ��������� ��� ����������� � ��� ���� */
		if (capacity == 0)
			capacity = 2;
		else
			capacity *= 2;

		/* �������� ������ */
		updateArray();
	}

	/* ���������� �������, �������������� �������� ������� */
	arr[size++] = Advert(advert);
}

/* ������� �������� � ������ ������� */
void AdvertBoard::insert(const Advert& advert, int pos)
{
	/* ������ ���������� � ������������� ��� ��������� �� ������ ��������� */
	if (pos < 0 || pos + 1 > size)
		return;

	/* ���������, ����� �� ������ */
	if (size == capacity)
	{
		/* ���� ���������� ������ ��� ����, ������ ��� ����������� 2 */
		/* ����� ��������� ��� ����������� � ��� ���� */
		if (capacity == 0)
			capacity = 2;
		else
			capacity *= 2;

		/* �������� ������ */
		updateArray();
	}

	/* �������� ��� �������� ������� ������ */
	Advert temp = arr[pos];
	for (int i = pos; i < size; i++)
	{
		arr[i] = temp;
		temp = arr[i + 1];
		arr[i + 1] = arr[i];
	}

	/* ��������� ������� �� ������ �������, ����������� ������ */
	arr[pos] = advert;
	size++;
}

/* ������� �������� � ����������� ������� */
void AdvertBoard::insort(const Advert& advert)
{
	/* ������� � ����������� ������ ���� ������� � ����������� */
	/* �������� ����� ������� � ����� � ����� ���������� ������� */
	insert(advert);
	sort();
}

/* �������� ���������� �������� ������� */
void AdvertBoard::remove()
{
	/* ���� ������ ������� ����� �������, �� �������� �������� ����� �������� */
	if (size == 1)
	{
		delete arr;
		size = 0;
		capacity = 0;
		return;
	}

	/* �������� �� ������ ������ */
	if (size > 0)
	{
		/* ������ ������ ��������� ������� ������, ��������� ������ ������� */
		arr[--size] = Advert();

		/* �������������, ��������� ����������� ����� ��� ������������� */
		/* �������������, ����� ������ ������ ����������� � ����� ��� ��� ���� */
		if ((capacity * 0.5) > size)
		{
			/* ��������� ����������� �����, �������� ������ */
			capacity /= 2;
			updateArray();
		}
	}
}

/* �������� �������� � ������ ������� */
void AdvertBoard::remove(int pos)
{
	/* ������ ���������� � ������������� ��� ��������� �� ������ ��������� */
	if (pos < 0 || pos + 1 > size)
		return;

	/* ���������� ��������� ����� ������ �� ������ �������� ���������� �������� */
	if (size == 1)
		remove();

	/* �������� �� ������ ������ */
	if (size > 0)
	{
		/* ������ ����� ������� ����� ��� �������� �������� */
		for (int i = pos; i < size - 1; i++)
			arr[i] = arr[i + 1];

		/* ������ ��������� ������� �������� ������ */
		/* ������� ��� � ������� ������ �������� ���������� �������� */
		remove();
	}
}

/* ��������� �������� ����� ��������� */
Advert* AdvertBoard::operator[](int pos) const
{
	/* ������ ���������� � ������������� ��� ��������� �� ������ ��������� */
	if (pos < 0 || pos + 1 > size)
		return nullptr;

	/* ���������� ������� */
	return &(arr[pos]);
}

/* ����� �� �������� ������� */
void AdvertBoard::findCategory(const std::string cat) const
{
	std::cout << "Search results:" << std::endl;

	/* ���������� �� ���� ����� ���������� */
	for (int i = 0; i < size; i++)
	{
		/* ���� ������� ����������, ������� ������� ���������� � ��� ���� */
		if (arr[i].category.find(cat) != std::string::npos)
		{
			std::cout << "At #" << i << "pos" << std::endl;
			arr[i].output();
		}
	}
}

/* ����� �� ������� �������� ����� � ������ ���������� */
void AdvertBoard::findAdText(const std::string ad) const
{
	std::cout << "Search results:" << std::endl;
	
	/* ���������� �� ���� ����� ���������� */
	for (int i = 0; i < size; i++)
	{
		/* ���� ������� ����������, ������� ������� ���������� � ��� ���� */
		if (arr[i].adText.find(ad) != std::string::npos)
		{
			std::cout << "At #" << i << "pos" << std::endl;
			arr[i].output();
		}
	}
}

/* ���������� �� ���� ������ */
void AdvertBoard::sort()
{
	/* ���������� ����������� ���������� */
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

/* ���������� ����� ���������� � ����� */
bool AdvertBoard::save(std::string file) const
{
	/* ��������� ���� � ������ ������ � �������� ���� */
	/* ����� ���������, ��� �� ������ ���� */
	std::fstream fl(file, std::ios::out | std::ios::binary);
	if (fl.is_open() == false)
		return false;

	/* ���������� ������ �������, ���� �� �� ���� */
	if (size > 0)
		fl.write((const char*)(&size), sizeof(size));

	/* �������� �� ����� �������, ���� �� ��������� ������ */
	for (int i = 0; i < size && fl.fail() == false; i++)
	{
		/* ������� ���������� ������ �������������� ������� */
		fl.write((const char*)(&arr[i].buySell), sizeof(arr[i].buySell));
		fl.write((const char*)(&arr[i].year), sizeof(arr[i].year));
		fl.write((const char*)(&arr[i].month), sizeof(arr[i].month));
		fl.write((const char*)(&arr[i].day), sizeof(arr[i].day));
		fl.write((const char*)(&arr[i].number), sizeof(arr[i].number));

		/* ����� ���������� ������ */
		/* ���������� ������ �����, ����� ����� ������ */
		/* ���� ������ �����, ������ ������ �� ������������ */
		int strSize = arr[i].category.size();
		fl.write((const char*)(&strSize), sizeof(strSize));
		if (strSize > 0)
			fl.write(arr[i].category.c_str(), strSize);

		strSize = arr[i].adText.size();
		fl.write((const char*)(&strSize), sizeof(strSize));
		if (strSize > 0)
			fl.write(arr[i].adText.c_str(), strSize);
	}

	/* ��������� ���� � ���������� false, ���� ���� ���������� ������ */
	fl.close();
	if (fl.fail())
		return false;
	else
		return true;
}

/* �������� ����� ���������� �� ����� */
bool AdvertBoard::load(std::string file)
{
	/* ��������� ���� � ������ ������ � �������� ���� */
	/* ����� ���������, ��� �� ������ ���� */
	std::fstream fl(file, std::ios::in | std::ios::binary);
	if (fl.is_open() == false)
		return false;

	/* ������ ���������� ����������� � ������� ������ ��� ������ */
	int arrCapacity = 0, arrSize = 0;
	fl.read((char*)(&arrCapacity), sizeof(arrCapacity));
	Advert* tempArr = new Advert[arrCapacity];

	/* ������ �� ������� ����������� �������, ���� �� ����� ����� */
	for (int i = 0; i < arrCapacity && fl.peek() != EOF; i++)
	{
		/* ��������� ������ ��� ������ */
		Advert temp;

		/* ������� ��������� ������ �������������� ������� */
		fl.read((char*)(&temp.buySell), sizeof(temp.buySell));
		fl.read((char*)(&temp.year), sizeof(temp.year));
		fl.read((char*)(&temp.month), sizeof(temp.month));
		fl.read((char*)(&temp.day), sizeof(temp.day));
		fl.read((char*)(&temp.number), sizeof(temp.number));

		/* ����� ������ ������ */
		/* ������ ������ �����, ����� ����� ������ */
		/* ��� ������ ����� ������������ ��������� ����� */
		/* ���� ������ �����, ������ ������ �� ������������ */
		int strSize = 0;
		fl.read((char*)(&strSize), sizeof(strSize));
		if (strSize > 0)
		{
			/* ������, ���������� � ������, ������� ������ ������ */
			char* strBuffer = new char[strSize];
			fl.read(strBuffer, strSize);
			temp.category.assign(strBuffer, strSize);
			delete[] strBuffer;
		}

		strSize = 0;
		fl.read((char*)(&strSize), sizeof(strSize));
		if (strSize > 0)
		{
			/* ������, ���������� � ������, ������� ������ ������ */
			char* strBuffer = new char[strSize];
			fl.read(strBuffer, strSize);
			temp.adText.assign(strBuffer, strSize);
			delete[] strBuffer;
		}

		/* ���������� � ������ ���������� ���������� */
		tempArr[i] = temp;
		arrSize++;
	}

	/* ��������� ���� */
	fl.close();
	
	/* ���������� false � ������� ������, ���� ���� ���������� ������ */
	/* ����� �������� ������������ ������ ����� ���������� ����� */
	if (fl.fail())
	{
		delete[] tempArr;
		return false;
	}

	else
	{
		/* ������� ������������ ������, ���� �� �� ���� */
		if (arr)
			delete arr;

		capacity = arrCapacity;
		size = arrSize;
		arr = tempArr;
		return true;
	}
}

/* ����� ����� ���������� */
void AdvertBoard::output() const
{
	std::cout << "Advert board:" << std::endl;

	/* ��������������� ������� ��� �������� ������� */
	for (int i = 0; i < size; i++)
	{
		std::cout << "Advert #" << i << std::endl;
		arr[i].output();
	}
}