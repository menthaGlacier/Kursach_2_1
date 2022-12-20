#include "List.h"

List::List()	//����������� ������
	: size(0)
{
	file.open("board.bin", ios::in | ios::out | ios::binary);	//�������� ������� ������������ ���� 
	if (!file.is_open())	//���� ���� �� ��������
	{
		file.open("board.bin", ios::out);	//������ ����
		if (!file.is_open())	//���� ������� ���� �� ������� �������� ������� �� ���������
		{
			cout << "�� ������� ������� ���� board.bin" << endl;
			exit(-1);
		}
		file.close();	//��������� ����
		file.open("board.bin", ios::in | ios::out | ios::binary);	//��������� �� �������� ������ � ������
	}
	else
	{
		Announcement temp;
		while (temp.loadFromFile(file))	//�������� �� ������ � �����
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
void List::add(Announcement& new_element)
{
	Announcement temp;
	long long int prev_pos = -1, cur_pos = 0;//�������� ��������� �� ������� ����� ����� � �� �����
	file.seekg(cur_pos);	//��������� � ������ �����

	while (temp.loadFromFile(file))	//�������� �� ���������� ��������, �������� ���
	{
		prev_pos = cur_pos;
		cur_pos = temp.next;
		if (cur_pos == -1) break;
		file.seekg(cur_pos);
	}

	file.clear();
	file.seekg(0, ios::end);	//��������� � ����� �����
	cur_pos = file.tellg();	//���������� ������� ������� � �����
	new_element.next = -1;

	if (prev_pos != -1)	//���� ����� ����� �������� ���� ��������
	{
		//��������� � ����� � �����, ��� �������� �������� ��������� 
		//�� ��������� ������� � �������� ����� �����
		file.seekg(prev_pos);
		file.write((const char*)(&cur_pos), sizeof(cur_pos));//���������� �������� ��������� �� ����� �������
		file.seekg(cur_pos);//��������� � ������� ����� �������
	}
	new_element.saveToFile(file);//���������� �������
	size++;//����������� ������ ������
	file.flush();//��������� ��������� � ����� �� ����
}

//������� ������ �� �������
void List::insert(Announcement& new_element, size_t index)
{
	if (index >= size)	//������� � �����
	{
		add(new_element);
		return;
	}
	
	if (index == 0)	//������� � ������
	{
		long long int prev_pos = 0, next_pos = -1;
		fstream temp_file("temp.bin", ios::out | ios::binary);//������ ��������� ����
		//�������������� ����� �������
		new_element.next = -1;
		new_element.saveToFile(temp_file);//���������� �� ��������� ����

		next_pos = temp_file.tellg();//���������� � �������� ��������� ������� ��� ���������� ��������
		file.seekg(0);//������������ � ������ ������� �����
		Announcement temp;
		for (size_t i = 0; i < size; i++)//�������� �� ������� ������
		{
			temp.loadFromFile(file);//��������� ������� �� ������� �����
			temp.next = -1;

			temp.saveToFile(temp_file);//���������� ������� �� ��������� ����

			//��������� ���������� ������� � ���������
			temp_file.seekg(prev_pos);
			temp_file.write((const char*)(&next_pos), sizeof(next_pos));

			prev_pos = next_pos;
			temp_file.seekg(0, ios::end);	//��������� � ����� ���������� ����� � ������� ���������
			next_pos = temp_file.tellg();
		}
		file.close();//��������� �����
		temp_file.close();
		remove("board.bin");//������� ������ ����
		rename("temp.bin", "board.bin");//��������������� ��������� ����
		file.open("board.bin", ios::in | ios::out | ios::binary);//������ ��� ��������
		size++;//����������� ������ ������
		return;
	}

	long long int prev_pos = -1, next_pos = 0;
	file.seekg(next_pos);//��������� � ������ �����
	Announcement temp;
	for (size_t i = 0; i < index; i++)//�������� �� ������� �������
	{
		file.seekg(next_pos);//��������� � ���������� �����
		temp.loadFromFile(file);//��������� �� ����� �����
		prev_pos = next_pos;//������� ���������
		next_pos = temp.next;
	}

	file.seekg(0, ios::end);//��������� � ����� �����
	long long int cur_pos = file.tellg();	//��������� ������� ������ ��������
	new_element.next = next_pos;
	new_element.saveToFile(file);//��������� ����� ������� � ����

	file.seekg(prev_pos);//��������� ���������� ������� � �����
	file.write((const char*)(&cur_pos), sizeof(cur_pos));

	file.flush();//��������� ��������� � ����� �� ����
	size++;//����������� ������ ������
}

bool List::removeAt(size_t index)	//�������� � �������� �������
{
	if (index >= size) return false; //���� ��� ������ ������� �� ������� �� ������ ��������

	long long int last = -1, prev = -1;
	Announcement temp;
	fstream temp_file("temp.bin", ios::out | ios::binary);//������ ��������� ����
	file.seekg(0);//��������� � ������ ������� �����
	for (size_t i = 0; i < size; i++) //�������� �� ������
	{
		temp.loadFromFile(file);//��������� �������
		if (i == index)//���� ������ ��������� � ���������, �� ���������� ���
		{
			if (temp.next != -1) file.seekg(temp.next);
			continue;
		}
		//����� ��������� ������� � ����� ����
		temp_file.seekg(0, ios::end);
		last = temp_file.tellg();
		temp.next = -1;
		temp.saveToFile(temp_file);
		
		if (prev != -1)//��������� ��������� ����������� � �����
		{
			temp_file.seekg(prev);
			temp_file.write((const char*)(&last), sizeof(last));
		}
		prev = last;//������� ���������
	}
	//��������� �����
	file.close();
	temp_file.close();
	//������� ������ ����, ������ ����� ��������
	remove("board.bin");
	rename("temp.bin", "board.bin");
	file.open("board.bin", ios::in | ios::out | ios::binary);
	size--;
	return true;
}

long long int List::getNode(size_t index, Announcement& node)	//��������� �������� �� �������
{
	if (index >= size) return -1;	//���� ��� �������� ���������� �������������� �������� ���������

	long long int pos = 0;
	file.seekg(pos);	//��������� � ������ �����
	for (size_t i = 0; i < size; i++)	//�������� �� ������
	{
		node.loadFromFile(file);	//��������� ������� �� �����
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
bool List::edit(Announcement& changed_element, size_t index)
{
	Announcement temp;
	long long int pos = getNode(index, temp);//�������� ������� �� �������
	if (pos == -1) return false;//���� ������� �� ������� ������� � �������

	if (temp.ad_text.size() + temp.category.size() == changed_element.ad_text.size() + changed_element.category.size())	//���� ������ ������ � ����� �� ���������
	{
		file.seekg(pos);	//��������� �� ��������� ���������
		changed_element.next = temp.next;
		changed_element.saveToFile(file);//�������������� ������
		return true;
	}
	//���� ������ ������ ����������
	removeAt(index);//������� ������ �������
	insert(changed_element, index);//��������� �����
	return true;
}

void List::out()//����� ������ � �������
{
	file.seekg(0);//��������� � ������ �����

	Announcement temp;
	cout << "������ ����������:";
	if (size == 0) { cout << " ����." << endl; return; }
	while (temp.loadFromFile(file))//��������� �������� �� �����
	{
		temp.print();//������� � ������� �������
		cout << endl;
		if (temp.next == -1) break;
		file.seekg(temp.next);//��������� � ���������� ��������
	}
}

//������� � ����������� �������
void List::insertInOrder(Announcement& new_element)
{
	if (size == 0)//���� ������ ����
	{
		//������ ��������� �������
		add(new_element);
		return;
	}

	Announcement temp;
	for (size_t i = 0; i < size; i++)//�������� �� ������
	{
		getNode(i, temp);//�������� ������� �� �������
		if (new_element < temp)//���� �������� ������ � ���������� ������� ����� ������
		{
			insert(new_element, i);//��������� �� ��� ����� ����� �������
			return;
		}
	}
	//���� ����� �� ����� ������ ��������� � ����� ������ ����� �������
	add(new_element);
}

void List::findCategory(const string& ctgry)	//����� �� �������
{
	Announcement temp;	
	bool found = false;
	cout << "��������� ���������� � ������� " << ctgry << ':' << endl;
	file.seekg(0);
	while (temp.loadFromFile(file))	//�������� �� ����� ������
	{
		if (temp.category == ctgry)	//���� ������� �������� �������� ���������
		{
			temp.print();	//������� �������
			found = true;
		}
	}
	if (found == false) { cout << "�� ������� �� ������ ����������" << endl; }
}

void List::findText(const string& text)	//����� �� ������ ����������
{
	Announcement temp;
	bool found = false;
	cout << "��������� ����������, ���������� � ������ " << text << ':' << endl;
	file.seekg(0);
	while (temp.loadFromFile(file))	//�������� �� ����� ������
	{
		if (temp.ad_text.find(text) != string::npos)	//���� � ������ ������� ����������
		{
			temp.print();	//������� �������
			found = true;
		}
	}
	if (found == false) { cout << "�� ������� �� ������ ����������" << endl; }
}

void List::sort()//����������
{
	if (size <= 1) return;	//���� ��������� ������ ���� �������

	long long int first_pos = 0;	//��������� �� ������ �������
	for (size_t i = 1; i < size; i++)	//�������� ���������� �������� ������ ��� ������ �� 1
	{
		file.seekg(first_pos);	//��������� � ������� ��������
		long long int prev = -1;
		for (size_t j = 0; j < size - i; j++)//�������� �� ����������������� �����
		{
			//�������� ��� �������� (����� � ������)
			long long int pos1 = file.tellg();	
			Announcement temp1, temp2;
			temp1.loadFromFile(file);
			file.seekg(temp1.next);

			long long int pos2 = file.tellg();
			temp2.loadFromFile(file);

			//���������� ��������
			if (temp1 > temp2)
			{
				if (pos1 != first_pos)//���� ����� ������� �� ������ � ������
				{
					file.seekg(prev);//��������� ��� ���������� ������� � ������ ���������
					file.write((const char*)(&pos2), sizeof(pos2));
				}
				else//� ���� ������ �������� �������� ��������� �� ������ ������� �� ������ �������
				{
					first_pos = pos2;
				}

				//������������ ��������� ���� ������������ ���������
				file.seekg(pos1);
				file.write((const char*)(&temp2.next), sizeof(temp2.next));

				file.seekg(pos2);
				file.write((const char*)(&pos1), sizeof(pos1));

				file.seekg(pos1);//��������� � ���������� ��������
				prev = pos2;
			}
			else
			{
				file.seekg(pos2);//��������� � ���������� ��������
				prev = pos1;
			}
		}
	}

	if (first_pos != 0)
	{
		Announcement temp;
		fstream temp_file("temp.bin", ios::binary | ios::out);//������ ��������� ����
		long long int temp_pos = -1, file_pos = first_pos, prev = -1;

		for (size_t i = 0; i < size; i++)//�������� �� ������ � �������� �������� � ����� ����
		{
			file.seekg(file_pos);	//������������ � ���������� �������� � ������ �����
			temp.loadFromFile(file);	//��������� �������
			file_pos = temp.next;	//��������� ��������� �� ��������� �������

			temp.next = -1;	//�� ����� ��������� ��� ����������
			temp_pos = temp_file.tellg();	//��������� ������� ������� � ����� ����� ��� ���������� ��� ���������� ��������
			temp.saveToFile(temp_file); //��������� ����� ������� � ����� �����

			if (prev != -1)	//���� ���� ���������� �������
			{
				temp_file.seekg(prev);	//��������� � ����������� ��������
				temp_file.write((const char*)(&temp_pos), sizeof(temp_pos));	//������������� ��������� �� ����� �������
			}
			prev = temp_pos;	//��������� � ��������� �������� ��������� �� ���������� �������
			temp_file.seekg(0, ios::end);
		}
		//��������� �����
		file.close();
		temp_file.close();
		//������� ������ ����, ����� ������ ��������
		remove("board.bin");
		rename("temp.bin", "board.bin");

		file.open("board.bin", ios::in | ios::out | ios::binary);
	}
}