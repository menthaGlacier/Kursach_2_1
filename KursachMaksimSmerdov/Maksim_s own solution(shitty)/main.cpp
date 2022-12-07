#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include "class.h"

using namespace std;

int main() // ������� �������
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    announcement st;
 
    List* head = NULL, * end = NULL; // ��������� ��������� �� ������ � ����� ������
    int choise;
    int d_v, m_v,  g_v;
    string buy;
    int number;
    do
    {
        system("cls"); // ������� �����
 
        // ������� ����
        cout << "1. �������� ������� � ������" << endl;
        cout << "2. ������������� �������� �� ����" << endl;
        cout << "3. ������� ������� �� ������" << endl;
        cout << "4. ����� ��������" << endl;
        cout << "5. ����� �������� �� ������ " << endl;
        cout << "6. ����� �������" << endl;
        cout << "7. ��������� ������ � ����" << endl;
        cout << "8. ������ ������ �� �����" << endl;
        cout << "9. �������� ������" << endl;
        cout << "10. �����" << endl;
        cout << "�������� ��������: ";
        cin >> choise;
        cout << endl;
 
        switch (choise) // � ����������� �� ����, ��� �������, ��������� ������������ ��������
        {
        case 1:
        {
            cout << "������� ����: ";
            cin >> d_v;
            cin >> m_v;
            cin >> g_v;
             if (d_v > 31 ||m_v > 12 || g_v > 2022) {
                cout << "�������� ����\n";
                break;
            }
            st.enter_new(st, d_v, m_v,  g_v); // �������� ������� ��� ��������� ������ �������� "����������"
            st.add(head, end, st, st.d,st.m,st.g, st.category, st.buy_sell, st.ad_text, st.num); // ���������  ���������� �  ������ 
            cout << "���������� ����������\n";
            break;
        }
 
        case 2:
        {
            st.sort(head); // �������� ������� ��� ���������� ������ � ����������� �� ����
            cout << "������ ������������\n";
            break;
        }
 
 
        case 3:
        {
            cout << "����� �������� ��� ��������: ";
            cin >> number;
            // �������� ����� ��� �������� ����������
            // � ���� ������� ����� 0 ������ �� ������ �������
            // ����� ���������� �� ���� �������
            if (st.del(head, end, number) == 0) cout << "������� � ������� " << number << " �����\n";
            else cout << "�������� � ������� " << number << " ���\n";
            break;
        }
 
        case 4:
        {
            cout << "������� ���������: "; 
            cin >> buy;
            cin.get();
            st.find(head, st, buy);
            buy.clear();
            break;
        }
        case 5:
        {
            cout << "������� �����: "; 
            cin >> buy;
            cin.get();
            st.find_str(head, st, buy);
            buy.clear();
            break;
        }
 
        case 6:
        {
            st.out(head); // �������� ������� ��� ������ ���������� � ����������
            break;
        }
 
        case 7:
        {
            int number;
            string a;
            cout << "1. ��������� � ���� �� ���������" << '\n';
            cout << "2. ������ ���� �������������� (������: 'D:\\file.txt')" << endl;
            cout << "�������� ��������: ";
            cin >> number;
            if (number == 1)
            {
                a = "file.txt";
                st.save(head, a);
            }
            else
            {
                cout << "������� ���� � �����: ";
                cin >> a;
                st.save(head, a);
            }
            break;
        }
 
        case 8:
        {
            int number;
            string a;
            cout << "1.������ �� ����� �� ���������" << '\n'
                << "2.������ ���� �������������� (������:'D:\\input.txt')" << endl;
            cout << "�������� ��������: "; cin >> number;
            if (number == 1)
            {
                a = "file.txt";
                st.load(head, end, st, a);
            }
            else
            {
                cout << "������� ���� � �����: ";
                cin >> a;
                st.load(head, end, st, a);
            }
            break;
        }
 
        case 9:
        {
            st.clear(head, end);
            cout << "�� �������� ������" << endl;
            break;
        }
 
        case 10:
        {
            return 0;
        }
        }
        if (choise > 0 && choise <= 8) system("pause"); // ���� ��������� �������� �������� � ���������� �� 1 �� 8, �� ����������� ��������� �� ������
    } while (choise != 0);
    return 0;
}