#include "ZoomerAnimation.h"
#include "MetroidContent.h"
#include "Zoomer.h"
#include "EnergyBall.h"

ZoomerAnimation::ZoomerAnimation()
{
}

ZoomerAnimation::~ZoomerAnimation()
{	
}

void ZoomerAnimation::OnSpawn()
{
	mainAnim = AddAnimation(MetroidContent::GetObjectByName<Animation>("ZoomerMainAnimation"));
	currentAnimation = mainAnim;
	zoomer = static_cast<Zoomer*>(gameObject);
	AnimationController::OnSpawn();
}

//void ZoomerAnimation::Update()
//{
//	AnimationController::Update();
//}
//
//void ZoomerAnimation::LateUpdate()
//{
//	AnimationController::LateUpdate();
//}
