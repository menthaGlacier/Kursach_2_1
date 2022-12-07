#include "dependencies.h"
//#include "Announcement.h"
#include "List.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List list;
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
				buffer.clear();
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
				cout << "�������� ��� ���������� (�����/������)" << std::endl;
				buffer.clear();
				cin >> buffer;
				if (buffer != "�����" && buffer != "������")
				{
					cout << "�������� ���" << endl;
				}
				else
				{
					new_element.setBS(buffer);
					break;
				}
			}

			cout << "������� ������� ����������" << endl;
			buffer.clear();
			cin >> buffer;
			new_element.setCategory(buffer);

			cout << "������� ���������� ����� (��� 8)" << endl;
			unsigned long long number;
			cin >> number;
			new_element.setNumber(number);

			cout << "������� ����� ����������" << endl;
			buffer.clear();
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
			if (list.del(index-1) == true) { cout << "���������� ������ �������"; }
			else { cout << "��� ������ ����������"; }
			break;
		}

		case 4:
		{
			break;
		}

		case 5:
		{
			break;
		}

		case 6:
		{
			list.out();
			break;
		}

		case 7:
		{
			break;
		}

		case 8:
		{
			break;
		}

		case 9:
		{
			list.clear();
			break;
		}

		case 10:
		{
			should_close = true;
			break;
		}

		default:
		{

		}
		}

		cout << "\n\n\n";
		system("pause");
	}
}