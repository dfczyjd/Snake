// ������� ����, ���������� ����

#include <WinSDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "������.h"
#include <vector>
#include <WindowsX.h>
#define ANS_SIZE 255

using namespace std;

// ���������� ����������:

struct Cell
{
	int x, y;
};

HINSTANCE hInst;	// ���������� ��������� ���������� ����������
HWND hWnd;			// ���������� �������� ����
vector<Cell> snake;
Cell food, bonus;
int dir = 0, level = 1, score = 0, count = 0, bonus_left = -1;
bool game = true;

// ���������� (���������) �������, ���������� � ���� ������ ����:

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

// *** ������� Main ***

int APIENTRY _tWinMain(HINSTANCE hInstance,		// ���������� �������� ���������� ����������
                     HINSTANCE hPrevInstance,	// �� ������������
                     LPTSTR    lpCmdLine,		// �� ������������
                     int       nCmdShow)		// ��������� �������� ���� ��� �������
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �.�. �� ������������
	UNREFERENCED_PARAMETER(lpCmdLine);		// �.�. �� ������������

 	// ��������� ���������� ������� _tWinMain

	MSG msg;			// ���������� ���������
	WNDCLASSEX wcex;	// ��������� ��� ����������� �������� ������

   hInst = hInstance; // ��������� ���������� ���������� ���������� � ���������� ����������

   // ���������� ��������� ��� ����������� �������� ������

	wcex.cbSize = sizeof(WNDCLASSEX); // ������ ���������
	wcex.style			= CS_HREDRAW | CS_VREDRAW; // ����������� ��������� ���� (������ ������ ��. � MSDN)
	wcex.lpfnWndProc	= WndProc; // ������� ���������
	wcex.cbClsExtra		= 0; // ������, ���������� �������� ������
	wcex.cbWndExtra		= 0; // �������, ���������� ������� ���������� ���� (� ��� ����� ������� ����������� ��������� ����)
	wcex.hInstance		= hInstance; // ���������� ����������
//	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST)); // ������ ���� (�� ��������)
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION); // ������ ���� (����������� Windows)
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW); // ������ (����������� Windows)
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1); // ����� ��� ���� ���� (�����������, ������ �����)
	wcex.lpszMenuName	= 0; // ���� (������ ���)
	wcex.lpszClassName	= L"MyClass"; // ��� �������� ������ (��� ������� )
//	wcex.hIconSm		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL)); // ��������� ������ ���� (�� ��������)
	wcex.hIconSm		= LoadIcon(NULL, IDI_APPLICATION); // ��������� ������ ���� (����������� Windows)

	// ����������� �������� ������

	RegisterClassEx(&wcex);

	// �������� ����

    hWnd = CreateWindow(L"MyClass",				// ������� �����
						L"Main Window",			// ��������� ����
						WS_OVERLAPPEDWINDOW,	// ����� ���� (��� � ���������) ������ ������ ��. � MSDN
						CW_USEDEFAULT, 0,		// ���������� ������ �������� ���� (����� �� ���������)
						CW_USEDEFAULT, 0,		// ������� ���� �� � � � (������ � ������)
						NULL,					// ����-��������
						NULL,					// ����
						hInstance,				// ���������� ����������
						NULL);					// ��������� �� ��������� CREATESTRUCT, ���� ��� �����

   if (hWnd==0) // ���� �� �������
   {
	   MessageBox(NULL, L"Main window error!", L"Error window", MB_OK); // ���� ���������� �� ������
       return 1;
   }

   ShowWindow(hWnd, nCmdShow);	// ���� �������� �������
   UpdateWindow(hWnd);			// ���� ���������������� (��� ������������ WM_PAINT)

   	// �������� ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0)) // ��������� ��������� (GetMessage ������ ���������� true, � ������ �� ��������� WM_QUIT ���������� false)
	{
		TranslateMessage(&msg);	// ������� ������ � �����
		DispatchMessage(&msg);	// �������� ��������� ����
	}

	return (int) msg.wParam;
}



//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������: ������� ��������� (������������ ��������� � ������� ����).
//
LRESULT CALLBACK WndProc(HWND hWnd,		// ���������� ����, ����������� ���������
						UINT message,	// ����� ���������
						WPARAM wParam,	// ������ �������� ���������
						LPARAM lParam)	// ������ �������� ���������
{
	PAINTSTRUCT ps;	// ����� ��������� WM_PAINT
	HDC hdc;		// ���������� ��������� ����������
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

		case WM_PAINT:						// ��������, ����� ����� ������������ ����
			hdc = BeginPaint(hWnd, &ps);	// ��������� ����������� ���������

			// TODO: �������� ����� ��� ���������...
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

		case WM_DESTROY:					// �������� ��� �������� ����
			if (game)
				KillTimer(hWnd, 42);
			DeleteBrush(brush);
			PostQuitMessage(0);				// ��������� ������ ��������� (������� ��������� WM_QUIT)
			break;

		default:							// ��������� ���� ��������� ��������� (������� �� ����� ������������ �����������)
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
