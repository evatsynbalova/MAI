Код программы
#include <iostream>
#include <fstream>
using namespace std;

/***************************************************************
*          Г Л О Б А Л Ь Н Ы Е     К О Н С Т А Н Т Ы           *
***************************************************************/
//const char* fNameA = "МатрицаA.txt";
//const char* fNameA = "МатрицаA1.txt"; //Ошибка: файл исходных данных не найден.
//const char* fNameA = "МатрицаA2.txt"; //Ошибка: файл исходных данных пуст.
//const char* fNameA = "МатрицаA3.txt"; //Ошибка ввода. В файле должны находиться только числа.
//const char* fNameA = "МатрицаA4.txt"; //Ошибка. Количество строк не может быть меньше 1.
//const char* fNameA = "МатрицаA5.txt"; //Ошибка. Количество столбцов не может быть меньше 1.
//const char* fNameA = "МатрицаA6.txt"; //Ошибка. Количество строк не может быть больше  MaxN 
//const char* fNameA = "МатрицаA7.txt"; //Ошибка. Количество столбцов не может быть больше  MaxN 
//const char* fNameA = "МатрицаA8.txt"; //Значения произведений одинаковы.
const char* fNameA = "МатрицаA9.txt"; //Значения произведений равны 0.
//const char* fNameA = "МатрицаA10.txt"; //Ошибка. Количество строк не может быть = 0.
//const char* fNameA = "МатрицаA11.txt"; //Ошибка. Количество столбцов не может быть = 0.
//const char* fNameA = "МатрицаA12.txt"; //Ошибка. Количество строк не может быть = 10.
//const char* fNameA = "МатрицаA13.txt"; //Ошибка. Количество строк не может быть = 11.
//const char* fNameA = "МатрицаA14.txt"; //Ошибка. Количество столбцов не может быть = 10.
//const char* fNameA = "МатрицаA15.txt"; //Ошибка. Количество столбцов не может быть = 11.


//const char* fNameB = "МатрицаB.txt";
//const char* fNameB = "МатрицаB1.txt"; //Ошибка: файл исходных данных не найден.
//const char* fNameB = "МатрицаB2.txt"; //Ошибка: файл исходных данных пуст.
//const char* fNameB = "МатрицаB3.txt"; //Ошибка ввода. В файле должны находиться только числа.
//const char* fNameB = "МатрицаB4.txt"; //Ошибка. Количество строк не может быть меньше 1.
//const char* fNameB = "МатрицаB5.txt"; //Ошибка. Количество столбцов не может быть меньше 1.
//const char* fNameB = "МатрицаB8.txt"; //Значения произведений одинаковы.
const char* fNameB = "МатрицаB9.txt"; //Значения произведений равны 0.
//const char* fNameB = "МатрицаB10.txt"; //Ошибка. Количество строк не может быть = 0.
//const char* fNameB = "МатрицаB11.txt"; //Ошибка. Количество столбцов не может быть = 0.

const int MaxN = 10;
int nmax = 0;
int nmax2 = 0;
/************************************************************
*         П Р О Т О Т И П Ы    Ф У Н К Ц И Й                *
*************************************************************/
int IntMatr(const char* fName,
	int A[][MaxN],
	int& N, int& M);  // Функция чтения из файла матриц


int ProductOfMatrixRows(int A[][MaxN],
	int N, int M); // Функция для вычисления произведение  строк матрицы, в элеемнтах которых отсутствуеь 0

int NMAX(int A[][MaxN],
	int N, int M,
	int& nmax); // Функция для нахождения максимального значения среди произведений

//чтение из файла
int IntMatr2(const char* fname_in//имя исходного файла
	, int*** Matr   
	//указатель на матрицу
	, int& N, int& M);             //размер матрицы

//чтение из файла
int ProductOfMatrixRows2(int*** Matr         //указатель на матрицу
	, int& N, int& M, 
	int& nmax2);             //размер матрицы

// Функция для нахождения максимального значения среди произведений
int NMAX2(int*** Matr,//указатель на матрицу
	int N, int M);  //размер матрицы

void ErrorCod(int err);//код ошибки

/**************************************************************
*                Р Е А Л И З А Ц И Я    Ф У Н К Ц И Й         *
***************************************************************/

//ПЕРВАЯ ЧАСТЬ ПРОГРАММЫ ДЛЯ МАТРИЦЫ А

