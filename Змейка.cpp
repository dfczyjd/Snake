// Образец кода, создающего окно

#include <WinSDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "Змейка.h"
#include <vector>
#include <WindowsX.h>
#define ANS_SIZE 255

using namespace std;

// Глобальные переменные:

struct Cell
{
	int x, y;
};

HINSTANCE hInst;	// дескриптор текущиего экземпляра приложения
HWND hWnd;			// дескриптор главного окна
vector<Cell> snake;
Cell food, bonus;
int dir = 0, level = 1, score = 0, count = 0, bonus_left = -1;
bool game = true;

// Объявления (прототипы) функций, включенных в этот модуль кода:

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

// *** Функция Main ***

int APIENTRY _tWinMain(HINSTANCE hInstance,		// дескриптор текущего экземпляра приложения
                     HINSTANCE hPrevInstance,	// не используется
                     LPTSTR    lpCmdLine,		// не используется
                     int       nCmdShow)		// состояние главного окна при запуске
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// т.е. не используется
	UNREFERENCED_PARAMETER(lpCmdLine);		// т.е. не используется

 	// Локальные переменные функции _tWinMain

	MSG msg;			// Дескриптор сообщения
	WNDCLASSEX wcex;	// Структура для регистрации оконного класса

   hInst = hInstance; // Сохранить дескриптор экземпляра приложения в глобальной переменной

   // Заполнение структуры для регистрации оконного класса

	wcex.cbSize = sizeof(WNDCLASSEX); // размер структуры
	wcex.style			= CS_HREDRAW | CS_VREDRAW; // особенности поведения окна (список ключей см. в MSDN)
	wcex.lpfnWndProc	= WndProc; // оконная процедура
	wcex.cbClsExtra		= 0; // память, выделяемая оконному классу
	wcex.cbWndExtra		= 0; // памяить, выделяемая каждому экземпляру окна (в ней можно хранить собственные параметры окна)
	wcex.hInstance		= hInstance; // дескриптор приложения
//	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST)); // иконка окна (из ресурсов)
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION); // иконка окна (стандартная Windows)
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); // курсор (стандартный Windows)
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1); // кисть для фона окна (стандартная, обычно белая)
	wcex.lpszMenuName	= 0; // меню (сейчас нет)
	wcex.lpszClassName	= L"MyClass"; // имя оконного класса (для функции )
