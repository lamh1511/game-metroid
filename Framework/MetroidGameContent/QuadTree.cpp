#include "QuadTree.h"
#include "GameFramework\GameObject\GameObject.h"
#include "ResourcesLoader\TinyXML2\tinyxml2.h"
#include "GameFramework\Scene\Scene.h"
#include "Zoomer.h"
#include "Skree.h"
#include "Rio.h"
#include "Spawner.h"
#include "MetroidCharacter.h"

using namespace tinyxml2;

QuadTree::QuadTree()
{
}

QuadTree::QuadTree(const RectF & rect, std::list<GameObject*> gameObjects) :
	rect(rect),
	tl(nullptr),
	tr(nullptr),
	bl(nullptr),
	br(nullptr)
{
	for (GameObject* ob : gameObjects)
	{
		Spawner* spawner = dynamic_cast<Spawner*>(ob);
		if (spawner)
		{
			this->spawners.push_back(spawner);
		}
		else
		{
			this->gameObjects.push_back(ob);
		}
	}

}

QuadTree::~QuadTree()
{
}

void QuadTree::Clear()
{
	if (tl)
	{
		tl->Clear();
		delete tl;
		tr->Clear();
		delete tr;
		bl->Clear();
		delete bl;
		br->Clear();
		delete br;
	}
	gameObjects.clear();
	spawners.clear();
}

bool QuadTree::IsContain(const RectF & otherRect)
{
	return !(rect.right < otherRect.left || rect.left > otherRect.right || rect.top < otherRect.bottom || rect.bottom > otherRect.top);
}

void QuadTree::Retrieve(std::list<GameObject*>& gameObjects, const RectF & rect)
{
	if (tl != nullptr)
	{
		if (tl->IsContain(rect))
			tl->Retrieve(gameObjects, rect);
		if (tr->IsContain(rect))
			tr->Retrieve(gameObjects, rect);
		if (bl->IsContain(rect))
			bl->Retrieve(gameObjects, rect);
		if (br->IsContain(rect))
			br->Retrieve(gameObjects, rect);
		return;
	}
	if (IsContain(rect))
	{
		for (GameObject* ob : this->gameObjects)
		{
			std::list<GameObject*>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), ob);
			if (it == gameObjects.end())
			{
				gameObjects.push_back(ob);
			}
		}
		for (Spawner* ob : this->spawners)
		{
			GameObject* gameObject = ob->GetGameObject();
			if (!gameObject) continue;
			std::list<GameObject*>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
			if (it == gameObjects.end())
			{
				gameObjects.push_back(gameObject);
			}
		}
	}
}

