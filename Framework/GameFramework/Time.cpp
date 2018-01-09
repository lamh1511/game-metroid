#include "Time.h"
#include "Main\GameSystem.h"

double Time::deltaTime = 0;

Time::Time()
{
}

Time::~Time()
{
}

double Time::GetDeltaTime()
{
	return GameSystem::GetDeltaTime();
}