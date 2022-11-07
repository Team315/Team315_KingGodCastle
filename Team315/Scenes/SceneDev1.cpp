#include "SceneDev1.h"
#include "../Frameworks.h"
#include "../GameObject/Button.h"

SceneDev1::SceneDev1()
	: Scene(Scenes::Dev1)
{
	CLOG::Print3String("scene1 create");
}

SceneDev1::~SceneDev1()
{
}

void SceneDev1::Init()
{
	CLOG::Print3String("scene1 init");

	button = new Button();
	button->SetButton(
		*RESOURCE_MGR->GetTexture("graphics/UIBackground.png"),
		*RESOURCE_MGR->GetFont("fonts/DNFBitBitTTF.ttf"), "button",
		10, 10, 100, 100, 2.f, 2.f, Color::Blue, Color::Cyan);
	objList.push_back(button);

	for (auto obj : objList)
	{
		obj->Init();
	}
}

void SceneDev1::Release()
{
}

void SceneDev1::Enter()
{
	CLOG::Print3String("scene1 enter");
}

void SceneDev1::Exit()
{
	CLOG::Print3String("scene1 exit");
}

void SceneDev1::Update(float dt)
{
	// dev input start
	if (InputMgr::GetKeyDown(Keyboard::Key::F7))
	{
		CLOG::Print3String("scene1 devmode on");
		FRAMEWORK->devMode = true;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F8))
	{
		CLOG::Print3String("scene1 devmode off");
		FRAMEWORK->devMode = false;
	}
	// dev input end

	// game input
	if (button->GetHitbox().getGlobalBounds().contains(ScreenToUiPos(Vector2i(InputMgr::GetMousePos()))))
	{
		CLOG::Print3String("contain");
		button->SetColor(button->GetHoverColor());
	}
	else
	{
		button->SetColor(button->GetBaseColor());
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Dev2);
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F1))
	{
		CLOG::Print3String("scene1");
		return;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		exit(0);

	Scene::Update(dt);
}

void SceneDev1::Draw(RenderWindow& window)
{
	Scene::Draw(window);	
}