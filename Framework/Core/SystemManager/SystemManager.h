#pragma once
#include <vector>

// include all system header files here.
#include "Core\System\Graphics\GraphicsD3D9.h"
#include "Core\System\Keyboard\KeyboardWindows.h"
#include "Core\System\Time\WindowsTime.h"
//================================================//
#define DRAW(transform, textureID, rect, pixelsPerUnit, sortingOrder, color) {SystemManager::GetInstance()->GetSystem<GraphicsD3D9>()->AddToDrawQueue(transform, textureID, rect, pixelsPerUnit, sortingOrder, color);}
#define SYSTEM_KEY_DOWN(key) SystemManager::GetInstance()->GetSystem<KeyboardWindows>()->IsKeyDown(key)
#define SYSTEM_KEY_PRESSED(key) SystemManager::GetInstance()->GetSystem<KeyboardWindows>()->IsKeyPressed(key)
#define SYSTEM_KEY_RELEASED(key) SystemManager::GetInstance()->GetSystem<KeyboardWindows>()->IsKeyReleased(key)
#define VIEW_POSITION(position) {SystemManager::GetInstance()->GetSystem<GraphicsD3D9>()->SetViewPosition(position);}

class Game;

class SystemManager
{
public:
	~SystemManager() {};
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
public:
	static SystemManager* GetInstance();
	template <typename Type> Type* GetSystem();
	bool Initialize();
	bool Shutdown();
private:
	SystemManager() {};
private:
	std::vector<System*> Systems;
	static SystemManager* instance;
	friend class Game;
};

template<typename Type>
inline Type * SystemManager::GetSystem()
{
	for (System* system : Systems)
	{
		Type * DesiredSystem = dynamic_cast<Type*>(system);
		if (DesiredSystem)
		{
			return DesiredSystem;
		}
	}
	Type* NewSystem = new Type();
	Systems.push_back(NewSystem);
	return NewSystem;
}
