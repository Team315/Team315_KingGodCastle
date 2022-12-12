#include "AltarScene.h"
#include "Altar.h"
#include "Brazier.h"

AltarScene::AltarScene()
	: Scene(Scenes::Battle), testPos({0.f,0.f})
{
	m_backGround = new RectangleObj();
	m_backGround->SetSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	m_backGround->SetFillColor(Color::White);
	m_backGround->SetFillColorAlpha(150);
	m_backGround->SetPos({ 0.f,0.f });
	m_backGround->SetOrigin(Origins::TL);

	objList.push_back(m_backGround);

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
	for (auto obj : objList)
	{
		obj->Draw(window);
	}
	for (auto obj : AltarList)
	{
		obj->Draw(window);
	}

	for (auto obj : BrazierList)
	{
		obj->Draw(window);
	}
}

void AltarScene::SetAltar()
{
	AltarData& data = GAME_MGR->altarData;

	Altar* mana = new Altar({ GAME_SCREEN_WIDTH * 0.15f,GAME_SCREEN_HEIGHT * 0.05f }, 0, L"마나의 제단", { 254,113,235,255 }, data.mana);
	AltarList.push_back(mana);

	Altar* silver = new Altar({ GAME_SCREEN_WIDTH * 0.62f,GAME_SCREEN_HEIGHT * 0.05f }, 1, L"은화의 제단", { 255,230,98,255 }, data.silver);
	AltarList.push_back(silver);

	Altar* physical = new Altar({ GAME_SCREEN_WIDTH * 0.15f,GAME_SCREEN_HEIGHT * 0.45f }, 2, L"신체의 제단", { 255,2,2,255 }, data.physical);
	AltarList.push_back(physical);

	Altar* enforce = new Altar({ GAME_SCREEN_WIDTH * 0.62f,GAME_SCREEN_HEIGHT * 0.45f }, 3, L"강화의 제단", { 0,203,255,255 }, data.enforce);
	AltarList.push_back(enforce);
}

void AltarScene::SetBrazier()
{
	Brazier* m_Brazier = new Brazier(20);
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
}
