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
		Announcement tmp;
		while (tmp.fileLoad(file))	//�������� �� ������ � �����
		{
			size++;	//������������ ������
			if (tmp.next != -1) file.seekg(tmp.next);
			else break;
		}
	}
}

List::~List()	//���������� ������
{
	if (file.is_open()) file.close();	//���� ���� ������, ���������
}

//���������� ������ � ����� ������
void List::add(Announcement& elem)
{
	Announcement tmp;
	long long int prev_pos = -1, cur_pos = 0;//�������� ��������� �� ������� ����� ����� � �� �����
	file.seekg(cur_pos);	//��������� � ������ �����

	while (tmp.fileLoad(file))	//�������� �� ���������� ��������, �������� ���
	{
		prev_pos = cur_pos;
		cur_pos = tmp.next;
		if (cur_pos == -1)
			break;
		file.seekg(cur_pos);
	}

	file.clear();
	file.seekg(0, ios::end);	//��������� � ����� �����
	cur_pos = file.tellg();	//���������� ������� ������� � �����
	elem.next = -1;

	if (prev_pos != -1)	//���� ����� ����� �������� ���� ��������
	{
		//��������� � ����� � �����, ��� �������� �������� ��������� 
		//�� ��������� ������� � �������� ����� �����
		file.seekg(prev_pos);
		file.write(reinterpret_cast<char*>(&cur_pos), sizeof(cur_pos));//���������� �������� ��������� �� ����� �������
		file.seekg(cur_pos);//��������� � ������� ����� �������
	}
	elem.fileSave(file);//���������� �������
	size++;//����������� ������ ������
	file.flush();//��������� ��������� � ����� �� ����
}

//������� ������ �� �������
void List::insert(Announcement& elem, unsigned int pos)
{
	if (pos >= size)	//������� � �����
	{
		add(elem);
		return;
	}
	
	if (pos == 0)	//������� � ������
	{
		long long int prev_pos = 0, next_pos = -1;
		fstream temp_file("tmp.bin", ios::out | ios::binary);//������ ��������� ����
		//�������������� ����� �������
		elem.next = -1;
		elem.fileSave(temp_file);//���������� �� ��������� ����

		next_pos = temp_file.tellg();//���������� � �������� ��������� ������� ��� ���������� ��������
		file.seekg(0);//������������ � ������ ������� �����
		Announcement tmp;
		for (unsigned int i = 0; i < size; i++)//�������� �� ������� ������
		{
			tmp.fileLoad(file);//��������� ������� �� ������� �����
			tmp.next = -1;
			tmp.fileSave(temp_file);//���������� ������� �� ��������� ����

			//��������� ���������� ������� � ���������
			temp_file.seekg(prev_pos);
			temp_file.write(reinterpret_cast<char*>(&next_pos), sizeof(next_pos));

			prev_pos = next_pos;
			temp_file.seekg(0, ios::end);	//��������� � ����� ���������� ����� � ������� ���������
			next_pos = temp_file.tellg();
		}
		file.close();//��������� �����
		temp_file.close();
		remove("board.bin");//������� ������ ����
		rename("tmp.bin", "board.bin");//��������������� ��������� ����
		file.open("board.bin", ios::in | ios::out | ios::binary);//������ ��� ��������
		size++;//����������� ������ ������
		return;
	}

	long long int prev_pos = -1, next_pos = 0;
	file.seekg(next_pos);//��������� � ������ �����
	Announcement tmp;
	for (unsigned int i = 0; i < pos; i++)//�������� �� ������� �������
	{
		file.seekg(next_pos);//��������� � ���������� �����
		tmp.fileLoad(file);//��������� �� ����� �����
		prev_pos = next_pos;//������� ���������
		next_pos = tmp.next;
	}

	file.seekg(0, ios::end);//��������� � ����� �����
	long long int cur_pos = file.tellg();	//��������� ������� ������ ��������
	elem.next = next_pos;
	elem.fileSave(file);//��������� ����� ������� � ����

	file.seekg(prev_pos);//��������� ���������� ������� � �����
	file.write(reinterpret_cast<char*>(&cur_pos), sizeof(cur_pos));

	file.flush();//��������� ��������� � ����� �� ����
	size++;//����������� ������ ������
}

