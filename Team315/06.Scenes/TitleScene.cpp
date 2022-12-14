#include "TitleScene.h"
#include "Include.h"
#include "Button.h"

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
		"Press Click to start!",
		wSize.x * 0.2f, wSize.y * 0.5f, Color::White, 35.f);
	titleText->SetOutlineColor(Color::Black);
	titleText->SetOutlineThickness(2.f);
	titleText->SetOrigin(Origins::MC);
	//objList.push_back(titleText);


	CreatButton();
	
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
	if (InputMgr::GetKeyDown(Keyboard::Key::Num1))
	{
		SCENE_MGR->ChangeScene(Scenes::Tool);
		return;
	}
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

		if (InputMgr::GetMouseUp(Mouse::Button::Left))
		{
			isMode = true;
		}
	}

	if (isMode)
	{
		if (m_gameStart->GetGlobalBounds().contains(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			m_gameStart->SetScale(0.8f,0.8f);
			if (InputMgr::GetMouseDown(Mouse::Button::Left))
			{
				SCENE_MGR->ChangeScene(Scenes::Battle);
			}
		}
		else if (!m_gameStart->GetGlobalBounds().contains(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			m_gameStart->SetScale(0.75f, 0.75f);
		}
		

		if (m_altarStart->GetGlobalBounds().contains(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			m_altarStart->SetScale(0.8f, 0.8f);
			if (InputMgr::GetMouseDown(Mouse::Button::Left))
			{
				SCENE_MGR->ChangeScene(Scenes::Altar);
			}
		}
		else if (!m_altarStart->GetGlobalBounds().contains(ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			m_altarStart->SetScale(0.75f, 0.75f);
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

void TitleScene::CreatButton()
{
	m_gameStart = new SpriteObj;
	m_gameStart->SetTexture(*RESOURCE_MGR->GetTexture("graphics/titleScene/startButton.png"));
	m_gameStart->SetScale(0.75f, 0.75f);
	m_gameStart->SetPos({ GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT * 0.45f });
	m_gameStart->SetOrigin(Origins::MC);
	buttonList.push_back(m_gameStart);

	m_altarStart = new SpriteObj;
	m_altarStart->SetTexture(*RESOURCE_MGR->GetTexture("graphics/titleScene/altarButton.png"));
	m_altarStart->SetScale(0.75f, 0.75f);
	m_altarStart->SetPos({ GAME_SCREEN_WIDTH * 0.5f, GAME_SCREEN_HEIGHT * 0.63f });
	m_altarStart->SetOrigin(Origins::MC);
	buttonList.push_back(m_altarStart);

	//m_tool = new TextObj(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"),
	//	"Tool Start", 160.f, 720.f, Color::White, 35.f);
	//m_tool->SetOutlineColor(Color::Black);
	//m_tool->SetOutlineThickness(2.f);
	//m_tool->SetOrigin(Origins::ML);
	//buttonList.push_back(m_tool);

}

//void TitleScene::IsPick(int picNum)
//{
//	//isPick = !isPick;
//
//	if (picNum == 0)
//	{
//		m_pick->SetPos({ 160.f,365.f });
//		m_gameStart->SetScale(1.1f, 1.1f);
//		//m_gameStart->SetCharacterSize(45);
//		m_tool->SetCharacterSize(35);
//		//m_altarStart->SetCharacterSize(35);
//	}
//	else if(picNum == 1)
//	{
//		m_pick->SetPos({ 160.f,445.f });
//		//m_gameStart->SetCharacterSize(35);
//		//m_altarStart->SetCharacterSize(45);
//		m_tool->SetCharacterSize(35);
//	}
//
//	else if (picNum == 2)
//	{
//		m_pick->SetPos({ 160.f,525.f });
//
//		m_tool->SetCharacterSize(45);
//	}
//}
