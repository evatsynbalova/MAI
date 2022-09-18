ClassDiagram.cd

#pragma once                  
#include <windows.h>
#include <conio.h>
#include <iostream>    
using namespace std;

#include "CocaCola.h"         
#include "GetConlWin.h"                

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ*/
HDC hdc;      //объявим контекст устройства

const int m = 4; // количество строк матрицы взаимодействия
const int n = 4; // количество столбцов матрицы взаимодействия

/*ПРОТОТИПЫ ФУНКЦИЙ*/
//для сокращения записи
void PressKey(int VkCode)
{
    while (1)
        if (KEY_DOWN(VkCode))
            break;
}//PressKey()

int** fillmatrix(int** xmatrix); // матрица взаимодействия (заполнение)
bool check(int& xactiveFISH, int& xactiveOBJECT, Point** xpPoint, Point2** xbPoint); // проверка столкновения
void change(int& xactiveFISH, int& xactiveOBJECT, int& xchangeFISH, int** xmatrix, Point** xpPoint, Point2** xbPoint); // изменение рыбы при произошедшем столкновении

  /*ОСНОВНАЯ ПРОГРАММА*/    
void main()
{
    system("color F0");

    int** matrix = 0;            // матрица взаимодействия
    matrix = fillmatrix(matrix);

    //объявление и инициализация переменных
    int Step = 30;           //шаг рыбы 3
    int x0 = 250, y0 = 250;  //начальные координаты 
    int Radius1 = 50;
    int Radius2 = 10;
    int Radius3 = 10;
    int Radius4 = 20;
    int DeltaRad = 30;       //начальное изменение радиуса 1

    HWND hwnd = GetConcolWindow();  //получим дескриптор окна   

    //доп. координаты
    int x1 = 125, y1 = 150;
    int x2 = 575, y2 = 250;
    int x3 = 1025, y3 = 100;
    int x4 = 75, y4 = 100;
    int x5 = 750, y5 = 550;
    int x6 = 300, y6 = 450;
    int x7 = 350, y7 = 50;
    int x8 = 500, y8 = 500;
    int x9 = 200, y9 = 200;

    int activeFISH = 0;        // текущая рыба
    int activeOBJECT = 0;      // текущее препятствие
    int changeFISH = 0;        // рыба, которую нужно скрыть
    bool ifboom = false;       // переменная для определения столкновения

   // если дескриптор не равен нулю то ... 
    if (hwnd != NULL)
    {
        // получим контекст устройства
        hdc = GetWindowDC(hwnd);

        // если контекст устройства не равен нулю то ... 
        if (hdc != 0)
        {
            Point** pPoint = new Point * [m]; //массив указателей на базовый класс

           //инициализация элементов массива указателей адресами фигур 
            pPoint[0] = new Fish1(x1, y1, 0, Radius1, Radius2, x4, y4, Radius3, Radius4);
            pPoint[1] = new Fish2(x2, y2, 1, Radius1, Radius2, x4, y4, Radius3, Radius4);
            pPoint[2] = new Fish3(x3, y3, 2, Radius1, Radius2, x4, y4, Radius3);
            pPoint[3] = new Fish4(x8, y8, 3, Radius1, Radius2, x4, y4, Radius3);

            Point2** bPoint = new Point2 * [n];
            bPoint[0] = new SeaweedMin(x5, y5, 0, x4, y4);
            bPoint[1] = new SeaweedMax(x6, y6, 1, x4, y4);
            bPoint[2] = new Air(x6, y6, 2, Radius3);
            bPoint[3] = new Air1(x9, y9, 3, Radius3);

            // показать препятствия
            for (int i = 0; i < n; i++)
                bPoint[i]->Show();

            // показать рыбу
            pPoint[0]->Show();
            activeFISH = pPoint[0]->GetIndex();


            // бесконечный цикл
            while (1)
            {
                // конец работы
                if (KEY_DOWN(50)) // цифра 2
                    break;
                // движение и смена РЫБЫ
                if (KEY_DOWN(49)) // цифра 1
                {
                    // двигаем РЫБУ
                    pPoint[activeFISH]->Drag(Step);

                    // проверяем, наехали ли мы на препятствие
                    ifboom = check(activeFISH, activeOBJECT, pPoint, bPoint);
                    // если наехали на препятствие, то
                    if (ifboom == true)
                    {
                        // меняем РЫБУ
                        change(activeFISH, activeOBJECT, changeFISH, matrix, pPoint, bPoint);
                    }
                }

            }// end if
        }// end if

       // return 0;
    }//end main()
}

 // матрица взаимодействия (заполнение)
 int** fillmatrix(int** xmatrix)
  
