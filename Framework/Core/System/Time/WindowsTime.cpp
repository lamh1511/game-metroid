#include "WindowsTime.h"


WindowsTime::WindowsTime() :
	isTimerRunning(0),
	TimerStartValue(0)
{
	LARGE_INTEGER frequency;
	if (QueryPerformanceFrequency(&frequency))
	{
		clockRate = frequency.QuadPart;
	}
	else return;

	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);
	createTime = start.QuadPart;
}

bool WindowsTime::Initialize()
{
	return true;
}

void WindowsTime::Update()
{
}

bool WindowsTime::Shutdown()
{
	return true;
}

void WindowsTime::StartTimer()
{
	isTimerRunning = 1;
	LARGE_INTEGER start;
	QueryPerformanceCounter(&start);
	TimerStartValue = start.QuadPart;
}

double WindowsTime::GetTimerValue()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return ((double)time.QuadPart - (double)TimerStartValue) / (double)clockRate;
}

void WindowsTime::ResetTimer()
{
	isTimerRunning = 0;
	TimerStartValue = 0;
}

bool WindowsTime::IsTimerRunning()
{
	return isTimerRunning;
}

double WindowsTime::GetLifeTime()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return ((double)time.QuadPart - (double)createTime) / (double)clockRate;
}
