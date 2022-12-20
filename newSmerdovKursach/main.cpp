#include "dependencies.h"
#include "Announcement.h"
#include "List.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");	//������������� ������� ������ � ��������� ��������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List list;	//������ ������
	bool should_close = false;	//����������, ������������ ����� �� ��������� ��� �������� true
	string buffer;
	while (!should_close)
	{
		system("cls");	//������� �����

		cout << "<============����============>" << endl;
		cout << "\t1. �������� ���������� � ������" << endl;
		cout << "\t2. ������������� ���������� �� ����" << endl;
		cout << "\t3. ������� ���������� �� ������" << endl;
		cout << "\t4. ������������� ���������� � ������" << endl;
		cout << "\t5. ����� ���������� �� �������" << endl;
		cout << "\t6. ����� ���������� �� ������" << endl;
		cout << "\t7. �������� ������ ����������" << endl;
		cout << "\t8. ������������ �������� ����������" << endl;
		cout << "\t9. �����" << endl;
		cout << "�������� ��������: " << flush;
		char choise;

		cin >> choise;	//�������� ����� �� ������������
		cout << endl;

		switch (choise)
		{
			case '1':		//���������� ����������
			{
				Announcement new_element;	//����������� �������
				new_element.inputAnnouncement(new_element);

				while (true)
				{
					cout
						<< "<<<���� �������� ����������>>>\n"
						<< "1. �������� ���������� � ����� ������\n"
						<< "2. �������� ���������� � �������� ������� ������\n"
						<< "3. �������� ���������� � ����������� �������\n"
						<< "�������� ��������: " << flush;

					char choise;

					cin >> choise;	//�������� ����� �� ������������
					cout << endl;

					switch (choise)
					{
						case '1': 
						{
							list.add(new_element);
							break;
						}
						case '2':
						{
							cout << "������� �����" << endl;
							unsigned long long number = 0;
							bool badInput = false;
							cin >> buffer;
							for (unsigned int i = 0; i < buffer.size(); i++)	//��������������� ���������� ������� � �����
							{
								if (buffer[i] >= '0' && buffer[i] <= '9')
								{
									number = number * 10 + buffer[i] - '0';
								}
								else		//���� ������ �� �����
								{
									cout << "�������� �����" << endl;
									badInput = true;	//������������� ���� ������
									break;	//���������� ��������������
								}
							}
							if (badInput == false)	//���� �� ���� �������� ������ ��� ��������������
							{
								list.insert(new_element, number - 1);	//��������� � �������� �������
								break;
							}
							break;
						}
						case '3':
						{
							list.insertInOrder(new_element);
							break;
						}
						default:
						{
							cout << "����������� ��������" << endl;
							continue;
						}
					}
					break;
				}
				break;
			}

			case '2':	//���������� ������
			{
				list.sort();
				cout << "������ ������������" << endl;
				break;
			}

			case '3':	//�������� ����������
			{
				cout << "������� ����� ����������: ";
				unsigned int pos = 0;
				bool badInput = false;
				cin >> buffer;	//�������� ������ �� ������������
				for (unsigned int i = 0; i < buffer.size(); i++)	//��������������� ������ � �����
				{
					if (buffer[i] >= '0' && buffer[i] <= '9')
					{
						pos = pos * 10 + buffer[i] - '0';
					}
					else		//���� ������ �� �����
					{
						cout << "�������� �����" << endl;
						badInput = true;	//������������� ���� ������
						break;	//��������� ��������������
					}
				}
				//���� ������� �������� ����� � ���������� ������� � ����� ��������, �� ������� ���
				if (badInput == false && list.removeByIndex(pos - 1) == true) { cout << "���������� ������� �������"; }
				else { cout << "��� ������ ����������"; }
				break;
			}

			case '4'://��������������
			{
				cout << "������� ����� ����������" << endl;
				unsigned int pos = 0;
				bool badInput = false;
				cin >> buffer;	//�������� ������ �� ������������
				for (unsigned int i = 0; i < buffer.size(); i++)	//��������������� ������ � �����
				{
					if (buffer[i] >= '0' && buffer[i] <= '9')
					{
						pos = pos * 10 + buffer[i] - '0';
					}
					else		//���� ������ �� �����
					{
						cout << "�������� �����" << endl;
						badInput = true;	//������������� ���� ������
						break;	//��������� ��������������
					}
				}

				Announcement tmp;
				if (badInput == true || list.getNode(pos-1, tmp) == -1)
				{
					cout << "��� ������ ����������"; 
					break;
				}

				tmp.inputAnnouncement(tmp);//�������� ���� ������ ����������
				//�������� ��������������� ����������
				if (list.edit(tmp, pos-1) == false) { cout << "�� ������� ��������" << endl; }
				else { cout << "��������" << endl; }
				break;
			}
			case '5':	//����� �� �������
			{
				cout << "������� ������� ��� ������: ";
				cin.ignore(256, '\n');
				getline(cin, buffer);

				list.findCategory(buffer);
				break;
			}

			case '6':	//����� �� ������ ����������
			{
				cout << "������� ����� ��� ������: ";
				cin.ignore(256, '\n');
				getline(cin, buffer);

				list.findText(buffer);
				break;
			}

			case '7':	//����� ������
			{
				list.out();
				break;
			}
			case '8'://�������� �����������
			{
				unsigned int pos = 1;
				Announcement tmp;
				bool go_back = false;
				while (!go_back)
				{
					if (list.getSize() == 0)
					{
						cout << "������ ����" << endl;
						break;
					}

					list.getNode(pos - 1, tmp);
					cout << "������� ���������� �" << pos << endl;
					tmp.print();
					cout << endl;
					cout << "�������� ��������:" << endl;
					cout << "1. ���������" << endl;
					cout << "2. ����������" << endl;
					cout << "b. ����������� � ����" << endl;

					char choise;

					cin >> choise;	//�������� ����� �� ������������
					cout << endl;
					switch (choise)
					{
						case '1'://���������
						{
							if (pos < list.getSize())
								pos++;
							else
								cout << "��������� �������" << endl;
							continue;
						}
						case '2'://����������
						{
							if (pos > 1)
								pos--;
							else
								cout << "������ �������" << endl;
							continue;
						}
						case 'b'://����������� �����
						{
							go_back = true;
							break;
						}
						default:	//��������� ������� �� ��������������
						{
							cout << "����������� ��������" << endl;
							continue;
						}
					}
					break;
				}
				break;
			}
			case '9':	//�����
			{
				should_close = true;
				break;
			}

			default:	//��������� ������� �� ��������������
				cout << "����������� ��������" << endl;
		}

		if (!should_close)
		{
			cin.unget();
			cin.ignore(256, '\n');
			cout << "\n\n\n";
			system("pause");
		}
	}
}