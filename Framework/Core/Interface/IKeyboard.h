#pragma once

class IKeyboard
{
public:
	IKeyboard() {};
	virtual ~IKeyboard() {};
public:
	virtual bool IsKeyDown(unsigned int key) = 0;
	virtual bool IsKeyUp(unsigned int key) = 0;
	virtual bool IsKeyPressed(unsigned int key) = 0;
	virtual bool IsKeyReleased(unsigned int key) = 0;
};

