#include "Game0.h"

Game0::Game0() : GameInterface(), currentScene(nullptr), currentSceneNum(0)
{

}

Game0::~Game0()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game0::OnCreate()
{
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		if (!currentScene->OnCreate())
		{
			return false;
		}
	return true;
	}
	Debug::FatalError("Engine scene number is not zero", "Game0.cpp", __LINE__);
	return false;
}

void Game0::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene())
	{
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game0::Render()
{
	currentScene->Render();
}

void Game0::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;

	default:
		currentScene = new StartScene();
		break;
	}

	if (!currentScene -> OnCreate())
	{
		CoreEngine::GetInstance()->Exit();
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
}

void Game0::Draw()
{

}