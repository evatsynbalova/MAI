#include <iostream>
#include <ctime>       //подключение библиотеки для функции time
#include <fstream>  
#include <chrono>      //подключение библиотеки для вычисления времени работы
#include <conio.h> 

using namespace std;

/*ГЛОБАЛЬНЫЕ КОНСТАНТЫ*/
const char* FNAME = "test.txt"; //имя файла

/*СТРУКТУРЫ*/
//структура для вводимых пользователем данных
struct Parametr
{
	int Posl = 0;     //выбор вида последовательности
	int Datatype = 0; //выбор типа данных
};
/*ПРОТОТИПЫ ФУНКЦИЙ*/

//случайная последовательность
int random(int min, int max);
float random(float min, float max);

//возрастающая последовательность
template <typename T>
void Vozrast(T* xarr, int xsize, T min, T max, T Eps, int);

//убывающая последовательность
template <typename T>
void Ubyv(T* xarr, int xsize, T min, T max, T Eps, int);

//синусоидальная последовательность
template <typename T>
void sinus(T* xarr, 
	       int xsize, //размерность массива
	       T min,     //минимальный элемент
	       T max,     //максимальный элемент
	       T Eps,     //погрешность
	       int xN);   //количество промежутков

//пилообразная последовательность
template <typename T>
void pila(T* xarr, int xsize, T min, T max, T Eps, int xN);

//ступенчатая последовательность
template <typename T>
void styp(T* xarr, int xsize, T min, T max, T Eps, int xN);

//квази-упорядоченная последовательность
template <typename T>
void kvazi(T* xarr, int xsize, T min, T max, T Eps, int xN);

//опрос пользователя
template <typename T>
void perform(Parametr options);

//получение вида последовательности и типа данных
Parametr xParametr();

//ввод цифры
int xNum(int xM, const char* err);

//печать последовательности в файл
template <typename T>
void printPosl(void (*pArr)(T*, int, T, T, T, int), //указатель на функцию
	           int size,                          //размер последовательности
	           T min, T max,                      //минимальный и максимальный элементы
	           T Eps,                             //погрешность
	           int xN);                           //кол-во интервалов

//получение минимального, максимального значений и погрешности
template <typename T>
void value(T& min, T& max, T& Eps);

//получение количества интервалов
int valueN();

//получение размера последовательности
int SizePosl();
/*ОСНОВНАЯ ПРОГРАММА*/
int main()
{
	auto begin = chrono::steady_clock::now(); //получаем время перед началом формирования последовательности

	setlocale(LC_ALL, "russian");
	system("color F0");
	srand(time(NULL));  //функция генерации случайных чисел

	Parametr parametr; //параметры задачи, вводимые пользователем

       //ввод параметров
	parametr = xParametr();

	//какой тип данных выбран
	switch (parametr.Datatype) 
	{
	case 1:
		perform<int>(parametr);
		break;
			
	case 2:
		perform<float>(parametr);
		break;
			
	}//switch

	system("cls");

	auto Time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - begin);
	cout << "Время выполнения алгоритма = " << Time.count() << "мс\n\n";
	
    return 0;
}//main()
/*РЕАЛИЗАЦИЯ ФУНКЦИЙ*/

//опрос пользователя
template <typename T>
void perform(Parametr options)
{
	void (*pArr[])(T*, int, T, T, T, int) //массив указателей на функции
	{
		Vozrast<T>, Ubyv<T>, sinus<T>, pila<T>, styp<T>, kvazi<T>
	};

	int size = 0; //размер последовательности
	T min = 0;    //минимальное значение 
	T max = 0;    //максимальное значение 
	T Eps = 0;    //погрешность
	int xN = 0;   //кол-во промежутков 
	
	value<T>(min, max, Eps); //ввод параметров 

	//выбор количества интервалов
	if (options.Posl != 1 && options.Posl != 2)
		xN = valueN();
		
	//выбор размера последовательности
	size = SizePosl();

	//создание последовательности и ее печать в файл
	printPosl<T>(pArr[options.Posl - 1], size, min, max, Eps, xN);

}//perform()

