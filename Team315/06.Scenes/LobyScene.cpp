#include "LobyScene.h"
#include "GameManager.h"
#include "Include.h"
#include "SpriteButton.h"
#include "LobySceneUI.h"
#include "SpriteObj.h"
#include "RssProgressWindow.h"
#include "RssTextWindow.h"

LobyScene::LobyScene()
	: Scene(Scenes::Loby), translateView(false), translateSpeed(10.f)
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
		string textureKey = "graphics/lobyScene/mainBackground_";
		textureKey += (i < 10 ? "0" : "") + to_string(i + 1) + ".png";
		backgrounds[i] = new SpriteObj();
		backgrounds[i]->SetTexture(*RESOURCE_MGR->GetTexture(textureKey));
	}

	Vector2f backgroundPos(0.f, 0.f);
	for (auto& background : backgrounds)
	{
		background->SetPos(backgroundPos);
		backgroundPos.x += GAME_SCREEN_WIDTH;
	}

	objList.push_back(ui);

	Scene::Init();
}

void LobyScene::Release()
{
}

void LobyScene::Enter()
{
	CLOG::Print3String("loby enter");

	FRAMEWORK->SetWindowSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	ui->Reset();
	currentView = gameView;
	curViewCenterDest = { GAME_SCREEN_WIDTH * 2.5f, GAME_SCREEN_HEIGHT * 0.5f };
	currentView.setCenter(curViewCenterDest);
	ui->SetPos(Vector2f(GAME_SCREEN_WIDTH * 2.0f, 0.f));
	translateView = false;
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
		CLOG::Print3String("loby devmode switch");
		FRAMEWORK->devMode = !FRAMEWORK->devMode;
	}
	if (InputMgr::GetKey(Keyboard::Key::A))
	{
		ui->GetExpWindow()->GetProgressBar().TranslateProgress(-dt);
	}
	if (InputMgr::GetKey(Keyboard::Key::S))
	{
		ui->GetExpWindow()->GetProgressBar().TranslateProgress(dt);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::D))
	{
		ui->GetExpWindow()->SetLevel();
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F))
	{
		ui->GetExpWindow()->SetLevel(1);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Q))
	{
		ui->GetGoldWindow()->SetGoal(ui->GetGoldWindow()->GetValueGoal() - 1000);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::W))
	{
		ui->GetGoldWindow()->SetGoal(ui->GetGoldWindow()->GetValueGoal() + 1000);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::E))
	{
		ui->GetJewelWindow()->SetGoal(ui->GetJewelWindow()->GetValueGoal() - 1000);
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::R))
	{
		ui->GetJewelWindow()->SetGoal(ui->GetJewelWindow()->GetValueGoal() + 1000);
	}
	// Dev Input End

	// game input
	int idx = 0;
	for (auto button : ui->GetButtons())
	{
		if (button->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			button->SetColor(button->GetHoverColor());
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				curViewCenterDest = Vector2f(GAME_SCREEN_WIDTH * (idx + 0.5f), GAME_SCREEN_HEIGHT * 0.5f);
				translateView = true;
				break;
			}
		}
		else
		{
			button->SetColor(button->GetBaseColor());
		}
		idx++;
	}
	if (translateView)
	{
		float deltaX = dt * translateSpeed * (curViewCenterDest.x - currentView.getCenter().x);
		currentView.move(deltaX, 0);
		ui->Translate(Vector2f(deltaX, 0));

		if (Utils::EqualFloat(currentView.getCenter().x, curViewCenterDest.x, 0.20f))
		{
			// cout << "equal!" << endl;
			translateView = false;
		}
	}

	Button* button = ui->GetStartButton();
	if (button->CollideTest(ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		button->SetColor(button->GetHoverColor());
		if (InputMgr::GetMouseDown(Mouse::Left))
		{
			SCENE_MGR->ChangeScene(Scenes::Battle);
			return;
		}
	}
	else
	{
		button->SetColor(button->GetBaseColor());
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
	for (auto& background : backgrounds)
	{
		background->Draw(window);
	}
}