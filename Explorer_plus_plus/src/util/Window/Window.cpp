#include "Window.h"

HWND text;
HWND button;
HWND textBox;

WCHAR textedSaved[20];

namespace Utils
{
	bool Window::isParent = true;

	LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CREATE:
			text = CreateWindow(L"STATIC",
				L"Hello World",
				WS_VISIBLE | WS_CHILD,
				20, 20,
				200, 50,
				hwnd,
				NULL,
				NULL,
				NULL);

			button = CreateWindow(L"BUTTON",
				L"Click Me",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				20, 90,
				200, 50,
				hwnd,
				(HMENU)1, // Command Identifier
				NULL,
				NULL);

			textBox = CreateWindow(L"EDIT",
				L"PLACEHOLDER..",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				20, 160,
				200, 50,
				hwnd,
				NULL,
				NULL,
				NULL);

			CreateWindow(L"BUTTON",
				L"Submit",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				20, 220,
				200, 50,
				hwnd,
				(HMENU)2,
				NULL,
				NULL);
			break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case 1:
				//MessageBeep(MB_DEFBUTTON1);
				//MessageBox(hwnd, L"Hello World!", L"Button", MB_OK | MB_OKCANCEL);

				text = CreateWindow(L"STATIC",
					L"Bye! World",
					WS_VISIBLE | WS_CHILD,
					20, 20,
					200, 50,
					hwnd,
					NULL,
					NULL,
					NULL);
				break;
			case 2:
				int getStatus = 0;

				getStatus = GetWindowText(textBox, &textedSaved[0], 20);
				MessageBox(hwnd, textedSaved, L"TextBox Entry", MB_OK);
				break;
			}
			break;
		case WM_DESTROY:
			if (isParent)
				PostQuitMessage(0);
			else
				DestroyWindow(hwnd);

			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
		return 0;

		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}

	Window::Window() {}

	Window::Window(HINSTANCE hInstance, int nCmdShow, WindowParams params, HWND parentWindow)
	{
		if (parentWindow != NULL)
			isParent = false;

		const wchar_t className[] = L"Explorer++";

		m_WindowClass.lpfnWndProc = WindowProc;
		m_WindowClass.hInstance = hInstance;
		m_WindowClass.lpszClassName = className;

		SetIcon(IDI_APPLICATION);
		SetCursor(IDC_CROSS);

		RegisterClass(&m_WindowClass);

		m_HWND = CreateWindowEx(
			params.m_ExtendedStyle,
			className,
			params.m_Title,
			WS_OVERLAPPEDWINDOW,
			params.m_PosX, params.m_PosY, params.m_Width, params.m_Height,
			parentWindow, 
			NULL,
			hInstance,
			NULL

		); // Create the Win32 API Window

		Debug::Assert(m_HWND == NULL, "Unable to create a WinAPI window.");

		ShowWindow(m_HWND, nCmdShow);
	}
	
	Window::~Window()
	{
	}

	// Window Set Functions

	void Window::SetIcon(LPCWSTR icon)
	{
		m_WindowClass.hIcon = LoadIcon(NULL, icon);
	}

	void Window::SetCursor(LPCWSTR icon)
	{
		m_WindowClass.hCursor = LoadCursor(NULL, icon);
	}

	// Extra Window Functions

	int Window::OpenFileExplorer()
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		if (FAILED(hr))
		{
			Utils::Debug::Assert(FAILED(hr), "Unable to init COM");
			return 0;
		}
		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* pFileOpen;

			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				hr = pFileOpen->Show(NULL);

				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						if (SUCCEEDED(hr))
						{
							MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}

			CoUninitialize();
		}
	}

	// Window Get Functions

	HWND Window::GetHWND()
	{
		return m_HWND;
	}
}