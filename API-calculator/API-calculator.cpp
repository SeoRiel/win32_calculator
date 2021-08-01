#include <windows.h>												// ������ �������
#include <iostream>
#include "API-calculator.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				// CALLBACK ��ũ��
HINSTANCE g_Instance;												// �ν��Ͻ� �ڵ�
LPCTSTR lpszClass = TEXT("Win32_Calculator");						// ���� ǥ���ٿ� ǥ�õǴ� ����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)								// main �Լ�
{
	HWND hWnd;														// ������ �ڵ� ����
	MSG Message;													// �޼��� ����ü ���� ����
	WNDCLASS WndClass;												// Windows Class ����ü ���� ����
	g_Instance = hInstance;											// hInstance���� �ܺο����� ����� �� �ֵ��� ���������� ���� ����

	WndClass.cbClsExtra = 0;										// ���� ����. ������ ���X
	WndClass.cbWndExtra = 0;										// ���� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// �������� ��� ������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// �������� Ŀ��(���콺������) ����� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// �������� Ŀ�� ������ ��� ����
	WndClass.hInstance = hInstance;									// ������ Ŭ������ ����ϴ� ���α׷� ��ȣ
	WndClass.lpfnWndProc = WndProc;									// ������ �޼��� ó�� �Լ� ����
	WndClass.lpszClassName = lpszClass;								// ������ Ŭ������ �̸� ����
	WndClass.lpszMenuName = NULL;									// �� ���α׷��� �޴� ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW;						// �������� ��Ÿ���� ����

	RegisterClass(&WndClass);										// WNDCLASS ����ü�� �ּ� ����

	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, 500, 430,
		NULL, (HMENU)NULL, hInstance, NULL);						// �����츦 �����ϰ� â�� ǥ���ϴ� ����� ����

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) 						// �޼��� ������ ����
	{																// Queue�� �ִ� �޼����� �о���δ�
		TranslateMessage(&Message);									// Ű���� �Է� �޼����� �����Ͽ� ���α׷����� ���� 
																	// ����� �� �ֵ���
		DispatchMessage(&Message);									// �޼����� �������� �޼��� ó�� �Լ� WndProc�� ����
	}
	return (int)Message.wParam;										// Ż�� �ڵ�. ���α׷� ����
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// General
	HDC hdc;
	PAINTSTRUCT ps;
	static int count = 0;
	static int vArray = 0;						// numberValue�� Array���� ����� �迭 index Ž���� ����
	static int pArray = 0;						// numberList�� Array���� ����� �迭 index Ž���� ����
	static TCHAR numberList[128]{ };
	static int numberValue = 0;

	// Pad Position
	const int numPadSizeX = 100;
	const int numPadSizeY = 50;
	const int padDistanceX = 40;
	const int padDistanceY = 150;

	// Static Text
	const int ID_STATIC = 99;

	// Button ID : Number Pad
	const int ID_NUMBER_0 = 0;
	const int ID_NUMBER_1 = 1;
	const int ID_NUMBER_2 = 2;
	const int ID_NUMBER_3 = 3;
	const int ID_NUMBER_4 = 4;
	const int ID_NUMBER_5 = 5;
	const int ID_NUMBER_6 = 6;
	const int ID_NUMBER_7 = 7;
	const int ID_NUMBER_8 = 8;
	const int ID_NUMBER_9 = 9;
	const int ID_POINT = 10;

	// Button ID : Operactor ID
	const int ID_DIVISION = 11;
	const int ID_MULTIPLICATION = 12;
	const int ID_SUBTRACTION = 13;
	const int ID_ADDITION = 14;
	const int ID_RESULT = 15;
	const int ID_PERCENT = 16;

	// Button ID : Other ID
	const int ID_CE = 17;
	const int ID_C = 18;
	const int ID_BACKSPACE = 19;


	switch (iMessage)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CREATE:
			// Static TextBox
			CreateWindowW(TEXT("static"), numberList, WS_CHILD | WS_VISIBLE | SS_RIGHT,
				padDistanceX, 15, 400, 80, hWnd, (HMENU)ID_STATIC, g_Instance, NULL);

			// Number Button
			CreateWindowW(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, 100 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_1, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, 100 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_2, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, 100 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_3, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, 50 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_4, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, 50 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_5, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, 50 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_6, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_7, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_8, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_9, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, 150 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_NUMBER_0, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, 150 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_POINT, g_Instance, NULL);

			// Operator Button
			CreateWindowW(TEXT("button"), TEXT("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_DIVISION, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("X"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY + 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_MULTIPLICATION, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY + 100, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_SUBTRACTION, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY + 150, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_ADDITION, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, padDistanceY + 150, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_RESULT, g_Instance, NULL);

			// Sub Button
			CreateWindowW(TEXT("button"), TEXT("%"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_PERCENT, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("CE"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_CE, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_C, g_Instance, NULL);

			// Back Space
			CreateWindowW(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_BACKSPACE, g_Instance, NULL);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case ID_NUMBER_0:
					if (numberValue > 0)
					{
						numberValue *= 10;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_1:
					if (numberValue == 0)
					{
						numberValue = 1;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 1;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_2:
					if (numberValue == 0)
					{
						numberValue = 2;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 2;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_3:
					if (numberValue == 0)
					{
						numberValue = 3;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 3;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_4:
					if (numberValue <= 0)
					{
						numberValue = 4;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 4;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_5:
					if (numberValue == 0)
					{
						numberValue = 5;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 5;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_6:
					if (numberValue == 0)
					{
						numberValue = 6;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 6;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_7:
					if (numberValue == 0)
					{
						numberValue = 7;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 7;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_8:
					if (numberValue <= 0)
					{
						numberValue = 8;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 8;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_9:
					if (numberValue <= 0)
					{
						numberValue = 9;
					}
					else if (numberValue > 0)
					{
						numberValue = numberValue * 10 + 9;
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_POINT:
					// numberValue�� �ڷ����� int -> float�� ����
					// 10 + 0.1f = 10.1���� numberValue�� ����Ǿ����
					// numberValue += 0.1f;
					wsprintfW(numberList, L"%0.f", (float)numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

					// Input operator button 
					// ������ ��ư Ŭ�� ��, ���� �迭�� ����
				case ID_DIVISION:
					if (numberList[pArray] < ' ' && numberValue < 0)
					{
						wsprintfW(numberList, L"%d", numberValue);
					}
					else
					{
						numberList[pArray] = '/';
					}

					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_MULTIPLICATION:
					break;

				case ID_SUBTRACTION:
					numberList[pArray] = '-';
					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_ADDITION:
					break;

				case ID_RESULT:
					break;

				case ID_PERCENT:
					wsprintfW(numberList, TEXT("%"));
					numberValue *= 0.001;
					wsprintfW(numberList, L"%d", numberValue, '%');
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_CE:
					break;

				case ID_C:
					memset(numberList, NULL, sizeof(numberList));

					if (count == 1)
					{
						numberValue = 0;
					}
					else
					{
						numberValue = 0;
						numberList[pArray] = '\0';
					}
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

					// numberList�� ����� ���������� numberValue�� ����� ���� �״���� ����
					// ������ �ڸ� ���� �ӽ� ���� �� Back Space �Է� ��, �� ��ȭ
				case ID_BACKSPACE:
					numberValue *= 0.1;
					numberList[lstrlen(numberList) - 1] = NULL;
					wsprintfW(numberList, L"%d", numberValue);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

					break;
			}

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			wsprintfW(numberList, L"%d", numberValue);
			TextOutW(hdc, 50, 360, numberList, sizeof(numberList));
			InvalidateRect(hWnd, NULL, false);
			ReleaseDC(hWnd, hdc);
			break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}