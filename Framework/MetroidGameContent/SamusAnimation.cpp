#include "SamusAnimation.h"
#include "MetroidContent.h"
#include "GameFramework\GameContent\Animation.h"
#include "MetroidCharacter.h"
#include "SamusDamage.h"



SamusAnimation::SamusAnimation() :
	stateLocked(0)
{
	run = MetroidContent::GetObjectByName<Animation>("Run");
	/*roll = MetroidContent::GetObjectByName<Animation>("Roll");*/
	idle = MetroidContent::GetObjectByName<Animation>("Idle");
	roll = idle;
	rotate = MetroidContent::GetObjectByName<Animation>("Rotate");
	jump = MetroidContent::GetObjectByName<Animation>("Jump");
	aimup = MetroidContent::GetObjectByName<Animation>("AimUp");
	shootup = MetroidContent::GetObjectByName<Animation>("ShootUp");
	runshootforward = MetroidContent::GetObjectByName<Animation>("RunShootForward");
	jumpshootup = MetroidContent::GetObjectByName<Animation>("JumpShootUp");
	jumpshootforward = MetroidContent::GetObjectByName<Animation>("JumpShootForward");
	runshootup = MetroidContent::GetObjectByName<Animation>("RunShootUp");

	AnimationCollection.push_back(runshootforward);
	AnimationCollection.push_back(jumpshootup);
	AnimationCollection.push_back(jumpshootforward);
	AnimationCollection.push_back(runshootup);

	AnimationCollection.push_back(run);
	AnimationCollection.push_back(roll);
	AnimationCollection.push_back(rotate);
	AnimationCollection.push_back(jump);
	AnimationCollection.push_back(idle);
	AnimationCollection.push_back(aimup);
	AnimationCollection.push_back(shootup);

	this->currentAnimation = idle;
	maxJumpSpeed = 16.0f;
	jumpSpeed = 20.0f;
	jumpTime = 0;

	RollFunc = &SamusAnimation::Roll_0;
	RollingBodySize = SAMUSBODYSIZE;
	this->EnableRolling();
}

SamusAnimation::~SamusAnimation()
{
}

void SamusAnimation::OnSpawn()
{
	physic = gameObject->GetComponent<SimulatePhysics>();
	Samus = static_cast<MetroidCharacter*>(gameObject);
}

void SamusAnimation::Update()
{
	if (stateLocked == true) return;
	if (isActive == 0) return;

	if (currentAnimation == idle)
	{
		Idle();
	}
	else if (currentAnimation == run)
	{
		Run();
	}
	else if (currentAnimation == rotate)
	{
		Rotate();
	}
	else if (currentAnimation == roll)
	{
		Roll();
	}
	else if (currentAnimation == jump)
	{
		Jump();
	}
	else if (currentAnimation == aimup)
	{
		AimUp();
	}
	else if (currentAnimation == shootup)
	{
		ShootUp();
	}
	else if (currentAnimation == runshootforward)
	{
		RunShootForward();
	}
	else if (currentAnimation == jumpshootup)
	{
		JumpShootUp();
	}
	else if (currentAnimation == jumpshootforward)
	{
		JumpShootForward();
	}
	else if (currentAnimation == runshootup)
	{
		RunShootUp();
	}

}

void SamusAnimation::LateUpdate()
{
	if (physic->GetVelocity().x < 0)
	{
		if (gameObject->GetTransform().scale.x > 0)
			gameObject->GetTransform().scale.x *= -1.0f;
	}
	else if (physic->GetVelocity().x > 0)
	{
		if (gameObject->GetTransform().scale.x < 0)
			gameObject->GetTransform().scale.x *= -1.0f;
	}
	AnimationController::LateUpdate();
}

void SamusAnimation::Idle()
{
	if (Input::IsKeyPressed(VK_DOWN))
	{
		currentAnimation = roll;
		Samus->canShoot = 0;
		physic->SetBodySize(RollingBodySize);
		return;
	}
	if (physic->GetVelocity().x != 0 && physic->GetVelocity().y == 0)
	{
		currentAnimation = run;
		return;
	}
	if (physic->GetVelocity().y > 0)
	{
		currentAnimation = jump;
		return;
	}
	if (Input::IsKeyPressed(VK_UP))
	{
		currentAnimation = aimup;
		return;
	}
}