{
    xmatrix = new int* [m];       // создаём одномерный массив указателей   
    xmatrix[0] = new int[n] {1, 2, 1, 3}; // заполняем матрицу
    xmatrix[1] = new int[n] {0, 2, 0, 3};
    xmatrix[2] = new int[n] {1, 0, 1, 3};
    xmatrix[3] = new int[n] {1, 0, 1, 2};
 
    // возвращаем матрицу
    return xmatrix;
}

// проверка столкновения
bool check(int& xactiveFISH, int& xactiveOBJECT, Point** xpPoint, Point2** xbPoint)
{

    bool boom = false;        // переменная для фиксирования столкновения
    int j;                    // индексная переменная
    int figx, figy, brx, bry; // координаты рыбы и препятствия


    // получаем координаты рыбы
    figx = xpPoint[xactiveFISH]->GetX();
    figy = xpPoint[xactiveFISH]->GetY();

    // проверяем, с каким препятствием столкнулась FISH
    for (j = 0; j < n; j++)
    {
        // получаем координаты препятствия
        brx = xbPoint[j]->GetX();
        bry = xbPoint[j]->GetY();

        // проверяем, наехали ли мы на j-ое препятствие
        if ((figx < brx + 150) && (figx > brx - 150) && (figy < bry + 150) && (figy > bry - 150))
        {
            xactiveOBJECT = xbPoint[j]->GetIndex(); // узнаём, на какое препятствие наехали
            boom = true; // говорим, что наехали на препятствие
        }// if
    }// for

    return boom; // возвращаем положительный результат столкновения
}// check()

// изменение fish при произошедшем столкновении
void change(int& xactiveFISH, int& xactiveOBJECT, int& xchangeFISH, int** xmatrix, Point** xpPoint, Point2** xbPoint)
{
    xchangeFISH = xactiveFISH; // запоминаем fish, которую нужно поменять
    xactiveFISH = *(*(xmatrix + xchangeFISH) + xactiveOBJECT); // меняем

    xpPoint[xchangeFISH]->Hide();    // скрываем старую fish
    xbPoint[xactiveOBJECT]->MoveTo(2000,2000); // перемещаем препятствие
    xpPoint[xactiveFISH]->MoveTo(xpPoint[xchangeFISH]->GetX(), xpPoint[xchangeFISH]->GetY()); // показываем новую fish
}// change()  



CocaCola.h

//Абстрактный базовый класс
class Location //класс местоположения
{
protected:
	int X;		// координата X
	int Y;		//координата Y

public:
	Location(int InitX, int InitY); //конструктор
	virtual ~Location();                    //деструктор
	int GetX();						//получаем значение Х
	int GetY();						//получаем значение У
	virtual void Show() = 0;   //показать фигуру
	virtual void Hide() = 0;   //скрыть фигуру

};//Location 

//Интерфейс
class Location2
{
public:
	//чистые виртуальные функции
	virtual void Show() = 0;   //показать фигуру
	virtual void Hide() = 0;   //скрыть фигуру
};//Location2


class Point : public Location //класс точка, наследуется от класса местоположения
{
protected:
	bool Visible;	//точка в пространстранстве, видим рисунок
	int Index;
public:
	Point(int InitX, int InitY, int InitIndex);	//конструктор класса
	virtual ~Point();               //виртуальный деструктор
	bool IsVisible();				//проверяет видимость точки
	void Drag(int Step);			//буксировка фигуры(перемещение)
	void MoveTo(int NewX, int NewY);  //передвижение всей фигуры
	void Show();              //показать точку
    void Hide();              //скрыть точку
	int GetIndex();                   //узнать индекс фигуры
};//Point


