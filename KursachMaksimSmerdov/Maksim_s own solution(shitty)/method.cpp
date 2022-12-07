#include "class.h"

 using namespace std;

void announcement::enter_new(announcement& st,int d_v,int m_v, int g_v) // ������� ��� ����� ���������� � ����� ����������
{
    st.d=d_v;
    st.m=m_v;
    st.g=g_v;
    cin.get(); // ��� ��������� �������� ���� �������
 
    cout << "������� ���������: ";
    getline(cin, st.category);
 
    cout << "������� �������� ��� ���������: ";
    getline(cin, st.buy_sell);
 
    cout << "������� ����� ����������  �����: ";
     getline(cin, st.ad_text);
 
    cout << "������� ����� , ��� 8: ";
    cin >> st.num;
    cin.get(); // ��� ��������� �������� ���� �������
}
 
void announcement::sort(List*& head) // ������� ��� ���������� ������
{
    List* t = head, * tt;
    announcement temp;
    while (t != NULL)
    {
        tt = t->next;
        while (tt != NULL)
        {
            if ((tt->info.d+tt->info.m+tt->info.g) < (t->info.d+t->info.m+t->info.g))
            {
                temp = tt->info;
                tt->info = t->info;
                t->info = temp;
            }
            tt = tt->next;
        }
        t = t->next;
    }
}
 
 
int announcement::del(List*& head, List*& end, int number) // ������� ��� �������� �������� ������ � ������� number
{
    int n = length(head); // �������� ���������� ��������� ������
    if (number > n || number <= 0 || n == 0) // ���� number ������ ���������� ��������� ������ ��� ������ ��� ����� ���� ��� ������ ���� ��
    {
        return 1; // ���������� ��������� ������ ������� = 1, �.�. ���� ������
    }
    List* t = head, * tt = head;
    if (number == 1) // ���� ���������� ������� ������ ������� ������ ��
    {
        t = head; // ���������� ������ ������� ������ � ���������� t
        head = head->next; // ��������� � ���������� ��������
        delete t; // ������� ������ �������
        // ���� ������ ������ ����� ������ ��
        // ����� ������ ������ ������
        if (head == NULL) end = NULL;
    }
    else // �����
    {
        tt = head; // ���������� ������� ������� ������
        t = head->next; // ���������� ����������� ������� ������
        int i = 1; // ���������� �������� � 1 �.�. ������ ������� ��� ����������
        while (t != NULL) // ���� �� ����� ������
        {
            i++; // ����������� ������ �� 1
            if (i == number) // ���� i == number, �.�. ����� �������� �������� ����� ������ ���������� ��
            {
                tt->next = t->next; // ������������ ���������
                break; // ��������� ����
            }
            // ��������� � ��������� ���������
            tt = tt->next;
            t = t->next;
        }
        if (number == n) end = tt; // ���� ��������� ������� �������� ��������� �� ������ ��������� �� ����� ������
        delete t; // ����������� ������ ������� ��� ������� � ������� number
    }
    return 0; // ��������� � ���������� ��������
}
 
int  announcement::find(List*& head, announcement& st, string buy_sell) // ������� ��� ������ �� ����
{
    int i = 0;
    List* pointer = head;
    while (head != NULL)
    {
        if (head->info.buy_sell == buy_sell) {
             cout << "����� ���������� ����." << endl;
             cout << setw(0) << i
            << setw(20) << head->info.d
            << setw(1) << "."
            << setw(1) << head->info.m
            << setw(1) << "."
            << setw(1) << head->info.g
            << setw(30) << head->info.category
            << setw(40) << head->info.buy_sell
            << setw(50) << head->info.ad_text
            << setw(60) << head->info.num
            << endl;
        }
        i++;
        head = head->next;
    }
    cout << "����� ���������� ���." << endl;
    head = pointer;
    return -1;
}

int  announcement::find_str(List*& head, announcement& st, string str) // ������� ��� ������ �� ����
{
    int flag = 0;
    int len = 0;
    List* pointer = head;
    int i = 0;
    while (head != NULL)
    {
        for (int j = 0; head->info.ad_text[j] != '\0'; j++) {
            if (head->info.ad_text[j] == str[j]) {
                len++;
                flag = 1;
            }
            else {
                len = 0;
                flag = 0;
                break;
            }
        }
            if (len = str.length() && flag==1) {
             cout << "����� ���������� ����." << endl;
            cout << setw(0) << i
            << setw(20) << head->info.d
            << setw(1) << "."
            << setw(1) << head->info.m
            << setw(1) << "."
            << setw(1) << head->info.g
            << setw(30) << head->info.category
            << setw(40) << head->info.buy_sell
            << setw(50) << head->info.ad_text
            << setw(60) << head->info.num
            << endl;
            }
            
        len = 0;
        i++;
        head = head->next;
    }
    cout << "����� ���������� ���." << endl;
    head = pointer;
    return -1;
}

