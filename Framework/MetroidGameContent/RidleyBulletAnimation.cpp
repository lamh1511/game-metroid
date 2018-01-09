#include "RidleyBulletAnimation.h"
#include "MetroidContent.h"
#include "RidleyBullet.h"


RidleyBulletAnimation::RidleyBulletAnimation()
{
	waiting = 0;
	//ridleybullet = static_cast<RidleyBullet*>(gameObject->GetScene()->FindGameObjectByName("RidleyBullet"));
}

RidleyBulletAnimation::~RidleyBulletAnimation()
{
}

void RidleyBulletAnimation::OnSpawn()
{
	anim = MetroidContent::GetObjectByName<Animation>("RidleyBulletAnimation");
	
	AnimationCollection.push_back(anim);

	currentAnimation = anim;
	
	AnimationController::OnSpawn();
}

void RidleyBulletAnimation::Update()
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

void RidleyBulletAnimation::LateUpdate()
{
	AnimationController::LateUpdate();
}