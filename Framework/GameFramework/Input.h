#pragma once
#include <Windows.h>

#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44
#define VK_W 0x57
#define VK_X 0x58
#define VK_Z 0x5A
#define VK_C 0x43

class Input
{
public:
	Input();
	~Input();
public:
	static bool IsKeyDown(unsigned int key);
	static bool IsKeyPressed(unsigned int key);
	static bool IsKeyReleased(unsigned int key);

	static bool locked;
};

