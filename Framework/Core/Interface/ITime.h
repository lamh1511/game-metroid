#pragma once
class ITime
{
public:
	ITime() {};
	virtual ~ITime() {};
public:
	virtual void StartTimer() = 0;
	virtual double GetTimerValue() = 0;
	virtual void ResetTimer() = 0;
	virtual bool IsTimerRunning() = 0;
	virtual double GetLifeTime() = 0;
};

