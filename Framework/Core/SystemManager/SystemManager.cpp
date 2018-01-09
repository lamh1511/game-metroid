#include "SystemManager.h"


SystemManager* SystemManager::instance = nullptr;

SystemManager * SystemManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SystemManager;
	}
	return instance;
}

bool SystemManager::Initialize()
{
	return
		SystemManager::GetInstance()->GetSystem<GraphicsD3D9>()->Initialize() &&
		SystemManager::GetInstance()->GetSystem<KeyboardWindows>()->Initialize() &&
		SystemManager::GetInstance()->GetSystem<WindowsTime>()->Initialize();
}

bool SystemManager::Shutdown()
{
	if (!
		SystemManager::GetInstance()->GetSystem<KeyboardWindows>()->Shutdown() &&
		SystemManager::GetInstance()->GetSystem<WindowsTime>()->Shutdown() &&
		SystemManager::GetInstance()->GetSystem<GraphicsD3D9>()->Shutdown()
		) return false;

	for (System* system : Systems)
	{
		if (system)
		{
			delete system;
			system = nullptr;
		}
	}
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
	return true;
}