int IntMatr(const char* fNameA, int A[][MaxN], int& N, int& M) // Функция чтения из файла матриц
{
	int err = 0;
	fstream fin;
	fin.open(fNameA);
	//Проверка на существование файла
	if (!fin)
	{
		fin.close();
		return 1;
	}
	//Проверка на пустоту файл
	if (fin.peek() == EOF)
	{
		N = 0;
		fin.close();
		return 2;
	}

	fin >> N >> M;
	//Проверка ввода на корректные данные
	if (fin.fail())
	{
		N = 0;
		fin.close();
		return 3;
	}

	cout << endl << endl;
	cout << " N = " << N << endl;
	cout << " M = " << M << endl;

	//Проверка на натуральность N
	if (N < 0)
	{
		fin.close();
		return 4;
	}

	//Проверка на натуральность N
	if (N == 0)
	{
		
		fin.close();
		return 10;
	}

	//Проверка на натуральность M
	if (M <= 0)
	{
		N = 0;
		fin.close();
		return 5;
	}

	//Проверка на натуральность M
	if (M == 0)
	{
		N = 0;
		fin.close();
		return 11;
	}

	// Проверка на превышение MaxN
	if (N > MaxN)
	{
		N = 0;
	      fin.close();
		return 6;
	}

	// Проверка на превышение MaxN
	if (N == MaxN)
	{
		N = 0;
		fin.close();
		return 12;
	}

	// Проверка на превышение MaxN
	if (N == (MaxN + 1))
	{
		N = 0;
		fin.close();
		return 13;
	}

	// Проверка на превышение MaxN
	if (M > MaxN)
	{
		N = 0;
		fin.close();
		return 7;
	}

	// Проверка на превышение MaxN
	if (M == MaxN)
	{
		N = 0;
		fin.close();
		return 14;
	}

	// Проверка на превышение MaxN
	if (M == (MaxN + 1))
	{
		N = 0;
		fin.close();
		return 15;
	}

	// Вывод матрицы
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			fin >> A[i][j];
		}
	}

	//Проверка ввода на корректные данные
	if (fin.fail())
	{
		N = 0;
		fin.close();
		return 3;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << ' ' << A[i][j] << ' ';
		}
		cout << endl;
	}
	return err;
}

int ProductOfMatrixRows(int A[][MaxN], int N, int M) // Функция для вычисления произведение  строк матрицы, в элеемнтах которых отсутствуеь 0
{

	int err = 0;

	int pr = 1; // Произведение строки

	if (N > 0)
		cout << "  Произведения строк матрицы: " << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			pr = pr * A[i][j];
		}

		if (pr == 0)
			cout << "";
		else
			cout << "  " << pr;

		pr = 1;
		cout << endl;
	}

	return err;
}

int NMAX(int A[][MaxN], int N, int M, int& nmax) // Функция для нахождения максимального значения среди произведений
{

	if (M < 1)
		N = 0;
	int err = 0;
	int pr = 1;
	// Макисмальное начение
	int vrem = 0; // Вспомогательная переменная
	int Temp = 0; // Счётчик
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			pr = pr * A[i][j];
		}

		if (pr > nmax)
			nmax = pr;

		vrem = pr;

		pr = 1;

		if (vrem == nmax && vrem != 0)
			Temp++;
	}

	//если произведения в строках одинаковы
	if (Temp == N && Temp != 0)
	{
		return 8;
	}

	//если произведения в строках равны 0
	if (Temp == 0 && Temp != N)
	{
		return 9;
	}
	return err;
}

//ВТОРАЯ ЧАСТЬ ПРОГРАММЫ ДЛЯ МАТРИЦЫ В

int IntMatr2(const char* fname_in//имя исходного файла
	, int*** Matr         //указатель на матрицу
	, int& N, int& M)             //размер матрицы
{
	int i;
	int j;
	int err = 0;
	fstream fin;
	fin.open(fname_in);

	//не удалось открыть файл
	if (!fin)
	{
		return 1;
	}

	//файл пуст
	if (fin.peek() == EOF)
	{
		fin.close();
		return 2;
	}

	fin >> N >> M;

	//Проверка ввода на корректные данные
	if (fin.fail())
	{
		N = 0;
		fin.close();
		return 3;
	}



	cout << "N = " << N << endl;
	cout << "M = " << M << endl;

	//если нестандартный размер матрицы(отрицательный)
	if (N < 0)
	{
		fin.close();
		return 4;
	}
	//если нестандартный размер матрицы(отрицательный)
	if (M < 0)
	{
        	N = 0;
		fin.close();
		return 5;
	}

	//Проверка на натуральность N
	if (N == 0)
	{
		fin.close();
		return 10;
	}
	//Проверка на натуральность M
	if (M == 0)
	{
		N = 0;
		fin.close();

		return 11;
	}
	//Инициализация динмического массива
	*Matr = new int* [N];

	//Создание Динамического массива
	for (i = 0; i < N; i++)
	{
		(*Matr)[i] = new int[M];
	}
	//Чтение матрицы из файла
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			fin >> *(*((*Matr) + i) + j);
		}
	}
	//Проверка ввода на корректные данные
	if (fin.fail())
	{
		N = 0;
		fin.close();
		return 3;
	}
	//Вывод массива
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			cout << *(*((*Matr) + i) + j) << " ";
		}
		cout << endl;
	}
	return err;
}//FRead

