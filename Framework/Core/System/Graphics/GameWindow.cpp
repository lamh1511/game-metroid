#include "GameWindow.h"


bool GameWindow::CreateGameWindow(int windowWidth, int windowHeight, int positionX, int positionY, std::string windowName, DWORD windowStyle, std::string windowClassName)
{
	this->positionX = positionX;
	this->positionY = positionY;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->windowName = windowName;
	this->windowClassName = windowClassName;
	this->handleInstance = GetModuleHandle(NULL);
	this->windowStyle = windowStyle;

	RECT rect = { 0, 0, windowWidth, windowHeight };
	AdjustWindowRect(&rect, windowStyle, FALSE);
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = handleInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = this->windowClassName.c_str();
	RegisterClassEx(&wc);
	handleWindow = CreateWindow(this->windowClassName.c_str(), this->windowName.c_str(), this->windowStyle, this->positionX, this->positionY, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, this->handleInstance, NULL);
	ShowWindow(this->handleWindow, SW_SHOW);
	return true;
}

LRESULT GameWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}