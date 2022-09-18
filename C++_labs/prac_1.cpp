#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/*ГЛОБАЛЬНЫЕ КОНСТАНТЫ*/
const char* FNAME = "Test.txt"; //корректный тест
constintMAXLEN = 10;           // Максимальное количество строк
const int WIDE = 22; //задаём ширину столбца 

/*СТРУКТУРЫ*/
struct PlaneData
{
    string Mark;         //марка ЛА
    string Number_Tail;   //бортовой номер
    string Number_Of_Passengers; //количество пассажиров
    string Weight;          //вес груза
};

/*ПРОТОТИПЫ ФУНКЦИЙ*/
// Чтение из файла
intReadStruct(PlaneData* xPlane,  // Данныеосамолетах
constchar* xFNAME,          // Имя файла исходных данных
int&xM);                    // Количество строк с данными в файле

// Вывод на экран
voidPrintStruct(PlaneData* xPlane, // Данныеосамолетах
intxM);                      // Количество строк с данными

// Вывод сообщений об ошибке
voidPrintMessage(intxErrCode, // Кодошибки
constchar* xFNAME);        // Имя файла исходных данных

// Формирование таблицы
void Table(string m, int WIDE);

// Входной контроль бортового номера
voidNumber_Tail(PlaneData* xPlane, // Данные о прибывших самолетах
intxM);    // Количество строк с данными

// Входной контроль количествa пассажиров
voidNumber_Of_Passengers(PlaneData* xPlane, // Данные о прибывших самолетах
intxM);          // Количество строк с данными

// Входной контроль веса груза
voidWeight(PlaneData* xPlane, // Данные о прибывших самолетах
intxM);          // Количество строк с данными

// Вывод сообщений ошибки входного контроля по бортовому номеру
void PrintMessage2(int xErr2,
    int xj);        // Номер элемента (3-5)

// Вывод сообщений ошибки входного контроля по количеству пассажиров
void PrintMessage3(int xErr3,
    int xj);       

// Вывод сообщений ошибки входного контроля по весу груза
void PrintMessage4(int xErr4,
    int xj);



/*РЕАЛИЗАЦИЯ ФУНКЦИЙ*/
// Чтение из файла
intReadStruct(PlaneData* xPlane,  // Данныеосамолетах
constchar* xFNAME,          // Имя файла исходных данных
int&xM)                     // Количество строк с данными в файле 
{
    int i = 0;

    ifstream fin(xFNAME);

//файл не найден 
if (!fin)
{
fin.close();
        return 1;
    }//if

    // файл пустой
    if (fin.peek() == EOF)
    {
        fin.close();
        return 2;
    }//if

    //считываемколичествострок
fin>>xM;
    //если количество строк некорректно
if ((xM< 1) || (xM>MAXLEN))
{
        fin.close();
        return 3;
    }//if

    while ((!fin.eof()) && (i < xM))
{
        //считываем марку самолета
fin>>xPlane[i].Mark;
        //считываем бортовой номер
fin>>xPlane[i].Number_Tail;
//считываем номер рейса
        fin >> xPlane[i].Number_Of_Passengers;
        //считываем время
        fin >> xPlane[i].Weight;

        i++;
    }

    fin.close();
    return 0;
}// ReadStruct()

