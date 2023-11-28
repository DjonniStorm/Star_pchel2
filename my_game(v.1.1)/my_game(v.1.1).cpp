﻿// my_game(v.1.1).cpp : Определяет точку входа для приложения.
//this is my game!!!!!!!!!
#include "stdafx.h"
#include "my_game(v.1.1).h"
#include <stdio.h>

#define MAX_LOADSTRING 100

RECT myWindow; //моё окно для закрашивания
int defaultWindowX = 1200; //дефолт
int defaultWindowY = 600;  //настройки
//разрешение экрана
int diff = 0;
int expansion_coefficient = 100;
int nowChange = 0;
//конец для разрешения
//
//для фоновых метеоритов
int spawn = 0;
int spawn_random_1 = rand() % 2;
//
//перс
int PlayerX = /*20*/ 20;
int PlayerY = /*220*/ 220;
int defaultPos = 2;
int PlayerHP = 2;
int PlayerWidth = 140;
int PlayerHeight = 170;
//
//массив отображения
#define VisA 3
#define VisB 3
int massivVis[VisA][VisB] = {
	{0, 0, 0}, //для видимости
	{0, 0, 0}, //
	{0, 0, 0} //
};

//массив для врагов и предметов
#define EnemyA 3
#define EnemyB 3
int massivEnemyX[EnemyA][EnemyB]{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};
int massivEnemyForY[EnemyA] = { 50, 250, 450 };
int EnemyMeteorWidth = 180;
int EnemyMeteorHeight = 100;
int massivEnemyY[EnemyA][EnemyB]{
	{50, 250, 450},
	{50, 250, 450},
	{50, 250, 450}
};
int EnemyHP[EnemyA][EnemyB]{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}   //пока не юзается
};
//
// 	
//поправь рандом в фуенкции спавна камней  
//глобальный таймер
int global_timer = 0;
int chest_spawn = 0;
int chest_width = 120;
int chest_height = 40;
//COLORREF chest_color = RGB(200, 0, 200);

//
int meteorScore = 0;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYGAMEV11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYGAMEV11));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = /*CS_HREDRAW | CS_VREDRAW | */CS_SAVEBITS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYGAMEV11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYGAMEV11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, defaultWindowX + 16, defaultWindowY + 59, nullptr, nullptr, hInstance, nullptr);
//
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//<LVL>
int forcheking = 0;