void SamusAnimation::Run()
{
	if (physic->GetVelocity().x == 0 && physic->GetVelocity().y == 0)
	{
		currentAnimation = idle;
		return;
	}
	if (physic->GetVelocity().y > 0)
	{
		currentAnimation = rotate;
		return;
	}
	if (physic->GetVelocity().y < 0)
	{
		currentAnimation = jump;
		return;
	}

	if (Input::IsKeyPressed(VK_X) || Input::IsKeyDown(VK_X))
	{
		currentAnimation = runshootforward;
		return;
	}

	if (Input::IsKeyPressed(VK_UP) || Input::IsKeyDown(VK_UP))
	{
		currentAnimation = aimup;
		return;
	}
}

void SamusAnimation::Roll()
{
	//(*this.*RollFunc)();
	if (CameraComponent::tiles[(int)Samus->GetTransform().position.y + 1][(int)Samus->GetTransform().position.x] != -1 && CameraComponent::tiles[(int)Samus->GetTransform().position.y][(int)Samus->GetTransform().position.x] != 79) return;

	if (Input::IsKeyDown(VK_X) && Samus->bombEnabled)
	{
		void (SamusDamage::*SamusWeaponType)();
		SamusWeaponType = Samus->WeaponType;
		Samus->WeaponType = &SamusDamage::SamusBomb;
		Samus->Fire(Vec2(1.0f, 0));
		Samus->WeaponType = SamusWeaponType;
	}
	/*if (physic->GetVelocity().y > 0)
	{
		physic->SetVelocity(Vec2(0, 0));
		Samus->jumpTime = 0;
		Samus->Translate(Vec2(0, 0.5f));
		currentAnimation = idle;
		Samus->canShoot = 1;
		physic->SetBodySize(SAMUSBODYSIZE);
		return;
	}*/
	if (Input::IsKeyDown(VK_UP) || Input::IsKeyDown(VK_C))
	{
		physic->SetVelocity(Vec2(0, 0));
		Samus->jumpTime = 0;
		Samus->Translate(Vec2(0, 0.7f));
		currentAnimation = idle;
		Samus->canShoot = 1;
		physic->SetBodySize(SAMUSBODYSIZE);
		return;
	}
}

void SamusAnimation::Jump()
{
	if (Input::IsKeyPressed(VK_UP) || Input::IsKeyDown(VK_UP))
	{
		currentAnimation = jumpshootup;
		return;
	}
	if (physic->GetVelocity().x != 0 && physic->GetVelocity().y == 0)
	{
		currentAnimation = run;
		return;
	}
	if (physic->GetVelocity().x == 0 && physic->GetVelocity().y == 0)
	{
		currentAnimation = idle;
		return;
	}

	if (Input::IsKeyPressed(VK_X) || Input::IsKeyDown(VK_X))
	{
		currentAnimation = jumpshootforward;
		return;
	}
}

void SamusAnimation::Rotate()
{
	if (physic->GetVelocity().x == 0 && physic->GetVelocity().y == 0)
	{
		currentAnimation = idle;
		return;
	}
	if (physic->GetVelocity().x != 0 && physic->GetVelocity().y == 0)
	{
		currentAnimation = run;
		return;
	}
}

void SamusAnimation::AimUp()
{
	if (physic->GetVelocity().x != 0)
	{
		currentAnimation = runshootup;
		return;
	}

	if (!Input::IsKeyDown(VK_UP))
	{
		currentAnimation = idle;
		return;
	}
	if (Input::IsKeyDown(VK_X))
	{
		currentAnimation = shootup;
		return;
	}
	if (physic->GetVelocity().y != 0 )
	{
		currentAnimation = jumpshootup;
		return;
	}
}

