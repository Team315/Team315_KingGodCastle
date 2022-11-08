#include "TitleScene.h"
#include "Include.h"

TitleScene::TitleScene()
	: Scene(Scenes::Title)
{
	CLOG::Print3String("title create");
	background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/titleBackground.png"));
	objList.push_back(background);

	Vector2i wSize = FRAMEWORK->GetWindowSize();
	titleText = new TextObj(
		*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"),
		"Press Space bar to start!",
		wSize.x * 0.4f, wSize.y * 0.7f, Color::Black, 50.f);
	titleText->SetOrigin(Origins::MC);
	objList.push_back(titleText);
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
	// Dev Input
	if (InputMgr::GetKeyDown(Keyboard::Key::Num1))
	{
		SCENE_MGR->ChangeScene(Scenes::Tool);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num2))
	{
		SCENE_MGR->ChangeScene(Scenes::Main);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Num3))
	{
		SCENE_MGR->ChangeScene(Scenes::Battle);
		return;
	}

	// Game Input
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