#include "MetroidContent.h"
#include "MetroidScene.h"
#include "GameFramework\GameContent\Texture.h"

void MetroidContent::Initialize()
{
	Texture* tileset = AddTexture("TileSet.png", ARGB(255, 0, 0, 0), "TileSet.png");
	//AddSprite(tileset, Rect(0, 8192, 0, 8192), 16.0f, "Brinstar");

	//Texture* tileset = AddTexture("TileSet.png", ARGB(255, 0, 0, 0), "TileSet.png");
	LoadSpriteFromFile("Texture.xml", tileset);
	Texture* tileset1 = AddTexture("ridley.png", ARGB(255, 0, 0, 0), "ridley.png");
	LoadSpriteFromFile("ridley.xml", tileset1);

	Texture* tileset2 = AddTexture("kraid.png", ARGB(255, 0, 0, 0), "kraid.png");
	LoadSpriteFromFile("kraid.xml", tileset2);

	Texture* tileset3 = AddTexture("Menus.png", NULL, "Menus.png");
	LoadSpriteFromFile("MenusTexture.xml", tileset3);
	//-------------------------------------------------------------------------------

	std::vector<Sprite*> sprites;

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_0"));
	GameContent::AddObject<Animation>(new Animation(sprites, 1.0, true, "Idle"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_2"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_3"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_4"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.0005, true, "Run"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_68"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_67"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_66"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_65"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.001, true, "Roll"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_6"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_7"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_8"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_9"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.001, true, "Rotate"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_5"));
	GameContent::AddObject<Animation>(new Animation(sprites, 1.0, true, "Jump"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_1"));
	GameContent::AddObject<Animation>(new Animation(sprites, 1.0, true, "AimUp"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_1"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_19"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.06, true, "ShootUp"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_23"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.08, true, "JumpShootUp"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_15"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_16"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_17"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.005, true, "RunShootForward"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_18"));
	GameContent::AddObject<Animation>(new Animation(sprites, 1.0, true, "JumpShootForward"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_20"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_21"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_22"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.008, true, "RunShootUp"));
	sprites.clear();
	//-------------------------------------------------------------------------------
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_26"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_27"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.1, true, "ZoomerMainAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_28"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_29"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_30"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.08, true, "SkreeMainAnimation"));
	sprites.clear();
	
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_34"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_35"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "RioMainAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_37"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_38"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_39"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_40"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.005, true, "MaruMariAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_41"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_42"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_43"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_44"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "MissileRocketAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_45"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_46"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_47"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_48"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "EnergyTankAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_49"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_50"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_51"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_52"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "BombAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_53"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_54"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_55"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_56"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "VariaAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_57"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_58"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_59"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_60"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "IceBeamAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_61"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_62"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_63"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_64"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "LongBeamAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_61"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_62"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_63"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_64"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "WaveBeamAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_87"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_72"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_73"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.006, false, "EnemyExposion"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_69"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_89"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.008, true, "EnergyBall"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_31"));
	GameContent::AddObject<Animation>(new Animation(sprites, 1.0, true, "SkreeExplosion"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_76"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_77"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.1, false, "OpenPortal"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_76"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_32"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.15, false, "ClosePortal"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_32"));
	GameContent::AddObject<Animation>(new Animation(sprites, 1.0, true, "NormalPortalEntrance"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_78"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_77"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.1, false, "OpenRedPortal"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_78"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_79"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.15, false, "CloseRedPortal"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_79"));
	GameContent::AddObject<Animation>(new Animation(sprites, 1.0, true, "NormalRedPortalEntrance"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_84"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_85"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.15, true, "ZebAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_81"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_82"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_83"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.15, true, "WaverAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_75"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.15, true, "RipperAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_90"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("TileSet_86"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.15, true, "SamusBombAnimation"));
	sprites.clear();
	//-----------------------------------------------------------------------------------------------
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_0"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_1"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.08, true, "RidleyIdleAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_2"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_3"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.06, true, "RidleyJumpAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_12"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_13"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.06, true, "RidleyDamagedIdleAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_14"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_15"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.06, true, "RidleyDamagedJumpAnimation"));
	sprites.clear();

	//Boss Ridley Bullet
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_4"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_5"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_6"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_7"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "RidleyBulletAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_16"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_17"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tileridley_18"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, false, "RidleyDeadAnimation"));
	sprites.clear();
	//---------------------------------------------------------------------

	//Boss Kraid------------------------------------------------------------
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_0"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_1"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "KraidAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_2"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_3"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "RedKraidAnimation"));
	sprites.clear();

	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_4"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_5"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "BrownKraidAnimation"));
	sprites.clear();

	//Boss Kraid Bumerang
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_6"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_7"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_8"));
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_9"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.04, true, "KraidBumerangAnimation"));
	sprites.clear();

	//Boss Kraid Bullet
	sprites.push_back(GameContent::GetObjectByName<Sprite>("tilekraid_10"));
	GameContent::AddObject<Animation>(new Animation(sprites, 0.05, true, "KraidBulletAnimation"));
	sprites.clear();
	//-----------------------------------------------------------------------



	Scene* scene = new MetroidScene("MetroidScene");
	GameContent::AddStartScene(scene);
}


MetroidContent::~MetroidContent()
{
	if (MainScene)
	{
		delete MainScene;
		MainScene = nullptr;
	}
}
