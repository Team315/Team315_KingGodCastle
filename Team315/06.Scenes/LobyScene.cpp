#include "LobyScene.h"
#include "Include.h"
#include "SpriteButton.h"
#include "LobySceneUI.h"
#include "SpriteObj.h"
#include "RssProgressWindow.h"
#include "RssTextWindow.h"

LobyScene::LobyScene()
	: Scene(Scenes::Loby), currentBackground(2)
{
	CLOG::Print3String("loby create");
	ui = new LobySceneUI(this);
	tabSize = ui->GetTabSize();
}

LobyScene::~LobyScene()
{
}

void LobyScene::Init()
{
	CLOG::Print3String("loby Init");

	backgrounds.resize(tabSize);
	for (int i = 0; i < tabSize; i++)
	{
		string textureKey = "graphics/mainScene/mainBackground_";
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

void LobyScene::Release()
{
}

void LobyScene::Enter()
{
	CLOG::Print3String("loby enter");
	FRAMEWORK->GetWindow().setView(worldView);
}

void LobyScene::Exit()
{
	CLOG::Print3String("loby exit");
}

void LobyScene::Update(float dt)
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
	if (InputMgr::GetKeyDown(Keyboard::Key::F7))
	{
		CLOG::Print3String("loby devmode on");
		FRAMEWORK->devMode = true;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F8))
	{
		CLOG::Print3String("loby devmode off");
		FRAMEWORK->devMode = false;
	}
	if (InputMgr::GetKey(Keyboard::Key::A))
	{
		ui->GetExpWindow()->GetProgressBar().TranslateProgress(-dt);
	}
	if (InputMgr::GetKey(Keyboard::Key::S))
	{
		ui->GetExpWindow()->GetProgressBar().TranslateProgress(dt);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Q))
	{
		ui->GetGoldWindow()->SetGoal(ui->GetGoldWindow()->GetValueGoal() - 100);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::W))
	{
		ui->GetGoldWindow()->SetGoal(ui->GetGoldWindow()->GetValueGoal() + 100);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::E))
	{
		ui->GetJewelWindow()->SetGoal(ui->GetJewelWindow()->GetValueGoal() - 100);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::R))
	{
		ui->GetJewelWindow()->SetGoal(ui->GetJewelWindow()->GetValueGoal() + 100);
	}
	// Dev Input End

	// game input
	int idx = 0;
	for (auto button : ui->GetButtons())
	{
		if (button->CollideTest(ScreenToUiPos(InputMgr::GetMousePosI())))
		{
			button->SetColor(button->GetHoverColor());
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				currentBackground = idx;
				break;
			}

			if (InputMgr::GetMouseDown(Mouse::Right))
				CLOG::Print3String("Right");
		}
		else
		{
			button->SetColor(button->GetBaseColor());
		}
		idx++;
	}
	// game input end

	Scene::Update(dt);
	ui->Update(dt);
}

void LobyScene::Draw(RenderWindow& window)
{
	DrawBackground(window);
	Scene::Draw(window);
	ui->Draw(window);
}

void LobyScene::DrawBackground(RenderWindow& window)
{
	backgrounds[currentBackground]->Draw(window);
}