// Вывод на экран
void PrintStruct(PlaneData* xPlane,  // Данные о самолетах
    intxM)                        // Количество строк с данными
{
cout<< "\tДанные о самолетах:\n\n";

setlocale(LC_ALL, "C"); //отключение русского языка

Table("шапка", WIDE);//вызов функции для шапки таблицы

cout << char(179);

    setlocale(LC_ALL, "RUSSIAN");
    cout << setfill(' ') << setw(WIDE) << "марка ЛА";

    setlocale(LC_ALL, "C"); //отключение русского языка
cout << char(179);

    setlocale(LC_ALL, "RUSSIAN");
    cout << setfill(' ') << setw(WIDE) << "бортовой номер";

    setlocale(LC_ALL, "C"); //отключение русского языка
cout << char(179);

    setlocale(LC_ALL, "RUSSIAN");
    cout<<setfill(' ') <<setw(WIDE) << "Количество пассажиров";

setlocale(LC_ALL, "C"); //отключение русского языка
cout << char(179);

    setlocale(LC_ALL, "RUSSIAN");
    cout << setfill(' ') << setw(WIDE) << "Вес груза";

    setlocale(LC_ALL, "C"); //отключение русского языка
cout<<char(179) <<endl;//заполнение 1 строки элементами

Table("строка", WIDE); //формирование разграничивающей строки таблицы

    //заполнение таблицы значениями

for (inti = 0; i<xM; i++)
{
setlocale(LC_ALL, "C"); //отключение русского языка
cout << char(179);

        setlocale(LC_ALL, "RUSSIAN");
        cout << setfill(' ') << setw(WIDE) << xPlane[i].Mark;

        setlocale(LC_ALL, "C"); //отключение русского языка
cout << char(179);

        setlocale(LC_ALL, "RUSSIAN");
        cout << setfill(' ') << setw(WIDE) << xPlane[i].Number_Tail;

        setlocale(LC_ALL, "C"); //отключение русского языка
cout << char(179);

        setlocale(LC_ALL, "RUSSIAN");
        cout << setfill(' ') << setw(WIDE) << xPlane[i].Number_Of_Passengers;

        setlocale(LC_ALL, "C"); //отключение русского языка
cout << char(179);

        setlocale(LC_ALL, "RUSSIAN");
        cout << setfill(' ') << setw(WIDE) << xPlane[i].Weight;

        setlocale(LC_ALL, "C"); //отключение русского языка
cout << char(179) << endl;


        if (i != xM - 1)//входной контроль
            Table("строка", WIDE); //формирование разграничивающей строки таблицы
    }
Table("нижняя граница", WIDE); //формирование разграничивающей строки таблицы

setlocale(LC_ALL, "RUSSIAN");
    cout << endl;
}// PrintStruct()

// Вывод сообщения об ошибке
void PrintMessage(int xErr,
    const char* xFNAME)
{
    switch (xErr)
    {
    case 1: cout << "\a\n\t\tФайл не найден\n\n";
        break;
    case 2: cout << "\a\n\t\tФайл пуст\n\n";
        break;
case 3: cout<< "\a\n\t\tКоличество строк с данными неверно\n\n";
break;
    default:
        break;
    }// switch
}// PrintMessage()


voidTable(stringm, intWIDE) //функция, формирущаятаблицусэлементамипсевдографики
{
if (m == "шапка")//входной контроль
    {
cout << char(218) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(194) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(194) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(194) << setfill(char(196)) << setw(WIDE) << char(196)
<<char(191) <<endl;//формирование верхней строки таблицы
    }
if (m == "строка")//входной контроль
    {
cout << char(195) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(197) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(197) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(197) << setfill(char(196)) << setw(WIDE) << char(196)
<<char(180) <<endl;//формирование разграничивающей строки
    }
if (m == "нижняя граница")//входной контроль
{
        cout << char(192) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(193) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(193) << setfill(char(196)) << setw(WIDE) << char(196)
<< char(193) << setfill(char(196)) << setw(WIDE) << char(196)
<<char(217) <<endl;//формирование нижней границы
    }//if
}//voidgraf

