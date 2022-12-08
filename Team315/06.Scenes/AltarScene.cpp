#include "AltarScene.h"
#include "Altar.h"

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


	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
		SCENE_MGR->ChangeScene(Scenes::Title);

}

void AltarScene::Draw(RenderWindow& window)
{
	for (auto obj : AltarList)
	{
		obj->Draw(window);
	}
}

void AltarScene::SetAltar()
{
	Altar* mana = new Altar({ 0.f,0.f }, 0);
	AltarList.push_back(mana);

}