void drawLevel(HDC hdc) {
	if (myWindow.right > defaultWindowX || myWindow.bottom > defaultWindowY) {
		(myWindow.right - defaultWindowX > myWindow.bottom - defaultWindowY) ? (diff = myWindow.right - defaultWindowX) : (diff = myWindow.bottom - defaultWindowY);
		//PlayerY += diff / 10;
	}
	HBRUSH levelBrush = CreateSolidBrush(RGB(0, 0, 51));
	FillRect(hdc, &myWindow, levelBrush);
	DeleteObject(levelBrush);

	HBRUSH starBrush1, starBrush2, starBrush3;
	starBrush1 = CreateSolidBrush(RGB(255, 204, 255));
	starBrush2 = CreateSolidBrush(RGB(204, 204, 255));
	starBrush3 = CreateSolidBrush(RGB(255, 255, 153));
	SelectObject(hdc, starBrush1);
	//ковш
	Ellipse(hdc, 100 + diff / expansion_coefficient, 100 + diff / expansion_coefficient, 109 + diff / expansion_coefficient * 2, 109 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 150 + diff / expansion_coefficient, 300 + diff / expansion_coefficient, 159 + diff / expansion_coefficient * 2, 309 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  10 + diff / expansion_coefficient, 450 + diff / expansion_coefficient,  19 + diff / expansion_coefficient * 2, 459 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 120 + diff / expansion_coefficient, 500 + diff / expansion_coefficient, 129 + diff / expansion_coefficient * 2, 509 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 170 + diff / expansion_coefficient,  10 + diff / expansion_coefficient, 179 + diff / expansion_coefficient * 2,  19 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  70 + diff / expansion_coefficient, 200 + diff / expansion_coefficient,  79 + diff / expansion_coefficient * 2, 209 + diff / expansion_coefficient * 2);
	//лев

	Ellipse(hdc, 1000 + diff / expansion_coefficient, 250 + diff / expansion_coefficient, 1009 + diff / expansion_coefficient * 2, 259 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 1050 + diff / expansion_coefficient, 280 + diff / expansion_coefficient, 1059 + diff / expansion_coefficient * 2, 289 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  950 + diff / expansion_coefficient, 300 + diff / expansion_coefficient,  959 + diff / expansion_coefficient * 2, 309 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  940 + diff / expansion_coefficient, 320 + diff / expansion_coefficient,  949 + diff / expansion_coefficient * 2, 329 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  990 + diff / expansion_coefficient, 320 + diff / expansion_coefficient,  999 + diff / expansion_coefficient * 2, 329 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  986 + diff / expansion_coefficient, 350 + diff / expansion_coefficient,  995 + diff / expansion_coefficient * 2, 359 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  900 + diff / expansion_coefficient, 370 + diff / expansion_coefficient,  909 + diff / expansion_coefficient * 2, 379 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  820 + diff / expansion_coefficient, 390 + diff / expansion_coefficient,  829 + diff / expansion_coefficient * 2, 399 + diff / expansion_coefficient * 2);
	Ellipse(hdc,  880 + diff / expansion_coefficient, 320 + diff / expansion_coefficient,  889 + diff / expansion_coefficient * 2, 329 + diff / expansion_coefficient * 2);
	//         **
	//       *
	//  *    * *
	//*   *      *
	//рак
	SelectObject(hdc, starBrush2);
	Ellipse(hdc, 600 + diff / expansion_coefficient, 400 + diff / expansion_coefficient, 609 + diff / expansion_coefficient * 2, 409 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 610 + diff / expansion_coefficient, 460 + diff / expansion_coefficient, 619 + diff / expansion_coefficient * 2, 469 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 604 + diff / expansion_coefficient, 480 + diff / expansion_coefficient, 613 + diff / expansion_coefficient * 2, 489 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 530 + diff / expansion_coefficient, 500 + diff / expansion_coefficient, 539 + diff / expansion_coefficient * 2, 509 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 650 + diff / expansion_coefficient, 520 + diff / expansion_coefficient, 659 + diff / expansion_coefficient * 2, 529 + diff / expansion_coefficient * 2);

	//овен
	SelectObject(hdc, starBrush3);
	Ellipse(hdc, 700 + diff / expansion_coefficient, 100 + diff / expansion_coefficient, 709 + diff / expansion_coefficient * 2, 109 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 690 + diff / expansion_coefficient,  90 + diff / expansion_coefficient, 699 + diff / expansion_coefficient * 2,  99 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 670 + diff / expansion_coefficient, 110 + diff / expansion_coefficient, 679 + diff / expansion_coefficient * 2, 119 + diff / expansion_coefficient * 2);
	Ellipse(hdc, 630 + diff / expansion_coefficient, 150 + diff / expansion_coefficient, 639 + diff / expansion_coefficient * 2, 159 + diff / expansion_coefficient * 2);

	//
	/*HBRUSH levelBrush1, levelBrush2;
	levelBrush1 = CreateSolidBrush(RGB(0, 0, 51));
	levelBrush2 = CreateSolidBrush(RGB(255, 255, 153));
	*///HPEN levelpen1, levelpen2;
	//levelpen1 = CreatePen(PS_SOLID, 2, RGB(0, 0, 51));
	//levelpen2 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	//SelectObject(hdc, levelBrush2);
	////Rectangle(hdc, -2, -2, 1600, 820);
	//SelectObject(hdc, levelBrush1); SelectObject(hdc, levelpen1);
	////Rectangle(hdc, 4, 10, 1594, 810);
	//SelectObject(hdc, levelpen2);
	//MoveToEx(hdc, 4, 266, NULL);
	//LineTo(hdc, 1600, 266);
	//MoveToEx(hdc, 4, 532, NULL);
	//LineTo(hdc, 1600, 532);
	//MoveToEx(hdc, 1200, 0, NULL);
	//LineTo(hdc, 1200, 810);

	HBRUSH levelBrush3;
	levelBrush3 = CreateSolidBrush(RGB(255, 255, 153));
	HPEN levelpen3;
	levelpen3 = CreatePen(PS_SOLID, 2, RGB(255, 255, 153));
	SelectObject(hdc, levelBrush3); SelectObject(hdc, levelpen3);
	POINT starpoints1[11] = { 16 + diff / expansion_coefficient, 20 + diff / expansion_coefficient, 25 + diff / expansion_coefficient,
		25 + diff / expansion_coefficient, 30 + diff / expansion_coefficient, 15 + diff / expansion_coefficient, 35 + diff / expansion_coefficient, 
		25 + diff / expansion_coefficient, 44 + diff / expansion_coefficient, 20 + diff / expansion_coefficient, 37 + diff / expansion_coefficient, 
		30 + diff / expansion_coefficient, 40 + diff / expansion_coefficient, 40 + diff / expansion_coefficient, 30 + diff / expansion_coefficient, 
		32 + diff / expansion_coefficient, 20 + diff / expansion_coefficient, 40 + diff / expansion_coefficient, 23 + diff / expansion_coefficient, 
		30 + diff / expansion_coefficient, 16 + diff / expansion_coefficient, 20 + diff / expansion_coefficient },
		starpoints2[11] = { 516 + diff / expansion_coefficient, 120 + diff / expansion_coefficient, 525 + diff / expansion_coefficient, 
		125 + diff / expansion_coefficient, 530 + diff / expansion_coefficient, 115 + diff / expansion_coefficient, 535 + diff / expansion_coefficient,
		125 + diff / expansion_coefficient, 544 + diff / expansion_coefficient, 120 + diff / expansion_coefficient, 537 + diff / expansion_coefficient,
		130 + diff / expansion_coefficient, 540 + diff / expansion_coefficient, 140 + diff / expansion_coefficient, 530 + diff / expansion_coefficient,
		132 + diff / expansion_coefficient, 520 + diff / expansion_coefficient, 140 + diff / expansion_coefficient, 523 + diff / expansion_coefficient, 
		130 + diff / expansion_coefficient, 516 + diff / expansion_coefficient, 120 + diff / expansion_coefficient },
		starpoints3[11] = { 16 + diff / expansion_coefficient, 720 + diff / expansion_coefficient, 25 + diff / expansion_coefficient, 725 + diff / expansion_coefficient, 
		 30 + diff / expansion_coefficient, 715 + diff / expansion_coefficient,  35 + diff / expansion_coefficient, 725 + diff / expansion_coefficient,  44 + diff / expansion_coefficient,
		720 + diff / expansion_coefficient,  37 + diff / expansion_coefficient, 730 + diff / expansion_coefficient,  40 + diff / expansion_coefficient, 740 + diff / expansion_coefficient,
		 30 + diff / expansion_coefficient, 732 + diff / expansion_coefficient,  20 + diff / expansion_coefficient, 740 + diff / expansion_coefficient,  23 + diff / expansion_coefficient,
		730 + diff / expansion_coefficient,  16 + diff / expansion_coefficient, 720 + diff / expansion_coefficient };
	
	Polygon(hdc, starpoints1, 11);
	Polygon(hdc, starpoints2, 11);
	Polygon(hdc, starpoints3, 11);
	
	HBRUSH levelBrush4;
	levelBrush4 = CreateSolidBrush(RGB(255, 204, 153));
	HPEN levelpen4;
	levelpen4 = CreatePen(PS_SOLID, 2, RGB(255, 204, 153));
	POINT starpoints4[11] = { 36 + diff / expansion_coefficient, 320 + diff / expansion_coefficient, 45 + diff / expansion_coefficient, 325 + diff / expansion_coefficient, 
		 50 + diff / expansion_coefficient, 315 + diff / expansion_coefficient,  55 + diff / expansion_coefficient, 325 + diff / expansion_coefficient,  64 + diff / expansion_coefficient, 
		320 + diff / expansion_coefficient,  57 + diff / expansion_coefficient, 330 + diff / expansion_coefficient,  60 + diff / expansion_coefficient, 340 + diff / expansion_coefficient, 
		 50 + diff / expansion_coefficient, 332 + diff / expansion_coefficient,  40 + diff / expansion_coefficient, 340 + diff / expansion_coefficient,  43 + diff / expansion_coefficient,
		330 + diff / expansion_coefficient,  36 + diff / expansion_coefficient, 320 + diff / expansion_coefficient },
		starpoints5[11] = { 1016 + diff / expansion_coefficient, 80 + diff / expansion_coefficient, 1025 + diff / expansion_coefficient, 85 + diff / expansion_coefficient, 
		1030 + diff / expansion_coefficient,  75 + diff / expansion_coefficient, 1035 + diff / expansion_coefficient,   85 + diff / expansion_coefficient, 1044 + diff / expansion_coefficient, 
		 80 + diff / expansion_coefficient, 1037 + diff / expansion_coefficient,   90 + diff / expansion_coefficient, 1040 + diff / expansion_coefficient,  100 + diff / expansion_coefficient, 
		1030 + diff / expansion_coefficient,  92 + diff / expansion_coefficient, 1020 + diff / expansion_coefficient,  100 + diff / expansion_coefficient, 1023 + diff / expansion_coefficient, 
		 90 + diff / expansion_coefficient, 1016 + diff / expansion_coefficient,   80 + diff / expansion_coefficient },
		starpoints6[11] = { 1516 + diff / expansion_coefficient, 720 + diff / expansion_coefficient, 1525 + diff / expansion_coefficient, 725 + diff / expansion_coefficient, 
		1530 + diff / expansion_coefficient,  715 + diff / expansion_coefficient, 1535 + diff / expansion_coefficient,  725 + diff / expansion_coefficient, 1544 + diff / expansion_coefficient, 
		 720 + diff / expansion_coefficient, 1537 + diff / expansion_coefficient,  730 + diff / expansion_coefficient, 1540 + diff / expansion_coefficient,  740 + diff / expansion_coefficient, 
		1530 + diff / expansion_coefficient,  732 + diff / expansion_coefficient, 1520 + diff / expansion_coefficient,  740 + diff / expansion_coefficient, 1523 + diff / expansion_coefficient, 
		 730 + diff / expansion_coefficient, 1516 + diff / expansion_coefficient,  720 + diff / expansion_coefficient };
	SelectObject(hdc, levelBrush4); SelectObject(hdc, levelpen4);
	
	Polygon(hdc, starpoints4, 11);
	Polygon(hdc, starpoints5, 11);
	Polygon(hdc, starpoints6, 11);
	HBRUSH levelBrush5;
	levelBrush5 = CreateSolidBrush(RGB(153, 255, 255));
	HPEN levelpen5;
	levelpen5 = CreatePen(PS_SOLID, 2, RGB(153, 255, 255));
	POINT starpoints7[11] = { 536 + diff / expansion_coefficient, 620 + diff / expansion_coefficient, 545 + diff / expansion_coefficient, 625 + diff / expansion_coefficient, 550 + diff / expansion_coefficient, 
		615 + diff / expansion_coefficient, 555 + diff / expansion_coefficient, 625 + diff / expansion_coefficient, 564 + diff / expansion_coefficient, 620 + diff / expansion_coefficient,
		557 + diff / expansion_coefficient, 630 + diff / expansion_coefficient, 560 + diff / expansion_coefficient, 640 + diff / expansion_coefficient, 550 + diff / expansion_coefficient, 
		632 + diff / expansion_coefficient, 540 + diff / expansion_coefficient, 640 + diff / expansion_coefficient, 543 + diff / expansion_coefficient, 630 + diff / expansion_coefficient, 
		536 + diff / expansion_coefficient, 620 + diff / expansion_coefficient },
		starpoints8[11] = { 1436 + diff / expansion_coefficient, 270 + diff / expansion_coefficient, 1445 + diff / expansion_coefficient, 275 + diff / expansion_coefficient, 1450 + diff / expansion_coefficient, 
		 265 + diff / expansion_coefficient, 1455 + diff / expansion_coefficient,  275 + diff / expansion_coefficient, 1464 + diff / expansion_coefficient,  270 + diff / expansion_coefficient,
		1457 + diff / expansion_coefficient,  280 + diff / expansion_coefficient, 1460 + diff / expansion_coefficient,  290 + diff / expansion_coefficient, 1450 + diff / expansion_coefficient,
		 282 + diff / expansion_coefficient, 1440 + diff / expansion_coefficient,  290 + diff / expansion_coefficient, 1443 + diff / expansion_coefficient,  280 + diff / expansion_coefficient, 
		1436 + diff / expansion_coefficient,  270 + diff / expansion_coefficient },
		starpoints9[11] = { 836 + diff / expansion_coefficient, 420 + diff / expansion_coefficient, 845 + diff / expansion_coefficient, 425 + diff / expansion_coefficient, 850 + diff / expansion_coefficient, 
		415 + diff / expansion_coefficient, 855 + diff / expansion_coefficient, 425 + diff / expansion_coefficient, 864 + diff / expansion_coefficient, 420 + diff / expansion_coefficient, 857 + diff / expansion_coefficient,
		430 + diff / expansion_coefficient, 860 + diff / expansion_coefficient, 440 + diff / expansion_coefficient, 850 + diff / expansion_coefficient, 432 + diff / expansion_coefficient, 840 + diff / expansion_coefficient, 
		440 + diff / expansion_coefficient, 843 + diff / expansion_coefficient, 430 + diff / expansion_coefficient, 836 + diff / expansion_coefficient, 420 + diff / expansion_coefficient };
	SelectObject(hdc, levelBrush5); SelectObject(hdc, levelpen5);
	Polygon(hdc, starpoints7, 11);
	Polygon(hdc, starpoints8, 11);
	Polygon(hdc, starpoints9, 11);
	HPEN starpen1;
	starpen1 = CreatePen(PS_SOLID, 7, RGB(255, 255, 255));
	MoveToEx(hdc, 400, 400, NULL);
	LineTo(hdc, 400, 400);
	MoveToEx(hdc, 800, 200, NULL);
	LineTo(hdc, 800, 200);
	MoveToEx(hdc, 100, 900, NULL);
	LineTo(hdc, 100, 900);
	MoveToEx(hdc, 1300, 800, NULL);
	LineTo(hdc, 1300, 800);
	MoveToEx(hdc, 1100, 700, NULL);
	LineTo(hdc, 1100, 700);



	DeleteObject(starBrush1); DeleteObject(starBrush2);
	DeleteObject(starBrush3); //DeleteObject(levelBrush);

/*
	DeleteObject(levelBrush1); DeleteObject(levelBrush2);
	DeleteObject(levelpen1); DeleteObject(levelpen2);*/
	DeleteObject(levelBrush3); DeleteObject(levelBrush4); DeleteObject(levelBrush5);
	DeleteObject(levelpen3); DeleteObject(levelpen4); DeleteObject(levelpen5);
	DeleteObject(starpen1); DeleteObject(starpoints1); DeleteObject(starpoints2);
	DeleteObject(starpoints3); DeleteObject(starpoints4); DeleteObject(starpoints5);
	DeleteObject(starpoints6); DeleteObject(starpoints7); DeleteObject(starpoints8);
	DeleteObject(starpoints9);

}
//метеориты которые на фоне летают
void drawLevelMeteor(HDC hdc, int cx, int cy) {
	HPEN levelmeteorpen = CreatePen(PS_SOLID, 5, RGB(192, 192, 192));
	SelectObject(hdc, levelmeteorpen);

	MoveToEx(hdc, 20 + diff / expansion_coefficient + cx, 0 + diff / expansion_coefficient + cy, NULL);
	LineTo(hdc, 90 + diff / expansion_coefficient + cx, 20 + diff / expansion_coefficient + cy);
	LineTo(hdc, 70 + diff / expansion_coefficient + cx, 60 + diff / expansion_coefficient + cy);
	LineTo(hdc, 30 + diff / expansion_coefficient + cx, 40 + diff / expansion_coefficient + cy);
	LineTo(hdc,  0 + diff / expansion_coefficient + cx, 20 + diff / expansion_coefficient + cy);
	LineTo(hdc, 20 + diff / expansion_coefficient + cx,  0 + diff / expansion_coefficient + cy);
	DeleteObject(levelmeteorpen);
}
struct levelmeteor {
	int levelmeteorX;
	int LevelmeteorY;
};

