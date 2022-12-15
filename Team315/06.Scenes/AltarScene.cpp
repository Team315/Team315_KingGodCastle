#include "AltarScene.h"
#include "Altar.h"
#include "Brazier.h"
#include "RssProgressWindow.h"

AltarScene::AltarScene()
	: Scene(Scenes::Battle), testPos({0.f,0.f})
{
	m_backGround = new SpriteObj();
	m_backGround->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/AltarBackGround.png"));
	m_backGround->SetPos({ 0.f,0.f });
	m_backGround->SetOrigin(Origins::TL);

	
	m_backButton.SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/BackButton.png"));
	m_backButton.SetPos({ GAME_SCREEN_WIDTH,0.f });
	m_backButton.SetOrigin(Origins::TR);


	levelBar = new RssProgressWindow();
	levelBar->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/Icon_Level.png"));
	IntRect texRect = levelBar->GetTextureRect();
	levelBar->SetSize(Vector2f(120, texRect.height * 0.5f));
	levelBar->SetColor(Color(0, 0, 0, 100), Color::Green, Color::Black, 2.f);
	levelBar->SetProgressLocalPos(Vector2f(texRect.width * 0.5f, texRect.height * 0.25f));
	levelBar->SetLevelTextLocalPos(Vector2f(texRect.width * 0.5f + 4, texRect.height * 0.5f + 6));
	levelBar->SetPos(Vector2f(10, 10));

	objList.push_back(m_backGround);
	objList.push_back(m_backGround);
	objList.push_back(levelBar);

	SetAltar();
	SetBrazier();
}

AltarScene::~AltarScene()
{
}

void AltarScene::Init()
{
	CLOG::Print3String("AltarScene Init");

}

void AltarScene::Release()
{
}

void AltarScene::Enter()
{
	CLOG::Print3String("AltarScene enter");
	// level
	levelBar->SetLevel(GAME_MGR->accountInfo.level);
	// exp
	float value = GAME_MGR->accountInfo.level != 10 ? (float)GAME_MGR->accountInfo.exp / (float)GAME_MGR->accountExpLimit : 1.f;
	levelBar->GetProgressBar().SetProgressValue(value);

	for (auto Altar : AltarList)
	{
		Altar->Enter();
	}

	for (auto Brazier : BrazierList)
	{
		Brazier->Enter();
	}
}

void AltarScene::Exit()
{
	CLOG::Print3String("AltarScene exit");

}

void AltarScene::Update(float dt)
{ 
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::Key::Up))
	{
		testPos.y -= 1.f;
		for (auto aa : AltarList)
		{
			if (aa->GetIndex() == 0)
			{
				aa->MoveSetPos(testPos);
			}
		}
		CLOG::PrintVectorState(testPos, "now pos");
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Down))
	{
		testPos.y += 1.f;
		for (auto aa : AltarList)
		{
			if (aa->GetIndex() == 0)
			{
				aa->MoveSetPos(testPos);
			}
		}
		CLOG::PrintVectorState(testPos, "now pos");
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Left))
	{
		testPos.x -= 1.f;
		for (auto aa : AltarList)
		{
			if (aa->GetIndex() == 0)
			{
				aa->MoveSetPos(testPos);
			}
		}
		CLOG::PrintVectorState(testPos, "now pos");
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Right))
	{
		testPos.x += 1.f;
		for (auto aa : AltarList)
		{
			if (aa->GetIndex() == 0)
			{
				aa->MoveSetPos(testPos);
			}
		}
		CLOG::PrintVectorState(testPos, "now pos");
	}


	if (InputMgr::GetKeyDown(Keyboard::Key::W))
	{
		testPos.y -= 10.f;
		for (auto aa : AltarList)
		{
			if (aa->GetIndex() == 0)
			{
				aa->MoveSetPos(testPos);
			}
		}
		CLOG::PrintVectorState(testPos, "now pos");
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::S))
	{
		testPos.y += 10.f;
		for (auto aa : AltarList)
		{
			if (aa->GetIndex() == 0)
			{
				aa->MoveSetPos(testPos);
			}
		}
		CLOG::PrintVectorState(testPos, "now pos");
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::A))
	{
		testPos.x -= 10.f;
		for (auto aa : AltarList)
		{
			if (aa->GetIndex() == 0)
			{
				aa->MoveSetPos(testPos);
			}
		}
		CLOG::PrintVectorState(testPos, "now pos");
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::D))
	{
		testPos.x += 10.f;
		for (auto aa : AltarList)
		{
			if (aa->GetIndex() == 0)
			{
				aa->MoveSetPos(testPos);
			}
		}
		CLOG::PrintVectorState(testPos, "now pos");
	}

	//if (InputMgr::GetMouseUp(Mouse::Left))
	//{
	//	for (auto Altar : AltarList)
	//	{
	//		int num = Altar->GetButtonCall(ScreenToWorldPos(InputMgr::GetMousePosI()));
	//		//Altar->AddCount(num);
	//	}
	//}
	
	if (InputMgr::GetKeyDown(Keyboard::Key::F))
	{
		for (auto a : BrazierList)
		{
			a->MoveSetPos({ 0.f,0.f });
		}
		for (auto aa : AltarList)
		{
			aa->ResetCount();;
		}
		cout << "reset grade" << endl;
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		SaveData();
		SCENE_MGR->ChangeScene(Scenes::Title);
	}

	if (InputMgr::GetMouseUp(Mouse::Left))
	{
		for (auto Altar : AltarList)
		{
			for (auto Brazier : BrazierList)
			{
				Brazier->PlayAni(Altar->GetButtonCall(ScreenToWorldPos(InputMgr::GetMousePosI()), Brazier->GetGrade()));
			}
		}
	}
	if (InputMgr::GetMouseUp(Mouse::Left))
	{
		for (auto Brazier : BrazierList)
		{
			if (Brazier->ClickButton(ScreenToWorldPos(InputMgr::GetMousePosI())))
			{
				for (auto Altar : AltarList)
				{
					Altar->ResetCount();
				}
			}
		}
	}

	CallButton();

	for (auto Altar : AltarList)
	{
		Altar->Update(dt);
	}

	for (auto a : BrazierList)
	{
		//a->MoveSetPos({ 0.f,0.f });
		a->Update(dt);
	}

}

void AltarScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	m_backButton.Draw(window);
	for (auto obj : AltarList)
	{
		obj->Draw(window);
	}

	for (auto obj : BrazierList)
	{
		obj->Draw(window);
	}
}

void AltarScene::CallButton()
{
	if (m_backButton.GetGlobalBounds().contains(
		ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		if (InputMgr::GetMouseUp(Mouse::Left))
		{
			SaveData();
			SCENE_MGR->ChangeScene(Scenes::Title);
		}

		IsSize(true);
	}
	else
	{
		IsSize(false);
	}
	
}

void AltarScene::IsSize(bool is)
{
	if (is)
	{
		m_backButton.SetPos({ GAME_SCREEN_WIDTH,0.f });
		m_backButton.SetOrigin(Origins::TR);
		m_backButton.SetScale( 1.2f,1.2f );
	}
	else
	{
		m_backButton.SetPos({ GAME_SCREEN_WIDTH,0.f });
		m_backButton.SetOrigin(Origins::TR);
		m_backButton.SetScale( 1.0f,1.0f );
	}
}

void AltarScene::SetAltar()
{
	AltarData& data = GAME_MGR->altarData;

	Altar* mana = new Altar({ GAME_SCREEN_WIDTH * 0.15f,GAME_SCREEN_HEIGHT * 0.1f }, 0, L"마나의 제단", { 254,113,235,255 }, data.mana);
	AltarList.push_back(mana);

	Altar* silver = new Altar({ GAME_SCREEN_WIDTH * 0.62f,GAME_SCREEN_HEIGHT * 0.1f }, 1, L"은화의 제단", { 255,230,98,255 }, data.silver);
	AltarList.push_back(silver);

	Altar* physical = new Altar({ GAME_SCREEN_WIDTH * 0.15f,GAME_SCREEN_HEIGHT * 0.50f }, 2, L"신체의 제단", { 255,2,2,255 }, data.physical);
	AltarList.push_back(physical);

	Altar* enforce = new Altar({ GAME_SCREEN_WIDTH * 0.62f,GAME_SCREEN_HEIGHT * 0.50f }, 3, L"강화의 제단", { 0,203,255,255 }, data.enforce);
	AltarList.push_back(enforce);
}

void AltarScene::SetBrazier()
{
	GAME_MGR->altarData.mana;
	int temp = 0;
	temp = GAME_MGR->altarData.mana + GAME_MGR->altarData.silver + GAME_MGR->altarData.physical + GAME_MGR->altarData.enforce;
	int level = GAME_MGR->accountInfo.level * 2;
	
	if (temp > level)
	{
		for (auto init : AltarList)
		{
			init->SetGrade(0);
			init->Enter();
		}
	}

	Brazier* m_Brazier = new Brazier(level-temp);
	m_Brazier->Init();
	BrazierList.push_back(m_Brazier);
}

void AltarScene::SaveData()
{
	AltarData data;
	data.mana = AltarList[0]->GetGrade();
	data.silver = AltarList[1]->GetGrade();
	data.physical = AltarList[2]->GetGrade();
	data.enforce = AltarList[3]->GetGrade();

	GAME_MGR->SaveAltarData(data.mana, data.silver, data.physical, data.enforce);
	GAME_MGR->LoadAltarEffectFromTable();
}
