#include<Windows.h>
#include<tchar.h>
#include<string>

#define ID_list1 1001
#define ID_list2 1002
#define ID_button1 1003
#define ID_button2 1004

static TCHAR WindowsClass[] = L"win32app";
static TCHAR Title[] = L"MyApp";
HINSTANCE hinst;
RECT desktop, cr;
LRESULT cur_sel;
wchar_t str[40];

HWND list1, list2, button1, button2;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(10, 128, 256));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call faild!", L"MyApp", NULL);
		return 1;
	}

	hinst = hinstance;
	GetWindowRect(GetDesktopWindow(), &desktop);
	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		desktop.right / 4,
		desktop.bottom / 6,
		960,
		540,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, L"Create window faild!", L"MyApp", NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{

	case WM_COMMAND:
				

	case BN_CLICKED:

		if (LOWORD(wParam) == ID_button1)
		{
			cur_sel = -1;
			cur_sel = SendMessage(list1, LB_GETCURSEL, 0, 0);
			SendMessage(list1, LB_GETTEXT, cur_sel, (LPARAM)str);							//Запомнить строку из выбранной позиции
			SendMessage(list1, LB_DELETESTRING, cur_sel, 0);								//Удалить выбранную строку
			SendMessage(list2, LB_ADDSTRING, 0, (LPARAM)str);
		}
				
		if (LOWORD(wParam) == ID_button2)
		{
			cur_sel = -1;
			cur_sel = SendMessage(list2, LB_GETCURSEL, 0, 0);
			SendMessage(list2, LB_GETTEXT, cur_sel, (LPARAM)str);							//Запомнить строку из выбранной позиции
			SendMessage(list2, LB_DELETESTRING, cur_sel, 0);								//Удалить выбранную строку
			SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)str);
		}
			
		

		break;

	case WM_CREATE:

		GetClientRect(hWnd, &cr);

		list1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"listbox",
			L"",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_SORT | ES_READONLY | LBS_HASSTRINGS,
			cr.right / 12,
			cr.bottom / 5,
			cr.right / 6.5 * 2,
			cr.bottom / 2,
			hWnd,
			(HMENU)ID_list1,
			hinst,
			NULL);

		list2 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"listbox",
			L"",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_SORT | ES_READONLY | LBS_HASSTRINGS,
			cr.right / 10 * 6,
			cr.bottom / 5,
			cr.right / 8 * 2.5,
			cr.bottom / 2,
			hWnd,
			(HMENU)ID_list1,
			hinst,
			NULL);
				
		
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Один");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Два");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Три");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Четыре");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Пять");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Шесть");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Семь");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Восемь");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Девять");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Десять");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Одиннадцать");
		SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)L"Двенадцать");

		button1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			L"Переместить >>",
			WS_CHILD | WS_VISIBLE,
			cr.right / 9 * 3.75,
			cr.bottom / 3,
			cr.right / 9*1.5,
			30,
			hWnd,
			(HMENU)ID_button1,
			hinst, NULL);

		button2 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			L"<< Переместить",
			WS_CHILD | WS_VISIBLE,
			cr.right / 9 * 3.75,
			cr.bottom / 2,
			cr.right / 9 * 1.5,
			30,
			hWnd,
			(HMENU)ID_button2,
			hinst, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
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