QuadTree* QuadTree::BuildQuadtreeFromFile(const std::string & path, Scene* scene)
{
	std::map<std::string, GameObject*> ID_Object_Map;
	std::map<int, QuadTree*> ID_Node_Map;
	QuadTree* MetroidQuadTree = nullptr;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(path.c_str());

	XMLElement* MetroidLevel = doc.RootElement();
	XMLElement* Quadtree = MetroidLevel->FirstChildElement();
	XMLElement* GameObjectInNodes = Quadtree->NextSiblingElement();

	for (XMLElement* GameObjectInNode = GameObjectInNodes->FirstChildElement(); GameObjectInNode != nullptr; GameObjectInNode = GameObjectInNode->NextSiblingElement())
	{
		float x, y, Center_Bounds_x, Center_Bounds_y, Bounds_Width, Bounds_Height;

		GameObjectInNode->QueryFloatAttribute("Center_Bounds_x", &Center_Bounds_x);
		GameObjectInNode->QueryFloatAttribute("Center_Bounds_y", &Center_Bounds_y);
		GameObjectInNode->QueryFloatAttribute("Bounds_Width", &Bounds_Width);
		GameObjectInNode->QueryFloatAttribute("Bounds_Height", &Bounds_Height);
		GameObjectInNode->QueryFloatAttribute("World_Position_x", &x);
		GameObjectInNode->QueryFloatAttribute("World_Position_y", &y);

		if (std::string(GameObjectInNode->Attribute("Type")) == "Terrain")
		{
			GameObject* newGameObject = new GameObject(Transform(Vec2(Center_Bounds_x, Center_Bounds_y)), "StaticBox", "None");
			newGameObject->isAlwaysActive = false;
			newGameObject->name = "Terrain";
			newGameObject->tag = "Terrain";
			SimulatePhysics* physic = newGameObject->AddComponent<SimulatePhysics>();
			physic->SetStatic(true);
			physic->SetVelocity(Vec2(0, 0));
			physic->DisableCollision(false);
			physic->SetBodySize(Vec2(Bounds_Width, Bounds_Height));
			scene->SpawnNewGameObject(newGameObject);
			ID_Object_Map.insert(std::pair<std::string, GameObject*>(std::string(GameObjectInNode->Attribute("ObjectID")), newGameObject));
		}
		else
		{
			Spawner* newSpawner = scene->SpawnNewGameObject<Spawner>(Transform(Vec2(x, y)));
			newSpawner->isAlwaysActive = false;
			newSpawner->SetSpawnType(std::string(GameObjectInNode->Attribute("Type")));
			ID_Object_Map.insert(std::pair<std::string, GameObject*>(std::string(GameObjectInNode->Attribute("ObjectID")), newSpawner));
		}

		/*else if (std::string(GameObjectInNode->Attribute("Type")) == "Zoomer")
		{
			Spawner* newSpawner = scene->SpawnNewGameObject<Spawner>(Transform(Vec2(x, y)));
			newSpawner->isAlwaysActive = false;
			newSpawner->SetSpawnType("Zoomer");
			ID_Object_Map.insert(std::pair<std::string, GameObject*>(std::string(GameObjectInNode->Attribute("ObjectID")), newSpawner));

		}
		else if (std::string(GameObjectInNode->Attribute("Type")) == "Skree")
		{
			Spawner* newSpawner = scene->SpawnNewGameObject<Spawner>(Transform(Vec2(x, y)));
			newSpawner->isAlwaysActive = false;
			newSpawner->SetSpawnType("Skree");
			ID_Object_Map.insert(std::pair<std::string, GameObject*>(std::string(GameObjectInNode->Attribute("ObjectID")), newSpawner));
		}
		else if (std::string(GameObjectInNode->Attribute("Type")) == "Rio")
		{
			Spawner* newSpawner = scene->SpawnNewGameObject<Spawner>(Transform(Vec2(x, y)));
			newSpawner->isAlwaysActive = false;
			newSpawner->SetSpawnType("Rio");
			ID_Object_Map.insert(std::pair<std::string, GameObject*>(std::string(GameObjectInNode->Attribute("ObjectID")), newSpawner));
		}
		else if (std::string(GameObjectInNode->Attribute("Type")) == "MaruMari")
		{
			Spawner* newSpawner = scene->SpawnNewGameObject<Spawner>(Transform(Vec2(x, y)));
			newSpawner->isAlwaysActive = false;
			newSpawner->SetSpawnType("MaruMari");
			ID_Object_Map.insert(std::pair<std::string, GameObject*>(std::string(GameObjectInNode->Attribute("ObjectID")), newSpawner));
		}
		else if (std::string(GameObjectInNode->Attribute("Type")) == "BluePortal")
		{
			Spawner* newSpawner = scene->SpawnNewGameObject<Spawner>(Transform(Vec2(x, y)));
			newSpawner->isAlwaysActive = false;
			newSpawner->SetSpawnType("MaruMari");
			ID_Object_Map.insert(std::pair<std::string, GameObject*>(std::string(GameObjectInNode->Attribute("ObjectID")), newSpawner));
		}
		else if (std::string(GameObjectInNode->Attribute("Type")) == "RedPortal")
		{
			Spawner* newSpawner = scene->SpawnNewGameObject<Spawner>(Transform(Vec2(x, y)));
			newSpawner->isAlwaysActive = false;
			newSpawner->SetSpawnType("MaruMari");
			ID_Object_Map.insert(std::pair<std::string, GameObject*>(std::string(GameObjectInNode->Attribute("ObjectID")), newSpawner));
		}*/
	}

	for (XMLElement* Node = Quadtree->FirstChildElement(); Node != nullptr; Node = Node->NextSiblingElement())
	{
		int NodeID;
		float x, y, width, height;
		std::list<GameObject*> ObjectsInNode;
		for (XMLElement* NodeObjectID = Node->FirstChildElement()->FirstChildElement(); NodeObjectID != nullptr; NodeObjectID = NodeObjectID->NextSiblingElement())
		{
			ObjectsInNode.push_back(ID_Object_Map.at(std::string(NodeObjectID->GetText())));
		}
		Node->QueryIntAttribute("NodeID", &NodeID);
		Node->QueryFloatAttribute("x", &x);
		Node->QueryFloatAttribute("y", &y);
		Node->QueryFloatAttribute("Width", &width);
		Node->QueryFloatAttribute("Height", &height);
		QuadTree* quadtree = new QuadTree(RectF(y + height * 0.5f, y - height * 0.5f, x - width * 0.5f, x + width * 0.5f), ObjectsInNode);
		ID_Node_Map.insert(std::pair<int, QuadTree*>(NodeID, quadtree));
		ObjectsInNode.clear();
	}

	for (std::map<int, QuadTree*>::iterator it = ID_Node_Map.begin(); it != ID_Node_Map.end(); it++)
	{
		if (it->first == 0)
		{
			MetroidQuadTree = it->second;
		}
		else
		{
			QuadTree* ParentNode = ID_Node_Map.at(it->first / 10);
			int child = it->first % 10;
			switch (child)
			{
			case 1:
			{
				ParentNode->tl = it->second;
				break;
			}
			case 2:
			{
				ParentNode->tr = it->second;
				break;
			}
			case 3:
			{
				ParentNode->bl = it->second;
				break;
			}
			case 4:
			{
				ParentNode->br = it->second;
				break;
			}
			default:
				break;
			}
		}
	}

	return MetroidQuadTree;
}
