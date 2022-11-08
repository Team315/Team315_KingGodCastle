#include "BattleScene.h"
#include "../Frameworks.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle)
{
	CLOG::Print3String("battle create");
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	CLOG::Print3String("battle Init");

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void BattleScene::Release()
{
}

void BattleScene::Enter()
{
	CLOG::Print3String("battle enter");
}

void BattleScene::Exit()
{
	CLOG::Print3String("battle exit");
}

void BattleScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		CLOG::Print3String("setting window");
		SCENE_MGR->ChangeScene(Scenes::Main);
		return;
	}

	Scene::Update(dt);
}

void BattleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}