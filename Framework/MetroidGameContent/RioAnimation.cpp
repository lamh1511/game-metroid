#include "RioAnimation.h"
#include "MetroidContent.h"


RioAnimation::RioAnimation()
{
}


RioAnimation::~RioAnimation()
{
}

void RioAnimation::OnSpawn()
{
	mainAnim = MetroidContent::GetObjectByName<Animation>("RioMainAnimation");

	AnimationCollection.push_back(mainAnim);

	currentAnimation = mainAnim;

	AnimationController::OnSpawn();
}
