#include "Scene.h"
#include <algorithm>
#include "GameFramework\GameObject\GameObject.h"
#include "GameFramework\GameComponent\SimulatePhysics.h"
#include "GameFramework\GameContent\GameContent.h"
#include "MetroidGameContent\QuadTree.h"
#include "MetroidGameContent\MainCamera.h"
#include "MetroidGameContent\Spawner.h"

Scene::Scene(const std::string& name) :
	Object(name)
{
}

Scene::~Scene()
{
	for (GameObject* gameObject : GameObjectsList)
	{
		if (gameObject)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}
	GameObjectsList.clear();
	MetroidQuadtree->Clear();
}

inline bool IsColliding(const RectF& bodyRect, const RectF & otherRect)
{
	return !(bodyRect.right < otherRect.left || bodyRect.left > otherRect.right || bodyRect.top < otherRect.bottom || bodyRect.bottom > otherRect.top);
}

void Scene::Update()
{
	MetroidQuadtree->Retrieve(ActiveGameObjects, camera->GetCameraRect());
	for (GameObject* box : ActiveGameObjects)
	{
		SimulatePhysics* staticBox = box->GetComponent<SimulatePhysics>();
		if (!staticBox) continue;
		boxes.push_back(staticBox);
	}
	for (GameObject* box : AlwaysActiveGameObjects)
	{
		SimulatePhysics* staticBox = box->GetComponent<SimulatePhysics>();
		if (!staticBox) continue;
		boxes.push_back(staticBox);
	}

	for (GameObject* gameObject : ActiveGameObjects) //luon luon dc update truoc ControllableGameObjects.
	{
		gameObject->Update();
	}
	for (GameObject* gameObject : AlwaysActiveGameObjects) //luon luon dc update truoc ControllableGameObjects.
	{
		gameObject->Update();
	}
	for (GameObject* gameObject : ControllableGameObjects)
	{
		gameObject->Update();
	}
	for (GameObject* gameObject : ActiveGameObjects)
	{
		gameObject->LateUpdate();
	}
	for (GameObject* gameObject : AlwaysActiveGameObjects)
	{
		gameObject->LateUpdate();
	}
	for (GameObject* gameObject : ControllableGameObjects)
	{
		gameObject->LateUpdate();
	}
	camera->GetOwner()->LateUpdate();
	static_cast<MainCamera*>(camera->GetOwner())->collidePortal = 0;
	boxes.clear();
	ActiveGameObjects.clear();
	HandlePendingGameObjects();
}

void Scene::BeginScene()
{
	HandlePendingGameObjects();
	camera = FindGameObjectByName("MainCamera")->GetComponent<CameraComponent>();
}

std::vector<SimulatePhysics*>& Scene::GetCollisionBoxes()
{
	return this->boxes;
}

GameObject * Scene::SpawnNewGameObject(GameObject * newGameObject)
{
	GameObjectsList.push_back(newGameObject);
	newGameObject->scene = this;
	newGameObject->pendingTask = CREATE;
	PendingGameObjects.push_back(newGameObject);
	return newGameObject;
}

void Scene::DestroyGameObject(GameObject * gameObject)
{
	if (!gameObject || gameObject->scene != this) return;
	if (gameObject->spawner) gameObject->spawner->DestroyGameObject();
	gameObject->pendingTask = DESTROY;
	PendingGameObjects.push_back(gameObject);
}

void Scene::RemoveGameObjectFromActiveList(GameObject * gameObject)
{
	gameObject->pendingTask = REMOVE_FROM_ACTIVE_LIST;
	PendingGameObjects.push_back(gameObject);
}

GameObject * Scene::FindGameObjectByName(const std::string & name)
{
	for (GameObject* gameObject : GameObjectsList)
	{
		if (gameObject->GetName() == name) return gameObject;
	}
	return nullptr;
}

void Scene::HandlePendingGameObjects()
{
	for (std::list<GameObject*>::iterator it = PendingGameObjects.begin(); it != PendingGameObjects.end(); it++)
	{
		if ((*it)->pendingTask == DESTROY)
		{
			ActiveGameObjects.remove((*it));
			GameObjectsList.remove((*it));
			ControllableGameObjects.remove((*it));
			AlwaysActiveGameObjects.remove((*it));
			if ((*it))
			{
				delete (*it);
				(*it) = nullptr;
			}
			continue;
		}
		if ((*it)->pendingTask == CREATE)
		{
			(*it)->pendingTask = NONE;
			if ((*it)->isControllable == true)
			{
				ControllableGameObjects.push_back((*it));
			}
			else if ((*it)->isAlwaysActive == true)
			{
				AlwaysActiveGameObjects.push_back((*it));
			}
			(*it)->OnSpawn();
			continue;
		}
		if ((*it)->pendingTask == REMOVE_FROM_ACTIVE_LIST)
		{
			ActiveGameObjects.remove((*it));
			(*it)->pendingTask = NONE;
			continue;
		}
	}
	PendingGameObjects.clear();
}

