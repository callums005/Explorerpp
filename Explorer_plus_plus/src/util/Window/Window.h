#pragma once

#include <stdint.h>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <ShObjIdl.h>

#include "../Debug.h"


namespace Utils
{
	class WindowParams
	{
	public:
		WindowParams(int width, int height, 
			int x, int y, LPCWSTR title, DWORD extendedStyle = 0)
			: m_Width(width), m_Height(height), m_PosX(x), m_PosY(y), m_Title(title), m_ExtendedStyle(extendedStyle)
		{
		}

		int m_Width;
		int m_Height;
		int m_PosX;
		int m_PosY;
		LPCWSTR m_Title;
		// Extended window styles can be found [here](https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles)
		DWORD m_ExtendedStyle;
	};

	class Window
	{
	public:
		Window();
		Window(HINSTANCE hInstance, int nCmdShow, WindowParams params, HWND parentWindow = NULL);
		~Window();

		void SetIcon(LPCWSTR icon);
		void SetCursor(LPCWSTR icon);
		int OpenFileExplorer();

		HWND GetHWND();
	private:
		WNDCLASS m_WindowClass = {};
		HWND m_HWND;

		static bool isParent;

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}