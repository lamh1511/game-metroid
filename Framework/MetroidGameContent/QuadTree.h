#pragma once
#include "Utilities\Utilities.h"
#include <list>
#include <map>
#include <string>

class GameObject;
class Scene;
class Spawner;

class QuadTree
{
public:
	QuadTree * tl, *tr, *bl, *br;
	RectF rect;
	std::list<GameObject*> gameObjects;
	std::list<Spawner*> spawners;
	
public:
	QuadTree();
	QuadTree(const RectF& rect, std::list<GameObject*> gameObjects);
	~QuadTree();

	void Clear();
	inline bool IsContain(const RectF& otherRect);
	void Retrieve(std::list<GameObject*>& gameObjects, const RectF& rect);
	static QuadTree* BuildQuadtreeFromFile(const std::string& path, Scene* scene);
};