bool List::removeAt(unsigned int pos)	//�������� � �������� �������
{
	if (pos >= size) return false; //���� ��� ������ ������� �� ������� �� ������ ��������

	long long int last = -1, prev = -1;
	Announcement tmp;
	fstream temp_file("tmp.bin", ios::out | ios::binary);//������ ��������� ����
	file.seekg(0);//��������� � ������ ������� �����
	for (unsigned int i = 0; i < size; i++) //�������� �� ������
	{
		tmp.fileLoad(file);//��������� �������
		if (i == pos)//���� ������ ��������� � ���������, �� ���������� ���
		{
			if (tmp.next != -1)
				file.seekg(tmp.next);
			continue;
		}
		//����� ��������� ������� � ����� ����
		temp_file.seekg(0, ios::end);
		last = temp_file.tellg();
		tmp.next = -1;
		tmp.fileSave(temp_file);
		
		if (prev != -1)//��������� ��������� ����������� � �����
		{
			temp_file.seekg(prev);
			temp_file.write(reinterpret_cast<char*>(&last), sizeof(last));
		}
		prev = last;//������� ���������
	}
	//��������� �����
	file.close();
	temp_file.close();
	//������� ������ ����, ������ ����� ��������
	remove("board.bin");
	rename("tmp.bin", "board.bin");
	file.open("board.bin", ios::in | ios::out | ios::binary);
	size--;
	return true;
}

long long int List::getNode(unsigned int pos, Announcement& node)	//��������� �������� �� �������
{
	if (pos >= size)
		return -1;	//���� ��� �������� ���������� �������������� �������� ���������
	long long int pos = 0;
	file.seekg(pos);	//��������� � ������ �����
	for (unsigned int i = 0; i < size; i++)	//�������� �� ������
	{
		node.fileLoad(file);	//��������� ������� �� �����
		if (i == pos)	//���� ������ ��������� � ������
			break;//������� �� �����

		pos = node.next;	//��������� � � ���������� ��������
		file.seekg(node.next);
	}
	return pos; //���������� �������� ���������
}

//�������������� �������� �� �������
bool List::edit(Announcement& elem, unsigned int pos)
{
	long long int pos = -1;
	Announcement tmp;
	pos = getNode(pos, tmp);//�������� ������� �� �������
	if (pos == -1)
		return false;//���� ������� �� ������� ������� � �������

	if ((tmp.ad_text.size() + tmp.category.size()) ==
		(elem.ad_text.size() + elem.category.size()))	//���� ������ ������ � ����� �� ���������
	{
		file.seekg(pos);	//��������� �� ��������� ���������
		elem.next = tmp.next;
		elem.fileSave(file);//�������������� ������
		return true;
	}
	//���� ������ ������ ����������
	removeAt(pos);//������� ������ �������
	insert(elem, pos);//��������� �����
	return true;
}

void List::out()//����� ������ � �������
{
	cout << "������ ����������: ";
	Announcement tmp;
	file.seekg(0);//��������� � ������ �����
	if (size == 0)
		cout << "�� ����� ���������" << endl;
	else {
		while (tmp.fileLoad(file))//��������� �������� �� �����
		{
			tmp.print();//������� � ������� �������
			cout << "------------------------------------------------------" << endl;;
			if (tmp.next == -1)
				break;
			file.seekg(tmp.next);//��������� � ���������� ��������
		}
	}
}

//������� � ����������� �������
void List::insertInOrder(Announcement& elem)
{
	if (size == 0)//���� ������ ����
	{
		//������ ��������� �������
		add(elem);
		return;
	}

	Announcement tmp;
	for (unsigned int i = 0; i < size; i++)//�������� �� ������
	{
		getNode(i, tmp);//�������� ������� �� �������
		if (elem < tmp)//���� �������� ������ � ���������� ������� ����� ������
		{
			insert(elem, i);//��������� �� ��� ����� ����� �������
			return;
		}
	}
	//���� ����� �� ����� ������ ��������� � ����� ������ ����� �������
	add(elem);
}

