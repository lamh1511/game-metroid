#pragma once
#include "GameFramework\GameObject\GameObject.h"
#include "MainCamera.h"
#include "GameFramework\GameComponent\SimulatePhysics.h"

class PortalEntrance;

class Portal : public GameObject
{
public:
	Portal(bool isRedPortal = 0,CAMERA_TYPE LeftLockType = MOVE_ALONG_X_AXIS, CAMERA_TYPE RightLockType = MOVE_ALONG_X_AXIS);
	virtual ~Portal();

	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
	MainCamera* camera;
	GameObject* Samus;
	CameraComponent* cameraRect;
	SimulatePhysics* physics;

	PortalEntrance* portalEntranceLeft;
	PortalEntrance* portalEntranceRight;

	bool isRedPortal;

	CAMERA_TYPE LeftLockType;
	CAMERA_TYPE RightLockType;
};