// Входной контроль бортового номера
voidNumber_Tail(PlaneData* xPlane, // Данные о прибывших самолетах
intxM   )        // Количество строк с данными    
{
inti, j;      // Индексные переменные
intErr2; // Код ошибки
int LenTeil;     // Количество элементов

    for (i = 0; i < xM; i++)
{
cout<< "Ошибки в строке " <<i + 1 << "\n\n";
Err2 = 0;
        LenTeil = 0;

        // Считаем количество элементов
        for (j = 0; xPlane[i].Number_Tail[j] != '\0'; j++)
{
LenTeil++;
        }// forj

// Количество элементов больше допустимого
if (LenTeil> 6)
{
            Err2 = 1;

            PrintMessage2(Err2, j);
continue;
}// if

        // Количество элементов мешьше положенного
if (LenTeil< 6)
{
            Err2 = 2;

            PrintMessage2(Err2, j);
            continue;
        }// if


        // Первыйэлементнебуква
if ((int(xPlane[i].Number_Tail[0]) + 256 < 192) ||
                (int(xPlane[i].Number_Tail[0]) + 256 > 223) ||
                (int(xPlane[i].Number_Tail[0]) + 256 == 201) ||
                ((int(xPlane[i].Number_Tail[0]) + 256 >= 218) && (int(xPlane[i].Number_Tail[0]) + 256 <= 220)))
        {
            Err2 = 3;
           PrintMessage2(Err2, j);
        }

        // Второй элемент не тире
        if (xPlane[i].Number_Tail[1] != '-')
{
Err2 = 4;

PrintMessage2(Err2, j);
}// if

        // Элементы 3-5 вышли за границы
for (j = 2; j< 5; j++)
{
            if ((int(xPlane[i].Number_Tail[j]) < 48) || (int(xPlane[i].Number_Tail[j]) > 58))
            {
                Err2 = 5;

                PrintMessage2(Err2, j);
            }
        }// for j

// Шестой элемент вышел за границы допустимых значений
if ((int(xPlane[i].Number_Tail[5]) < 48) || (int(xPlane[i].Number_Tail[5]) > 58))
        {
            Err2 = 6;

            PrintMessage2(Err2, j);
        }// if

        // Ошибок нет
        if (Err2 == 0)
        {
cout<< "\tВ данной строке нет ошибок!\n";
}// if

cout<<endl;

    }// fori
}//Tail_number()

// Вывод сообщений ошибки входного контроля по бортовому номеру
void PrintMessage2(int xErr2, // Код ошибки
    intxj)         // Номер элемента (3-5)
{
    // Выводим сообщение об ошибке по ее коду
switch (xErr2)
    {
case 1: cout<< "\tОшибка во втором столбце! Количество элементов больше положенного!\n\n";
break;
case 2: cout<< "\tОшибка во втором столбце! Количество элементов меньше положенного!\n";
break;
case 3: cout<< "\tОшибка во втором столбце! Первый элемент не буква !\n";
break;
case 4: cout<< "\tОшибка во втором столбце! Второй элемент не тире!\n";
break;
case 5: cout<< "\tОшибка во втором столбце! Элемент под номером " <<xj<< " вышел за границы допустимых значений!\n";
break;
case 6: cout<< "\tОшибка во втором столбце! Шестой элемент вышел за границы допустимых значений\n";
break;
default:
break;
    }// switch
}// PrintMassage2


    // Входной контроль количествa пассажиров
void Number_Of_Passengers(PlaneData* xPlane, // Данные о прибывших самолетах
        intxM)          // Количество строк с данными

 {
inti, j;      // Индексные переменные
intErr3; // Код ошибки
int LenTeil;     // Количество элементов

        for (i = 0; i < xM; i++)
{
cout<< "Ошибки в строке " <<i + 1 << "\n\n";
Err3 = 0;
            LenTeil = 0;

            // Считаем количество элементов
            for (j = 0; xPlane[i].Number_Of_Passengers[j] != '\0'; j++)
{
LenTeil++;
            }// forj


// Количество элементов больше допустимого
if (LenTeil> 3)
            {
Err3 = 1;

PrintMessage3(Err3, j);
continue;
}// if

            // Количество элементов меньше допустимого
if (LenTeil< 1)
{
                Err3 = 2;

                PrintMessage3(Err3, j);
                continue;
            }// if

            for (intj = 0; j< 3; j++)
{
                // Первый элемент вышел за границы допустимых значений
if ((int(xPlane[i].Number_Of_Passengers[j]) < 48) || (int(xPlane[i].Number_Of_Passengers[j]) > 58))
                {
                    Err3 = 3;

                    PrintMessage3(Err3, j);
                }// iff
            }


// Ошибок нет
if (Err3 == 0)
            {
cout<< "\tВ данной строке нет ошибок!\n";
}// if

            cout << endl;
        }// for i
 }

// Вывод сообщений ошибки входного контроля по бортовому номеру
void PrintMessage3(int xErr3, // Код ошибки
     intj)         // Номер элемента (3-5)
 {
     // Выводим сообщение об ошибке по ее коду
switch (xErr3)
     {
case 1: cout<< "\tОшибка в третьем столбце! Количество элементов больше положенного!\n\n";
break;
case 2: cout<< "\tОшибка в четвёртом столбце! Количество элементов меньше положенного!\n";
break;
case 3: cout<< "\tОшибка в четвёртом столбце! Элемент под номером " <<j+1 << " вышел за границы допустимых значений!\n";
break;
default:
break;
     }// switch
 }// PrintMassage3

  // Входной контроль веса груза
