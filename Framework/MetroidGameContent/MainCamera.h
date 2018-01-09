#pragma once
#include "GameFramework\GameObject\GameObject.h"

class MetroidCharacter;

enum CAMERA_TYPE
{
	MOVE_ALONG_X_AXIS, MOVE_ALONG_Y_AXIS, SLIDE_TO_LEFT, SLIDE_TO_RIGHT
};
class Portal;

class MainCamera : public GameObject
{
public:
	MainCamera();
	virtual ~MainCamera();

	virtual void OnSpawn() override;
	virtual void LateUpdate() override;

	void SetLockType(CAMERA_TYPE Type);
	MetroidCharacter* Samus;
	CameraComponent* Camera;
	float * SamusPositonX;

	friend class Portal;

	CAMERA_TYPE cameraType;
	int collidePortal;
	float slideSpeed;
	Vec2 stopPosition;
	void (MainCamera::*Move)();
	void MoveAlongXAxis();
	void MoveAlongYAxis();
	CAMERA_TYPE nextType;
	void SlideToLeft();
	void SlideToRight();
	void SlideCamera(CAMERA_TYPE newType, bool slideToRight, const Vec2& stopPosition);
};

