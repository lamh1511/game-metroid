#pragma once

class Time
{
public:
	Time();
	~Time();
public:
	static double GetDeltaTime();
private:
	static double deltaTime;
};

