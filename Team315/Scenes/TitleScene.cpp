#include "TitleScene.h"
#include "../Frameworks.h"

TitleScene::TitleScene()
	: Scene(Scenes::Title)
{
	CLOG::Print3String("title create");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	CLOG::Print3String("title Init");

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void TitleScene::Release()
{
}

void TitleScene::Enter()
{
	CLOG::Print3String("title enter");
}

void TitleScene::Exit()
{
	CLOG::Print3String("title exit");
}

void TitleScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Main);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		exit(0);

	Scene::Update(dt);
}

void TitleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}