//получение вида последовательности и типа данных
Parametr xParametr()
{
	Parametr number;
	for (;;) 
	{
		cout << "\nВыберите вид последовательности:\n";
		cout << "\n\t" << "1. возрастающая";
		cout << "\n\t" << "2. убывающая";
		cout << "\n\t" << "3. синусоидальная";
		cout << "\n\t" << "4. пилообразная";
		cout << "\n\t" << "5. ступенчатая";
		cout << "\n\t" << "6. квази-упорядоченная";
		cout << "\n";

		number.Posl = xNum(6, "Ошибка!");

		cout << "\nВыберите тип данных последовательности:\n";
		cout << "\n\t" << "1. int";
		cout << "\n\t" << "2. float";
		cout << "\n";

		number.Datatype = xNum(2, "Ошибка!");

		break;
	}//for
	return number;
}//xParametr()

//ввод цифры
int xNum(int xM, const char* err) 
{
	int number = 0;
	int symb = 0;
	while (true) 
	{

		cout << "\n\t>> "; //приглашение ко вводу

		symb = _getch();   //получение нажатой клавиши в виде символа

		number = symb - '0';  //получаем из символа число

		if (number >= 0 && number <= xM) //входной контроль
			break;

		//если входной контроль не прошёл - сообщение об ошибке
		cout << "\t" << err << '\n';
	}//while

	cout << number << '\n'; 
	return number;
}//xNum()

//печать последовательности в файл
template <typename T>
void printPosl(void (*pArr)(T*, int, T, T, T, int), int size, T min, T max, T Eps, int xN)
{
	T * arr = new T[size];

	//формирование последовательности
	pArr(arr, size, min, max, Eps, xN);

	fstream file;
	file.open(FNAME, ios::out);

	//вывод последовательости в файл
	for (int i = 0; i < size; i++)
		file << arr[i] << '\n';

	file.close();

	delete[] arr;
}//printPosl()

//получение минимального, максимального значений и погрешности
template <typename T>
void value(T& min, T& max, T& Eps)
{
	cout << " Ведите минимальный и максимальный элементы последовательности и погрешность : ";

	for (;;) 
	{
		cin >> min >> max >> Eps;

		//если введено не число
		if (!cin)
		{
			cout << "\n\tВведено не число.";
			cin.clear();
			cin.ignore(99999, '\n');

			continue;
		} //if

		//входной контроль
		if (min >= max)
		{
			cout << "\n\tОшибка: минимальный элемент не может быть больше максимального";
			continue;
		} //if 

		//входной контроль
		if (Eps < 0) {
			cout << "\n\tОшибка: погрешность не может быть отрицательной";
			continue;
		} //if (eps < 0)

		break;
	}
}//value()
	
//получение количества интервалов
int valueN()
{
	int number = 0; //вводимое значение

	cout << "\n\tВведите количество интервалов генерируемой последовательности : ";

	for (;;) 
	{
		cin >> number; //ввод

		//если введено не число
		if (!cin)
		{
			cout << "\n\tВведено не число.";
			cin.clear();
			cin.ignore(99999, '\n');
			continue;
		} //if 

		//входной контроль
		if (number <= 0)
		{
			cout << "\n\tОшибка: кол-во интервалов последовательности должно быть больше нуля";
			continue;
		} //if 
		break;
	}
	return number;
}//valueN()

//получение размера последовательности
int SizePosl() 
{
	int number = 0; //вводимое значение

	cout << "\n\tВведите количество элементов последовательности : ";

	//пока не будет введено корректное значение
	for (;;) 
	{
		cin >> number;

		//если введено не число
		if (!cin)
		{
			cout << "\n\tВведено не число.";
			cin.clear();
			cin.ignore(99999, '\n');
			continue;
		} //if 

		//входной контроль
		if (number < 100)
		{
			cout << "\n\tОшибка: минимальное кол-во элементов последовательности: 100";
			continue;
		}//if
		break;
	}//for
	return number;
}//SizePosl()

