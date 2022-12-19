#include "List.h"

void Node::inputProduct()//���� ������ � ������
{ 
	for(;;)
	{
		cout << "������� ���������" << endl;
		cin >> category;

		cout << "������� �������� ������" << endl;
		cin >> name;

		cout << "������� ����������" << endl;
		cin >> quantity;

		cout << "������� ����" << endl;
		cin >> price;

		cout << "������� �������� ��������" << endl;
		cin >> percentage;

		cout << "������� ����" << endl;
		cin >> day;

		cout << "������� �����" << endl;
		cin >> month;

		cout << "������� ���" << endl;
		cin >> year;

		//��������� ���������� ������
		if (quantity < 0 || price < 0 || percentage < 0
			|| year < 1900 || month < 1 || day < 1 || day > 31 || month > 12 || year > 2022)
		{
			cout << "��������� ������" << endl;
			continue;
		}

		int maximum_day = 31;
		if (month == 2)
		{
			if (year % 4 == 0) 	//� ������� � ���������� ��� 29 ����
			{
				maximum_day = 29;
			}
			else
			{
				maximum_day = 28;//� ������� ��� 28 ����
			}
		}
		else
			if ((month < 8 && month % 2 == 0)	//� ������ ��� �� ������� 30 ����
			|| (month > 7 && month % 2 == 1)) //� �������� ��� ����� ���� 30 ����
			{
				maximum_day= 30;
			}
		
		if (day > maximum_day)	//���� ���� ����������� �����
		{
			cout << "��������� ������" << endl;
			continue;
		}

		cout << "\n�������� �����:\n";
		show();
		cout << "\n[1] - �����������" << endl;

		int key = _getch();
		//����������� ������������� ������
		if (key == '1') return;
		else continue;//��� ���������� ��������� ����
	}
}

bool Node::toFile(fstream& file)	//������ ������� ������ � ����
{
	if (!file.is_open()) return false;	//���� ���� ������ ������� � �������
	file.clear();//�������� ������ ��������� ��������� ������
	//��������� ���������� � ���� ���� ������ ������� ������
	file.write((const char*)(&prev), sizeof(prev));	
	file.write((const char*)(&next), sizeof(next));
	file.write((const char*)(&quantity), sizeof(quantity));
	file.write((const char*)(&day), sizeof(day));
	file.write((const char*)(&month), sizeof(month));
	file.write((const char*)(&year), sizeof(year));
	file.write((const char*)(&price), sizeof(price));
	file.write((const char*)(&percentage), sizeof(percentage));


	size_t size = name.size();	//�������� ������ ������ � ��������� � ���������� � ���� �� ������ ������
	file.write((const char*)(&size), sizeof(size));
	if (size > 0) file.write(name.c_str(), size);//���� ������ �� ������� ���������� � ���� ������

	size = category.size();	//�������� ������ ������ � ���������� ������
	file.write((const char*)(&size), sizeof(size));//��������� ���������� ������ ������
	if (size > 0) file.write(category.c_str(), size);//���� ������ �� ������� �� ���������� � ���� ������

	file.flush();//���������� ����� ������ � ���� �� �����
	if (file.fail()) return false;//��� ���� ������� � �������
	return true;
}

bool Node::fromFile(fstream& file)	//������ ������� ������ �� �����
{
	if (!file.is_open()) return false;//���� ���� ������ ������� � �������
	file.clear();//�������� ������ ��������� ��������� ������ 
	file.flush();//���������� ����� ������ � ���� �� �����
	//��������� ������ �� ����� ���� ������ ������� ������
	file.read((char*)(&prev), sizeof(prev));
	file.read((char*)(&next), sizeof(next));
	file.read((char*)(&quantity), sizeof(quantity));
	file.read((char*)(&day), sizeof(day));
	file.read((char*)(&month), sizeof(month));
	file.read((char*)(&year), sizeof(year));
	file.read((char*)(&price), sizeof(price));
	file.read((char*)(&percentage), sizeof(percentage));

	size_t size = 0;
	file.read((char*)(&size), sizeof(size));	//��������� ������ ������
	if (size > 0)//���� ������ �� �������
	{
		char* str = new char[size];//�������� ������ ������
		file.read(str, size);//��������� ������
		name.assign(str, size);//����������� ������ � ������
		delete[] str;//����������� ������
	}

	size = 0;
	file.read((char*)(&size), sizeof(size));//��������� ������ ������
	if (size > 0)//���� ������ �� �������
	{
		char* str = new char[size];//�������� ������ ������
		file.read(str, size);//��������� ������
		category.assign(str, size);//����������� ������ � ������
		delete[] str;//����������� ������
	}

	if (file.fail()) return false;//��� ����  ������� � �������
	return true;
}

