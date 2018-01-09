#include "Portal.h"
#include "MainCamera.h"
#include "PortalEntrance.h"

Portal::Portal(bool isRedPortal, CAMERA_TYPE LeftLockType, CAMERA_TYPE RightLockType) :
	GameObject(Transform(), "Portal"),
	LeftLockType(LeftLockType),
	RightLockType(RightLockType),
	isRedPortal(isRedPortal)
{
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(1.0f, 3.0f));
	physics->DisableCollision(false);
	physics->SetStatic(true);
	physics->SetMass(0);
}

Portal::~Portal()
{
}

void Portal::OnSpawn()
{
	if (isRedPortal)
	{
		portalEntranceLeft = new PortalEntrance(true);
		portalEntranceLeft->transform = transform.position - Vec2(1.25f, 0);
		scene->SpawnNewGameObject(portalEntranceLeft);

		portalEntranceRight = new PortalEntrance(true);
		portalEntranceRight->transform = Transform(Vec2(transform.position + Vec2(1.25f, 0)), 0, Vec2(-1.0f, 1.0f));
		scene->SpawnNewGameObject(portalEntranceRight);
	}
	else
	{
		portalEntranceLeft = scene->SpawnNewGameObject<PortalEntrance>(Transform(transform.position - Vec2(1.25f, 0)));
		portalEntranceRight = scene->SpawnNewGameObject<PortalEntrance>(Transform(Vec2(transform.position + Vec2(1.25f, 0)), 0, Vec2(-1.0f, 1.0f)));
	}
	camera = static_cast<MainCamera*>(scene->FindGameObjectByName("MainCamera"));
	cameraRect = camera->GetComponent<CameraComponent>();
	Samus = GetScene()->FindGameObjectByName("Samus");
	GameObject::OnSpawn();
}

void Portal::Update()
{
	GameObject::Update();
	scene->GetCollisionBoxes().push_back(portalEntranceLeft->physics);
	scene->GetCollisionBoxes().push_back(portalEntranceRight->physics);
	portalEntranceLeft->Update();
	portalEntranceRight->Update();
	if (std::abs(Samus->GetTransform().position.x - transform.position.x) < (cameraRect->cameraWidth * 0.5f))
	{
		camera->collidePortal += 1;
	}
}

void Portal::LateUpdate()
{
	GameObject::LateUpdate();
	portalEntranceLeft->LateUpdate();
	portalEntranceRight->LateUpdate();
}

void Portal::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (other->GetTag() == "Player")
	{
		if (other->GetTransform().position.x < transform.position.x)
		{
			other->SetTransform(this->transform);
			portalEntranceRight->animation->currentAnimation = portalEntranceRight->open;
			
			if(RightLockType == MOVE_ALONG_Y_AXIS) camera->SlideCamera(RightLockType, 1, Vec2(transform.position.x + 8.0f, transform.position.y));
			else camera->SlideCamera(RightLockType, 1, Vec2(transform.position.x + cameraRect->cameraWidth * 0.5f, transform.position.y));
		}
		else
		{
			other->SetTransform(this->transform);
			portalEntranceLeft->animation->currentAnimation = portalEntranceLeft->open;
		
			if (LeftLockType == MOVE_ALONG_Y_AXIS) camera->SlideCamera(LeftLockType, 0, Vec2(transform.position.x - 8.0f, transform.position.y));
			else camera->SlideCamera(LeftLockType, 0, Vec2(transform.position.x - cameraRect->cameraWidth * 0.5f, transform.position.y));
		}
	}

}

