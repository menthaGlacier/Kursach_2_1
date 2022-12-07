
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>

using namespace std;


class List;
class announcement// Структура "обьявление"
{
public:
    int d,g,m; // Дата 
    string category; // Категория
    string buy_sell; // куплю , продам 
    string ad_text; // текст обьявления
    long long num; // номер телефона
    void enter_new(announcement& st, int d_v, int m_v, int g_v); // Функция для ввода информации о новом объявлении с клавиатуры
    void sort(List*& head); // Функция для сортировка списка по дате
    int del(List*& head, List*& end, int number); // Функция для удаления элемента списка с номером number
    int find(List*& head, announcement& st, string buy_sell);
    int find_str(List*& head, announcement& st, string str); // Функция для поиска по строке
    void out(List* head); // Функция для вывода списка на экран
    void save(List* head, string a); // Функция для сохранения списка в файл
    void load(List*& head, List*& end, announcement& st, string a); // Функция для чтения списка из файла
    void add(List*& head, List*& end, announcement st, int d, int m, int g, string category, string buy_sell, string ad_text, long long num); // Функция для добавления элемента st в список 
    int length(List* head); // Функция для получения количества элементов в списке head
    void clear(List*& head, List*& end); // Функция для очистки памяти занятой списком
};
class List // Cтруктура линейный динамический спискок
{
public:
    announcement info; // Информация хранящиеся в элементах списка
    List* next; // Указатель на следующий элемент списка
};



