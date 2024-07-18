// WindowsProject1.cpp : Определяет точку входа для приложения.
//
#include <iostream>
#include "framework.h"
#include "WindowsProject1.h"
#include <vector>
#define MAX_LOADSTRING 100

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
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

struct point { double x, y, z; };

void onPaint(HDC hdc, LONG width, LONG height) {

    MoveToEx(hdc, 50, 250, 0);
    LineTo(hdc, width - 50, 250); // система координат с центром в точке (500, 250)
    MoveToEx(hdc, 500, 50, 0);
    LineTo(hdc, 500, height - 50);

    double r = 200;
    double x1, y1, z1;

    double xi, yi;
    double xi1, yi1;
    const double PI = 3.141592653589793;

    int num = 300;
    double h = PI / num;

    std::vector <point> points;
    point Point;

    for (double phi = 0;phi < 2 * PI;phi += 2*h) {
        for (double teta = 0; teta < PI;teta += h) {

            Point.x = r * cos(phi) * sin(teta);
            Point.y = r * sin(phi) * sin(teta);
            Point.z = r * cos(teta);
            double y = Point.y;
            Point.y = Point.y * cos(PI / 2) + Point.z * sin(PI / 2);
            Point.z = y * sin(PI / 2) + Point.z * cos(PI / 2);
            /*x'=x*cos(L)+z*sin(L);
                y'=y;
                z'=-x*sin(L)+z*cos(L);*/              // нужно преобразовать на следующем этапе
            //double x = Point.x;
            //Point.x = Point.x * cos(PI / 2) + Point.z * sin(PI / 2);
            //Point.z = x * sin(PI / 2) + Point.z * cos(PI / 2);
            points.push_back(Point);
        }
    }
    xi = points[0].x; 
    yi = points[0].y;
    MoveToEx(hdc, xi + 500, yi + 250, 0);
    for (int i = 1; i < points.size(); i++) {
        xi = points[i].x; 
        yi = points[i].y; 
        LineTo(hdc, xi + 500, yi + 250);
    }

    for (double teta = 0; teta < PI; teta += h) {
        for (double phi = 0;phi < 2*PI; phi += 2*h) {

            Point.x = r * cos(phi) * sin(teta);
            Point.y = r * sin(phi) * sin(teta);
            Point.z = r * cos(teta);
            double y = Point.y;
            Point.y = Point.y * cos(PI / 2) + Point.z * sin(PI / 2);
            Point.z = y * sin(PI / 2) + Point.z * cos(PI / 2);
            points.push_back(Point);
        }
    }
    xi = points[0].x;
    yi = points[0].y; 
    MoveToEx(hdc, xi + 500, yi + 250, 0);
    for (int i = 1; i < points.size(); i++) {
        xi = points[i].x; 
        yi = points[i].y; 
        LineTo(hdc, xi + 500, yi + 250);
    }  

}
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

    RECT rect;
    GetClientRect(hWnd, &rect);
    LONG width = rect.right - rect.left;
    LONG height = rect.bottom - rect.top;

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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            // создается вектор треугольник
            // сортируем по первой точек массив чтобы z было от минимального
            // один за один рисуем треугольники
            onPaint(hdc, width, height);
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