class Point2 : public Location2
{
protected:
	bool Visible;  //светится точка или нет
	int X;		   //координата X
	int Y;	       //координата Y
	int Index;     //индекс объекта
public:
	Point2(int InitX, int InitY, int InitIndex);	//конструктор
	virtual ~Point2();                //виртуальный деструктор
	bool IsVisible();				  //узнать про светимость точки
	int GetX();					      //получить X координату точки
	int GetY();						  //получить Y координату точки
	void Drag(int Step);			  //буксировка фигуры
	void MoveTo(int NewX, int NewY);  //переместить фигуру
	void Show();                      //показать фигуру
	void Hide();                      //скрыть фигуру
	int GetIndex();                   //узнать индекс фигуры
};//Point2


class  Body : public  Point //класс круг (туловище)
{
protected:
	int Radius1;					//радиус круга 1
public:
	Body(int InitX, int InitY, int InitIndex, int initRadius1);//конструктор
	virtual~Body();					//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру
};//class IziFish


class  Eye : public  Body //класс круг (глаз)
{
protected:
	int Radius2;					//радиус круга 2
public:
	Eye(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2);//конструктор
	virtual~Eye();					//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру
};//class Eye


class  IziFish :public Eye //класс рыба простая
{
protected:
	int X4; 
	int Y4; 
public:
	IziFish(int InitX, int InitY, int InitIndex,int initRadius1, int initRadius2, int InitX4, int InitY4);//конструктор
	virtual~IziFish();	 				//деструктор
	virtual void Show();            //показать фигуру 
	virtual void Hide();            //спрятать фигуру 
};//class Fish1

class Fish : public IziFish//класс рыба 
{
protected:
	int Radius3;
public:
	Fish(int InitX, int InitY, int InitIndex,int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3);//конструктор
	virtual~Fish();	 		//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру 
};//class Fish2

class Fish1 : public Fish//класс рыба 1
{
protected:
	int Radius4;
public:
	Fish1(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3, int initRadius4);//конструктор
	virtual~Fish1();	 		//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру 
};//class Fish1


class Fish2 : public Fish//класс рыба 2
{
protected:
	int Radius4;
public:
	Fish2(int InitX, int InitY, int InitIndex,int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3, int initRadius4);//конструктор
	virtual~Fish2();	 		//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру 
};//class Fish2


class Fish3 : public IziFish//класс крест (глаз 2)
{
protected:
	int Radius3;
public:
	Fish3(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3);//конструктор
	virtual~Fish3();	 		//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру 
};//class Cross

class Fish4 : public IziFish//класс крест 
{
protected:
	int Radius3;
public:
	Fish4(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3);//конструктор
	virtual~Fish4();	 		//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру 
};//class Cross



class SeaweedMin: public Point2//класс водоросли маленькие
{
protected:
	int X4;
	int Y4;
public:
	SeaweedMin(int InitX, int InitY, int InitIndex, int InitX4, int InitY4);//конструктор
	virtual~SeaweedMin();	 		//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру 
};//class SeaweedMin


class SeaweedMax : public Point2//класс водоросли маленькие
{
protected:
	int X4;
	int Y4;
public:
	SeaweedMax(int InitX, int InitY, int InitIndex, int InitX4, int InitY4);//конструктор
	virtual~SeaweedMax();	 		//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру 
};//class SeaweedMax


class  Air : public  Point2 //класс круг (глаз)
{
protected:
	int Radius3;					//радиус круга 3
public:
	Air(int InitX, int InitY, int InitIndex, int initRadius3);//конструктор
	virtual~Air();					//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру
};//class Air


class  Air1 : public  Point2 //класс круг (глаз)
{
protected:
	int Radius3;					//радиус круга 3
public:
	Air1(int InitX, int InitY, int InitIndex, int initRadius3);//конструктор
	virtual~Air1();					//деструктор
	void Show();        //показать фигуру 
	void Hide();        //спрятать фигуру
};//class Air1




CocaCola.cpp

#include <windows.h>
#include "CocaCola.h"
#include <iostream> 
using namespace std;

//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
extern HDC hdc;      //объявим  контекст устройства

//Макрос для проверки состояния клавиатуры – из ШАБЛОНА
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*РЕАЛИЗАЦИЯ МЕТОДОВ КЛАССА*/