struct levelmeteor meteor1 = { rand() % 1300, myWindow.top - 100 };
struct levelmeteor meteor2 = { rand() % 1300, myWindow.bottom + 810};

//</LVL>
//<Character>
void drawTIE(HDC hdc, int cx, int cy) { //типа СИД на англ.
	HBRUSH characterBrush1, characterBrush2, characterBrush3;
	characterBrush1 = CreateSolidBrush(RGB(131, 135, 138));
	characterBrush2 = CreateSolidBrush(RGB(86, 86, 86));
	characterBrush3 = CreateSolidBrush(RGB(10, 10, 10));
	HPEN characterpen1, characterpen2;
	characterpen1 = CreatePen(PS_SOLID, 1, RGB(13, 13, 13));
	characterpen2 = CreatePen(PS_SOLID, 2, RGB(71, 78, 82));
	//
	SelectObject(hdc, characterBrush3); SelectObject(hdc, characterpen2);
	//пушки
	Rectangle(hdc, 100 + cx + diff / 10, 60 + cy + diff / 10, 120 + cx + diff / 8, 70 + cy + diff / 8);
	Rectangle(hdc, 100 + cx + diff / 10, 100 + cy + diff / 8, 120 + cx + diff / 8, 110 + cy + diff / 7);
	//переднее стекло
	Ellipse(hdc, 30 + cx + diff / 9, 52 + cy + diff / 9, 116 + cx + diff / 8, 118 + cy + diff / 8);
	//корпус
	SelectObject(hdc, characterpen1); 
	SelectObject(hdc, characterBrush1); 
	
	Rectangle(hdc, 60 + cx + diff / 10, 0 + cy + diff / 10, 80 + cx + diff / 9, 170 + cy + diff / 9);

	Rectangle(hdc, 0 + cx + diff / 10, 0 + cy + diff / 10, 140 + cx + diff / 9, 12 + cy + diff / 9);
	Rectangle(hdc, 0 + cx + diff / 10, 158 + cy + diff / 9, 140 + cx + diff / 9, 170 + cy + diff / 8);
	Ellipse(hdc, 30 + cx + diff / 9, 50 + cy + diff / 9, 110 + cx + diff / 8, 120 + cy + diff / 8);
	//люк (не Скайуокер!)
	SelectObject(hdc, characterBrush2);
	Ellipse(hdc, 35 + cx + diff / 9, 55 + cy + diff / 9, 105 + cx + diff / 8, 115 + cy + diff / 8);
	SelectObject(hdc, characterBrush3);
	Ellipse(hdc, 54 + cx + diff / 9, 70 + cy + diff / 9, 86 + cx + diff / 8, 100 + cy + diff / 8);

	DeleteObject(characterBrush1); DeleteObject(characterBrush2); DeleteObject(characterBrush3);
	DeleteObject(characterpen1); DeleteObject(characterpen2); //DeleteObject();
}



