#pragma once
#include "Core\System\System.h"
#include "Core\Interface\IKeyboard.h"
#include <Windows.h>

class SystemManager;

class KeyboardWindows final : public System, public IKeyboard
{
public:
	KeyboardWindows() {};
	~KeyboardWindows() {};
public:
	bool IsKeyDown(unsigned int key);
	bool IsKeyUp(unsigned int key);
	bool IsKeyPressed(unsigned int key);
	bool IsKeyReleased(unsigned int key);
public:
	bool Initialize();
	void Update();
	bool Shutdown();
private:
	BYTE* current_keyboard_state;
	BYTE* previous_keyboard_state;
	BYTE* keyboard_state_0;
	BYTE* keyboard_state_1;

	bool keyboard_state_0_active;
private:
	friend class SystemManager;
};

