#include "MainScene.h"
#include "Include.h"

MainScene::MainScene()
	: Scene(Scenes::Main), tabCount(5), currentBackground(2)
{
	CLOG::Print3String("main create");
	ui = new MainSceneUI(this);
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	CLOG::Print3String("main Init");

	backgrounds.resize(tabCount);
	for (int i = 0; i < tabCount; i++)
	{
		string textureKey = "graphics/mainBackground_";
		textureKey += (i < 10 ? "0" : "") + to_string(i + 1) + ".png";
		backgrounds[i] = new SpriteObj();
		backgrounds[i]->SetTexture(*RESOURCE_MGR->GetTexture(textureKey));
	}

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
	FRAMEWORK->GetWindow().setView(worldView);
}

void MainScene::Exit()
{
	CLOG::Print3String("main exit");
}

void MainScene::Update(float dt)
{
	// Dev Input
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
	if (InputMgr::GetKeyDown(Keyboard::Key::Num1))
	{
		CLOG::Print3String("상점");
		currentBackground = 0;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num2))
	{
		CLOG::Print3String("병영");
		currentBackground = 1;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num3))
	{
		CLOG::Print3String("성문");
		currentBackground = 2;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num4))
	{
		CLOG::Print3String("제단");
		currentBackground = 3;
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num5))
	{
		CLOG::Print3String("모드");
		currentBackground = 4;
		return;
	}

	Scene::Update(dt);
}

void MainScene::Draw(RenderWindow& window)
{
	DrawBackground(window);
	Scene::Draw(window);
}

void MainScene::DrawBackground(RenderWindow& window)
{
	backgrounds[currentBackground]->Draw(window);
}