void  announcement::out(List* head) // ������� ��� ������ ������ �� �����
{
    if (head == NULL) // ���� head = NULL ������ ������ ����
    {
        cout << "������ ����\n";
        return;
    }
 
    // ������� ����� ��� ������ ����������
    cout << setw(0) << "�"
        << setw(24) << "���� "
        << setw(34) << "���������"
        << setw(42) << "�����,������"
        << setw(54) << "����� ����������"
        << setw(53) << "�����"
        << endl;
 
    for (int i = 1; head != NULL; i++)
    {
        cout << setw(0) << i
            << setw(20) << head->info.d
            << setw(1) << "."
            << setw(1) << head->info.m
            << setw(1) << "."
            << setw(1) << head->info.g
            << setw(30) << head->info.category
            << setw(40) << head->info.buy_sell
            << setw(50) << head->info.ad_text
            << setw(60) << head->info.num
            << endl;
        head = head->next;
    }
}
 
void  announcement::save(List* head, string a) // ������� ��� ���������� ������ � ����
{
    ofstream out;
    out.open(a);
    if (out.is_open())
    {
        for (int i = 0; head != NULL; i++)
        {
            out << setw(20) << head->info.d
            << setw(22) << head->info.m
            << setw(24) << head->info.g
            << setw(30) << head->info.category
            << setw(40) << head->info.buy_sell
            << setw(50) << head->info.ad_text
                 << endl
            << setw(60) << head->info.num
            << endl;
            head = head->next;
        }
        cout << "������ ��������� � ����\n";
    }
    else cout << "���������� �� �������" << endl;
    out.close();
}
 
void  announcement::load(List*& head, List*& end, announcement& st, string a)// ������� ��� �������� �� �����
{
    ifstream in;
    in.open(a);
    if (in.is_open())
    {
        while (!in.eof())
        {
            
            in >> st.d;
            if (in.eof()) break;
            in >> st.m;
            in >> st.g;
            in >> st.category;
            in >> st.buy_sell;
            getline(in,ad_text);
            in >> st.num;
            add(head, end, st, st.d,st.m,st.g, st.category, st.buy_sell, st.ad_text, st.num);
        }
    }
    else cout << "������ �� ����� �� �������" << endl;
    in.close();
}
 
void announcement::add(List*& head, List*& end, announcement st, int d,int m,int g, string category, string buy_sell, string ad_text, long long num) // ������� ��� ���������� �������� st � ������ 
{
    if (head == NULL) // ���� ������ ��� �� ������,��
    {
        head = new List; // �������� ����� ��� ������ ������
        head->next = NULL; // �������� ��������� �� ��������� �������
        head->info = st; // ������� ������ � ������ ������
        end = head; // ����� ������ ������������� � head
    }
    else // �����
    {
        List* x = new List; // �������� ����� ��� ����� �������
        x->info = st; // ������� ���� ������
        x->next = NULL; // ��������� �� ��������� ������� ������ � NULL �.�. ��� �� ���������� ���� ���
        end->next = x; // � ��������� ����� ������� � ������ ������
        end = x; // � ����� ������ �������� x
    }
}
 
int announcement::length(List* head) // ������� ��� ��������� ���������� ��������� � ������ head
{
    int n = 0; // �������� ���������� ��������� ������
    while (head != NULL) // ���� �� ����� ������ ������
    {
        n++; // ����������� ���������� ��������� �� 1
        head = head->next; // ��������� � ���������� ����� ������
    }
    return n; // ���������� ���������� ��������� ������
}
 
void announcement::clear(List*& head, List*& end) // ������� ��� ������� ������ ������� �������
{
    List* t;
    while (head != NULL) // ���� �� ����� ������, ������
    {
        t = head->next; // ��������� � ���������� ��������
        delete head; // ������� ������ ������� ��� head
        head = t; // ������� � head �������� t
    }
    end = NULL;
}