#include "dependencies.h"
#include "Announcement.h"
#include "List.h"

using namespace std;

#define TEST1											\
Announcement ann;																					\
\
ann.setCategory(string("1"));																		\
ann.setBS(1);																\
ann.setAdText(string("1"));													\
ann.setNumber(1);													\
\
ann.setDate(3, 3, 2003);				\
list.add(ann);										\
\
ann.setDate(2, 2, 2002);				\
list.add(ann);										\
\
ann.setDate(1,1,2001);										\
list.add(ann);									\

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	List list;
	TEST1

	{ cout << "Test1 failed" << endl; }
	bool should_close = false;
	while (!should_close)
	{
		system("cls");

		cout
			<< "<<<������ ��������� ��������>>>\n"
			<< "1. �������� ���������� � ������\n"
			<< "2. ������������� ���������� �� ����\n"
			<< "3. ������� ���������� �� ������\n"
			<< "4. ����� ���������� �� �������\n"
			<< "5. ����� ���������� �� ������\n"
			<< "6. �������� ������ ����������\n"
			<< "7. ��������� ������ � ����\n"
			<< "8. ��������� ������ �� �����\n"
			<< "9. �������� ������\n"
			<< "10. �����\n"
			<< "�������� ��������: " << flush;
		int choise;

		cin >> choise;
		cout << endl;

		switch (choise)
		{
		case 1:
		{
			bool result = false;
			string buffer;
			Announcement new_element;
			while (true)
			{
				cout << "������� ���� (��.��.����)" << endl;
				cin >> buffer;

				if (!Announcement::dateCheck(buffer))
				{
					cout << "�������� ����" << endl;
				}
				else
				{
					unsigned short day = (buffer[0] - '0') * 10 + (buffer[1] - '0');
					unsigned short month = (buffer[3] - '0') * 10 + (buffer[4] - '0');
					unsigned short year = 0;
					for (size_t i = 6; i < 10; i++)
					{
						year = year * 10 + buffer[i] - '0';
					}
					new_element.setDate(day, month, year);
					break;
				}
			}

			while (true)
			{
				cout
					<< "�������� ��� ����������:\n"
					<< "1. �����\n"
					<< "2. �������" << endl;

				unsigned short choice;
				cin >> choice;
				if (choice == 1 || choice == 2)
				{
					new_element.setBS(choice);
					break;
				}
				else { cout << "�������� ���" << endl; }
			}

			cout << "������� ������� ����������" << endl;
			cin >> buffer;
			new_element.setCategory(buffer);

			while (true)
			{
				cout << "������� ���������� ����� (��� 8)" << endl;
				unsigned long long number = 0;
				bool failed = false;
				cin >> buffer;
				for (size_t i = 0; i < buffer.size(); i++)
				{
					if (buffer[i] >= '0' && buffer[i] <= '9')
					{
						number = number * 10 + buffer[i] - '0';
					}
					else
					{
						cout << "�������� �����" << endl;
						failed = true;
						break;
					}
				}
				if (failed == false)
				{
					new_element.setNumber(number);
					break;
				}
			}

			cout << "������� ����� ����������" << endl;
			cin >> buffer;
			new_element.setAdText(buffer);

			list.add(new_element);
			break;
		}

		case 2:
		{
			list.sort();
			cout << "������ ������������" << endl;
			break;
		}

		case 3:
		{
			cout << "������� ����� ����������: ";
			size_t index;
			cin >> index;
			if (list.del(index-1) == true) { cout << "���������� ������� �������"; }
			else { cout << "��� ������ ����������"; }
			break;
		}

		case 4:
		{
			cout << "������� ������� ��� ������: ";
			string buffer;
			cin >> buffer;
			list.findCategory(buffer);
			break;
		}

		case 5:
		{
			cout << "������� ����� ��� ������: ";
			string buffer;
			cin >> buffer;
			list.findText(buffer);
			break;
		}

		case 6:
		{
			list.out();
			break;
		}

		case 7:
		{
			cout << "������� �������� ����� ��� ���������" << endl;
			string buffer;
			cin >> buffer;
			if (list.save(buffer) == false) { cout << "��������� ������ ��� ����������" << endl; }
			else { cout << "������ ������� � ���� " << buffer << endl; }
			break;
		}

		case 8:
		{
			cout << "������� �������� ����� ��� ���������" << endl;
			string buffer;
			cin >> buffer;
			if (list.load(buffer) == false) { cout << "��������� ������ ��� ��������" << endl; }
			else { cout << "������ �� ����� " << buffer << " ������� ��������"<< endl; }
			break;
		}

		case 9:
		{
			list.clear();
			cout << "������ ������" << endl;
			break;
		}

		case 10:
		{
			should_close = true;
			break;
		}

		default:
		{
			cout << "����������� ��������" << endl;
		}
		}
		
		if (!should_close)
		{
			cout << "\n\n\n";
			system("pause");
		}
	}
}