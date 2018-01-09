#include "MaruMari.h"
#include "MetroidGameContent\MetroidContent.h"
#include "SamusAnimation.h"

MaruMari::MaruMari()
{
	this->name = "MaruMari";
	
	SimulatePhysics* physic = AddComponent<SimulatePhysics>();
	physic->SetBodySize(Vec2(0.8f, 0.8f));
	physic->SetStatic(true);
	physic->DisableCollision(true);
	physic->SetMass(0);

	AnimationController* anim = AddComponent<AnimationController>();
	anim->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("MaruMariAnimation"));

}

MaruMari::~MaruMari()
{
}

void MaruMari::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	GameObject::OnCollisionEnter(other, normal);
	if (other->GetName() == "Samus")
	{
		SamusAnimation* anim = other->GetComponent<SamusAnimation>();
		anim->EnableRolling();
		Sleep(4000);
		GetScene()->DestroyGameObject(this);
	}
}

void MaruMari::OnSpawn()
{
	SetTransform(Transform(Vec2(22.5f, 80.5f)));
	GameObject::OnSpawn();
}

void MaruMari::Update()
{
	GameObject::Update();
}