void Node::show()//����� ������ � �������
{
	cout << "���������: " << category 
		<< "\n��������: " << name 
		<< "\n����������: " << quantity 
		<< "\n����:" << day << '.' << month << '.' << year 
		<< "\n����: " << price 
		<< "\n��������: " << percentage;
}

List::List()	//����������� ������
	: size(0)
{
	file.open("warehouse.bin", ios::in | ios::out | ios::binary);	//�������� ������� ������������ ���� 
	if (!file.is_open())	//���� ���� �� ��������
	{
		file.open("warehouse.bin", ios::out);	//������ ����
		if (!file.is_open())	//���� ������� ���� �� ������� �������� ������� �� ���������
		{
			cout << "�� ������� ������� ���� warehouse.bin" << endl;
			exit(-1);
		}
		file.close();	//��������� ����
		file.open("warehouse.bin", ios::in | ios::out | ios::binary);	//��������� �� �������� ������ � ������
	}
	else
	{
		Node temp;
		while (temp.fromFile(file))	//�������� �� ������ � �����
		{
			size++;	//������������ ������
			if (temp.next != -1) file.seekg(temp.next);
			else break;
		}
	}
}

List::~List()	//���������� ������
{
	if (file.is_open()) file.close();	//���� ���� ������, ���������
}

//���������� ������ � ����� ������
void List::add(string name, string category, int quantity, int day, int month, int year, int price, float percentage)
{
	Node temp;
	long long int prev_pos = -1, cur_pos = 0;//�������� ��������� �� ������� ����� ����� � �� �����
	file.seekg(cur_pos);	//��������� � ������ �����

	while (temp.fromFile(file))	//�������� �� ���������� ��������, �������� ���
	{
		prev_pos = cur_pos;
		cur_pos = temp.next;
		if (cur_pos == -1) break;
		file.seekg(cur_pos);
	}

	file.seekg(0, ios::end);	//��������� � ����� �����
	cur_pos = file.tellg();	//���������� ������� ������� � �����
	//�������������� ���� ����� ������� ������
	temp.prev = prev_pos;
	temp.next = -1;
	temp.name = name;
	temp.category = category;
	temp.quantity = quantity;
	temp.day = day;
	temp.month = month;
	temp.year = year;
	temp.price = price;
	temp.percentage = percentage;

	if (prev_pos != -1)	//���� ����� ����� �������� ���� ��������
	{
		//��������� � ����� � �����, ��� �������� �������� ��������� 
		//�� ��������� ������� � �������� ����� �����
		file.seekg(prev_pos + sizeof(long long int));
		file.write((const char*)(&cur_pos), sizeof(cur_pos));//���������� �������� ��������� �� ����� �������
	}
	file.seekg(cur_pos);//��������� � ������� ����� �������
	temp.toFile(file);//���������� �������
	size++;//����������� ������ ������
	file.flush();//��������� ��������� � ����� �� ����
}

