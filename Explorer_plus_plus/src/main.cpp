#pragma comment(linker, "/SUBSYSTEM:CONSOLE /ENTRY:wWinMainCRTStartup") // Makes sure the linker actually uses the wWinMain function instead of default "main"
#include <Windows.h>


#include "util/Window/Window.h"

// Adapted main function that works with Win32 API
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Utils::Window* window = new Utils::Window(hInstance, nCmdShow, Utils::WindowParams(900, 600, CW_USEDEFAULT, CW_USEDEFAULT, L"Explorer++")); // Wrapper round the Win32 API window class, makes it cleaner to create multiple windows.
	Utils::Window* childW = new Utils::Window(hInstance, nCmdShow, Utils::WindowParams(400, 400, CW_USEDEFAULT, CW_USEDEFAULT, L"Tool", FCW_TOOLBAR), window->GetHWND()); // Wrapper round the Win32 API window class, makes it cleaner to create multiple windows.
	
	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}