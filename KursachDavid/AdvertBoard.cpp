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
	{
		return;
	}

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
	// TODO
}

/* ������� �������� � ����������� ������� */
void AdvertBoard::insort(const Advert& advert)
{
	// TODO
}

/* �������� ���������� �������� ������� */
void AdvertBoard::remove()
{
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
	// TODO
}

/* ��������� �������� ����� ��������� */
Advert* AdvertBoard::operator[](int pos) const
{
	/* ������ ���������� � ������������� ��� ��������� �� ������ ��������� */
	if (pos < 0 || pos + 1 > size)
	{
		return nullptr;
	}

	/* ���������� ������� */
	return &(arr[pos]);
}

/* ����� �� �������� ������� � �� ������� �������� ����� � ������ ���������� */
void AdvertBoard::find() const
{
	// TODO
}

/* ���������� �� ���� ������ */
void AdvertBoard::sort()
{
	// TODO
}

/* ���������� ����� ���������� � ����� */
void AdvertBoard::save(std::string file) const
{
	// TODO
}

/* �������� ����� ���������� �� ����� */
void AdvertBoard::load(std::string file)
{
	// TODO
}

/* ����� ����� ���������� */
void AdvertBoard::output() const
{
	// TODO
}