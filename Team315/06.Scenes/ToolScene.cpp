#include "ToolScene.h"
#include "Include.h"

ToolScene::ToolScene()
	: Scene(Scenes::Tool)
{
	CLOG::Print3String("tool create");
}

ToolScene::~ToolScene()
{
}

void ToolScene::Init()
{
	CLOG::Print3String("tool Init");

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void ToolScene::Release()
{
}

void ToolScene::Enter()
{
	CLOG::Print3String("tool enter");
}

void ToolScene::Exit()
{
	CLOG::Print3String("tool exit");
}

void ToolScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::Main);
		return;
	}

	Scene::Update(dt);
}

void ToolScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}

void ToolScene::CreateTileSet(int cols, int rows, float quadWidth, float quadHeight)
{
}
