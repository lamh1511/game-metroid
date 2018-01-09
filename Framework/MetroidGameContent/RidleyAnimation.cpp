#include "RidleyAnimation.h"
#include "MetroidContent.h"
#include "Ridley.h"


RidleyAnimation::RidleyAnimation()
{
}

RidleyAnimation::~RidleyAnimation()
{
}

void RidleyAnimation::OnSpawn()
{
	idle = MetroidContent::GetObjectByName<Animation>("RidleyIdleAnimation");
	jump = MetroidContent::GetObjectByName<Animation>("RidleyJumpAnimation");
	damagedIdle = MetroidContent::GetObjectByName<Animation>("RidleyDamagedIdleAnimation");
	damagedJump = MetroidContent::GetObjectByName<Animation>("RidleyDamagedJumpAnimation");
	dead = MetroidContent::GetObjectByName<Animation>("RidleyDeadAnimation");
	AnimationCollection.push_back(idle);
	AnimationCollection.push_back(jump);
	AnimationCollection.push_back(damagedIdle);
	AnimationCollection.push_back(damagedJump);

	currentAnimation = idle;


	ridley = static_cast<Ridley*>(gameObject->GetScene()->FindGameObjectByName("Ridley"));
	AnimationController::OnSpawn();
}

void RidleyAnimation::Update()
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

	if (ridley->isDead)
	{
		currentAnimation = dead;
		this->SetColor(ARGB(180, 255, 255, 255));
	}
	else
	{
		if (ridley->waiting == 0 && !ridley->damaged)
		{
			currentAnimation = jump;
		}
		else if (ridley->waiting == 1 && !ridley->damaged)
		{
			currentAnimation = idle;
		}

		if (ridley->damagedIdle)
		{
			currentAnimation = damagedIdle;
		}
		else if (ridley->damagedJump)
		{
			currentAnimation = damagedJump;
		}
	}
	
	
	AnimationController::Update();
}

void RidleyAnimation::LateUpdate()
{
	AnimationController::LateUpdate();
}

//void RidleyAnimation::Jump()
//{
//	if (CameraComponent::tiles[(int)(ridley->GetTransform().position.y -1.25f)][(int)ridley->GetTransform().position.x] != -1)
//	{
//		currentAnimation = jump;
//		return;
//	}
//}
//
//void RidleyAnimation::Idle()
//{
//	if (CameraComponent::tiles[(int)(ridley->GetTransform().position.y -1.25f)][(int)ridley->GetTransform().position.x] != -1)
//	{
//		currentAnimation = idle;
//		return;
//	}
//}