int ProductOfMatrixRows2(int*** Matr, int& N, int& M) // Функция для вычисления произведение  строк матрицы, в элеемнтах которых отсутствуеь 0
{
	int err = 0;
	int pr = 1; // Произведение строки
	if (N > 0)
		cout << "  Произведения строк матрицы: " << endl;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			pr = pr * (*(*((*Matr) + i) + j));
		}

		if (pr == 0)
			cout << "";
		else
			cout << "  " << pr;

		pr = 1;
		cout << endl;
	}

	return err;
}

int NMAX2(int*** Matr, int N, int M, int& nmax2) // Функция для нахождения максимального значения среди произведений
{
	if (M < 1)
		N = 0;
	int err = 0;
	int pr = 1;
	int vrem = 0; // Вспомогательная переменная
	int Temp = 0; // Счётчик

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			pr = pr * (*(*((*Matr) + i) + j));
	}

		if (pr > nmax2)
			nmax2 = pr;
		vrem = pr;
		pr = 1;
		if (vrem == nmax2 && vrem != 0)
			Temp++;
	}

	//если произведения в строках одинаковы
	if (Temp == N && Temp != 0)
	{
		return 8;
	}

	//если произведения в строках равны 0
	if (Temp == 0 && Temp != N)
	{
		return 9;
	}
	return err;
}



void ErrorCod(int err)
{
	switch (err)
	{
	case 1:
		cout << "Ошибка: файл исходных данных не найден." << endl;
		break;
	case 2:
		cout << "Ошибка: файл исходных данных пуст." << endl;
		break;
	case 3:
		cout << "Ошибка ввода. В файле должны находиться только числа." << endl;
		break;
	case 4:
		cout << "Ошибка. Количество строк не может быть меньше 1." << endl;
		break;
	case 5:
		cout << "Ошибка. Количество столбцов не может быть меньше 1." << endl;
		break;
	case 6:
		cout << "Ошибка. Количество строк не может быть больше  MaxN     MaxN = " << MaxN << endl;
		break;
	case 7:
		cout << " Ошибка. Количество столбцов не может быть больше  MaxN     MaxN = " << MaxN << endl;
		break;
	case 8:
		cout << " Значения произведений одинаковы. " << endl << endl;
		break;

	case 9:
		cout << " Значения произведений равны 0. " << endl << endl;
		break;

	case 10:
		cout << "Ошибка. Количество строк не может быть = 0." << endl;
		break;

	case 11:
		cout << "Ошибка. Количество столбцов не может быть = 0." << endl;
		break;

	case 12:
		cout << "Ошибка. Количество строк не может быть = 10." << endl;
		break;
	case 13:
		cout << "Ошибка. Количество строк не может быть = 11." << endl;
		break;
	case 14:
		cout << "Ошибка. Количество столбцов не может быть = 10." << endl;
		break;
	case 15:
		cout << "Ошибка. Количество столбцов не может быть = 11." << endl;
		break;
	default: //cообщение для случая, если в функцию поступил не известный ей код ошибки
		cout << "Неизвестная ошибка с кодом " << err << ".\n\n";

		break;
	}
}

/***************************************************************
*              О С Н О В Н А Я      П Р О Г Р А М М А          *
****************************************************************/

int main() {

	setlocale(LC_ALL, "Rus");
	int N;
	int M;
	int err = 0;
	int A[MaxN][MaxN] = {0};

	err = IntMatr(fNameA, A, N, M);
	if (err != 0)
	{
		ErrorCod(err);
	}
	else {
		cout << "\n";

	    ProductOfMatrixRows(A, N, M);
		cout << "\n";
		cout << "\n";
		err = NMAX(A, N, M, nmax);
		if (err != 0)
		{
			ErrorCod(err);
		}
		else
		{
			cout << "\n";
			cout << "  Наибольшее значение произведений строк = " << nmax << endl << endl;
		}  
	}
	cout << "/****************************************************/" << "\n";

	int** MatrB = 0; //Создание нулевого указателя , который хранит в себе указатели (матрица)
	err = IntMatr2(fNameB, &MatrB, N, M);
	if (err != 0) {
		ErrorCod(err);
	}
	else {
		cout << "\n";

		ProductOfMatrixRows2(&MatrB, N, M);
		cout << "\n";
        	cout << "\n";

		err = NMAX2(&MatrB, N, M, nmax2);
		if (err != 0)
		{
			ErrorCod(err);
		}
		else
		{
			cout << "\n";
			cout << "  Наибольшее значение произведений строк = " << nmax2 << endl << endl;
		}		
	}
	cout << "/****************************************************/" << "\n";
	system("pause");
	return err;
} 
