#include "TitleScene.h"
#include "Include.h"

TitleScene::TitleScene()
	: Scene(Scenes::Title), duration(0.5f), timer(duration), isMode(false), m_pickNum(0)
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

		if (InputMgr::GetKeyDown(Keyboard::Key::Up))
		{
			if (m_pickNum != 0)
			{
				--m_pickNum;
				IsPick(m_pickNum);
			}
		}
		else if (InputMgr::GetKeyDown(Keyboard::Key::Down))
		{
			if (m_pickNum != 2)
			{
				++m_pickNum;
				IsPick(m_pickNum);
			}

		}
	
		

		if (InputMgr::GetKeyDown(Keyboard::Key::Space) || InputMgr::GetKeyDown(Keyboard::Key::Enter))
		{
			if (m_pickNum == 0)
			{
				SCENE_MGR->ChangeScene(Scenes::Battle);
			}
			else if (m_pickNum == 1)
			{
				SCENE_MGR->ChangeScene(Scenes::Altar);
			}
			else if (m_pickNum == 2)
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

	m_altarStart = new TextObj(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"),
		"Altar Start", 160.f, 440.f, Color::White, 35.f);
	m_altarStart->SetOutlineColor(Color::Black);
	m_altarStart->SetOutlineThickness(2.f);
	m_altarStart->SetOrigin(Origins::ML);
	buttonList.push_back(m_altarStart);

	m_tool = new TextObj(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"),
		"Tool Start", 160.f, 520.f, Color::White, 35.f);
	m_tool->SetOutlineColor(Color::Black);
	m_tool->SetOutlineThickness(2.f);
	m_tool->SetOrigin(Origins::ML);
	buttonList.push_back(m_tool);

}

void TitleScene::IsPick(int picNum)
{
	//isPick = !isPick;

	if (picNum == 0)
	{
		m_pick->SetPos({ 160.f,365.f });
		m_gameStart->SetCharacterSize(45);
		m_tool->SetCharacterSize(35);
		m_altarStart->SetCharacterSize(35);
	}
	else if(picNum == 1)
	{
		m_pick->SetPos({ 160.f,445.f });
		m_gameStart->SetCharacterSize(35);
		m_altarStart->SetCharacterSize(45);
		m_tool->SetCharacterSize(35);
	}

	else if (picNum == 2)
	{
		m_pick->SetPos({ 160.f,525.f });
		m_gameStart->SetCharacterSize(35);
		m_altarStart->SetCharacterSize(35);
		m_tool->SetCharacterSize(45);
	}
}
