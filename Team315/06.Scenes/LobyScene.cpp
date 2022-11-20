#include "LobyScene.h"
#include "GameManager.h"
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
	GAME_MGR;
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

	Scene::Init();
}

void LobyScene::Release()
{
}

void LobyScene::Enter()
{
	CLOG::Print3String("loby enter");

	FRAMEWORK->SetWindowSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	currentView = gameView;
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
	if (InputMgr::GetKeyDown(Keyboard::Key::F6))
	{
		int ranNum;
		int ranIdx;
		int characterSize = GAME_MGR->GetCharacterCount();
		
		ranNum = Utils::RandomRange(0, characterSize);
		ranIdx = Utils::RandomRange(0, PRESET_SIZE);
		GAME_MGR->SetPresetElem(ranIdx, ranNum);
		cout << ranIdx << " " << ranNum << " ";
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::F5))
	{
		vector<int>& preset = GAME_MGR->GetPreset();
		CLOG::Print3String("preset state");
		for (auto elem : preset)
		{
			cout << elem << " ";
		}
		cout << endl;
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
	Button* button = ui->GetStartButton();
	if (button->CollideTest(ScreenToUiPos(InputMgr::GetMousePosI())))
	{
			button->SetColor(button->GetHoverColor());
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				SCENE_MGR->ChangeScene(Scenes::Battle);
				return;
			}

			if (InputMgr::GetMouseDown(Mouse::Right))
				CLOG::Print3String("Right");
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
	backgrounds[currentBackground]->Draw(window);
}