//������� ������ �� �������
void List::insert(string name, string category, int quantity, int day, int month, int year, int price, float percentage, size_t index)
{
	if (index >= size)	//������� � �����
	{
		add(name, category, quantity, day, month, year, price, percentage);
		return;
	}

	Node temp;
	
	if (index == 0)	//������� � ������
	{
		long long int prev_pos = 0, next_pos = -1;
		fstream temp_file("temp.bin", ios::out | ios::binary);//������ ��������� ����
		//�������������� ����� �������
		temp.prev = -1;
		temp.next = -1;
		temp.name = name;
		temp.category = category;
		temp.quantity = quantity;
		temp.day = day;
		temp.month = month;
		temp.year = year;
		temp.price = price;
		temp.percentage = percentage;
		temp.toFile(temp_file);//���������� �� ��������� ����

		next_pos = temp_file.tellg();//���������� � �������� ��������� ������� ��� ���������� ��������
		file.seekg(0);//������������ � ������ ������� �����
		for (size_t i = 0; i < size; i++)//�������� �� ������� ������
		{
			temp.fromFile(file);//��������� ������� �� ������� �����
			temp.prev = prev_pos;//��������� � � ���������� ��������, ���������� �� ��������� ����
			temp.next = -1;

			temp.toFile(temp_file);//���������� ������� �� ��������� ����

			//��������� ���������� ������� � ���������
			temp_file.seekg(prev_pos + sizeof(next_pos));
			temp_file.write((const char*)(&next_pos), sizeof(next_pos));

			prev_pos = next_pos;
			temp_file.seekg(0, ios::end);	//��������� � ����� ���������� ����� � ������� ���������
			next_pos = temp_file.tellg();
		}
		file.close();//��������� �����
		temp_file.close();
		remove("warehouse.bin");//������� ������ ����
		rename("temp.bin", "warehouse.bin");//��������������� ��������� ����
		file.open("warehouse.bin", ios::in | ios::out | ios::binary);//������ ��� ��������
		size++;//����������� ������ ������
		return;
	}

	long long int prev_pos = -1, next_pos = 0;
	file.seekg(next_pos);//��������� � ������ �����
	for (size_t i = 0; i < index; i++)//�������� �� ������� �������
	{
		file.seekg(next_pos);//��������� � ���������� �����
		temp.fromFile(file);//��������� �� ����� �����
		prev_pos = next_pos;//������� ���������
		next_pos = temp.next;
	}

	file.seekg(0, ios::end);//��������� � ����� �����
	long long int cur_pos = file.tellg();	//��������� ������� ������ ��������
	//�������������� ����� �������
	temp.prev = prev_pos;
	temp.next = next_pos;
	temp.name = name;
	temp.category = category;
	temp.quantity = quantity;
	temp.day = day;
	temp.month = month;
	temp.year = year;
	temp.price = price;
	temp.percentage = percentage;
	temp.toFile(file);//��������� ����� ������� � ����

	file.seekg(prev_pos + sizeof(next_pos));//��������� ���������� ������� � �����
	file.write((const char*)(&cur_pos), sizeof(cur_pos));

	file.seekg(next_pos);//��������� ��������� ������� � �����
	file.write((const char*)(&cur_pos), sizeof(cur_pos));

	file.flush();//��������� ��������� � ����� �� ����
	size++;//����������� ������ ������
}

bool List::removeAt(size_t index)	//�������� � �������� �������
{
	if (index >= size) return false; //���� ��� ������ ������� �� ������� �� ������ ��������

	long long int last = -1, prev = -1;
	Node temp;
	fstream temp_file("temp.bin", ios::out | ios::binary);//������ ��������� ����
	file.seekg(0);//��������� � ������ ������� �����
	for (size_t i = 0; i < size; i++) //�������� �� ������
	{
		temp.fromFile(file);//��������� �������
		if (i == index)//���� ������ ��������� � ���������, �� ���������� ���
		{
			if (temp.next != -1) file.seekg(temp.next);
			continue;
		}
		//����� ��������� ������� � ����� ����
		temp_file.seekg(0, ios::end);
		last = temp_file.tellg();
		temp.prev = prev;
		temp.next = -1;
		temp.toFile(temp_file);
		
		if (prev != -1)//��������� ��������� ����������� � �����
		{
			temp_file.seekg(prev + sizeof(prev));
			temp_file.write((const char*)(&last), sizeof(last));
		}
		prev = last;//������� ���������
	}
	//��������� �����
	file.close();
	temp_file.close();
	//������� ������ ����, ������ ����� ��������
	remove("warehouse.bin");
	rename("temp.bin", "warehouse.bin");
	file.open("warehouse.bin", ios::in | ios::out | ios::binary);
	size--;
	return true;
}