void List::findCategory(const string& ctgry)	//����� �� �������
{
	Announcement tmp;	
	bool found = false;
	cout << "��������� ���������� � ������� " << ctgry << ':' << endl;
	file.seekg(0);
	while (tmp.fileLoad(file))	//�������� �� ����� ������
	{
		if (tmp.category == ctgry)	//���� ������� �������� �������� ���������
		{
			tmp.print();	//������� �������
			found = true;
		}
	}
	if (found == false) { cout << "�� ������� �� ������ ����������" << endl; }
}

void List::findText(const string& text)	//����� �� ������ ����������
{
	Announcement tmp;
	bool found = false;
	cout << "��������� ����������, ���������� � ������ " << text << ':' << endl;
	file.seekg(0);
	while (tmp.fileLoad(file))	//�������� �� ����� ������
	{
		if (tmp.ad_text.find(text) != string::npos)	//���� � ������ ������� ����������
		{
			tmp.print();	//������� �������
			found = true;
		}
	}
	if (found == false) { cout << "�� ������� �� ������ ����������" << endl; }
}

void List::sort()//����������
{
	if (size <= 1) return;	//���� ��������� ������ ���� �������

	long long int first_pos = 0;	//��������� �� ������ �������
	for (unsigned int i = 1; i < size; i++)	//�������� ���������� �������� ������ ��� ������ �� 1
	{
		file.seekg(first_pos);	//��������� � ������� ��������
		long long int prev = -1;
		for (unsigned int j = 0; j < size - i; j++)//�������� �� ����������������� �����
		{
			//�������� ��� �������� (����� � ������)
			long long int pos1 = file.tellg();	
			Announcement temp1, temp2;
			temp1.fileLoad(file);
			file.seekg(temp1.next);

			long long int pos2 = file.tellg();
			temp2.fileLoad(file);

			//���������� ��������
			if (temp1 > temp2)
			{
				if (pos1 != first_pos)//���� ����� ������� �� ������ � ������
				{
					file.seekg(prev);//��������� ��� ���������� ������� � ������ ���������
					file.write(reinterpret_cast<char*>(&pos2), sizeof(pos2));
				}
				else//� ���� ������ �������� �������� ��������� �� ������ ������� �� ������ �������
				{
					first_pos = pos2;
				}

				//������������ ��������� ���� ������������ ���������
				file.seekg(pos1);
				file.write(reinterpret_cast<char*>(&temp2.next), sizeof(temp2.next));

				file.seekg(pos2);
				file.write(reinterpret_cast<char*>(&pos1), sizeof(pos1));

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
		Announcement tmp;
		fstream temp_file("tmp.bin", ios::binary | ios::out);//������ ��������� ����
		long long int temp_pos = -1, file_pos = first_pos, prev = -1;

		for (unsigned int i = 0; i < size; i++)//�������� �� ������ � �������� �������� � ����� ����
		{
			file.seekg(file_pos);	//������������ � ���������� �������� � ������ �����
			tmp.fileLoad(file);	//��������� �������
			file_pos = tmp.next;	//��������� ��������� �� ��������� �������

			tmp.next = -1;	//�� ����� ��������� ��� ����������
			temp_pos = temp_file.tellg();	//��������� ������� ������� � ����� ����� ��� ���������� ��� ���������� ��������
			tmp.fileSave(temp_file); //��������� ����� ������� � ����� �����

			if (prev != -1)	//���� ���� ���������� �������
			{
				temp_file.seekg(prev);	//��������� � ����������� ��������
				temp_file.write(reinterpret_cast<char*>(&temp_pos), sizeof(temp_pos));	//������������� ��������� �� ����� �������
			}
			prev = temp_pos;	//��������� � ��������� �������� ��������� �� ���������� �������
			temp_file.seekg(0, ios::end);
		}
		//��������� �����
		file.close();
		temp_file.close();
		//������� ������ ����, ����� ������ ��������
		remove("board.bin");
		rename("tmp.bin", "board.bin");

		file.open("board.bin", ios::in | ios::out | ios::binary);
	}
}