//возрастающая последовательность
template <typename T>
void Vozrast(T* xarr, int xsize, T min, T max, T Eps, int)
{

	T h;   //шаг 
	T arg = 0; //значение аргумента
	h = (max - min) / (T)xsize;
	
	for (int j = 0; j < xsize; j++)
	{
		arg = min + (T)j * h;
		xarr[j] = arg + random(-(T)Eps, (T)Eps);
	}//for

}//Vozrast()

//убывающая последовательность
template <typename T>
void Ubyv(T* xarr, int xsize, T min, T max, T Eps, int)
{
	T h;   //шаг 
	T arg; //значение аргумента
	h = (max - min) / (T)xsize;

	for (int j = 0; j < xsize; j++)
	{
		arg = min + j * h;
		xarr[xsize - 1 - j] = arg + random(Eps / (T)-2, Eps / (T)2);
	}//for

}//Ubyv()

//случайная последовательность
int random(int min, int max)
{
	return min + rand() % (max + 1 - min);
}//random()

//случайная последовательность
float random(float min, float max)
{
	return (float)random((int)(min) * 10, (int)(max) * 10) / (float)10;
}//random()


//синусоидальная последовательность
template <typename T>
void sinus(T* xarr, int xsize, T min, T max, T Eps, int xN)
{
	double h; //шаг
	double x; //аргумент синуса
	T arg;    //значение синуса
	h = (max - min)*1.0 / xN;
	
	for (int i = 0; i < xsize; i++)
	{
		x = min + i * h;
		arg = 100*sin(x);
		xarr[i] = arg + random(-(T)Eps, (T)Eps);
	}//for

}//sinus()

//пилообразная последовательность
template <typename T>
void pila(T* xarr, int xsize, T min, T max, T Eps, int xN)
{
	double h; //шаг
	int j; //индексная переменная
	T arg;
	h = (max - min) / xN;

	xarr[0] = min;

	//вычисляем элементы на первом интервале
	for ( j = 1; j <= xN; j++)
	{
		arg = xarr[j - 1] + h;
		xarr[j] = arg + random(-(T)Eps, (T)Eps);
	}//for 

	//повторяем элементы на остальных интервалах
	while (j < xsize)
	{
		arg = xarr[j - xN];
		xarr[j] = arg + random(-(T)Eps, (T)Eps);
		j++;
	}//while

}//pila()

//ступенчатая последовательность
template <typename T>
void styp(T* xarr, int xsize, T min, T max, T Eps, int xN)
{
	int i;    //индексная переменная
	double h; //шаг
	int st;   //пременная для определения подъема ступеньки
	int j = 0;
	T arg;
	h = (max - min) / xN;
	st = xsize / xN;

	for (i = 0; i < xsize; i++)
	{

		if (((i + 1) % st) == 0) // пока мы не дошли до подъема ступеньки
		{
			j++;
			min = min + j * h;
		}//if
		arg = min;
		xarr[i] = arg + random(-(T)Eps, (T)Eps);
	}//for
}//styp()

//квази-упорядоченная последовательность
template <typename T>
void kvazi(T* xarr, int xsize, T min, T max, T Eps, int xN)
{
	int inver = 0; //индекс для добавления инверсий

	//формируем возрастающую последовательность
	Vozrast<T>(xarr, xsize, min, max, 0, 0);

	//добавляем определенное количество инверсий
	for (int i = 0; i < inver + 1; i++)
	{
		inver = random(0, xsize - 1);
		xarr[inver]+= random(-(T)Eps, (T)Eps);
	}//for
}//kvazi() 
