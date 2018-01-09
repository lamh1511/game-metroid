#include "Explosion.h"
#include "MetroidContent.h"


Explosion::Explosion()
{
	this->tag = "Explosion";
	this->name = "Explosion";
	explosion = AddComponent<AnimationController>()->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("EnemyExposion"));
}


Explosion::~Explosion()
{
}

void Explosion::LateUpdate()
{
	GameObject::LateUpdate();
	if (explosion->currentActiveSprite == nullptr)
	{
		scene->DestroyGameObject(this);
	}
}
