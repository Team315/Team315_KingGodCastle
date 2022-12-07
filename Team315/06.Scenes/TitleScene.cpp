#include "TitleScene.h"
#include "Include.h"

TitleScene::TitleScene()
	: Scene(Scenes::Title), duration(0.5f), timer(duration), isMode(false), isPick(false)
{
	CLOG::Print3String("title create");
	background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/titleScene/titleBackground.png"));
	objList.push_back(background);

	Vector2u wSize = FRAMEWORK->GetWindowSize();
	titleText = new TextObj(
		*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"),
		"Press Space bar to start!",
		wSize.x * 0.2f, wSize.y * 0.72f, Color::White, 30.f);
	titleText->SetOutlineColor(Color::Black);
	titleText->SetOutlineThickness(2.f);
	titleText->SetOrigin(Origins::MC);
	//objList.push_back(titleText);


	CreatButton();

	SetModePick({ 160.f,365.f });
	
	GAME_MGR->SetTilesData();
	GAME_MGR->CreatedTiles();
	GAME_MGR->SetBackGroundDatas();
	GAME_MGR->SetCharacterDatas();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	CLOG::Print3String("title Init");
	Scene::Init();
}

void TitleScene::Release()
{
}

void TitleScene::Enter()
{
	CLOG::Print3String("title enter");

	FRAMEWORK->SetWindowSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	currentView = gameView;
	SOUND_MGR->Play("sounds/Lobby.wav", 20.f, true);
}

void TitleScene::Exit()
{
	CLOG::Print3String("title exit");
	SOUND_MGR->StopAll();
}

void TitleScene::Update(float dt)
{

	// Dev Input
	/*if (InputMgr::GetKeyDown(Keyboard::Key::Num1))
	{
		SCENE_MGR->ChangeScene(Scenes::Tool);
		return;
	}*/
	/*if (InputMgr::GetKeyDown(Keyboard::Key::Num2))
	{
		SCENE_MGR->ChangeScene(Scenes::Loby);
		return;
	}*/
	/*if (InputMgr::GetKeyDown(Keyboard::Key::Num3))
	{
		SCENE_MGR->ChangeScene(Scenes::Battle);
		return;
	}*/

	// Game Input
	if (!isMode)
	{
		timer -= dt;

		if (timer <= 0.f)
		{
			titleText->SetActive(!titleText->GetActive());
			timer = duration;
		}

		if (InputMgr::GetKeyUp(Keyboard::Key::Space))
		{
			isMode = true;
			//SCENE_MGR->ChangeScene(Scenes::Loby);
			//SCENE_MGR->ChangeScene(Scenes::Battle);
			//return;
		}
	}

	if (isMode)
	{

		if (InputMgr::GetKeyDown(Keyboard::Key::Up) || InputMgr::GetKeyDown(Keyboard::Key::Down))
		{
			IsPick();
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::Space) || InputMgr::GetKeyDown(Keyboard::Key::Enter))
		{
			if (!isPick)
			{
				SCENE_MGR->ChangeScene(Scenes::Battle);
			}
			else
			{
				SCENE_MGR->ChangeScene(Scenes::Tool);
			}
		}
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		exit(0);

	Scene::Update(dt);
}

void TitleScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);

	if (!isMode&& titleText->GetActive())
	{
		titleText->Draw(window);
	}

	if (isMode)
	{
		for (auto button : buttonList)
		{
			button->Draw(window);
		}
	}
}

void TitleScene::SetModePick(Vector2f pos)
{
	m_pick = new SpriteObj();
	m_pick->SetTexture(*RESOURCE_MGR->GetTexture("graphics/titleScene/pick.png"));
	m_pick->SetPos(pos);
	m_pick->SetOrigin(Origins::MR);
	buttonList.push_back(m_pick);

}

void TitleScene::CreatButton()
{
	m_gameStart = new TextObj(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"),
		"Game Start", 160.f, 360.f, Color::White, 45.f);
	m_gameStart->SetOutlineColor(Color::Black);
	m_gameStart->SetOutlineThickness(2.f);
	m_gameStart->SetOrigin(Origins::ML);
	buttonList.push_back(m_gameStart);

	m_tool = new TextObj(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"),
		"Tool Start", 160.f, 440.f, Color::White, 35.f);
	m_tool->SetOutlineColor(Color::Black);
	m_tool->SetOutlineThickness(2.f);
	m_tool->SetOrigin(Origins::ML);
	buttonList.push_back(m_tool);

}

void TitleScene::IsPick()
{
	isPick = !isPick;

	if (!isPick)
	{
		m_pick->SetPos({ 160.f,365.f });
		m_gameStart->SetCharacterSize(45);
		m_tool->SetCharacterSize(35);
	}
	else
	{
		m_pick->SetPos({ 160.f,445.f });
		m_tool->SetCharacterSize(45);
		m_gameStart->SetCharacterSize(35);
	}
}