/*МЕТОДЫ КЛАССА Location*/
//конструктор
Location::Location(int InitX, int InitY)
{
	//инициализация закрытых переменных своего класса
	X = InitX;
	Y = InitY;
};//Location::Location()

 //деструктор
Location::~Location(void)
{
};//Location::~Location()

  //получить X координату точки
int Location::GetX(void)
{
	return X;
};//GetX()	

  //получить Y координату точки
int Location::GetY(void)
{
	return Y;
}; //GetY()

/*МЕТОДЫ КЛАССА Point*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Point::Point(int InitX, int InitY, int InitIndex) : Location(InitX, InitY)
{
	//инициализация закрытых переменных своего класса
	Index = InitIndex;
	Visible = false;
}//Point()

 //деструктор
Point::~Point(void)
{
}//~Point()

//показать ТОЧКУ
void Point::Show(void)
{
	Visible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}//Show()



//скрыть ТОЧКУ
void Point::Hide(void)
{
	Visible = false;

	SetPixel(hdc, X, Y, RGB(0, 0, 255));//рисуем синим цветом 
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
}//Hide()

 //узнать про светимость ТОЧКИ
bool Point::IsVisible(void)
{
	return Visible;
};//IsVisible()

//переместить ТОЧКУ
void Point::MoveTo(int NewX, int NewY)
{
	Hide();		//сделать точку невидимой
	X = NewX;	//поменять координаты ТОЧКИ
	Y = NewY;
	Show();		//показать точку на новом месте
};//Point::MoveTo()

//узнать индекс фигуры
int Point::GetIndex()
{
	return Index;
};

//буксировка фигуры
void Point::Drag(int Step)
{
	int FigX, FigY;   //новые координаты фигуры

	FigX = GetX();    //получаем начальное положение фигуры
	FigY = GetY();

	while (1)	//бесконечный цикл буксировки фигуры
	{
		if (KEY_DOWN(VK_ESCAPE))     //конец работы 27
			break;

		//направление движения объекта
		if (KEY_DOWN(VK_LEFT)) //стрелка влево  37
		{
			FigX -= Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}//if

		if (KEY_DOWN(VK_RIGHT)) //стрелка вправо  39
		{
			FigX += Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}// if

		if (KEY_DOWN(VK_DOWN)) //стрелка вниз  40
		{
			FigY += Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}// if

		if (KEY_DOWN(VK_UP)) //стрелка вверх  38
		{
			FigY -= Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}//if
	}//while
}//Drag()

/*МЕТОДЫ КЛАССА Point2*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Point2::Point2(int InitX, int InitY, int InitIndex) : Location2()
{
	X = InitX;
	Y = InitY;
	Index = InitIndex;
	Visible = false;
}//Point2()

 //деструктор
Point2::~Point2(void)
{
}//~Point2()

//показать ТОЧКУ
void Point2::Show(void)
{
	Visible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	//4 точки
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}//Show()

//скрыть ТОЧКУ
void Point2::Hide(void)
{
	Visible = false;

	SetPixel(hdc, X, Y, RGB(0, 0, 255));//рисуем синим цветом 
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
}//Hide()

 //узнать про светимость ТОЧКИ
bool Point2::IsVisible(void)
{
	return Visible;
};//IsVisible()

//получить X координату точки
int Point2::GetX(void)
{
	return X;
};//GetX()	

//получить Y координату точки
int Point2::GetY(void)
{
	return Y;
}; //GetY()

//переместить ТОЧКУ
void Point2::MoveTo(int NewX, int NewY)
{
	Hide();		//сделать точку невидимой
	X = NewX;	//поменять координаты ТОЧКИ
	Y = NewY;
	Show();		//показать точку на новом месте
};//Point::MoveTo()

//узнать индекс фигуры
int Point2::GetIndex()
{
	return Index;
};

//буксировка фигуры
void Point2::Drag(int Step)
{
	int FigX, FigY;   //новые координаты фигуры

	FigX = GetX();    //получаем начальное положение фигуры
	FigY = GetY();

	while (1)	//бесконечный цикл буксировки фигуры
	{
		if (KEY_DOWN(VK_ESCAPE))     //конец работы 27
			break;

		//направление движения объекта
		if (KEY_DOWN(VK_LEFT)) //стрелка влево  37
		{
			FigX -= Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}//if

		if (KEY_DOWN(VK_RIGHT)) //стрелка вправо  39
		{
			FigX += Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}// if

		if (KEY_DOWN(VK_DOWN)) //стрелка вниз  40
		{
			FigY += Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}// if

		if (KEY_DOWN(VK_UP)) //стрелка вверх  38
		{
			FigY -= Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}//if
	}//while
}//Drag()


/* МЕТОДЫ КЛАССА  Body*/
//конструктор
Body::Body(int InitX, int InitY, int InitIndex, int initRadius1) : Point(InitX, InitY, InitIndex)
{
	Radius1 = initRadius1;
}//IziFish()

