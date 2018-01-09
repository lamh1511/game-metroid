#include "EnergyBall.h"
#include "MetroidCharacter.h"
#include "MetroidContent.h"

EnergyBall::EnergyBall() :
	lifeTime(8.0)
{
	this->tag = "EnergyBall";
	this->name = "EnergyBall";

	SimulatePhysics* physic = AddComponent<SimulatePhysics>();
	physic->SetBodySize(Vec2(0.2f, 0.2f));
	physic->SetStatic(1);
	physic->DisableCollision(true);

	AddComponent<AnimationController>()->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("EnergyBall"));
}


EnergyBall::~EnergyBall()
{
}

void EnergyBall::Update()
{
	GameObject::Update();
	lifeTime -= Time::GetDeltaTime();
	if (lifeTime <= 0) scene->DestroyGameObject(this);
}

void EnergyBall::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (other->GetTag() == "Player")
	{
		MetroidCharacter* samus = static_cast<MetroidCharacter*>(other);
		samus->energy += 5;
		if (samus->energy >= 100) samus->energy = 99;
		scene->DestroyGameObject(this);
	}
}
