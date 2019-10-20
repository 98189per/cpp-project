// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <string>
#include <vector>

// Global variables

#define ID_BUTTON1 1
#define ID_BUTTON2 3
#define ID_BUTTON3 4
#define ID_BUTTON4 5
#define ID_TEXTBOX 2
#pragma warning(push)
#pragma warning(disable: 4996) 

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Pro Calculator");

HINSTANCE hInst;

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
			NULL);

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
			NULL);

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");

	switch (message)
	{
	case WM_CREATE:{
		hWndTextbox = CreateWindow(
			TEXT("STATIC"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			450, 10, 100, 40,
			hWnd,
			(HMENU)ID_TEXTBOX,
			NULL,
			NULL);
		hWndButton1 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"1",      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			10,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU) ID_BUTTON1,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		hWndButton2 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"+",      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			120,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON2,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		hWndButton3 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"1",      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			230,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON3,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		hWndButton4 = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"=",      // Button text 
			WS_CHILD | WS_VISIBLE,  // Styles 
			340,         // x position 
			10,         // y position 
			100,        // Button width
			40,        // Button height
			hWnd,     // Parent window
			(HMENU)ID_BUTTON4,       // No menu.
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		ShowWindow(hWndButton2, SW_HIDE);
		ShowWindow(hWndButton3, SW_HIDE);
		ShowWindow(hWndButton4, SW_HIDE);

		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
			case ID_BUTTON1: {
				int len = GetWindowTextLength(hWndTextbox);
				std::vector<TCHAR> temp(len + 2);

				GetWindowText(hWndTextbox, temp.data(), temp.size());
				_tcscat(temp.data(), L"1");
				SetWindowText(hWndTextbox, temp.data());

				ShowWindow(hWndButton1, SW_HIDE);
				ShowWindow(hWndButton2, SW_SHOW);

				break;
			}
			case ID_BUTTON2: {
				int len = GetWindowTextLength(hWndTextbox);
				std::vector<TCHAR> temp(len + 2);

				GetWindowText(hWndTextbox, temp.data(), temp.size());
				_tcscat(temp.data(), L"+");
				SetWindowText(hWndTextbox, temp.data());

				ShowWindow(hWndButton2, SW_HIDE);
				ShowWindow(hWndButton3, SW_SHOW);

				break;
			}
			case ID_BUTTON3: {
				int len = GetWindowTextLength(hWndTextbox);
				std::vector<TCHAR> temp(len + 2);

				GetWindowText(hWndTextbox, temp.data(), temp.size());
				_tcscat(temp.data(), L"1");
				SetWindowText(hWndTextbox, temp.data());

				ShowWindow(hWndButton3, SW_HIDE);
				ShowWindow(hWndButton4, SW_SHOW);

				break;
			}
			case ID_BUTTON4: {
				int len = GetWindowTextLength(hWndTextbox);
				std::vector<TCHAR> temp(len + 15);

				GetWindowText(hWndTextbox, temp.data(), temp.size());
				_tcscat(temp.data(), L"= I don't know");
				SetWindowText(hWndTextbox, temp.data());

				ShowWindow(hWndButton4, SW_HIDE);

				break;
			}
		}
		
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		/*TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));*/
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}