//деструктор
Body::~Body()
{
}//Body()

//показать круг
void  Body::Show()
{
	Point::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, PenRed);

	//рисуем круг установленным цветом(туловище)
	Ellipse(hdc, X - 1.5 * Radius1, Y - Radius1, X + 1.5 * Radius1, Y + Radius1);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть круг
void  Body::Hide()
{
	Point::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);

	//рисуем круг установленным цветом(туловище)
	Ellipse(hdc, X - 1.5*Radius1, Y - Radius1, X + 1.5*Radius1, Y + Radius1);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()



/* МЕТОДЫ КЛАССА  Eye*/
//конструктор
Eye::Eye(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2) : Body(InitX, InitY,  InitIndex,initRadius1)
{
	Radius2 = initRadius2;
}//Eye()

//деструктор
Eye::~Eye()
{
}//Eye()

//показать круг
void  Eye::Show()
{
	Body::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, PenRed);

	//рисуем круг установленным цветом
	Ellipse(hdc, X-3.5* Radius2, Y - Radius2, X - 1.5 * Radius2, Y + Radius2);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть круг
void  Eye::Hide()
{
	Body::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);

	//рисуем круг установленным цветом
	Ellipse(hdc, X - 3.5 * Radius2, Y - Radius2, X - 1.5 * Radius2, Y + Radius2);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()


/* МЕТОДЫ КЛАССА IziFish*/
//конструктор
IziFish::IziFish(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2,int InitX4, int InitY4) : Eye(InitX,  InitY,  InitIndex, initRadius1,  initRadius2)
{
	X4 = InitX4;
	Y4 = InitY4;
}//IziFish()

//деструктор
IziFish::~IziFish()
{
}//~ IziFish()

//показать треугольник
void  IziFish::Show()
{
	Eye::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255,0,0));
	SelectObject(hdc, PenRed);

	POINT poly[4];

	//координаты отрезков
	poly[0].x = X+X4 ;
	poly[0].y = Y;

	poly[1].x = X+125;
	poly[1].y = Y-50;

	poly[2].x = X+125;
	poly[2].y = Y+50;

	poly[3].x = X + X4;
	poly[3].y = Y;

	//рисуем треугольник установленным цветом
	Polyline(hdc, poly, 4);

	//уничтожим созданные объекты
	DeleteObject(PenRed);
}//Show()

//скрыть треугольник
void  IziFish::Hide()
{
	Eye::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);
	POINT poly[4];

	poly[0].x = X + X4;
	poly[0].y = Y;

	poly[1].x = X + 125;
	poly[1].y = Y - 50;

	poly[2].x = X + 125;
	poly[2].y = Y + 50;

	poly[3].x = X + X4;
	poly[3].y = Y;

	//рисуем треугольник установленным цветом
	Polyline(hdc, poly, 4);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()


/*МЕТОДЫ КЛАССА Fish*/
//конструктор
Fish::Fish(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3) : IziFish( InitX,  InitY,  InitIndex, initRadius1,  initRadius2,  InitX4,  InitY4)
{
     Radius3 = initRadius3;
}//Fish()

//деструктор
Fish::~Fish()
{

}//~Fish()

