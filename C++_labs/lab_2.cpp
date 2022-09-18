#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    system("color F0");
    
    double A; // Начало отрезка
    double B; // Конец отрезка
    int N; // Количество интервалов
    float h; // Шаг
    float F; // Функция F(x)
    float G; // Функция G(x)
    float x; // Аргумент x

    // Ввод данных
    cout << "Введите значение A = ";
    cin >> A;
    cout << "Введите значение B = ";
    cin >> B;
    //Входной контроль
    if (A == B)
    {
        N = 1;
        h = 0;

    }//if 1

    // Входной контроль
    if (A > B)
    {
        int C;
        C = A;
        A = B;
        B = C;
        cout << "А должно быть меньше В, меняем А и В местами !" << endl;
        
    }// if 2

    
   // Входной контроль
    if (A < B )
    {
        cout << "Введите значение N = ";
        cin >> N;
        if (N <= 0)
        {
            // Вывод сообщения об ошибке

            cout << "Ошибка! N должен быть больше или равен 1  " << endl;
            h = 1.0 * (B - A) / N;
            system("pause");
            return 0;
        }
        else
            h = 1.0 * (B - A) / N;
        
    }// if 3

    // Инициализация исходных данных

    cout << "h = " << h << endl;
    setlocale(LC_ALL, "C");

    // Шапка таблицы
    cout << char(218) << setfill(char(196)) << setw(20) << char(194)
        << setfill(char(196)) << setw(20) << char(194)
        << setfill(char(196)) << setw(20) << char(191) << endl;
    cout << char(179) << setfill(char(32)) << setw(10) <<  "x" << setfill(char(32)) << setw(10) << char(179) <<
        setw(10) << "F" << setfill(char(32)) << setw(10) << char(179)
        << setw(10) << "G" << setfill(char(32)) << setw(10) << char(179) << endl;
    
     for (int i = 0; i < (N+1) ; i++)
    {
        x = A + i * h;// Увеличение аргумента x на шаг h

        F = sin(x) + cos(x) - 1; // Рассчет значения функции F

        G = pow((x + 5), 3) / (1 + pow((sin(x)), 2));// Рассчет значения функции G
        setlocale(LC_ALL, "C");
        // Вывод промежуточных данных с использованием псевдографики
        cout << char(195) << setfill(char(196)) << setw(20) << char(197)
            << setfill(char(196)) << setw(20) << char(197)
            << setfill(char(196)) << setw(20) << char(180) << endl;
        cout << char(179)<< setfill(char(32)) << setw(13) << fixed << setprecision(5) << x << setfill(char(32)) << setw(7) <<
            char(179) << setw(13) << fixed << setprecision(5) << F << setfill(char(32)) << setw(7) <<
            char(179) << setw(13) << fixed << setprecision(5) << G << setfill(char(32)) << setw(7) << char(179) << endl;

    }// for

    // Закрытие таблицы
    cout << char(192) << setfill(char(196)) << setw(20) << char(193)
        << setfill(char(196)) << setw(20) << char(193)
        << setfill(char(196)) << setw(20) << char(217) << endl;
    system("pause");

    return 0;

}// main