long long int List::getNode(size_t index, Node& node)	//��������� �������� �� �������
{
	if (index >= size) return -1;	//���� ��� �������� ���������� �������������� �������� ���������

	long long int pos = 0;
	file.seekg(pos);	//��������� � ������ �����
	for (size_t i = 0; i < size; i++)	//�������� �� ������
	{
		node.fromFile(file);	//��������� ������� �� �����
		if (i == index)	//���� ������ ��������� � ������
		{
			break;//������� �� �����
		}

		pos = node.next;	//��������� � � ���������� ��������
		file.seekg(node.next);
	}
	return pos; //���������� �������� ���������
}

//�������������� �������� �� �������
bool List::edit(string name, string category, int quantity, int day, int month, int year, int price, float percentage, size_t index)
{
	Node temp;
	long long int pos = getNode(index, temp);//�������� ������� �� �������
	if (pos == -1) return false;//���� ������� �� ������� ������� � �������

	if (temp.name.size() + temp.category.size() == name.size() + category.size())	//���� ������ ������ � ����� �� ���������
	{
		file.seekg(pos);	//��������� �� ��������� ���������
		temp.name = name;
		temp.category = category;
		temp.quantity = quantity;
		temp.day = day;
		temp.month = month;
		temp.year = year;
		temp.price = price;
		temp.percentage = percentage;
		temp.toFile(file);//�������������� ������
		return true;
	}
	//���� ������ ������ ����������
	removeAt(index);//������� ������ �������
	insert(name, category, quantity, day, month, year, price, percentage, index);//��������� �����
	return true;
}

void List::show()//����� ������ � �������
{
	file.seekg(0);//��������� � ������ �����

	Node temp;
	cout << "������: " << endl;
	while (temp.fromFile(file))//��������� �������� �� �����
	{
		temp.show();//������� � ������� �������
		cout << endl << endl;
		if (temp.next == -1) break;
		file.seekg(temp.next);//��������� � ���������� ��������
	}
}

//������� � ����������� �������
void List::insertInOrder(string name, string category, int quantity, int day, int month, int year, int price, float percentage)
{
	if (size == 0)//���� ������ ����
	{
		//������ ��������� �������
		add(name, category, quantity, day, month, year, price, percentage);
		return;
	}

	Node temp;
	for (size_t i = 0; i < size; i++)//�������� �� ������
	{
		getNode(i, temp);//�������� ������� �� �������
		if (temp.name >= name)//���� �������� ������ � ���������� ������� ����� ������
		{
			insert(name, category, quantity, day, month, year, price, percentage, i);//��������� �� ��� ����� ����� �������
			return;
		}
	}
	//���� ����� �� ����� ������ ��������� � ����� ������ ����� �������
	add(name, category, quantity, day, month, year, price, percentage);
}

