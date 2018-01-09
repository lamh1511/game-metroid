#pragma once
#include "GameFramework\GameContent\GameContent.h"

class MetroidScene;

class MetroidContent : public GameContent
{
public:
	virtual void Initialize() override;
	MetroidContent() {};
	~MetroidContent();
public:
	MetroidScene* MainScene;
};

