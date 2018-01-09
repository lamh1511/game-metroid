#pragma once

class Scene;
class GameContent;
struct GameSystem;

class Game
{
public:
	Game(GameContent* Content);
	virtual ~Game() {};
public:
	unsigned int Run();
private:
	bool Start();
	inline void Update();
	bool Exit();
private:
	Game() {};
	Scene* MainScene;
	GameContent* Content;
	static double updateTime;
	static double deltaTime;
	friend struct GameSystem;
};

