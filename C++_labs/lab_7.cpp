#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

/*ГЛОБАЛЬНЫЕ КОНСТАНТЫ*/
#define size 10

/*СТРУКТУРЫ*/
struct Parametr
{
    int count = 0;  //количество сравнений   
    int swap = 0;   //количество престановок
};

/*ПРОТОТИПЫ ФУНКЦИЙ*/
//выбор исходного массива
void vvod(int* xArr, int xsize);

//вывод количества сранений и перестановок
void counters(Parametr options);

//шейкерная сортировка
void ShakerSort(int* xArr, int xsize, Parametr& counters);

//сортировка слиянием
int MergeSort(int* xArr, int xp, int xr, Parametr& counters);
int Merge(int* xArr, int xleft, int xright, Parametr& counters);

/*ОСНОВНАЯ ПРОГРАММА*/
int main()
{
    setlocale(LC_ALL, "Russian");
    system("color F0");
    srand(time(NULL));
    
    Parametr parametr;
    
    //создание массива   
    int* Arr = new int[size]; 

    //шейкерная сортировка
    vvod(Arr, size);
    cout << " \n Шейкерная сортировка : " << endl;

    auto begin = chrono::steady_clock::now();

    ShakerSort(Arr, size, parametr);
    counters(parametr);

    cout << " Отсортированный массив : ";
    for (int i = 0; i < size; i++)
    {
        cout << Arr[i] << " ";
    }//for()

    auto Time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - begin);
    cout << "\n Время выполнения шейкерной сортировки = " << Time.count() << "мс\n\n";

    //сортировка слиянием
    vvod(Arr, size);
    cout << " \n Сортировка слиянием : " << endl;

    auto start = chrono::steady_clock::now();

    MergeSort(Arr, 0, size - 1, parametr);
    counters(parametr);

    cout << " Отсортированный массив : ";
    for (int i = 0; i < size; i++)
    {
        cout << Arr[i] << " ";
    }//for()
   
    auto end = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start);
    cout << "\n Время выполнения сортировки слиянием = " << end.count() << "мс\n\n";

    delete[]Arr;
    system("pause");
    return 0;
}//main()

/*РЕАЛИЗАЦИЯ ФУНКЦИЙ*/
//выбор исходного массива
void vvod(int* xArr, int xsize)
{
    int i; //индексная переменная
    int n; //номер массива

    cout << " Выберете исходный массив : " << endl;
    cout << " 1. Массив случайных чисел" << endl;
    cout << " 2. Массив упорядочен по возрастанию" << endl;
    cout << " 3. Массив упорядочен по убыванию" << endl;
    cin >> n;
    
    if (n == 1)
    {
        cout << " Исходный массив : ";
        for (i = 0; i < xsize; i++)
        {
            xArr[i] = rand() % 50;
            cout << xArr[i] << " ";
        }//for()
    }//if

    if (n == 2)
    {
        cout << " Исходный массив : ";
        for (i = 0; i < xsize; i++)
        {
            xArr[i] = i + 1;
            cout << xArr[i] << " ";
        }//for()
    }//if

    if (n == 3)
    {
        cout << " Исходный массив : ";
        for (i = 0; i < xsize; i++)
        {
            xArr[i] = xsize - i;
            cout << xArr[i] << " ";
        }//for()
    }//if
 
}//vvod()

//вывод количества сранений и перестановок
void counters(Parametr options)
{
    cout << " Итоговое количество сравнений: " << options.count << endl;
    cout << " Итоговое количество перестановок: " << options.swap << endl;
}//perform()

//шейкерная сортировка
void ShakerSort(int* xArr, int xsize, Parametr& counters)
{   
    int left = 0;      //левая граница
    int right = xsize; //правая граница
    int count = 0;     //количество сравнений
    int swap = 0;      //количество перестановок
    int temp = 0;

    while (left < right)
    {
        //прямой проход
        for (int i = left; i < right - 1; i++)
        {
            if (xArr[i] < xArr[i + 1])
            {
                temp = xArr[i];
                xArr[i] = xArr[i + 1];
                xArr[i + 1] = temp;
                counters.swap++;
            }//if()

        }//for()
  
        //обратный проход
        for (int i = right - 1; i > left; i--)
        {
            if (xArr[i] > xArr[i - 1])
            {
                temp = xArr[i];
                xArr[i] = xArr[i - 1];
                xArr[i - 1] = temp;
                counters.swap++;
            }//if()

        }//for()
        counters.count++;

        //вывод промежуточных результатов
        cout << " ";
        for (int k = 0; k < xsize; k++)
        {
            cout << xArr[k] << " ";
        }//for()

        cout << endl;
        right--;
        left++;
    }//while()

}//ShakerSort() 

//сортировка слиянием
int MergeSort(int* xArr, int xleft, int xright, Parametr& counters)
{
    int temp;
    int count = 0;     //количество сравнений
    int swap = 0;      //количество перестановок

    if (xleft < xright)
    {
        //если в массиве 2 элемента
        if (xright - xleft == 1)
        {
            //если правый элемент больше левого
            if (xArr[xright] > xArr[xleft])
            {
                //меняем местами правый и левый элемент
                temp = xArr[xleft];
                xArr[xleft] = xArr[xright];
                xArr[xright] = temp;
                counters.swap++;
            }//if()
            counters.count++;
        }//if()
        else
        {
            MergeSort(xArr, xleft, (xleft + xright) / 2, counters);      //левая половина
            MergeSort(xArr, (xleft + xright) / 2 + 1, xright, counters); //правая половина
            Merge(xArr, xleft, xright, counters);                        
        }//else
        
    }//if()
    return 0;
}//MergeSort()

int Merge(int* xArr, int begin, int end, Parametr& counters)
{
    int* mas = new int[size];

    int count = 0;   //количество сравнений
    int swap = 0;    //количество перестановок
    int i = begin;   //левая граница
    int k = 0;       //индексная переменная для результирующего массива
    int mid = begin + (end - begin) / 2; //середина
    int j = mid + 1; //правая граница

    while (i <= mid && j <= end) //пока не дойдем до конца подмассива
    {
        counters.count++;
        //сравниваем элементы из левой и правой части
        if (xArr[i] >= xArr[j]) 
        {
            mas[k] = xArr[i];
            i++;
            counters.swap++;
        }//if()
        else 
        {
            mas[k] = xArr[j];
            j++;
            counters.swap++;
        }//else
        k++;       
    }//while()
   
    while (i <= mid) //пока не дойдем до конца левой половины
    {
        mas[k] = xArr[i]; //дополняем массив элементами из левой половины
        i++;
        k++;
        counters.swap++;
    }//while()

    while (j <= end) //пока не дойдем до конца правой половины
    {
        mas[k] = xArr[j]; //дополняем массив элементами из правой половины
        j++;
        k++;
        counters.swap++;
    }//while()

    //вывод в результирующий массив
    for (i = 0; i < k; i++)
    {
        xArr[begin + i] = mas[i];
    }//for()

    //вывод промежуточных результатов
    cout << " ";
    for (int k = 0; k < size; k++)
    {
        cout << xArr[k] << " ";
    }//for()
    cout << endl;

    delete[] mas;
    return 0;
}//Merge()
 
