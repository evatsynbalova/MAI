#include <iostream>

using namespace std;

#define size 5 //начальный размер списка

/*СТРУКТУРЫ*/
//элемент списка
struct list
{
	char data;  //Данные
	list* next; //Указатель на следующий элемент
	list* prev; //Указатель на предыдущий элемент
};

list* Begin = NULL; //Указатель на начало списка
list* End = NULL; //Указатель на конец списка
int Count = size;  //Количество элементов в списке

/*ПРОТОТИПЫ ФУНКЦИЙ*/
//создание списка
void create(const int& count);

//печать списка
void print();

//удаление списка
void Delete();

//поиск элемента с максимальным значением
void max();

//включение нового элемента в начало списка
void add_elem(char value);

//удаление элемента из начала списка
void delete_elem();
/*ОСНОВНАЯ ПРОГРАММА*/
int main()
{
	setlocale(LC_ALL, "russian");
	system("color F0");

	char newelem; //новый элемент
	int n = 1;    //выбор действия

	while (n)
	{
		cout << " Выберете действие :" << endl;
		cout << " 0) Выход" << endl;
		cout << " 1) Создание списка" << endl;
		cout << " 2) Вывод списка" << endl;
		cout << " 3) Удаление списка" << endl;
		cout << " 4) Поиск элемента с максимальным значением" << endl;
		cout << " 5) Включение нового элемента в начало списка" << endl;
		cout << " 6) Удаление элемента из начала списка" << endl;
		
		cin >> n;

		switch (n)
		{
		case 0:
		{
			cout << "\n Выход из программы " << endl;
			Delete(); 
			return 0;
		}

		case 1:
		{
			create(size);
			break;
		}
		case 2:
		{
			print();
			break;
		}

		case 3:
		{
			Delete();
			break;
		}

		case 4:
		{
			max();
			break;
		}
		
		case 5:
		{
			if (Begin == NULL)
			{
				cout << " Список не создан" << endl;
				break;
			}

			cout << " Введите значение элемента: ";
			cin >> newelem;
			add_elem(newelem);
			break;
		}

		case 6:
		{
			delete_elem();
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
}//main()
/*РЕАЛИЗАЦИЯ ФУНКЦИЙ*/
//создание списка
void create(const int& count)
{
	if (Begin != NULL)
	{
		cout << " Спиcок уже создан" << endl;
		return;
	}//if

	char elem; //элемент списка

	for (int i = 0; i < count; ++i)
	{
		list* temp = new list; //новый элемент

		if (i == 0)
		{
			Begin = temp; //начало списка
		}//if
		else
		{
			End->next = temp; //связываем с предыдущим элементом
		}//else

		temp->prev = End; //cвязь с предыдущим элементом
		End = temp;       //текущий элемент - конец списка
		temp->next = NULL; //следующего элемента нет

		cin >> elem;
		temp->data = elem; //заполнение данными
	}//for()
	cout << " \n Список создан" << endl;
	Count = size;
}//create()

//печать списка
void print()
{
	if (Begin == NULL)
	{
		cout << " Список не создан" << endl;
		return;
	}//if

	list* lst = Begin;
	int i = 0;

	while (lst != NULL) //пока не дойдем до конца списка
	{
		cout << " " << i << "\t" << lst->data << endl;
		lst = lst->next;
		i++;
	}//while()
}//print()

//удаление списка
void Delete()
{
	if (Begin == NULL)
	{
		cout << " \n Список не создан" << endl;
		return;
	}//if

	while (Begin != NULL) //пока не дойдем до конца списка, удаляем начальный элемент списка
	{
		list* lst = Begin; //текущий элемент - начало списка
		Begin = lst->next; //следующий элемент - начало списка
		lst->prev = NULL; 
		lst->next = NULL;
		delete lst;
	}//while

	Begin = NULL;
	End = NULL;
	cout << " Список удалён " << endl;
	Count = 0;
}//Delete()

//поиск элемента с максимальным значением
void max()
{
	if (Begin == NULL)
	{
		cout << " \nСписок не создан " << endl;
		return;
	}//if

	list* lst = Begin; //текущий элемент - начало списка
	double max;       
	max = lst->data;  //первый элемент максимальный
	lst = lst->next;  

	while (lst != NULL) //пока не дойдем до конца списка
	{
		if (max < lst->data) //текущий максимальный элемент меньше данного элемента в списке
		{
			max = lst->data; //присваиваем этому элементу масимум
		}//if
		lst = lst->next;     //переходим к следующему элементу
	}//while

	cout << " Максимальный элемент: " << max << endl;
	cout << "\n Его номер в списке: ";

	int num = 0;
	lst = Begin;

	//выводим номер максимума в списке
	while (lst != NULL) 
	{
		if (max == lst->data)   
		{
			cout << num << " "; 
		}//if

		lst = lst->next;
		num++;
	}//while
	cout << endl;
}//max()

//включение нового элемента в начало списка
void add_elem(char xnewelem)
{
	list* lst = Begin;      //текущий элемент - начало списка
	list* temp = new list; //создание нового элемента

	temp->prev = lst->prev; //меняем связи с предыдущим элементом
	Begin = temp;            //добавляемый элемент - начало списка
	lst->prev = temp;       //соединяем с актуальным
	temp->next = lst;       //созданный элемент указывает на следующий
	temp->data = xnewelem;  //записываем значение

	cout << " Элемент добавлен в начало списка" << endl;
	Count++;
}//add_elem()

//удаление элемента из начала списка
void delete_elem()
{
	if (Begin == NULL)
	{
		cout << " \nСписок не создан " << endl;
		return;
	}//if
	
	list* lst = Begin; //текущий элемент - начало списка
	Begin = lst->next; //меняем начальный элемент на следующий

	if (Count == 1) //количество элементов равно 1
	{
		End = NULL; //удаляем указатель на конец списка
	}//if
	else
	{
		Begin->prev = NULL; //убираем связь с первым элементом
	}//else

	delete lst;
	cout << " \n Элемент из начала списка удален " << endl;
}//delete_elem()
 
