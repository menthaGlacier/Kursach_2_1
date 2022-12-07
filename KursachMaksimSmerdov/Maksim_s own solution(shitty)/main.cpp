#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include "class.h"

using namespace std;

int main() // Главная функция
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    announcement st;
 
    List* head = NULL, * end = NULL; // Объявляем указатели на начало и конец списка
    int choise;
    int d_v, m_v,  g_v;
    string buy;
    int number;
    do
    {
        system("cls"); // Очищаем экран
 
        // Выводим меню
        cout << "1. Добавить элемент в список" << endl;
        cout << "2. Отсортировать элементы по дате" << endl;
        cout << "3. Удалить элемент из списка" << endl;
        cout << "4. Поиск элемента" << endl;
        cout << "5. Поиск элемента по строке " << endl;
        cout << "6. Вывод таблицы" << endl;
        cout << "7. Сохранить список в файл" << endl;
        cout << "8. Чтение списка из файла" << endl;
        cout << "9. Очистить список" << endl;
        cout << "10. Выход" << endl;
        cout << "Выберете действие: ";
        cin >> choise;
        cout << endl;
 
        switch (choise) // В зависимости от того, что выбрали, выполняем определенные действия
        {
        case 1:
        {
            cout << "Введите дату: ";
            cin >> d_v;
            cin >> m_v;
            cin >> g_v;
             if (d_v > 31 ||m_v > 12 || g_v > 2022) {
                cout << "Неверная дата\n";
                break;
            }
            st.enter_new(st, d_v, m_v,  g_v); // Вызываем функцию для получения нового элемента "объявление"
            st.add(head, end, st, st.d,st.m,st.g, st.category, st.buy_sell, st.ad_text, st.num); // Добавляем  объявление в  список 
            cout << "Обьявление добавленно\n";
            break;
        }
 
        case 2:
        {
            st.sort(head); // Вызываем функция для сортировки данных о объявлениях по дате
            cout << "Список отсортирован\n";
            break;
        }
 
 
        case 3:
        {
            cout << "Номер элемента для удаления: ";
            cin >> number;
            // Вызываем метод для удаления объявления
            // И если функция равна 0 значит всё прошло успешно
            // Иначе объявление не было удалено
            if (st.del(head, end, number) == 0) cout << "Элемент с номером " << number << " удалён\n";
            else cout << "Элемента с номером " << number << " нет\n";
            break;
        }
 
        case 4:
        {
            cout << "Введите категорию: "; 
            cin >> buy;
            cin.get();
            st.find(head, st, buy);
            buy.clear();
            break;
        }
        case 5:
        {
            cout << "Введите слово: "; 
            cin >> buy;
            cin.get();
            st.find_str(head, st, buy);
            buy.clear();
            break;
        }
 
        case 6:
        {
            st.out(head); // Вызываем функцию для вывода информации о объявлении
            break;
        }
 
        case 7:
        {
            int number;
            string a;
            cout << "1. Сохранить в файл по умолчанию" << '\n';
            cout << "2. Ввести путь самостоятельно (Пример: 'D:\\file.txt')" << endl;
            cout << "Выберите действие: ";
            cin >> number;
            if (number == 1)
            {
                a = "file.txt";
                st.save(head, a);
            }
            else
            {
                cout << "Введите путь к файлу: ";
                cin >> a;
                st.save(head, a);
            }
            break;
        }
 
        case 8:
        {
            int number;
            string a;
            cout << "1.Читать из файла по умолчанию" << '\n'
                << "2.Ввести путь самостоятельно (Пример:'D:\\input.txt')" << endl;
            cout << "Выберите действие: "; cin >> number;
            if (number == 1)
            {
                a = "file.txt";
                st.load(head, end, st, a);
            }
            else
            {
                cout << "Введите путь к файлу: ";
                cin >> a;
                st.load(head, end, st, a);
            }
            break;
        }
 
        case 9:
        {
            st.clear(head, end);
            cout << "Вы очистили список" << endl;
            break;
        }
 
        case 10:
        {
            return 0;
        }
        }
        if (choise > 0 && choise <= 8) system("pause"); // Если выбранное действие попадает в промежуток от 1 до 8, то задерживаем результат на экране
    } while (choise != 0);
    return 0;
}