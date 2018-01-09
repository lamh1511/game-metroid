#pragma once
#include "Core\System\System.h"
#include "Core\Interface\ITime.h"
#include <Windows.h>

class SystemManager;

class WindowsTime final : public System, public ITime
{
public:
	WindowsTime();
	~WindowsTime() {};
public:
	bool Initialize();
	void Update();
	bool Shutdown();
public:
	void StartTimer();
	double GetTimerValue();
	void ResetTimer();
	bool IsTimerRunning();

	double GetLifeTime();
private:
	LONGLONG TimerStartValue;
	bool isTimerRunning;
	LONGLONG clockRate;
	LONGLONG createTime;
private:
	friend class SystemManager;
};

