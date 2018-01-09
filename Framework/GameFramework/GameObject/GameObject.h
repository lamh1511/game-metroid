#pragma once
#include "GameFramework\Object.h"
#include <string>
#include <list>
#include "GameFramework\GameComponent\AnimationController.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "GameFramework\GameComponent\SpriteRenderer.h"
#include "GameFramework\GameComponent\SimulatePhysics.h"
#include "GameFramework\Input.h"
#include "GameFramework\Time.h"
#include "GameFramework\Scene\Scene.h"

class Scene;
class Component;
class QuadTree;
class Spawner;

enum PENDING_TASK
{
	NONE, DESTROY, CREATE, REMOVE_FROM_ACTIVE_LIST
};

class GameObject : public Object
{
public:
	GameObject(const Transform& transform = Transform(Vec2(0, 0), 0, Vec2(1.0f, 1.0f)), const std::string& tag = "None", const std::string& name = "None", bool isControllable = false);
	virtual ~GameObject();
public:
	template <class Type> Type* AddComponent();
	template <class Type> Type* GetComponent();
	std::list<Component*>& GetAllComponents();
public:
	bool IsControllable();
	const std::string& GetTag();
	Transform& GetTransform();
	void SetTransform(const Transform& transform);
	void Translate(const Vec2& translation);
	Scene* GetScene();
	void SetTag(const std::string& tag);
protected:
	bool isControllable;
	Spawner* spawner;
	bool isAlwaysActive;
protected:
	Transform transform;
	Scene* scene;
	std::string tag;
	PENDING_TASK pendingTask;
	std::list<Component*> components;
protected:
	virtual void OnSpawn(); // Khi game object vua duoc scene tao ra
	virtual void Update(); // Update game logic
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2(0, 0)) {};// tu kich hoat khi va cham voi game object khac
	virtual void LateUpdate(); // Chu yeu dung de render
	friend class Scene;
	friend class SimulatePhysics;
	friend class QuadTree;
	friend class Spawner;
};


template<class Type>
inline Type * GameObject::AddComponent()
{
	Type* newComponent = new Type();
	this->components.push_back(newComponent);
	newComponent->gameObject = this;
	return newComponent;
}

template<class Type>
inline Type * GameObject::GetComponent()
{
	for (Component* component : components)
	{
		Type * com = dynamic_cast<Type*>(component);
		if (com)
		{
			return com;
		}
	}
	return nullptr;
}


