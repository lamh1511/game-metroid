#include "GameContent.h"
#include "GameFramework\GameContent\Sprite.h"
#include "GameFramework\GameContent\Texture.h"
#include "GameFramework\Scene\Scene.h"
#include "ResourcesLoader\TinyXML2\tinyxml2.h"

using namespace tinyxml2;

std::list<Object*> GameContent::ObjectsList = std::list<Object*>();
std::vector<CollisionBox> GameContent::CollisionBoxes = std::vector<CollisionBox>();

Scene* GameContent::StartScene = nullptr;

GameContent::GameContent()
{
}

GameContent::~GameContent()
{
}

void GameContent::Destroy()
{
	if (GameContent::StartScene)
	{
		delete GameContent::StartScene;
		GameContent::StartScene = nullptr;
	}

	for (Object* object : ObjectsList)
	{
		if (object)
		{
			delete object;
			object = nullptr;
		}
	}

}

Texture* GameContent::AddTexture(const std::string & path, const ARGB& colorKey, const std::string& name)
{
	Texture* texture = new Texture(path, colorKey, name);
	ObjectsList.push_back(texture);
	return texture;
}

Texture * GameContent::GetTextureByName(const std::string & name)
{
	for (Object* ob : ObjectsList)
	{
		Texture * tex = dynamic_cast<Texture*>(ob);
		if (tex && tex->GetName() == name)
		{
			return tex;
		}
	}
	return nullptr;
}

Sprite * GameContent::AddSprite(Texture* texture, const Rect& srcRect, float pixelsPerUnit, const std::string& name)
{
	Sprite* sprite = new Sprite(texture, srcRect, pixelsPerUnit, name);
	ObjectsList.push_back(sprite);
	return sprite;
}

Sprite * GameContent::GetSpriteByName(const std::string & name)
{
	for (Object* ob : ObjectsList)
	{
		Sprite * s = dynamic_cast<Sprite*>(ob);
		if (s != nullptr && s->GetName() == name)
		{
			return s;
		}
	}
	return nullptr;
}

bool GameContent::LoadSpriteFromFile(const std::string & fileName, Texture* tex)
{
	int Rect_Left, Rect_Top, Rect_Right, Rect_Bottom;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName.c_str());
	XMLElement* spriteContainer = doc.RootElement();
	XMLElement* sprites = spriteContainer->FirstChildElement();
	XMLElement* sprite = nullptr;

	for (sprite = sprites->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
	{
		sprite->QueryIntAttribute("Rect_Left", &Rect_Left);
		sprite->QueryIntAttribute("Rect_Top", &Rect_Top);
		sprite->QueryIntAttribute("Rect_Right", &Rect_Right);
		sprite->QueryIntAttribute("Rect_Bottom", &Rect_Bottom);

		GameContent::AddSprite(tex, Rect(Rect_Top, Rect_Bottom, Rect_Left, Rect_Right), 16.0f, sprite->Attribute("Sprite_Name"));
	}

	return true;
}

Scene * GameContent::GetStartScene()
{
	return GameContent::StartScene;
}

void GameContent::AddStartScene(Scene* startScene)
{
	if (!startScene) return;
	GameContent::StartScene = startScene;
}

void GameContent::LoadCollisionBoxes(const std::string & fileName)
{
	float x, y, width, height;
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fileName.c_str());
	XMLElement* BoxesContainer = doc.RootElement();
	XMLElement* Boxes = BoxesContainer->FirstChildElement();
	XMLElement* Box = nullptr;
	for (Box = Boxes->FirstChildElement(); Box != NULL; Box = Box->NextSiblingElement())
	{
		Box->QueryFloatAttribute("x", &x);
		Box->QueryFloatAttribute("y", &y);
		Box->QueryFloatAttribute("Width", &width);
		Box->QueryFloatAttribute("Height", &height);

		CollisionBox box(x, y, width, height);
		CollisionBoxes.push_back(box);
	}
}

void GameContent::AddObject(Object * object)
{
	if (!object) return;
	GameContent::ObjectsList.push_back(object);
}

