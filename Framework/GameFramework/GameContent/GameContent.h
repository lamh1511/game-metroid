#pragma once
#include "Utilities\Utilities.h"
#include "GameFramework\GameContent\Sprite.h"
#include "GameFramework\GameContent\Texture.h"
#include "GameFramework\GameContent\Animation.h"
#include "GameFramework\GameObject\GameObject.h"
#include <list>
#include <string>
#include "GameFramework\GameContent\CollisionBox.h"

class Texture;
class Sprite;
class Object;
class Scene;

class GameContent
{
public:
	GameContent();
	virtual ~GameContent();
public:
	GameContent(const GameContent&) = delete;
	GameContent& operator=(const GameContent&) = delete;
public:
	virtual void Initialize() = 0;
	static void Destroy();
public:
	static Texture* AddTexture(const std::string& path, const ARGB& colorKey, const std::string& name);
	static Texture* GetTextureByName(const std::string& name);

	static Sprite* AddSprite(Texture* texture, const Rect& srcRect, float pixelsPerUnit, const std::string& name);
	static Sprite* GetSpriteByName(const std::string& name);
	
	void AddObject(Object* object);
	template <class Type> static void AddObject(Type* object);
	template <class Type> static Type* GetObjectByName(const std::string& name);

	static bool LoadSpriteFromFile(const std::string& fileName, Texture* tex);

	static Scene* GetStartScene();
	static void AddStartScene(Scene* startScene);

	static void LoadCollisionBoxes(const std::string& fileName);
protected:
	static Scene* StartScene;
	static std::list<Object*> ObjectsList;
	
	static std::vector<CollisionBox> CollisionBoxes;
	friend class Scene;
};


template<class Type>
inline void GameContent::AddObject(Type * object)
{
	if (!object) return;
	ObjectsList.push_back(object);
}

template<class Type>
inline Type * GameContent::GetObjectByName(const std::string & name)
{
	for (Object* object : ObjectsList)
	{
		Type * ob = dynamic_cast<Type*>(object);
		if (ob != nullptr && object->GetName() == name)
		{
			return ob;
		}
	}
	return nullptr;
}
