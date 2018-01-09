#include "SkreeAnimation.h"
#include "MetroidContent.h"


SkreeAnimation::SkreeAnimation()
{
}


SkreeAnimation::~SkreeAnimation()
{
}

void SkreeAnimation::OnSpawn()
{
	mainAnim = MetroidContent::GetObjectByName<Animation>("SkreeMainAnimation");

	AnimationCollection.push_back(mainAnim);

	currentAnimation = mainAnim;

	AnimationController::OnSpawn();
}

void SkreeAnimation::Update()
{
	AnimationController::Update();
}

void SkreeAnimation::LateUpdate()
{
	AnimationController::LateUpdate();
}