void SamusAnimation::ShootUp()
{
	if (physic->GetVelocity().y != 0)
	{
		currentAnimation = jumpshootup;
		return;
	}
	if (physic->GetVelocity().x != 0)
	{
		currentAnimation = runshootup;
		return;
	}
	Samus->Fire(Vec2(0, 1.0f));
	//if (Samus->shootDelayTime <= 0)
	//{
	//	Samus->shootDelayTime = SHOOTDELAYTIME;
	//	//gameObject->GetScene()->SpawnNewGameObject(new SamusDamage(Vec2(gameObject->GetTransform().position.x, gameObject->GetTransform().position.y + 1.2f), Vec2(0, 18.0f), &SamusDamage::NormalBeam));
	//	/*Bullet* b = gameObject->GetScene()->SpawnNewGameObject<Bullet>(Transform());
	//	b->Fire(Vec2(gameObject->GetTransform().position.x, gameObject->GetTransform().position.y + 1.2f), Vec2(0.0f, 1.0f));*/
	//}
	
	if (!Input::IsKeyDown(VK_X))
	{
		currentAnimation = aimup;
		return;
	}
	if (!Input::IsKeyDown(VK_X) && !Input::IsKeyDown(VK_UP))
	{
		currentAnimation = idle;
		return;
	}
}

inline void SamusAnimation::RunShootForward()
{
	if (Input::IsKeyDown(VK_UP))
	{
		currentAnimation = runshootup;
		return;
	}
	if (physic->GetVelocity().y != 0)
	{
		currentAnimation = jump;
		return;
	}
	if (!Input::IsKeyDown(VK_X) && physic->GetVelocity().x != 0)
	{
		currentAnimation = run;
		return;
	}
	if (Input::IsKeyDown(VK_X) && physic->GetVelocity().x == 0)
	{
		currentAnimation = idle;
		return;
	}
}

inline void SamusAnimation::JumpShootUp()
{
	if (!Input::IsKeyDown(VK_X) && !Input::IsKeyDown(VK_UP))
	{
		currentAnimation = jump;
		return;
	}
	
	if (Input::IsKeyDown(VK_X))
	{
		Samus->Fire(Vec2(0, 1.0f));
		/*Samus->shootDelayTime = SHOOTDELAYTIME;
		Bullet* b = gameObject->GetScene()->SpawnNewGameObject<Bullet>(Transform());
		b->Fire(Vec2(gameObject->GetTransform().position.x, gameObject->GetTransform().position.y + 1.2f), Vec2(0.0f, 1.0f));*/
	}
	if (physic->GetVelocity().y == 0)
	{
		currentAnimation = aimup;
		return;
	}
	
}

inline void SamusAnimation::JumpShootForward()
{
	if (Input::IsKeyPressed(VK_UP) || Input::IsKeyDown(VK_UP))
	{
		currentAnimation = jumpshootup;
		return;
	}
	if (physic->GetVelocity().y == 0)
	{
		currentAnimation = idle;
		return;
	}
	if (!Input::IsKeyDown(VK_X))
	{
		currentAnimation = jump;
		return;
	}
	
}

inline void SamusAnimation::RunShootUp()
{
	if (physic->GetVelocity().y != 0)
	{
		currentAnimation = jump;
		return;
	}
	if (physic->GetVelocity().x == 0)
	{
		currentAnimation = aimup;
		return;
	}
	if (!Input::IsKeyDown(VK_UP))
	{
		currentAnimation = run;
		return;
	}
	
	if (Input::IsKeyDown(VK_X))
	{
		Samus->Fire(Vec2(0, 1.0f));
		/*Samus->shootDelayTime = SHOOTDELAYTIME;
		Bullet* b = gameObject->GetScene()->SpawnNewGameObject<Bullet>(Transform());
		b->Fire(Vec2(gameObject->GetTransform().position.x, gameObject->GetTransform().position.y + 1.2f), Vec2(0.0f, 1.0f));*/
	}
}

void SamusAnimation::LockCurrentState(bool locked)
{
	stateLocked = locked;
}

void SamusAnimation::Roll_0()
{
	currentAnimation = idle;
	Samus->canShoot = 1;
}

void SamusAnimation::Roll_1()
{
	if (physic->GetVelocity().y > 0)
	{
		currentAnimation = idle;
		Samus->canShoot = 1;
		physic->SetBodySize(SAMUSBODYSIZE);
		return;
	}
}

void SamusAnimation::EnableRolling()
{
	//RollFunc = &SamusAnimation::Roll_1;
	RollingBodySize = ROLLINGBODYSIZE;
	roll = MetroidContent::GetObjectByName<Animation>("Roll");
	//AnimationCollection.push_back(roll);
}
