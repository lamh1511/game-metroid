#include "KeyboardWindows.h"



bool KeyboardWindows::IsKeyDown(unsigned int key)
{
	return ((previous_keyboard_state[key] & 0xF0) != 0 && (current_keyboard_state[key] & 0xF0) != 0);
}

bool KeyboardWindows::IsKeyUp(unsigned int key)
{
	return ((previous_keyboard_state[key] & 0xF0) == 0 && (current_keyboard_state[key] & 0xF0) == 0);
}

bool KeyboardWindows::IsKeyPressed(unsigned int key)
{
	return ((previous_keyboard_state[key] & 0xF0) == 0 && (current_keyboard_state[key] & 0xF0) != 0);
}

bool KeyboardWindows::IsKeyReleased(unsigned int key)
{
	return ((previous_keyboard_state[key] & 0xF0) != 0 && (current_keyboard_state[key] & 0xF0) == 0);
}

bool KeyboardWindows::Initialize()
{
	keyboard_state_0 = new BYTE[256];
	keyboard_state_1 = new BYTE[256];

	GetKeyboardState(keyboard_state_0);
	GetKeyboardState(keyboard_state_1);

	keyboard_state_0_active = 0;
	return true;
}

void KeyboardWindows::Update()
{
	BOOL getKeyboardResult;
	if (keyboard_state_0_active)
	{
		getKeyboardResult = GetKeyboardState(keyboard_state_1);
		previous_keyboard_state = keyboard_state_0;
		current_keyboard_state = keyboard_state_1;
	}
	else
	{
		getKeyboardResult = GetKeyboardState(keyboard_state_0);
		previous_keyboard_state = keyboard_state_1;
		current_keyboard_state = keyboard_state_0;
	}
	keyboard_state_0_active = !keyboard_state_0_active;
}

bool KeyboardWindows::Shutdown()
{
	if (keyboard_state_0)
	{
		delete keyboard_state_0;
		keyboard_state_0 = nullptr;
	}
	if (keyboard_state_1)
	{
		delete keyboard_state_1;
		keyboard_state_1 = nullptr;
	}
	return true;
}