//</Character>
//<Enemy & Co.>

void drawEnemyMeteor1(HDC hdc, int cx, int cy) {
	HBRUSH enemyMeteorBrush1;
	enemyMeteorBrush1 = CreateSolidBrush(RGB(89, 101, 107));
	HPEN enemyMeteorpen1;
	enemyMeteorpen1 = CreatePen(PS_SOLID, 2, RGB(49, 52, 54));
	SelectObject(hdc, enemyMeteorBrush1); SelectObject(hdc, enemyMeteorpen1);
	Ellipse(hdc, 0 + cx, 0 + cy, 180 + cx, 100 + cy);
	Ellipse(hdc, 20 + cx, 20 + cy, 50 + cx, 50 + cy);
	Ellipse(hdc, 30 + cx, 70 + cy, 45 + cx, 85 + cy);
	Ellipse(hdc, 70 + cx, 30 + cy, 98 + cx, 62 + cy);
	Ellipse(hdc, 130 + cx, 50 + cy, 160 + cx, 80 + cy);
	DeleteObject(enemyMeteorBrush1); DeleteObject(enemyMeteorpen1);
}
void spawEnemies() {
	int randomspawnY = rand() % 3; //для колличества на строке
	int random_line = rand() % 2 + 1;  //для начала цикла с определённой линии
	int randomK = rand() % 3;      //для рандомного Y
	int randomK2 = rand() % 3;
	if (randomK == randomK2) {
		randomK2 = rand() % 3;
	}
	int random_for_chest = rand() % 9 + 1;
	for (int i = 0; i < random_line; i++) {
		for (int j = 0; j < VisB; j = VisB) {
			switch (randomspawnY)
			{
			case 0:
				if (massivVis[i][j] == 0) {
					if (random_for_chest != 0 && chest_spawn == 1) {//!!!!!
						massivVis[i][j] = 2; massivEnemyY[i][j] = massivEnemyForY[randomK];  massivEnemyX[i][j] = myWindow.right;
						break;
					}
					massivVis[i][j] = 1; massivEnemyY[i][j] = massivEnemyForY[randomK]; massivEnemyX[i][j] = myWindow.right;
					EnemyHP[i][j] = 2;
				}
				break;
			case 1:
				if (massivVis[i][j] == 0) {
					if (massivVis[i][j + 1] == 0) {
						massivVis[i][j] = 1; EnemyHP[i][j] = 2; massivEnemyY[i][j] = massivEnemyForY[randomK]; massivEnemyX[i][j] = myWindow.right;
						massivVis[i][j + 1] = 1; EnemyHP[i][j + 1] = 2; massivEnemyY[i][j + j] = massivEnemyForY[randomK]; massivEnemyX[i][j + 1] = myWindow.right + 200;
					}
				}
				break;
			case 2:
				if (massivVis[i][j] == 0) {
					if (massivVis[i][j + 1] == 0) {
						massivVis[i][j] = 1; EnemyHP[i][j] = 2; massivEnemyY[i][j] = massivEnemyForY[randomK]; massivEnemyX[i][j] = myWindow.right;
						massivVis[i][j + 1] = 1; EnemyHP[i][j + 1] = 2; massivEnemyY[i][j + 1] = massivEnemyForY[randomK]; massivEnemyX[i][j + 1] = myWindow.right + 200;
						massivVis[i][j + 2] = 1; EnemyHP[i][j + 2] = 2; massivEnemyY[i][j + 2] = massivEnemyForY[randomK]; massivEnemyX[i][j + 2] = myWindow.right + 400;
					}
				}
				break;
			}

		}
		randomK = randomK2;
	}


}
void moveEnemies() { //временно не работает
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] != 0) {
				massivEnemyX[i][j] -= 30;
				if (massivEnemyX[i][j] <= myWindow.left) {
					massivVis[i][j] = 0;
					massivEnemyX[i][j] = myWindow.right;
				}
			}

		}

	}
}
void drawEnemies(HDC hdc) {
	

	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 1) {
				drawEnemyMeteor1(hdc, massivEnemyX[i][j], massivEnemyY[i][j]);

			}
			
		}
	}
}
//& co.
void drawChest(HDC hdc, int cx, int cy/*, COLORREF color*/) {
	HBRUSH chestBrush1, chestBrush2, chestBrush3, chestBrush4;
	chestBrush1 = CreateSolidBrush(RGB(96, 96, 96));
	chestBrush2 = CreateSolidBrush(RGB(192, 192, 192));
	chestBrush3 = CreateSolidBrush(RGB(64, 64, 64));
	chestBrush4 = CreateSolidBrush(RGB(40, 40, 160));
	HPEN chestpen1, chestpen2;
	chestpen1 = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
	chestpen2 = CreatePen(PS_SOLID, 1, RGB(40, 40, 40));

	SelectObject(hdc, chestBrush1); SelectObject(hdc, chestpen1);
	Rectangle(hdc, 0 + cx, 0 + cy, 120 + cx, 100 + cy);
	SelectObject(hdc, chestBrush2);
	Rectangle(hdc, 0 + cx, 30 + cy, 120 + cx, 50 + cy);
	Rectangle(hdc, 0 + cx, 20 + cy, 20 + cx, 100 + cy);
	Rectangle(hdc, 100 + cx, 20 + cy, 120 + cx, 100 + cy);
	SelectObject(hdc, chestBrush3);
	Rectangle(hdc, 20 + cx, 50 + cy, 100 + cx, 100 + cy);
	SelectObject(hdc, chestpen2);
	Rectangle(hdc, 20 + cx, 10 + cy, 100 + cx, 30 + cy);
	Rectangle(hdc, 30 + cx, 80 + cy, 90 + cx, 90 + cy);
	SelectObject(hdc, chestBrush4);
	Rectangle(hdc, 40 + cx, 12 + cy, 50 + cx, 28 + cy);
	Rectangle(hdc, 55 + cx, 14 + cy, 65 + cx, 26 + cy);
	Rectangle(hdc, 70 + cx, 12 + cy, 80 + cx, 28 + cy);

	DeleteObject(chestBrush1); DeleteObject(chestBrush2); DeleteObject(chestBrush3); DeleteObject(chestBrush4);
	DeleteObject(chestpen1); DeleteObject(chestpen2);
}
void chests(HDC hdc) {
	//COLORREF color;
	//color = chest_color;
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 2) {
				/*if (justyes[i][j] == 1) {
					color = RGB(0, 255, 0);
				}*/
				drawChest(hdc, massivEnemyX[i][j], massivEnemyY[i][j]/*, color*/);
			}
		}
	}
}
void drawDroid(HDC hdc, int cx, int cy) {
	HBRUSH droidBrush1, droidBrush2, droidBrush3, droidBrush4/*, droidBrush5*/;
	droidBrush1 = CreateSolidBrush(RGB(250, 250, 250)); //белый
	droidBrush2 = CreateSolidBrush(RGB(139, 141, 165)); //серебристый
	droidBrush3 = CreateSolidBrush(RGB(15, 19, 86)); //синий 
	droidBrush4 = CreateSolidBrush(RGB(0, 0, 0)); //чёрный для "глаз"

	HPEN droidpen1, droidpen2, droidpen3, droidpen4;
	droidpen1 = CreatePen(PS_SOLID, 1, RGB(/*250*/ 0, /*250*/ 0, /*250*/ 0));
	droidpen2 = CreatePen(PS_SOLID, 1, RGB(90, 90, 90));
	droidpen3 = CreatePen(PS_SOLID, 3, RGB(15, 19, 86));
	droidpen4 = CreatePen(PS_SOLID, 3, RGB(85, 85, 90));
	SelectObject(hdc, droidBrush1); SelectObject(hdc, droidpen1);
	//telo
	POINT telo[5] = { 70 + cx, 20 + cy, 125 + cx, 30 + cy,/* */85 + cx, 90 + cy, 30 + cx, 73 + cy,/* */ 70 + cx, 20 + cy }; //просто тело
	Polygon(hdc, telo, 5);

	POINT telo2[5] = { 30 + cx, 73 + cy, 32 + cx, 77 + cy, 83 + cx, 93 + cy, 85 + cx, 90 + cy, 30 + cx, 73 + cy };
	Polygon(hdc, telo2, 5);

	Chord(hdc, 70 + cx, 40 + cy, 100 + cx, 60 + cy, 100 + cx, 50 + cy, 70 + cx, 50 + cy);                         //начало ноги или как её
	Rectangle(hdc, 70 + cx, 48 + cy, 100 + cx, 62 + cy);                                      //
	Rectangle(hdc, 75 + cx, 50 + cy, 95 + cx, 100 + cy);
	POINT t[5] = { 68 + cx, 110 + cy, 75 + cx, 100 + cy, 95 + cx, 100 + cy, 100 + cx, 110 + cy, 68 + cx, 110 + cy };
	Polygon(hdc, t, 5);


	POINT t2[7] = { 44 + cx, 82 + cy,
		40 + cx, 88 + cy,
		42 + cx, 90 + cy,
		40 + cx, 94 + cy,
		56 + cx, 98 + cy,
		62 + cx, 87 + cy,
		44 + cx, 82 + cy
	};
	Polygon(hdc, t2, 7);
	POINT t3s[9] = { 40 + cx, 94 + cy,
		54 + cx, 97 + cy,
		52 + cx, 99 + cy,
		54 + cx, 100 + cy,
		60 + cx, 110 + cy,
		30 + cx, 110 + cy,
		36 + cx, 99 + cy,
		40 + cx, 99 + cy,
		40 + cx, 94 + cy
	};
	Polygon(hdc, t3s, 9);

	//
	SelectObject(hdc, droidBrush2);//серебристый
	Chord(hdc, 65 + cx, 10 + cy, 126 + cx, 50 + cy, 144 + cx, 56 + cy, 65 + cx, 23 + cy);
	//Ellipse(hdc, 85, 20, 95, 30);
	//
				//
	SelectObject(hdc, droidBrush3);//синий
	Rectangle(hdc, 80 + cx, 55 + cy, 90 + cx, 100 + cy);

	Chord(hdc, 65 + cx, 10 + cy, 126 + cx, 50 + cy, 85 + cx, 16 + cy, 50 + cx, 20 + cy);
	Chord(hdc, 65 + cx, 10 + cy, 126 + cx, 50 + cy, 120 + cx, 25 + cy, 78 + cx, 0 + cy);
	POINT eye[5] = { 67 + cx, 20 + cy, 80 + cx, 25 + cy, 89 + cx, 16 + cy, 78 + cx, 12 + cy, 67 + cx, 20 + cy };
	Polygon(hdc, eye, 5);
	//синие полоски
	SelectObject(hdc, droidpen3); //синяя ручка
	MoveToEx(hdc, 66 + cx, 24 + cy, NULL);
	LineTo(hdc, 75 + cx, 27 + cy);
	MoveToEx(hdc, 62 + cx, 30 + cy, NULL);
	LineTo(hdc, 71 + cx, 32 + cy);
	MoveToEx(hdc, 57 + cx, 37 + cy, NULL);
	LineTo(hdc, 66 + cx, 40 + cy);


	//
	SelectObject(hdc, droidBrush4);//черный
	SelectObject(hdc, droidpen2);
	Ellipse(hdc, 74 + cx, 14 + cy, 83 + cx, 23 + cy);
	//


	HPEN pen;
	pen = CreatePen(PS_SOLID, 2, RGB(228, 228, 232));
	SelectObject(hdc, pen);
	Ellipse(hdc, 80 + cx, 24 + cy, 82 + cx, 26 + cy);

	DeleteObject(droidBrush1); DeleteObject(droidBrush2); DeleteObject(droidBrush3); DeleteObject(droidBrush4);
	//DeleteObject(droidBrush5); //вроде все кисти
		DeleteObject(droidpen1); DeleteObject(droidpen2); DeleteObject(droidpen3); DeleteObject(droidpen4); 
		DeleteObject(pen);
}
int animtion_time = 25;
int help_me = 0;
int animation_key = 0;
int droidposX = (defaultWindowX + diff) / 2 - 100;
int droidposY = (defaultWindowY + diff) / 4;
void drawDroidAnimation(HDC hdc) {
	int random_item = rand() % 2;
	if (animation_key == 1) {
		drawDroid(hdc, droidposX, droidposY);
	}
}
void checkCrash() {
	for (int i = 0; i < EnemyA; i++) {
		for (int j = 0; j < EnemyB; j++) {
			if (massivVis[i][j] == 1) {
				if (PlayerX + PlayerWidth >= massivEnemyX[i][j] && PlayerX <= massivEnemyX[i][j] + EnemyMeteorWidth &&
					PlayerY + PlayerHeight >= massivEnemyY[i][j] && PlayerY <= massivEnemyY[i][j] + EnemyMeteorHeight) {
					PlayerHP--;
					return;
				}
			}
		}
	}
}
//</Enemy & Co.>
//<shooter>
struct laser {
	int laser1X;
	int laser1Y;
};
struct laser fire1 = { PlayerX + 120, PlayerY + 60 };

