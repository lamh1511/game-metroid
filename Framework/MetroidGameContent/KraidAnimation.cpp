#include "KraidAnimation.h"
#include "MetroidContent.h"
#include "Kraid.h"


KraidAnimation::KraidAnimation()
{
}

KraidAnimation::~KraidAnimation()
{
}

void KraidAnimation::OnSpawn()
{
	idle = MetroidContent::GetObjectByName<Animation>("KraidAnimation");

	AnimationCollection.push_back(idle);

	currentAnimation = idle;

	AnimationController::OnSpawn();
}

void KraidAnimation::Update()
{
	AnimationController::Update();
	//gameObject->GetTransform().scale.x *= -1.0f;
}
