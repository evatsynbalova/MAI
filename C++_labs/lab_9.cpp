#include <iostream>
#include <ctime>

using namespace std;

#define size 5

/*СТРУКТУРЫ*/
struct List 
{
	List* prev;  //указатель на предыдущий элемент
	List* next;  //указатель на следующий элемент
	int data;    //данные
	int num;     //информац. поле
};
struct deque 
{
private:
	List* Begin = NULL; //начало дека
	List* End = NULL;   //конец дека
	int Size = 0;       //количество элементов

public:
	//размер дека
	int xsize() 
	{
		return Size;
	}//xsize()

	//создание дека
	void create(int k)
	{
		if (Begin != NULL) //не начало дека
		{
			cout << " Дек уже создан" << endl;
			return;
		}//if

		cout << " Дек создан " << endl;
		//заполняем дек данными
		for (int i = 0; i < k; i++)
		{
			int xdata;
			xdata = rand() % 100; 
			add_back(xdata);
		}//for		
	}//create()
	
	//печать дека
	void print() 
	{
		if (Begin == NULL) //если начало дека
		{
			cout << " Дек не создан" << endl;
			return;
		}//if

		List* lst = new List;
		lst = Begin;
		int i = 0;

		while (lst != NULL) //пока не дойдем до конца дека
		{
			cout << " " << i << "\t" << lst->data << endl;
			lst = lst->next;
			i++;
		}//while()		
	}//print() 

	//добавление элемента в конец дека
	void add_back(int p) 
	{
		if (Size == 0) 
		{
			List* temp = new List; //создание нового элемента
			temp->next = NULL;     
			temp->prev = NULL;
			temp->data = p;        //записываем значение нового элемента
			Begin = End = temp;    
			Size++;
			temp->num = Size;
		}//if
		else 
		{
			List* temp = new List; //создание нового элемента
			temp->next = NULL;     
			temp->prev = End;      
			temp->data = p;        //записываем значение нового элемента
			End->next = temp;      //созданный элемент указывает на следующий
			End = temp;
			Size++;
			temp->num = Size;
		}//else		
	}//add_back()

	//выборка элемента из конца дека
	void del_back() 
	{
		if (Begin == NULL) //если начало дека
		{
			cout << " Дек не создан" << endl;
			return;
		}//if

		List* temp;
		if (End != NULL) //не конец дека
		{
			temp = End;
			End = End->prev; //меняем последний элемент на предыдущий
			delete temp;     //удаляем последний элемент

			if (End == NULL)  //конец дека равен нулю
				Begin = NULL; //удаляем указатель на начало дека
			else
				End->next = NULL; //убираем связь с последним элементом

			--Size;
		}//if		
	}//del_back() 

	//очистка дека
	void clear() 
	{
		List* temp;
		while (Begin != NULL) //пока не дек не закончится
		{
			temp = Begin;        //присваиваем элементу начало дека
			Begin = Begin->next; //меняем указатель на следующий элемент
			delete temp;         //удаляем элемент
		}//while

		Begin = NULL;  //удаляем указатель на начало дека
		Size = 0;

		cout << " Дек очищен \n";
	}//clear()
};
int main()
{
	setlocale(LC_ALL, "russian");
	system("color F0");
	srand(time(NULL));

	int newelem;  //новый элемент
	int n = 1;    //выбор действия

	deque D; 
	while (n)
	{
		cout << " Выберете действие :" << endl;
		cout << " 0) Выход" << endl;
		cout << " 1) Создание дека" << endl;
		cout << " 2) Вывод дека" << endl;
		cout << " 3) Очистка дека" << endl;
		cout << " 4) Выборка элемента из конца дека" << endl;
		cout << " 5) Добавление элемента в конец дека" << endl;

		cin >> n;
		switch (n)
		{
		case 0:
		{
			cout << "\n Выход из программы " << endl;
			D.clear();
			return 0;
		}

		case 1:
		{
			D.create(size);
			break;
		}
		case 2:
		{
			D.print();
			break;
		}

		case 3:
		{
			D.clear();
			break;
		}

		case 4:
		{
		
			if (size)
			{
				D.del_back();
			}
			else 
			{
				cout << " Ошибка\n";
			}
			break;
		}

		case 5:
		{
			if (size)
			{
				int elem; 
				cout << " Введите элемент : ";
				cin >> elem;
				D.add_back(elem);
			}
			else
			{
				cout << " Ошибка\n";
			}
			
			break;
		}

		default:
		{
			cout << "\n Введите значение ещё раз :" << endl;
			break;
		}
		}//switch

		system("pause");
		system("cls");
	}//while
	return 0;
}//main()
 