struct laser fire2 = { PlayerX + 120, PlayerY + 60 };

struct laser fire3 = { PlayerX + 120, PlayerY + 60 };

int laserstruct[3] = { 0, 0, 0 };

void firetop(HDC hdc) {
	HBRUSH laserBrush1;
	laserBrush1 = CreateSolidBrush(RGB(200, 0, 0));
	HPEN laserpen1;
	laserpen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, laserBrush1); SelectObject(hdc, laserpen1);
	if (laserstruct[0] == 1) {
		Rectangle(hdc, fire1.laser1X, fire1.laser1Y, fire1.laser1X + 50, fire1.laser1Y + 10);
		Rectangle(hdc, fire1.laser1X, fire1.laser1Y + 40, fire1.laser1X + 50, fire1.laser1Y + 50);
	}
	if (laserstruct[1] == 1) {
		Rectangle(hdc, fire2.laser1X, fire2.laser1Y, fire2.laser1X + 50, fire2.laser1Y + 10);
		Rectangle(hdc, fire2.laser1X, fire2.laser1Y + 40, fire2.laser1X + 50, fire2.laser1Y + 50);
	}
	if (laserstruct[2] == 1) {
		Rectangle(hdc, fire3.laser1X, fire3.laser1Y, fire3.laser1X + 50, fire3.laser1Y + 10);
		Rectangle(hdc, fire3.laser1X, fire3.laser1Y + 40, fire3.laser1X + 50, fire3.laser1Y + 50);
	}
	DeleteObject(laserBrush1); DeleteObject(laserpen1);
}