//показать линию
void Fish::Show()
{
	IziFish::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, PenRed);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X;
	poly[0].y = Y - Radius1;

	poly[1].x = X + Radius1;
	poly[1].y = Y - Y4;

	//рисуем линию
	Polyline(hdc, poly, 2);

	POINT poly2[2];

	//координаты отрезков
	poly2[0].x = X;
	poly2[0].y = Y + Radius1;

	poly2[1].x = X + Radius1;
	poly2[1].y = Y + Y4;

	//рисуем линию
	Polyline(hdc, poly2, 2);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть линию
void Fish::Hide()
{
	IziFish::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(192,192,192));
	SelectObject(hdc, PenBlue);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X;
	poly[0].y = Y - Radius1;

	poly[1].x = X + Radius1;
	poly[1].y = Y - Y4;

	//рисуем линию
	Polyline(hdc, poly, 2);

	POINT poly2[2];

	//координаты отрезков
	poly2[0].x = X;
	poly2[0].y = Y + Radius1;

	poly2[1].x = X + Radius1;
	poly2[1].y = Y + Y4;

	//рисуем линию
	Polyline(hdc, poly2, 2);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()


/*МЕТОДЫ КЛАССА Fish1*/
//конструктор
Fish1::Fish1(int InitX, int InitY, int InitIndex,int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3, int initRadius4) : Fish(InitX,  InitY,  InitIndex, initRadius1,  initRadius2,  InitX4, InitY4,  initRadius3)
{
	Radius4 = initRadius4;
}//Fish1()

//деструктор
Fish1::~Fish1()
{

}//~Fish1()

//показать линию
void Fish1::Show()
{
	Fish::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, PenRed);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X;
	poly[0].y = Y- Radius1;

	poly[1].x = X + Radius1;
	poly[1].y = Y-Y4;

	//рисуем линию
	Polyline(hdc, poly, 2);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть линию
void Fish1::Hide()
{
	Fish::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(192, 192, 192));
	SelectObject(hdc, PenBlue);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X;
	poly[0].y = Y - Radius1;

	poly[1].x = X + Radius1;
	poly[1].y = Y - Y4;

	//рисуем линию
	Polyline(hdc, poly, 2);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()


/* МЕТОДЫ КЛАССА  Fish2*/
//конструктор
Fish2::Fish2(int InitX, int InitY, int InitIndex,int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3, int initRadius4) : Fish( InitX,  InitY,  InitIndex,initRadius1,  initRadius2, InitX4,  InitY4,  initRadius4)
{
	Radius4 = initRadius4;
}//Fish2()

//деструктор
Fish2::~Fish2()
{
}//Fish2()

//показать круг
void  Fish2::Show()
{
	Fish::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, PenRed);

	//рисуем круг установленным цветом
	Ellipse(hdc, X - 3.5 * Radius4, Y - Radius4, X - 1.5 * Radius4, Y + Radius4);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть круг
void  Fish2::Hide()
{
	Fish::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(192,192,192));
	SelectObject(hdc, PenBlue);

	//рисуем круг установленным цветом
	Ellipse(hdc, X - 3.5 * Radius4, Y - Radius4, X - 1.5 * Radius4, Y + Radius4);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()


/*МЕТОДЫ КЛАССА Fish3*/
//конструктор
Fish3::Fish3(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3) : IziFish( InitX,  InitY, InitIndex, initRadius1,  initRadius2,  InitX4,  InitY4)
{
	Radius3 = initRadius3;
}//Cross()

//деструктор
Fish3::~Fish3()
{

}//~Fish3()

//показать линию
void Fish3::Show()
{
	IziFish::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, PenRed);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X - 3.5*Radius2;
	poly[0].y = Y - Radius2;

	poly[1].x = X - 1.5 *  Radius2;
	poly[1].y = Y +  Radius2;

	//рисуем линию
	Polyline(hdc, poly, 2);

	POINT poly2[2];

	//координаты отрезков
	poly2[0].x = X - 3.5 * Radius2;
	poly2[0].y = Y + Radius2;

	poly2[1].x = X - 1.5 * Radius2;
	poly2[1].y = Y - Radius2;

	//рисуем линию
	Polyline(hdc, poly2, 2);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть линию
