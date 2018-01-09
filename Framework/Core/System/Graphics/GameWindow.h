#pragma once
#include <Windows.h>
#include <string>

class GraphicsD3D9;

class GameWindow
{
public:
	GameWindow() {};
	~GameWindow() {};
	bool CreateGameWindow(int windowWidth, int windowHeight, int positionX, int positionY, std::string windowName, DWORD windowStyle, std::string windowClassName);
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	int	windowWidth;
	int	windowHeight;
	int positionX;
	int positionY;
	HWND handleWindow;
	HINSTANCE handleInstance;
	std::string windowName;
	std::string windowClassName;
	DWORD windowStyle;
private:
	friend class GraphicsD3D9;
};

