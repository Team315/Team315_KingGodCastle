#include "MainScene.h"
#include "../Frameworks.h"

MainScene::MainScene()
	: Scene(Scenes::Main)
{
	CLOG::Print3String("main create");
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	CLOG::Print3String("main Init");

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void MainScene::Release()
{
}

void MainScene::Enter()
{
	CLOG::Print3String("main enter");
}

void MainScene::Exit()
{
	CLOG::Print3String("main exit");
}

void MainScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Battle);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::Title);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::T))
	{
		SCENE_MGR->ChangeScene(Scenes::Tool);
		return;
	}

	Scene::Update(dt);
}

void MainScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}