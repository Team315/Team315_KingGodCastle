#include "BattleScene.h"
#include "Include.h"
#include "BattleSceneUI.h"

BattleScene::BattleScene()
	: Scene(Scenes::Battle)
{
	CLOG::Print3String("battle create");

	ui = new BattleSceneUI(this);
	evan = new Evan();
	goblin00 = new Goblin00();
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	CLOG::Print3String("battle Init");

	evan->SetTarget(goblin00);
	goblin00->SetTarget(evan);

	objList.push_back(evan);
	objList.push_back(goblin00);
	objList.push_back(ui);
	Scene::Init();
	CLOG::Print3String("battle Init end");
}

void BattleScene::Release()
{
}

void BattleScene::Enter()
{
	CLOG::Print3String("battle enter");

	FRAMEWORK->SetWindowSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	currentView = gameView;
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
		SCENE_MGR->ChangeScene(Scenes::Loby);
		return;
	}

	Scene::Update(dt);
}

void BattleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}