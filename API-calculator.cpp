#include <windows.h>												// ������ �������
#include "API-calculator.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				// CALLBACK ��ũ��
HINSTANCE g_Instance;												// �ν��Ͻ� �ڵ�
LPCTSTR lpszClass = TEXT("Win32_Calculator");						// ���� ǥ���ٿ� ǥ�õǴ� ����

void Insert(TCHAR* numberList, TCHAR input, HWND* hwnd);
BOOLEAN isCurrent(TCHAR* numberList);

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

	RegisterClass(&WndClass);										// WNDCLASS ����ü�� ������ ����



	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		, NULL, (HMENU)NULL, hInstance, NULL);	// �����츦 �����ϰ� â�� ǥ���ϴ� ����� ����

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
	HDC hdc;
	PAINTSTRUCT ps;
	const int numPadSizeX = 100;
	const int numPadSizeY = 50;
	const int padDistanceX = 150;
	const int padDistanceY = 150;

	static TCHAR numberList[256] = {0, };
	static int next = 0;

	switch (iMessage) 
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		case WM_CREATE:
		{
			CreateWindowW(TEXT("static"), numberList, WS_CHILD | WS_VISIBLE | SS_RIGHT,
				150, 0, 400, 80, hWnd, (HMENU)99, g_Instance, NULL);

			// Number Button
			CreateWindowW(TEXT("button"), TEXT("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, 100 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)1, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, 100 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)2, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, 100 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)3, g_Instance, NULL);

			CreateWindowW(TEXT("button"), TEXT("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, 50 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)4, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, 50 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)5, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, 50 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)6, g_Instance, NULL);

			CreateWindowW(TEXT("button"), TEXT("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)7, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)8, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)9, g_Instance, NULL);

			CreateWindowW(TEXT("button"), TEXT("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, 150 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)0, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, 150 + padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)10, g_Instance, NULL);

			// Operator Button
			CreateWindowW(TEXT("button"), TEXT("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY, numPadSizeX, numPadSizeY, hWnd, (HMENU)11, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("X"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY + 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)12, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY + 100, numPadSizeX, numPadSizeY, hWnd, (HMENU)13, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY + 150, numPadSizeX, numPadSizeY, hWnd, (HMENU)14, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, padDistanceY + 150, numPadSizeX, numPadSizeY, hWnd, (HMENU)15, g_Instance, NULL);

			// Sub Button
			CreateWindowW(TEXT("button"), TEXT("%"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)16, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("CE"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				100 + padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)17, g_Instance, NULL);
			CreateWindowW(TEXT("button"), TEXT("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				200 + padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)18, g_Instance, NULL);

			// Back Space
			CreateWindowW(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)20, g_Instance, NULL);

			break;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				// Number 0
				case 0:
				{
					Insert(numberList, '0', &hWnd);
					break;
				}
				// Number 1
				case 1:
				{
					Insert(numberList, '1', &hWnd);
				}
				// Number 2
				case 2:
				{
					Insert(numberList, '2', &hWnd);
					break;
				}
				// Number 3
				case 3:
				{
					Insert(numberList, '3', &hWnd);
					break;
				}
				// Number 4
				case 4:
				{
					Insert(numberList, '4', &hWnd);
					break;
				}
				// Number 5
				case 5:
				{
					Insert(numberList, '5', &hWnd);
					break;
				}
				// number 6
				case 6:
				{
					Insert(numberList, '6', &hWnd);
					break;
				}
				// number 7
				case 7:
				{
					Insert(numberList, '7', &hWnd);
					break;
				}
				// number 8
				case 8:
				{
					Insert(numberList, '8', &hWnd);
					break;
				}
				// number 9
				case 9:
				{
					Insert(numberList, '9', &hWnd);
					break;
				}
				// .
				case 10:
				{
					Insert(numberList, '.', &hWnd);
					break;
				}
				// /
				case 11:
				{
					Insert(numberList, '/', &hWnd);
					break;
				}
				// X
				case 12:
				{
					Insert(numberList, 'X', &hWnd);
					break;
				}
				// -
				case 13:
				{
					Insert(numberList, '-', &hWnd);
					break;
				}
				// +
				case 14:
				{
					Insert(numberList, '+', &hWnd);
					break;
				}
				// =
				case 15:
				{

					break;
				}
				// %
				case 16:
				{
					Insert(numberList, '%', &hWnd);
					break;
				}
				// CE
				case 17:
				{

					break;
				}
				// C
				case 18:
				{
					memset(numberList, NULL, sizeof(numberList));
					SetDlgItemText(hWnd, 99, numberList);
					break;
				}
				// BackSpace
				case 19:
				{
					if (lstrlen(numberList))
					{
						numberList[lstrlen(numberList) - 1] = NULL;
						SetDlgItemText(hWnd, 99, numberList);
					}
					break;
				}
			}
			break;
		}

		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			ReleaseDC(hWnd, hdc);
			break;
		}
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void Insert(TCHAR* numberList, TCHAR input, HWND* hwnd)
{
	TCHAR copyText[2] = { NULL, };

	if (!isdigit(input))
	{
		if(isCurrent(numberList))
		{
			copyText[0] = input;
			lstrcat(numberList, copyText);
			SetDlgItemText(*hwnd, 99, numberList);
		}
	}
}

BOOLEAN isCurrent(TCHAR* numberList)
{
	int length = lstrlen(numberList);
	if (isdigit(numberList[length -1]))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}