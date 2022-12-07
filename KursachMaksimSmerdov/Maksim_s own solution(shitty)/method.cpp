#include "class.h"

 using namespace std;

void announcement::enter_new(announcement& st,int d_v,int m_v, int g_v) // Функция для ввода информации о новом объявлении
{
    st.d=d_v;
    st.m=m_v;
    st.g=g_v;
    cin.get(); // Для остановки закрытия окна консоли
 
    cout << "Введите категорию: ";
    getline(cin, st.category);
 
    cout << "Введите покупать или продовать: ";
    getline(cin, st.buy_sell);
 
    cout << "Введите текст обьявления  сумму: ";
     getline(cin, st.ad_text);
 
    cout << "Введите номер , без 8: ";
    cin >> st.num;
    cin.get(); // Для остановки закрытия окна консоли
}
 
void announcement::sort(List*& head) // Функция для сортировка списка
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
 
 
int announcement::del(List*& head, List*& end, int number) // Функция для удаления элемента списка с номером number
{
    int n = length(head); // Получаем количество элементов списка
    if (number > n || number <= 0 || n == 0) // Если number больше количества элементов списка или меньше или равно нуля или список пуст то
    {
        return 1; // Возвращаем результат работы функции = 1, т.е. есть ошибки
    }
    List* t = head, * tt = head;
    if (number == 1) // Если необходимо удалить первый элемент списка то
    {
        t = head; // Запоминаем первый элемент списка в переменной t
        head = head->next; // Переходим к следующему элементу
        delete t; // Удаляем первый элемент
        // Если голова списка стала пустой то
        // Конец списка ставим пустым
        if (head == NULL) end = NULL;
    }
    else // Иначе
    {
        tt = head; // Запоминаем текущий элемент списка
        t = head->next; // Запоминаем последующий элемент списка
        int i = 1; // Индексацию начинаем с 1 т.к. первый элемент уже просмотрен
        while (t != NULL) // Пока не конец списка
        {
            i++; // Увеличиваем индекс на 1
            if (i == number) // Если i == number, т.е. номер текущего элемента равен номеру удаляемого то
            {
                tt->next = t->next; // Переставляем указатели
                break; // Прерываем цикл
            }
            // Переходим к следующим элементам
            tt = tt->next;
            t = t->next;
        }
        if (number == n) end = tt; // Если удаляемый элемент является последним то меняем указатель на конец списка
        delete t; // Освобождаем память занятую под элемент с номером number
    }
    return 0; // Оповещаем о корректном удалении
}
 
int  announcement::find(List*& head, announcement& st, string buy_sell) // Функция для поиска по теме
{
    int i = 0;
    List* pointer = head;
    while (head != NULL)
    {
        if (head->info.buy_sell == buy_sell) {
             cout << "Такое объявление есть." << endl;
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
    cout << "Такое объявления нет." << endl;
    head = pointer;
    return -1;
}

int  announcement::find_str(List*& head, announcement& st, string str) // Функция для поиска по теме
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
             cout << "Такое объявление есть." << endl;
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
    cout << "Такое объявления нет." << endl;
    head = pointer;
    return -1;
}

void  announcement::out(List* head) // Функция для вывода списка на экран
{
    if (head == NULL) // Если head = NULL значит список пуст
    {
        cout << "Список пуст\n";
        return;
    }
 
    // Выводим шапку для вывода информации
    cout << setw(0) << "№"
        << setw(24) << "Дата "
        << setw(34) << "Категория"
        << setw(42) << "Куплю,продам"
        << setw(54) << "Текст обьявления"
        << setw(53) << "Номер"
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
 
void  announcement::save(List* head, string a) // Функция для сохранения списка в файл
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
        cout << "Данные сохранены в файл\n";
    }
    else cout << "Сохранение не удалось" << endl;
    out.close();
}
 
void  announcement::load(List*& head, List*& end, announcement& st, string a)// Функция для загрузки из файла
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
    else cout << "Чтение из файла не удалось" << endl;
    in.close();
}
 
void announcement::add(List*& head, List*& end, announcement st, int d,int m,int g, string category, string buy_sell, string ad_text, long long num) // Функция для добавления элемента st в список 
{
    if (head == NULL) // Если список ещё не создан,то
    {
        head = new List; // Выделяем место под голову списка
        head->next = NULL; // Зануляем указатель на следующий элемент
        head->info = st; // Заносим данные в голову списка
        end = head; // Конец списка устанавливаем в head
    }
    else // Иначе
    {
        List* x = new List; // Выделяем место под новый элемент
        x->info = st; // Заносим туда данные
        x->next = NULL; // Указатель на следующий элемент ставим в NULL т.е. его не существует пока что
        end->next = x; // И связываем новый элемент с концом списка
        end = x; // И концу списка присваем x
    }
}
 
int announcement::length(List* head) // Функция для получения количества элементов в списке head
{
    int n = 0; // Обнуляем количество элементов списка
    while (head != NULL) // Пока не конец списка делаем
    {
        n++; // Увеличиваем количество элементов на 1
        head = head->next; // Переходим к следующему звену списка
    }
    return n; // Возвращаем количество элементов списка
}
 
void announcement::clear(List*& head, List*& end) // Функция для очистки памяти занятой списком
{
    List* t;
    while (head != NULL) // Пока не конец списка, делаем
    {
        t = head->next; // Переходим к следующему элементу
        delete head; // Очищаем память занятой под head
        head = t; // Заносим в head значение t
    }
    end = NULL;
}