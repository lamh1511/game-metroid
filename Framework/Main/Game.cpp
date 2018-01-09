#include "Game.h"
#include "GameFramework\Scene\Scene.h"
#include "Core\SystemManager\SystemManager.h"
#include "GameFramework\GameContent\GameContent.h"

double Game::updateTime = 0;
double Game::deltaTime = 0;
GraphicsD3D9* graphics = nullptr;
KeyboardWindows* keyboardInput = nullptr;
WindowsTime* windowTime = nullptr;

Game::Game(GameContent * Content) :
	MainScene(nullptr),
	Content(Content)
{
}

unsigned int Game::Run()
{
	if (!Start()) {}
	MSG msg = { 0 };
	graphics = SystemManager::GetInstance()->GetSystem<GraphicsD3D9>();
	keyboardInput = SystemManager::GetInstance()->GetSystem<KeyboardWindows>();
	windowTime = SystemManager::GetInstance()->GetSystem<WindowsTime>();
	windowTime->StartTimer();
	this->MainScene->BeginScene();
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Update();
	}

	if (!Exit()) {}
	return msg.wParam;
}

bool Game::Start()
{
	if (!SystemManager::GetInstance()->Initialize()) return false;
	Content->Initialize();
	this->MainScene = Content->GetStartScene();
	return true;
}

void Game::Update()
{
	keyboardInput->Update();

	if (keyboardInput->IsKeyPressed(VK_ESCAPE) || keyboardInput->IsKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	MainScene->Update();
	graphics->Update();
	Game::updateTime = windowTime->GetTimerValue();
	/*if (Game::updateTime < 0.025)
	{
		Game::deltaTime = 0.025;
		Sleep(25 - ((int)Game::updateTime) * 1000);
	}
	else */Game::deltaTime = Game::updateTime;
	windowTime->ResetTimer();
	windowTime->StartTimer();
}


bool Game::Exit()
{
	GameContent::Destroy();
	if (!SystemManager::GetInstance()->Shutdown()) return false;
	return true;
}
