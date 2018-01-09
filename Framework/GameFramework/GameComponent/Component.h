#pragma once
#include "GameFramework\Object.h"

class GameObject;

class Component : public Object
{
public:
	Component(const std::string& name = "None");
	virtual ~Component();
public:
	GameObject* GetOwner();
	std::string GetTag();
protected:
	GameObject* gameObject;
protected:
	virtual void OnSpawn() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	friend class GameObject;
};

