// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <wchar.h>
#include <string.h>

// Global variables

#define ID_BUTTON1 1
#define ID_BUTTON2 3
#define ID_BUTTON3 4
#define ID_BUTTON4 5
#define ID_BUTTON5 6
#define ID_TEXTBOX 2

using namespace std;

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Pro Calculator");

HINSTANCE hInst;
//HBRUSH hbrWhite;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			0LL);

		return 1;
	}

	// Store instance handle in our global variable
	hInst = hInstance;

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		580, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			0LL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

static HWND hWndTextbox;
static HWND hWndButton1;
static HWND hWndButton2;
static HWND hWndButton3;
static HWND hWndButton4;
static HWND hWndButton5;
static char msg[100];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	wchar_t greeting[25] = L"@Kyle Pereira coded this";

	switch (message)
	{
	case WM_CREATE:{
		hWndTextbox = CreateWindowW(
			L"STATIC", L"Made by Kyle Pereira",
			WS_CHILD | WS_VISIBLE,
			0, 0, 580, 100,
			hWnd,
			NULL,
			NULL,
			NULL);
		hWndTextbox = CreateWindow(
			TEXT("STATIC"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			450, 10, 100, 40,
			hWnd,
			(HMENU)ID_TEXTBOX,
			NULL,
			NULL);
		hWndButton1 = CreateWindow(
			_T("BUTTON"),  // Predefined class; Unicode assumed 
			_T("1"),      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			10,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU) ID_BUTTON1,       // No menu.
			NULL,
			NULL);      // Pointer not needed.
		hWndButton2 = CreateWindow(
			_T("BUTTON"),  // Predefined class; Unicode assumed 
			_T("+"),      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			120,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON2,       // No menu.
			NULL,
			NULL);      // Pointer not needed.
		hWndButton3 = CreateWindow(
			_T("BUTTON"),  // Predefined class; Unicode assumed 
			_T("1"),      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			230,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON3,       // No menu.
			NULL,
			NULL);      // Pointer not needed.
		hWndButton4 = CreateWindow(
			_T("BUTTON"),  // Predefined class; Unicode assumed 
			_T("="),      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			340,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON4,       // No menu.
			NULL,
			NULL);      // Pointer not needed.
		hWndButton5 = CreateWindow(
			_T("BUTTON"),  // Predefined class; Unicode assumed 
			_T("retry"),      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			10,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON5,       // No menu.
			NULL,
			NULL);      // Pointer not needed.

		ShowWindow(hWndButton2, SW_HIDE);
		ShowWindow(hWndButton3, SW_HIDE);
		ShowWindow(hWndButton4, SW_HIDE);
		ShowWindow(hWndButton5, SW_HIDE);

		//hbrWhite = CreateSolidBrush(RGB(255, 0 , 0)); 

		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
			case ID_BUTTON1: {
				int len = GetWindowTextLength(hWndTextbox);

				strcat(msg, "1");
				wchar_t temp[100];
				std::mbstowcs(temp, msg, strlen(msg)+1);
				SetWindowTextW(hWndTextbox, temp);

				ShowWindow(hWndButton1, SW_HIDE);
				ShowWindow(hWndButton2, SW_SHOW);

				break;
			}
			case ID_BUTTON2: {
				int len = GetWindowTextLength(hWndTextbox);

				strcat(msg, "+");
				wchar_t temp[100];
				std::mbstowcs(temp, msg, strlen(msg)+1);
				SetWindowTextW(hWndTextbox, temp);

				ShowWindow(hWndButton2, SW_HIDE);
				ShowWindow(hWndButton3, SW_SHOW);

				break;
			}
			case ID_BUTTON3: {
				int len = GetWindowTextLength(hWndTextbox);
				
				strcat(msg, "1");
				wchar_t temp[100];
				std::mbstowcs(temp, msg, strlen(msg)+1);
				SetWindowTextW(hWndTextbox, temp);

				ShowWindow(hWndButton3, SW_HIDE);
				ShowWindow(hWndButton4, SW_SHOW);

				break;
			}
			case ID_BUTTON4: {
				int len = GetWindowTextLength(hWndTextbox);
				
				strcat(msg, "= I don't know");
				wchar_t temp[100];
				std::mbstowcs(temp, msg, strlen(msg)+1);
				SetWindowTextW(hWndTextbox, temp);

				ShowWindow(hWndButton4, SW_HIDE);
				ShowWindow(hWndButton5, SW_SHOW);

				break;
			}
			case ID_BUTTON5: {
				SetWindowText(hWndTextbox, _T(""));
				for(int i = 0; i < 100; i++){
					msg[i] = ' ';
				}

				ShowWindow(hWndButton5, SW_HIDE);
				ShowWindow(hWndButton1, SW_SHOW);

				break;
			}
		}
		
		break;
	}
	case WM_PAINT:
		//HBRUSH whitebrush;
		//whitebrush = CreateSolidBrush(WHITE_BRUSH);
		hdc = BeginPaint(hWnd, &ps);
		//LPRECT rectangle;
		//SetRect(rectangle, 0, 0, 580, 100);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		/*TextOutW(hdc,
			5, 5,
			greeting, wcslen(greeting));*/
		// End application-specific layout section.

		//SendMessageW(hWnd, WM_ERASEBKGND, 0LL, 0LL);
		//GetClientRect(hWnd, rectangle);
		//FillRect(GetDC(hWnd), rectangle, WHITE_BRUSH);

		EndPaint(hWnd, &ps);
		break;
	/*case WM_ERASEBKGND: 
		RECT rc;
		//SetRect(&rc, 0, 0, 540, 100);
		hdc = (HDC) wParam; 
		GetClientRect(hWnd, &rc); 
		//SetMapMode(hdc, MM_ANISOTROPIC); 
		//SetWindowExtEx(hdc, 100, 100, NULL); 
		//SetViewportExtEx(hdc, rc.right, rc.bottom, NULL); 
		FillRect(hdc, &rc, hbrWhite); 
		break;*/
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}