void shooting() {
	for (int i = 0; i < 3; i++) {
		if (laserstruct[i] == 0) {
			laserstruct[i] = 1;
			switch (i) {
			case 0:
				fire1.laser1Y = PlayerY + 60;
				break;
			case 1:
				fire2.laser1Y = PlayerY + 60;
				break;
			case 2:
				fire3.laser1Y = PlayerY + 60;
				break;
			}
			return;
		}
	}
}
void shoot() {
	for (int i = 0; i < 3; i++) {
		if (laserstruct[i] == 1) {
			switch (i) {
			case 0:
				fire1.laser1X += 50;
				if (fire1.laser1X > 1200) {
					fire1.laser1X = PlayerX + 110;
					laserstruct[i] = 0;
				}
				break;
			case 1:
				fire2.laser1X += 50;
				if (fire2.laser1X > 1200) {
					fire2.laser1X = PlayerX + 110;
					laserstruct[i] = 0;
				}
				break;
			case 2:
				fire3.laser1X += 50;
				if (fire3.laser1X > 1200) {
					fire3.laser1X = PlayerX + 110;
					laserstruct[i] = 0;
				}

				break;
			}

		}
	}

}
void checkShoot1() {
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 1 && laserstruct[0]) {
				if (fire1.laser1X + 50 >= massivEnemyX[i][j] && fire1.laser1X <= massivEnemyX[i][j] + EnemyMeteorWidth &&
					fire1.laser1Y + 10 >= massivEnemyY[i][j] && fire1.laser1Y <= massivEnemyY[i][j] + EnemyMeteorHeight) {
					massivVis[i][j] = 0;
					laserstruct[0] = 0;
					fire1.laser1X = PlayerX + 100;
				}
			}
		}
	}
}
void checkShoot2() {
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 1 && laserstruct[0]) {
				if (fire2.laser1X + 50 >= massivEnemyX[i][j] && fire2.laser1X <= massivEnemyX[i][j] + EnemyMeteorWidth &&
					fire2.laser1Y + 10 >= massivEnemyY[i][j] && fire2 .laser1Y <= massivEnemyY[i][j] + EnemyMeteorHeight) {
					massivVis[i][j] = 0;
					laserstruct[0] = 0;
					fire2.laser1X = PlayerX + 100;
				}
			}
		}
	}
}
void checkShoot3() {
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 1 && laserstruct[0]) {
				if (fire3.laser1X + 50 >= massivEnemyX[i][j] && fire3.laser1X <= massivEnemyX[i][j] + EnemyMeteorWidth &&
					fire3.laser1Y + 10 >= massivEnemyY[i][j] && fire3.laser1Y <= massivEnemyY[i][j] + EnemyMeteorHeight) {
					massivVis[i][j] = 0;
					laserstruct[0] = 0;
					fire3.laser1X = PlayerX + 100;
				}
			}
		}
	}
}
int checkChest1() {
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 2) {
				//if (rect1.x + rect1.width >= rect2.x && rect1.x <= rect2.x + rect2.width &&
	//				//	rect1.y + rect1.height >= rect2.y && rect1.y <= rect2.y + rect2.height)
				if (PlayerX + PlayerWidth >= massivEnemyX[i][j] && PlayerX <= massivEnemyX[i][j] + chest_width &&
					PlayerY + PlayerHeight >= massivEnemyY[i][j] && PlayerY <= massivEnemyY[i][j] + chest_height) {
					massivVis[i][j] = 0;
					PlayerHP--;
					animation_key = 1;
					return 1;
					
				}
			}
		}
	}
	return 0;
}
int checkChest2() {
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 2) {
				if (fire1.laser1X + 50 >= massivEnemyX[i][j] && fire1.laser1X <= massivEnemyX[i][j] + chest_width &&
					fire1.laser1Y + 20 >= massivEnemyY[i][j] && fire1.laser1Y <= massivEnemyY[i][j] + chest_height) {
					animation_key = 1;
					return 1;
				}
			}
		}
	}
	return 0;
}
int checkChest3() {
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 2) {
				if (fire2.laser1X + 50 >= massivEnemyX[i][j] && fire2.laser1X <= massivEnemyX[i][j] + chest_width &&
					fire2.laser1Y + 20 >= massivEnemyY[i][j] && fire2.laser1Y <= massivEnemyY[i][j] + chest_height) {
					animation_key = 1;
					return 1;
				}
			}
		}
	}
	return 0;
}
int checkChest4() {
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisB; j++) {
			if (massivVis[i][j] == 2) {
				if (fire3.laser1X + 50 >= massivEnemyX[i][j] && fire3.laser1X <= massivEnemyX[i][j] + chest_width &&
					fire3.laser1Y + 20 >= massivEnemyY[i][j] && fire3.laser1Y <= massivEnemyY[i][j] + chest_height) {
					animation_key = 1;
					return 1;		
				}
			}
		}
	}
	return 0;
}
//</shooter>
//<other>
void save() {
	FILE * fout = fopen("D:\\програмки\\my_game.txt", "wt");
	if (fout == NULL) { return; }
	fprintf(fout, "%d ", PlayerX); fprintf(fout, "%d ", PlayerX); //всё о Player
	fprintf(fout, "%d ", PlayerHP); fprintf(fout, "\n"); //точно всё о Player
	//massivVis
	for (int i = 0; i < VisA; i++) {
		for (int j = 0; j < VisA; j++) {
			fprintf(fout, "%d ", massivVis[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
	for (int i = 0; i < EnemyA; i++) {
		for (int j = 0; j < EnemyB; j++) {
			fprintf(fout, "%d ", massivEnemyX[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
	for (int i = 0; i < EnemyA; i++) {
		for (int j = 0; j < EnemyB; j++) {
			fprintf(fout, "%d ", massivEnemyY[i][j]);
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "%d", global_timer);
	fclose(fout);
}

//</other>
//<status>
void drawStatus(HDC hdc) {

}
//</status>
//void drawStatus(HDC hdc) {
//	HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
//		DEFAULT_CHARSET, 0, 0, 0, 0, L"Courier New");
//	SelectObject(hdc, hFont);
//	SetTextColor(hdc, RGB(0, 0, 128));
//	char str[180];
//	sprintf_s(str, "x0 = %d, y0 = %d, x1 = %d, y1 = %d", /* x0, y0, x1, y1*/);
//	TCHAR strT[180];
//	OemToCharBuff(str, strT, 180);
//	TextOut(hdc, 0, 0, (LPCWSTR)strT, _tcslen(strT));
//
//	DeleteObject(hFont);
//}
//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GetClientRect(hWnd, &myWindow);
	if (global_timer >= 20) {
		chest_spawn = 1;
	}
	int timer1 = 50;
//BITMAP bit;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		SetTimer(hWnd, 0, 10000, NULL); //для метеоритов на уровне
		SetTimer(hWnd, 1, 50, NULL);    //для движения "уровневых" метеоритов
		SetTimer(hWnd, 2, 20, NULL);  //для честно пока хз чего
		SetTimer(hWnd, 3, 400, NULL);  //
		//SetTimer(hWnd, 4, 1000, NULL);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			spawn = 1;
			spawn_random_1 = rand() % 2;
			global_timer += 10;//timer1 -= 10;
			break;
		case 1:
			if (spawn == 1) {
				if (spawn_random_1 == 0) {
					meteor1.LevelmeteorY += 30;
					InvalidateRect(hWnd, NULL, TRUE);
					if (meteor1.LevelmeteorY >= myWindow.bottom + 100) {
						spawn = 0;
						meteor1.LevelmeteorY = myWindow.top - 100;
					}
				}
				else {
					meteor2.LevelmeteorY -= 30;
					InvalidateRect(hWnd, NULL, TRUE);
					if (meteor2.LevelmeteorY <= myWindow.top - 100) {
						spawn = 0;
						meteor2.LevelmeteorY = myWindow.bottom + 100;
					}
				}
			}

			shoot();
			
			
			
			break;

		case 2:
			for (int i = 0; i < VisA; i++) {
				for (int j = 0; j < VisB; j++) {
					if (massivVis[i][j] != 0) {
						massivEnemyX[i][j] -= 30;
						InvalidateRect(hWnd, NULL, TRUE);
						if (massivEnemyX[i][j] <= myWindow.left) {
							massivVis[i][j] = 0;
							massivEnemyX[i][j] = myWindow.right;
						}
					}

				}

			}
			//это всё нужно)
			checkShoot1();
			checkShoot2(); 
			checkShoot3();
			checkChest1();
			checkChest2();
			checkChest3();
			checkChest4();

			//ValidateRect(hWnd, myrect);
			break;
		case 3:
			if (animation_key == 1) {
				if (droidposY < defaultWindowY - 200) {
					animation_key = 0;
					droidposY = (defaultWindowY + diff) / 4;
				}
				droidposY += 5;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			spawEnemies();
			checkCrash();
			break;
		}
		
		break;
		
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (PlayerX <= 20) 
				break;
			PlayerX -= 30 /*+ diff / 2*/;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_RIGHT:
			if (PlayerX >= 1200)
				break;
			PlayerX += 30 /*+ diff / 2*/;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_UP:
			if (defaultPos <= 1)
				break;
			PlayerY -= 200 + diff / 10;
			InvalidateRect(hWnd, NULL, TRUE);
			defaultPos--;
			break;
		case VK_DOWN:
			if (defaultPos >= 3)
				break;
			PlayerY += 200 + diff / 10;
			InvalidateRect(hWnd, NULL, TRUE);
			defaultPos++;
			break;
		case VK_SPACE:
			shooting();
			break;
		case 0x58:
			save();
			break;
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
			//GetClientRect(hWnd, &myWindow);

			//drawStatus(hdc);
			drawLevel(hdc);
			drawLevelMeteor(hdc, meteor1.levelmeteorX, meteor1.LevelmeteorY);
			drawLevelMeteor(hdc, meteor2.levelmeteorX, meteor2.LevelmeteorY);

			HFONT hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0,
				DEFAULT_CHARSET, 0, 0, 0, 0, L"Courier New");
			SelectObject(hdc, hFont);
			SetTextColor(hdc, RGB(0, 0, 128));
			char str[180];
			sprintf_s(str, "HP = %d ", PlayerHP);
			TCHAR strT[180];
			OemToCharBuff(str, strT, 180);
			TextOut(hdc, 0, 0, (LPCWSTR)strT, _tcslen(strT));
			DeleteObject(hFont);
			
			firetop(hdc);
			drawTIE(hdc, PlayerX, PlayerY);
			//drawChest(hdc, 0, 0, RGB(153, 204, 255));
			//drawEnemies(hdc);
			for (int i = 0; i < VisA; i++) {
				for (int j = 0; j < VisB; j++) {
					if (massivVis[i][j] == 1) {
						drawEnemyMeteor1(hdc, massivEnemyX[i][j], massivEnemyY[i][j]);
					}
				}
			}
			//drawChest(hdc, 0, 0, RGB(0, 0, 255));
			chests(hdc);
			////drawDroid(hdc, 100, 100);
			//if (checkChest4() == 1 || checkChest3() == 1 || checkChest2() == 1 || checkChest1() == 1) {
			//	help_me = global_timer;
			//	while (help_me + animtion_time < global_timer) {
			//		drawDroidAnimation(hdc);
			//	}
			//}			
			drawDroidAnimation(hdc);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
