#pragma once
#include "GameFramework\Object.h"
#include <list>
#include <vector>

class Game;
class CameraComponent;
class SimulatePhysics;
class GameObject;
class QuadTree;

class Scene : public Object
{
public:
	Scene(const std::string& name = "None");
	virtual ~Scene();
public:
	std::vector<SimulatePhysics*>& GetCollisionBoxes();
protected:
	void BeginScene();
	void Update();
	
	inline void HandlePendingGameObjects();
public:
	template <class Type> Type* SpawnNewGameObject(const Transform& transform);
	GameObject* SpawnNewGameObject(GameObject* newGameObject);
	void DestroyGameObject(GameObject* gameObject);
	void RemoveGameObjectFromActiveList(GameObject* gameObject);
	GameObject* FindGameObjectByName(const std::string& name);
	CameraComponent* camera;
protected:
	std::list<GameObject*> GameObjectsList;// tat ca game object ton tai trong scene
	std::list<GameObject*> PendingGameObjects;// nhung game object can xu ly khi ket thuc framne hien tai
	std::list<GameObject*> ActiveGameObjects;// nhung game object se duoc update, clear moi frame
	std::list<GameObject*> AlwaysActiveGameObjects;
	std::list<GameObject*> ControllableGameObjects;// game object do nguoi choi dieu khien, samus, bomb, beam,..

	std::list<GameObject*> GameObjectsInQuadTree;

	QuadTree* MetroidQuadtree;
	friend class Game;
	friend class QuadTree;
	std::vector<SimulatePhysics*> boxes;
	
};

template<class Type>
inline Type* Scene::SpawnNewGameObject(const Transform & transform)
{
	Type* newGameObject = new Type();
	GameObjectsList.push_back(newGameObject);
	newGameObject->scene = this;
	newGameObject->transform = transform;
	newGameObject->pendingTask = CREATE;
	PendingGameObjects.push_back(newGameObject);
	return newGameObject;
}