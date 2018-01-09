#include "Input.h"
#include "Main\GameSystem.h"

bool Input::locked = 0;

Input::Input()
{
}


Input::~Input()
{
}

bool Input::IsKeyDown(unsigned int key)
{
	return (locked) ? (false):(GameSystem::IsKeyDown(key));
}

bool Input::IsKeyPressed(unsigned int key)
{
	return (locked) ? (false) : (GameSystem::IsKeyPressed(key));
}

bool Input::IsKeyReleased(unsigned int key)
{
	return (locked) ? (false) : (GameSystem::IsKeyReleased(key));
}
