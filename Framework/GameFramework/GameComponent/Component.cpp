#include "Component.h"
#include "GameFramework\GameObject\GameObject.h"


Component::Component(const std::string & name):
	Object(name),
	gameObject(nullptr)
{
}


Component::~Component()
{
}

GameObject * Component::GetOwner()
{
	return this->gameObject;
}

std::string Component::GetTag()
{
	return this->gameObject->GetTag();
}