//	wcex.hIconSm		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL)); // маленькая иконка окна (из ресурсов)
	wcex.hIconSm		= LoadIcon(NULL, IDI_APPLICATION); // маленькая иконка окна (стандартная Windows)

	// Регистрация оконного класса

	RegisterClassEx(&wcex);

	// Создание окна

    hWnd = CreateWindow(L"MyClass",				// Оконный класс
						L"Main Window",			// Заголовок окна
						WS_OVERLAPPEDWINDOW,	// стиль окна (вид и поведение) список ключей см. в MSDN
						CW_USEDEFAULT, 0,		// координаты левого верхнего угла (здесь по умолчанию)
						CW_USEDEFAULT, 0,		// РАЗМЕРЫ окна по х и у (ширина и высота)
						NULL,					// окно-владелец
						NULL,					// меню
						hInstance,				// дескриптор приложения
						NULL);					// указатель на структуру CREATESTRUCT, если она нужна

   if (hWnd==0) // Окно не создано
   {
	   MessageBox(NULL, L"Main window error!", L"Error window", MB_OK); // Окно соообщения об ошибке
       return 1;
   }

   ShowWindow(hWnd, nCmdShow);	// окно делается видимым
   UpdateWindow(hWnd);			// окно перерисовывается (ему отправляется WM_PAINT)

   	// Основной цикл обработки сообщений:
	while (GetMessage(&msg, NULL, 0, 0)) // получение сообщения (GetMessage обычно возвращает true, и только на сообщение WM_QUIT возвращает false)
	{
		TranslateMessage(&msg);	// перевод клавиш в буквы
		DispatchMessage(&msg);	// передача сообщения окну
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ: оконная процедура (обрабатывает сообщения в главном окне).
//
LRESULT CALLBACK WndProc(HWND hWnd,		// дескриптор окна, получившего сообщение
						UINT message,	// номер сообщения
						WPARAM wParam,	// первый параметр сообщения
						LPARAM lParam)	// второй параметр сообщения
{
	PAINTSTRUCT ps;	// нужна сообщению WM_PAINT
	HDC hdc;		// дескриптор контекста устройства
	static HBRUSH brush, tmp_br, food_brush, bonus_brush, black_brush;
	static RECT tmp;
	Cell tmp_sn;
	WCHAR str1[ANS_SIZE], str2[ANS_SIZE];
	int size;

	switch (message)
	{
		case WM_CREATE:
			brush = CreateSolidBrush(RGB(0, 255, 0));
			food_brush = CreateSolidBrush(RGB(0, 0, 255));
			bonus_brush = CreateSolidBrush(RGB(255, 0, 0));
			black_brush = CreateSolidBrush(RGB(0, 0, 0));
			snake.resize(3);
			snake[0].x = 2;
			snake[0].y = 0;
			snake[1].x = 1;
			snake[1].y = 0;
			snake[2].x = 0;
			snake[2].y = 0;
			food.x = rand() % 20;
			food.y = rand() % 20;
			SetTimer(hWnd, 42, 420, NULL);
			break;

		case WM_PAINT:						// приходит, когда нужно перерисовать окно
			hdc = BeginPaint(hWnd, &ps);	// получение дескриптора контекста

			// TODO: добавьте любой код отрисовки...
			for (int i = 0; i < 21; ++i)
			{
				Rectangle(hdc, 400, 100 + i * 20, 800, 101 + i * 20);
				Rectangle(hdc, 400 + i * 20, 100, 401 + i * 20, 500);
			}
			switch (dir)
			{
				case 0:
					Ellipse(hdc, snake[0].x * 20 + 6, snake[0].y * 20 + 6, snake[0].x * 20 + 7, snake[0].y * 20 + 7);
					break;

				case 1:
					Ellipse(hdc, snake[0].x * 20 + 6, snake[0].y * 20 + 6, snake[0].x * 20 + 7, snake[0].y * 20 + 7);
					break;

				case 2:
					Ellipse(hdc, snake[0].x + 6, snake[0].y + 6, snake[0].x + 7, snake[0].y + 7);
					break;

				case 3:
					Ellipse(hdc, snake[0].x + 6, snake[0].y + 6, snake[0].x + 7, snake[0].y + 7);
					break;

			}
			tmp_br = SelectBrush(hdc, brush);
			for (int i = 0; i < snake.size(); ++i)
			{
				Rectangle(hdc, 400 + snake[i].x * 20, 100 + snake[i].y * 20, 400 + (snake[i].x + 1) * 20, 100 + (snake[i].y + 1) * 20);
			}
			tmp.left = 400 + snake[0].x * 20;
			tmp.top = 100 + snake[0].y * 20;
			tmp.right = 400 + (snake[0].x + 1) * 20;
			tmp.bottom = 100 + (snake[0].y + 1) * 20;
			//DrawText(hdc, L"h", 1, &tmp, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			brush = SelectBrush(hdc, tmp_br);
			tmp_br = SelectBrush(hdc, food_brush);
			Ellipse(hdc, 400 + food.x * 20, 100 + food.y * 20, 400 + (food.x + 1) * 20, 100 + (food.y + 1) * 20);
			food_brush = SelectBrush(hdc, tmp_br);
			if (bonus_left >= 0)
			{
				Rectangle(hdc, 400, 510, 600, 525);
				tmp_br = SelectBrush(hdc, bonus_brush);
				Ellipse(hdc, 400 + bonus.x * 20, 100 + bonus.y * 20, 400 + (bonus.x + 2) * 20, 100 + (bonus.y + 2) * 20);
				Rectangle(hdc, 400, 510, 400 + bonus_left * 5, 525);
				bonus_brush = SelectBrush(hdc, tmp_br);
			}
			size = wsprintf(str1, L"score: %d", score);
			wsprintf(str2, L"level: %d", level);
			TextOut(hdc, 10, 10, str1, size);
			TextOut(hdc, 10, 30, str2, 8);
			EndPaint(hWnd, &ps);
			break;

		case WM_TIMER:
			tmp_sn = snake[snake.size() - 1];
			for (int i = snake.size() - 1; i > 0; --i)
				snake[i] = snake[i - 1];
			switch (dir)
			{
			case 0:
				++snake[0].x;
				snake[0].x %= 20;
				break;
			case 1:
				++snake[0].y;
				snake[0].y %= 20;
				break;
			case 2:
				--snake[0].x;
				if (snake[0].x < 0)
					snake[0].x += 20;
				break;
			case 3:
				--snake[0].y;
				if (snake[0].y < 0)
					snake[0].y += 20;
				break;
			}
			for (int i = 1; i < snake.size(); ++i)
			{
				if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
				{
					game = false;
					KillTimer(hWnd, 42);
					MessageBox(hWnd, L"You lose.", L"Error window", MB_OK);
				}
			}
			if (snake[0].x == food.x && snake[0].y == food.y)
			{
				snake.push_back(tmp_sn);
				food.x = rand() % 20;
				food.y = rand() % 20;
				score += level;
				++count;
				if (bonus_left < 0 && count % 4 == 0)
				{
					bonus.x = rand() % 19;
					bonus.y = rand() % 19;
					bonus_left = 40;
				}
			}
			if (bonus_left >= 0)
			{
				if ((snake[0].x == bonus.x && snake[0].y == bonus.y) ||
				(snake[0].x == bonus.x + 1 && snake[0].y == bonus.y) ||
				(snake[0].x == bonus.x && snake[0].y == bonus.y + 1) ||
				(snake[0].x == bonus.x + 1 && snake[0].y == bonus.y + 1))
				{
					score += level * bonus_left;
					bonus_left = -1;
				}
			}
            if (bonus_left >= 0)
                --bonus_left;
			InvalidateRect(hWnd, 0, true);
			UpdateWindow(hWnd);
			break;

		case WM_CHAR:
			switch (wParam)
			{
			case 'w':
				if (dir != 1)
					dir = 3;
				break;
			case 's':
				if (dir != 3)
					dir = 1;
				break;
			case 'a':
				if (dir != 0)
					dir = 2;
				break;
			case 'd':
				if (dir != 2)
					dir = 0;
				break;
			case '+':
				KillTimer(hWnd, 42);
				++level;
				if (level > 7)
					level = 7;
				SetTimer(hWnd, 42, 420 / level, NULL);
				break;

			case '-':
				KillTimer(hWnd, 42);
				--level;
				if (level < 1)
					level = 1;
				SetTimer(hWnd, 42, 420 / level, NULL);
				break;

			}
			break;

		case WM_DESTROY:					// приходит при закрытии окна
			if (game)
				KillTimer(hWnd, 42);
			DeleteBrush(brush);
			PostQuitMessage(0);				// завершить работу программы (послать сообщение WM_QUIT)
			break;

		default:							// обработка всех остальных сообщений (которые не хочет обрабатывать программист)
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
