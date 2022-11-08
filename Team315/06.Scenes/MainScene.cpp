#include "MainScene.h"
#include "Include.h"

MainScene::MainScene()
	: Scene(Scenes::Main)
{
	CLOG::Print3String("main create");
	ui = new MainSceneUI(this);
	worldView.setViewport(FloatRect(0, 0, 1, 1));
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	CLOG::Print3String("main Init");

	objList.push_back(ui);

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
	ui->DrawBackground(window);
	Scene::Draw(window);
}