voidWeight(PlaneData* xPlane, // Данные о прибывших самолетах
intxM)          // Количество строк с данными

 {
inti, j;      // Индексные переменные
intErr4; // Код ошибки
int LenTeil;     // Количество элементов



         for (i = 0; i < xM; i++)
{
cout<< "Ошибки в строке " <<i + 1 << "\n\n";
Err4 = 0;
LenTeil = 0;

             // Считаем количество элементов
for (j = 0; xPlane[i].Weight[j] != '\0'; j++)
{
LenTeil++;
             }// forj

// Количество элементов больше допустимого
if (LenTeil> 4)
{
                 Err4 = 1;

                 PrintMessage4(Err4, j);
continue;
}// if

             // Количество элементов мешьше положенного
if (LenTeil< 4)
{
                 Err4 = 2;

                 PrintMessage4(Err4, j);
continue;
}// if

             //  Элементы вышедшие за границы допустимых значений (от 1 до 3)
for (j = 0; j < 2; j++)
             {

                 if ((int(xPlane[i].Weight[j]) < 48) || (int(xPlane[i].Weight[j]) > 58))
                 {
                     Err4 = 3;

                     PrintMessage4(Err4, j);
                     continue;
                 }// iff
}

             // Третий элемент не тире
if (xPlane[i].Weight[2] != '.')
{
Err4 = 4;

PrintMessage4(Err4, j);
}// if

             //  Элементы вышедшие за границы допустимых значений (от 3 до 4)
for (j = 3; j < 4; j++)
             {
                 if ((int(xPlane[i].Weight[j]) < 48) || (int(xPlane[i].Weight[j]) > 58))
                 {
                     Err4 = 3;

                     PrintMessage4(Err4, j);
                     continue;
}// iff
             }


// Ошибок нет
if (Err4 == 0)
             {
cout<< "\tВ данной строке нет ошибок!\n";
}// if

             cout << endl;

         }// for i

 }

// Вывод сообщений ошибки входного контроля по весу груза
void PrintMessage4(int xErr4, // Код ошибки
     intj)        
 {
     // Выводим сообщение об ошибке по ее коду
switch (xErr4)
     {
case 1: cout<< "\tОшибка в четвёртом столбце! Количество элементов больше положенного!\n\n";
break;
case 2: cout<< "\tОшибка в четвёртом столбце! Количество элементов меньше положенного!\n";
break;
case 3: cout<< "\tОшибка в четвёртом столбце! Элемент под номером " <<j+1 << " вышел за границы допустимых значений!\n";
break;
case 4: cout<< "\tОшибка в четвёртом столбце! Третий элемент не точка!\n";
break;
     default:
         break;
     }// switch
 }// PrintMassage4

 /*ОСНОВНАЯ ПРОГРАММА*/
 int main()
 {
     setlocale(LC_ALL, "RUSSIAN");
     system("color F0");

     PlaneDataPlane[MAXLEN];  // Данные о самолетах
int Err;            // Код ошибки
     int M;

// Читаем данные из файла
cout<< "\t\t<ЧТЕНИЕ ИЗ ФАЙЛА>\n\n";
Err = ReadStruct(Plane, FNAME, M);

//код ошибки не 0
if (Err != 0)
{
PrintMessage(Err, FNAME);
         system("pause");
         returnErr;
     }// if

     // Выводим данные на экран
PrintStruct(Plane, M);

     //проверка ботового номера
cout<< "\t ПРОВЕРКА БОРТОВОГО НОМЕРА\n";
Number_Tail(Plane, M);

     //проверка колличества пассажиров
cout<< "\t ПРОВЕРКА КОЛИЧЕСТВА ПАССАЖИРОВ\n";
Number_Of_Passengers(Plane, M);

//проверка массы груза
cout<< "\t ПРОВЕРКА МАССЫ ГРУЗА\n";
Weight(Plane, M);


     system("pause");
     return 0;
 } 
