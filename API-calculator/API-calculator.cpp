#include <windows.h>												// 윈도우 헤더파일
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				// CALLBACK 매크로
HINSTANCE g_Instance;												// 인스턴스 핸들
LPCTSTR lpszClass = TEXT("Win32_Calculator");						// 제목 표시줄에 표시되는 내용

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)								// main 함수
{
	HWND hWnd;														// 윈도우 핸들 선언
	MSG Message;													// 메세지 구조체 변수 선언
	WNDCLASS WndClass;												// Windows Class 구조체 변수 선언
	g_Instance = hInstance;											// hInstance값을 외부에서도 사용할 수 있도록 전역변수에 값을 저장

	WndClass.cbClsExtra = 0;										// 예약 영역. 지금은 사용X
	WndClass.cbWndExtra = 0;										// 예약 영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 윈도우의 배경 색상을 지정
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// 윈도우의 커서(마우스포인터) 모양을 지정
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// 윈도우의 커서 아이콘 모양 지정
	WndClass.hInstance = hInstance;									// 윈도우 클래스를 등록하는 프로그램 번호
	WndClass.lpfnWndProc = WndProc;									// 윈도우 메세지 처리 함수 지정
	WndClass.lpszClassName = lpszClass;								// 윈도우 클래스의 이름 지정
	WndClass.lpszMenuName = NULL;									// 이 프로그램의 메뉴 지정
	WndClass.style = CS_HREDRAW | CS_VREDRAW;						// 윈도우의 스타일을 정의

	RegisterClass(&WndClass);										// WNDCLASS 구조체의 주소 전달

	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, 500, 430,
		NULL, (HMENU)NULL, hInstance, NULL);						// 윈도우를 생성하고 창에 표시하는 기능을 수행

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) 						// 메세지 루프를 실행
	{																// Queue에 있는 메세지를 읽어들인다
		TranslateMessage(&Message);									// 키보드 입력 메세지를 가공하여 프로그램에서 쉽게 
																	// 사용할 수 있도록
		DispatchMessage(&Message);									// 메세지를 윈도우의 메세지 처리 함수 WndProc로 전달
	}
	return (int)Message.wParam;										// 탈출 코드. 프로그램 종료
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	// General
	HDC hdc;
	PAINTSTRUCT ps;
	static int count = 0;
	static int vArray = 0;						// numberValue의 Array에서 사용할 배열 index 탐색용 변수
	static int lArray = 0;						// numberList의 Array에서 사용할 배열 index 탐색용 변수
	TCHAR numberList[128]{ '\0', };
	static int numberValue[128]{ 0, };

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
			CreateWindowW(TEXT("button"), TEXT("←"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				300 + padDistanceX, padDistanceY - 50, numPadSizeX, numPadSizeY, hWnd, (HMENU)ID_BACKSPACE, g_Instance, NULL);
			break;

		// 출력 가능한 숫자의 자리 수는 최대 10억까지 가능
		// 연산자 출력이 되지 않는 상태
		// 실수 변경이 되지 않는 상태


		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case ID_NUMBER_0:
					if (numberValue[vArray] > 0)
					{
						numberValue[vArray] *= 10;
					}
					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_1:
					if (numberValue[vArray] == 0)
					{
						numberValue[vArray] = 1;
					}
					else if (numberValue[vArray] > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 1;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);			// 여기서 출력이 초기화 됨
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_2:
					if (numberValue[vArray] == 0)
					{
						numberValue[vArray] = 2;
					}
					else if (numberValue[vArray] > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 2;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_3:
					if (numberValue[vArray] == 0)
					{
						numberValue[vArray] = 3;
					}
					else if (numberValue[vArray] > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 3;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_4:
					if (numberValue[vArray] <= 0)
					{
						numberValue[vArray] = 4;
					}
					else if (numberValue[vArray] > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 4;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_5:
					if (numberValue[vArray] == 0)
					{
						numberValue[vArray] = 5;
					}
					else if (numberValue[vArray] > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 5;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_6:
					if (numberValue[vArray] == 0)
					{
						numberValue[vArray] = 6;
					}
					else if (numberValue[vArray] > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 6;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_7:
					if (numberValue == 0)
					{
						numberValue[vArray] = 7;
					}
					else if (numberValue > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 7;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_8:
					if (numberValue <= 0)
					{
						numberValue[vArray] = 8;
					}
					else if (numberValue > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 8;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_NUMBER_9:
					if (numberValue[vArray] <= 0)
					{
						numberValue[vArray] = 9;
					}
					else if (numberValue > 0)
					{
						numberValue[vArray] = numberValue[vArray] * 10 + 9;
					}

					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				// Operator

				case ID_POINT:
					// numberValue의 자료형을 int -> float로 변경
					// wsprinfW의 매개변수를 동적으로 생성하여 저장

					vArray++;
					numberValue[vArray] *= 0.1;
					numberValue[vArray] += numberValue[vArray - 1];
					wsprintfW(numberList, L"%d %s", numberValue[vArray], L".");
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

					// Input operator button 
					// 연산자 버튼 클릭 시, 다음 배열로 변경
				case ID_DIVISION:
					wsprintfW(numberList, L"%d %s %d", numberValue[vArray], L"/", numberValue[vArray+1]);
					vArray++;
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

				case ID_MULTIPLICATION:
					break;

				case ID_SUBTRACTION:
					break;

				case ID_ADDITION:
					break;

				case ID_RESULT:
					break;

				case ID_PERCENT:
					break;

				case ID_CE:
					break;

				case ID_C:
					memset(numberList, NULL, sizeof(numberList));

					if (count == 1)
					{
						numberValue[vArray] = 0;
					}
					else
					{
						numberValue[vArray] = 0;
						numberList[lArray] = '\0';
					}
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

					// numberList의 출력은 삭제되지만 numberValue에 저장된 값은 그대로인 상태
					// 마지막 자리 숫자 임시 저장 및 Back Space 입력 시, 값 변화
				case ID_BACKSPACE:
					numberValue[vArray] *= 0.1;
					numberList[lstrlen(numberList) - 1] = NULL;
					wsprintfW(numberList, L"%d", numberValue[vArray]);
					SetDlgItemText(hWnd, ID_STATIC, numberList);
					break;

					break;
			}

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			wsprintfW(numberList, L"%d", numberValue[vArray]);
			TextOutW(hdc, 50, 360, numberList, sizeof(numberList));
			InvalidateRect(hWnd, NULL, false);
			ReleaseDC(hWnd, hdc);
			break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}