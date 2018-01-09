#include "BumerangAnimation.h"
#include "MetroidContent.h"
#include "Bumerang.h"


BumerangAnimation::BumerangAnimation()
{
	waiting = 0;
	//ridleybullet = static_cast<RidleyBullet*>(gameObject->GetScene()->FindGameObjectByName("RidleyBullet"));
}

BumerangAnimation::~BumerangAnimation()
{
}

void BumerangAnimation::OnSpawn()
{
	anim = MetroidContent::GetObjectByName<Animation>("KraidBumerangAnimation");

	AnimationCollection.push_back(anim);

	currentAnimation = anim;

	AnimationController::OnSpawn();
}

void BumerangAnimation::Update()
{
	//if (this->currentAnimation == idle)
	//{
	//	Jump(); //nhay
	//	if (CameraComponent::tiles[(int)(ridley->GetTransform().position.y - 1.25f)][(int)ridley->GetTransform().position.x] == -1)
	//		currentAnimation = jump;
	//}
	//else if (this->currentAnimation == jump)
	//{
	//	Idle(); // dung

	//}

	AnimationController::Update();
}

void BumerangAnimation::LateUpdate()
{
	AnimationController::LateUpdate();
}