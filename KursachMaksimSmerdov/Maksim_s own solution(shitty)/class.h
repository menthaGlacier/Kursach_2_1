
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>

using namespace std;


class List;
class announcement// ��������� "����������"
{
public:
    int d,g,m; // ���� 
    string category; // ���������
    string buy_sell; // ����� , ������ 
    string ad_text; // ����� ����������
    long long num; // ����� ��������
    void enter_new(announcement& st, int d_v, int m_v, int g_v); // ������� ��� ����� ���������� � ����� ���������� � ����������
    void sort(List*& head); // ������� ��� ���������� ������ �� ����
    int del(List*& head, List*& end, int number); // ������� ��� �������� �������� ������ � ������� number
    int find(List*& head, announcement& st, string buy_sell);
    int find_str(List*& head, announcement& st, string str); // ������� ��� ������ �� ������
    void out(List* head); // ������� ��� ������ ������ �� �����
    void save(List* head, string a); // ������� ��� ���������� ������ � ����
    void load(List*& head, List*& end, announcement& st, string a); // ������� ��� ������ ������ �� �����
    void add(List*& head, List*& end, announcement st, int d, int m, int g, string category, string buy_sell, string ad_text, long long num); // ������� ��� ���������� �������� st � ������ 
    int length(List* head); // ������� ��� ��������� ���������� ��������� � ������ head
    void clear(List*& head, List*& end); // ������� ��� ������� ������ ������� �������
};
class List // C�������� �������� ������������ �������
{
public:
    announcement info; // ���������� ���������� � ��������� ������
    List* next; // ��������� �� ��������� ������� ������
};



