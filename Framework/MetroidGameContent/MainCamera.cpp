#include "MainCamera.h"
#include "MetroidCharacter.h"


MainCamera::MainCamera()
{
	this->name = "MainCamera";
	this->cameraType = MOVE_ALONG_X_AXIS;
	Camera = AddComponent<CameraComponent>();
	collidePortal = 0;
	Move = &MainCamera::MoveAlongXAxis;
	slideSpeed = 5.0f;
}


MainCamera::~MainCamera()
{
}

void MainCamera::OnSpawn()
{
	GameObject::OnSpawn();
	this->Samus = static_cast<MetroidCharacter*>(GetScene()->FindGameObjectByName("Samus"));
	//transform.position = Samus->GetTransform().position;
}

void MainCamera::LateUpdate()
{
	/*if (std::abs(this->GetTransform().position.x - *SamusPositonX) >= 2.5f)
	{
		if(GetTransform().position.x < *SamusPositonX) this->SetTransform(Vec2(*SamusPositonX - 2.5f, 82.6f));
		else SetTransform(Vec2(*SamusPositonX + 2.5f, 82.6f));
	}*/

	(*this.*Move)();
	GameObject::LateUpdate();


}

void MainCamera::SetLockType(CAMERA_TYPE Type)
{
	if (Type == MOVE_ALONG_X_AXIS)
	{
		this->Move = &MainCamera::MoveAlongXAxis;
	}
	else this->Move = &MainCamera::MoveAlongYAxis;
}

void MainCamera::MoveAlongXAxis()
{
	if (collidePortal == 0)
	{
		transform.position.x = Samus->GetTransform().position.x;
	}
}

void MainCamera::MoveAlongYAxis()
{
	if (std::abs(transform.position.y - Samus->GetTransform().position.y) >= 2.f)
	{
		if (GetTransform().position.y < Samus->GetTransform().position.y) transform.position.y = Samus->GetTransform().position.y - 2.f;
		else transform.position.y = Samus->GetTransform().position.y + 2.f;
	}
}

void MainCamera::SlideToLeft()
{
	transform.position.x -= slideSpeed * (float)Time::GetDeltaTime();
	if (transform.position.x <= this->stopPosition.x)
	{
		transform.position.x = this->stopPosition.x;
		transform.position.y = stopPosition.y - 1.0f;
		if (Samus->GetTransform().position.x >= (this->stopPosition.x + 5.75f))
		{
			Samus->CharacterPhysics->SetVelocityX(-Samus->moveSpeed);
		}
		else
		{
			Samus->CharacterPhysics->SetVelocityX(0);
			this->SetLockType(nextType);
			Input::locked = 0;
		}
	}
}

void MainCamera::SlideToRight()
{
	transform.position.x += slideSpeed * (float)Time::GetDeltaTime();
	if (transform.position.x >= this->stopPosition.x)
	{
		transform.position.x = this->stopPosition.x;
		transform.position.y = stopPosition.y - 1.0f;
		if (Samus->GetTransform().position.x <= (this->stopPosition.x - 5.75f))
		{
			Samus->CharacterPhysics->SetVelocityX(Samus->moveSpeed);
		}
		else
		{
			Samus->CharacterPhysics->SetVelocityX(0);
			this->SetLockType(nextType);
			Input::locked = 0;
		}
	}
}

void MainCamera::SlideCamera(CAMERA_TYPE newType, bool slideToRight, const Vec2& stopPosition)
{
	Input::locked = 1;
	Samus->CharacterPhysics->SetVelocityX(0);
	this->nextType = newType;
	this->stopPosition = stopPosition;
	if (slideToRight) this->Move = &MainCamera::SlideToRight;
	else this->Move = &MainCamera::SlideToLeft;
}