void List::sort(SortType type)//����������
{
	if (size <= 1) return;	//���� ��������� ������ ���� �������

	long long int first_pos = 0;	//��������� �� ������ �������
	for (size_t i = 1; i < size; i++)	//�������� ���������� �������� ������ ��� ������ �� 1
	{
		file.seekg(first_pos);	//��������� � ������� ��������
		for (size_t j = 0; j < size - i; j++)//�������� �� ����������������� �����
		{
			//�������� ��� �������� (����� � ������)
			long long int pos1 = file.tellg();	
			Node temp1, temp2;
			temp1.fromFile(file);
			file.seekg(temp1.next);

			long long int pos2 = file.tellg();
			temp2.fromFile(file);

			//���������� �������� �� ��������� ��������
			if ((type == SortType::Category && temp1.category > temp2.category)
				|| (type == SortType::Name && temp1.name > temp2.name)
				|| (type == SortType::Percentage && temp1.percentage > temp2.percentage)
				|| (type == SortType::Price && temp1.price > temp2.price)
				|| (type == SortType::Quantity && temp1.quantity > temp2.quantity)
				|| (type == SortType::Date && (temp1.year > temp2.year 
					|| (temp1.year == temp2.year && (temp1.month > temp2.month 
						|| (temp1.month == temp2.month && temp1.day > temp2.day))))))
			{
				if (temp1.prev != -1)//���� ����� ������� �� ������ � ������
				{
					file.seekg(temp1.prev + sizeof(pos2));//��������� ��� ���������� ������� � ������ ���������
					file.write((const char*)(&pos2), sizeof(pos2));
				}
				else//� ���� ������ �������� �������� ��������� �� ������ ������� �� ������ �������
				{
					first_pos = pos2;
				}

				if (temp2.next != -1)//���� ������ ������� �� ��������� � ������
				{
					file.seekg(temp2.next);//��������� ��������� �� ��� ������� � ����� ���������
					file.write((const char*)(&pos1), sizeof(pos1));
				}
				//������������ ��������� ���� ������������ ���������
				file.seekg(pos1);
				file.write((const char*)(&pos2), sizeof(pos2));
				file.write((const char*)(&temp2.next), sizeof(temp2.next));

				file.seekg(pos2);
				file.write((const char*)(&temp1.prev), sizeof(temp1.prev));
				file.write((const char*)(&pos1), sizeof(pos1));

				file.seekg(pos1);//��������� � ���������� ��������
			}
			else file.seekg(pos2);//��������� � ���������� ��������
		}
	}

	Node first, temp;
	long long int file_pos = getNode(0, first);//�������� ��������� ��� �������� �� ������� �����
	size_t index = 0;
	while (first.prev != -1) //������� ������ ������� � ������
	{
		file_pos = first.prev;//������������ � ���������� ���������
		file.seekg(first.prev);
		first.fromFile(file);
		index++;//������� ������ ��������, ������� ����� ������ � �����
	}

	if (index != 0)	//���� ������ �� �������(�� ���� ������ � ����� ������� - �� ������ � ������)
	{
		fstream temp_file("temp.bin", ios::binary | ios::out);//������ ��������� ����

		long long int temp_pos = -1;
		for (size_t i = 0; i < size; i++)//�������� �� ������ � �������� �������� � ����� ����
		{
			file.seekg(file_pos);	//������������ � ���������� �������� � ������ �����
			temp.fromFile(file);	//��������� �������
			file_pos = temp.next;	//������� ��������� �� ��������� �������

			temp.prev = temp_pos;	//��������� � ��������� �������� ��������� �� ���������� �������
			temp.next = -1;	//�� ����� ��������� ��� ����������
			temp_pos = temp_file.tellg();	//��������� ������� ������� � ����� ����� ��� ���������� ��� ���������� ��������
			temp.toFile(temp_file); //��������� ����� ������� � ����� �����

			if (temp.prev != -1)	//���� ���� ���������� �������
			{
				temp_file.seekg(temp.prev + sizeof(temp_pos));	//��������� � ��������� �� ��������� ������� ����������� ��������
				temp_file.write((const char*)(&temp_pos), sizeof(temp_pos));	//������������� ��������� �� ����� �������
			}
			temp_file.seekg(0, ios::end);
		}
		//��������� �����
		file.close();
		temp_file.close();
		//������� ������ ����, ����� ������ ��������
		remove("warehouse.bin");
		rename("temp.bin", "warehouse.bin");

		file.open("warehouse.bin", ios::in | ios::out | ios::binary);
	}
}

void List::invoice() //�������
{
	int total_sum = 0, total_quantity = 0;
	float total_percentage = 0.f;

	long long int position = 0;
	
	for (size_t i = 0; i < size; i++)//�������� �� ������
	{
		file.seekg(position);
		Node temp;
		temp.fromFile(file);//��������� �������

		total_sum += temp.price * temp.quantity;//���������� �����
		total_quantity += temp.quantity;//���������� ����������
		total_percentage += temp.percentage;//���������� ��������

		file.seekg(position);//��������� � ������ ��������
		temp.quantity = 0;//������ ���������� �� ����
		temp.toFile(file);//��������� �������

		position = temp.next;//��������� � ���������� ��������
	}
	//������� ��������
	cout << "�������� �����: " << total_sum << endl;
	cout << "�������� ��������: " << total_percentage<< endl;
	cout << "����� ����������: " << total_quantity << endl;
}