void Fish3::Hide()
{
	IziFish::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X - 3.5 * Radius2;
	poly[0].y = Y - Radius2;

	poly[1].x = X - 1.5 * Radius2;
	poly[1].y = Y + Radius2;

	//рисуем линию
	Polyline(hdc, poly, 2);

	POINT poly2[2];

	//координаты отрезков
	poly2[0].x = X - 3.5 * Radius2;
	poly2[0].y = Y + Radius2;

	poly2[1].x = X - 1.5 * Radius2;
	poly2[1].y = Y - Radius2;

	Polyline(hdc, poly2, 2);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()



/*МЕТОДЫ КЛАССА Fish4*/
//конструктор
Fish4::Fish4(int InitX, int InitY, int InitIndex, int initRadius1, int initRadius2, int InitX4, int InitY4, int initRadius3) : IziFish(InitX, InitY, InitIndex, initRadius1, initRadius2, InitX4, InitY4)
{
	Radius3 = initRadius3;
}//Cross()

//деструктор
Fish4::~Fish4()
{

}//~Fish4()

//показать линию
void Fish4::Show()
{
	IziFish::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, PenRed);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X - 3.5 * Radius2;
	poly[0].y = Y - Radius2;

	poly[1].x = X - 1.5 * Radius2;
	poly[1].y = Y + Radius2;

	//рисуем линию
	Polyline(hdc, poly, 2);


	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть линию
void Fish4::Hide()
{
	IziFish::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X - 3.5 * Radius2;
	poly[0].y = Y - Radius2;

	poly[1].x = X - 1.5 * Radius2;
	poly[1].y = Y + Radius2;

	//рисуем линию
	Polyline(hdc, poly, 2);


	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()



/*МЕТОДЫ КЛАССА SeaweedMin*/
//конструктор
SeaweedMin::SeaweedMin(int InitX, int InitY, int InitIndex, int InitX4, int InitY4) : Point2(InitX,  InitY,  InitIndex)
{
	X4 = InitX4;
	Y4 = InitY4;
}//SeaweedMin()

//деструктор
SeaweedMin::~SeaweedMin()
{

}//~SeaweedMin()

//показать линию
void SeaweedMin::Show()
{
	Point2::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	SelectObject(hdc, PenRed);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X ;
	poly[0].y = Y +Y4;

	poly[1].x = X -100 ;
	poly[1].y = Y ;

	//рисуем линию
	Polyline(hdc, poly, 2);

	POINT poly2[2];

	//координаты отрезков
	poly2[0].x = X ;
	poly2[0].y = Y + Y4;

	poly2[1].x = X ;
	poly2[1].y = Y ;

	//рисуем линию
	Polyline(hdc, poly2, 2);

	POINT poly3[2];

	//координаты отрезков
	poly3[0].x = X ;
	poly3[0].y = Y + Y4;

	poly3[1].x = X + 100 ;
	poly3[1].y = Y  ;

	//рисуем линию
	Polyline(hdc, poly3, 2);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть линию
void SeaweedMin::Hide()
{
	Point2::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X;
	poly[0].y = Y + Y4;

	poly[1].x = X - 100;
	poly[1].y = Y;

	//рисуем линию
	Polyline(hdc, poly, 2);

	POINT poly2[2];

	//координаты отрезков
	poly2[0].x = X;
	poly2[0].y = Y + Y4;

	poly2[1].x = X;
	poly2[1].y = Y;

	//рисуем линию
	Polyline(hdc, poly2, 2);

	POINT poly3[2];

	//координаты отрезков
	poly3[0].x = X;
	poly3[0].y = Y + Y4;

	poly3[1].x = X + 100;
	poly3[1].y = Y;


	//рисуем линию
	Polyline(hdc, poly3, 2);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()


/*МЕТОДЫ КЛАССА SeaweedMax*/
//конструктор
SeaweedMax::SeaweedMax(int InitX, int InitY, int InitIndex,int InitX4, int InitY4) : Point2(InitX, InitY,  InitIndex)
{
	X4 = InitX4;
	Y4 = InitY4;
}//SeaweedMax()

//деструктор
SeaweedMax::~SeaweedMax()
{

}//~SeaweedMax()

//показать линию
void SeaweedMax::Show()
{
	Point2::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(0,255,0));
	SelectObject(hdc, PenRed);

	POINT poly[2];

	//координаты отрезков
	poly[0].x = X ;
	poly[0].y = Y*1.5;

	poly[1].x = X /2 ;
	poly[1].y = Y  ;

	//рисуем линию
	Polyline(hdc, poly, 2);

	POINT poly2[2];

	//координаты отрезков
	poly2[0].x = X ;
	poly2[0].y = Y*1.5;

	poly2[1].x = X  ;
	poly2[1].y = Y;

	//рисуем линию
	Polyline(hdc, poly2, 2);

	POINT poly3[2];

	//координаты отрезков
	poly3[0].x = X ;
	poly3[0].y = Y*1.5;

	poly3[1].x = X *1.5 ;
	poly3[1].y = Y  ;

	//рисуем линию
	Polyline(hdc, poly3, 2);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть линию
void SeaweedMax::Hide()
{
	Point2::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);

	/*POINT poly[2];

	//координаты отрезков
	poly[0].x = X;
	poly[0].y = Y * 1.5;

	poly[1].x = X / 2;
	poly[1].y = Y;

	//рисуем линию
	Polyline(hdc, poly, 2);

	POINT poly2[2];

	//координаты отрезков
	poly2[0].x = X;
	poly2[0].y = Y * 1.5;

	poly2[1].x = X;
	poly2[1].y = Y;

	//рисуем линию
	Polyline(hdc, poly2, 2);*/

	POINT poly3[2];

	//координаты отрезков
	poly3[0].x = X;
	poly3[0].y = Y * 1.5;

	poly3[1].x = X * 1.5;
	poly3[1].y = Y;

	//рисуем линию
	Polyline(hdc, poly3, 2);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()


/* МЕТОДЫ КЛАССА  Air*/
//конструктор
Air::Air(int InitX, int InitY, int InitIndex,int InitRadius3) : Point2(InitX, InitY,  InitIndex)
{
	Radius3 = InitRadius3;
}//Air()

//деструктор
Air::~Air()
{
}//Air()

//показать круг
void  Air::Show()
{
	Point2::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
	SelectObject(hdc, PenRed);

	//рисуем круг установленным цветом
	Ellipse(hdc, X - Radius3+100, Y - Radius3, X+ Radius3+100, Y + Radius3);

	//рисуем круг установленным цветом
	Ellipse(hdc, 410, Y - Radius3-50, 430, Y + Radius3-50);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть круг
void  Air::Hide()
{
	Point2::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);

	//рисуем круг установленным цветом
	Ellipse(hdc, X - Radius3 + 100, Y - Radius3, X + Radius3 + 100, Y + Radius3);

	//рисуем круг установленным цветом
	Ellipse(hdc, 410, Y - Radius3 - 50, 430, Y + Radius3 - 50);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()




/* МЕТОДЫ КЛАССА  Air1*/
//конструктор
Air1::Air1(int InitX, int InitY, int InitIndex, int InitRadius3) : Point2(InitX, InitY, InitIndex)
{
	Radius3 = InitRadius3;
}//Air()

//деструктор
Air1::~Air1()
{
}//Air1()

//показать круг
void  Air1::Show()
{
	Point2::Show();
	Visible = true;

	//зададим перо и цвет пера
	HPEN PenRed = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
	SelectObject(hdc, PenRed);

	//рисуем круг установленным цветом
	Ellipse(hdc, X - Radius3 + 100, Y - Radius3, X + Radius3 + 100, Y + Radius3);

	//рисуем круг установленным цветом
	Ellipse(hdc, 410, Y - Radius3 - 50, 430, Y + Radius3 - 50);

	//уничтожим созданные объекты
	DeleteObject(PenRed);

}//Show()

//скрыть круг
void  Air1::Hide()
{
	Point2::Hide();
	Visible = false;

	//зададим перо и цвет пера
	HPEN PenBlue = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, PenBlue);

	//рисуем круг установленным цветом
	Ellipse(hdc, X - Radius3 + 100, Y - Radius3, X + Radius3 + 100, Y + Radius3);

	//рисуем круг установленным цветом
	Ellipse(hdc, 410, Y - Radius3 - 50, 430, Y + Radius3 - 50);

	//уничтожим созданные объекты
	DeleteObject(PenBlue);
}//Hide()


GetConlWin.h


#pragma once
HWND GetConcolWindow();