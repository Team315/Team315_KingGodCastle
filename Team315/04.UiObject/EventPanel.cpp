#include "EventPanel.h"
#include "BackgroundText.h"
#include "Include.h"
#include "ItemInfoWindow.h"
#include "Scene.h"
#include "SpriteObj.h"
#include "DataTableMgr.h"
#include "StringTable.h"

EventPanel::EventPanel(Scene* scene)
	: parentScene(scene), previewOn(false)
{
	SetSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	SetFillColor(Color(0x0f, 0x0f, 0x0f, 60.f));

	previewButton = new SpriteObj();
	previewButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Pagedown.png"));
	Vector2f textureSize(
		previewButton->GetTextureRect().width * 0.8f,
		previewButton->GetTextureRect().height * 0.8f);
	previewButton->SetHitbox(FloatRect(0, 0, textureSize.x, textureSize.y), Origins::TL);
	previewButton->SetScale(0.8f, 0.8f);
	previewButton->Init();
	SetPos(Vector2f(0, GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.5f));

	title = new BackgroundText();
	title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/BlueRibbon.png"));
	title->SetTextStyle(Color::White, 25, Color::Black, 1.0f);
}

EventPanel::~EventPanel()
{
}

void EventPanel::Init()
{
}

void EventPanel::Release()
{
}

void EventPanel::Reset()
{
}

void EventPanel::Update(float dt)
{
	if (previewButton->CollideTest(parentScene->ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		if (InputMgr::GetMouseDown(Mouse::Left))
		{
			previewOn = true;
			previewButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Pageup.png"));
		}
	}
	
	if (previewOn)
	{
		if (InputMgr::GetMouseUp(Mouse::Left))
		{
			previewOn = false;
			previewButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Pagedown.png"));
		}
	}
}

void EventPanel::Draw(RenderWindow& window)
{
	if (!previewOn)
	{
		RectangleObj::Draw(window);
		title->Draw(window);
		window.draw(head);
	}

	previewButton->Draw(window);
}

void EventPanel::SetOrigin(Origins origin)
{
}

void EventPanel::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	previewButton->SetPos(pos +
		Vector2f(GAME_SCREEN_WIDTH - previewButton->GetSize().x,
			GAME_SCREEN_HEIGHT - previewButton->GetSize().y));
}

void EventPanel::SetEventPanelType(EventType eType)
{
	string key = "";

	switch (eType)
	{
	case EventType::Forge:
		key = "ForgeTitle";
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_forge.png"));
		GAME_MGR->GetWaveRewardMapElem();
		break;
	case EventType::Power:
		key = "PowerTitle";
		break;
	case EventType::GameOver:
		key = "GameOverTitle";
		break;
	case EventType::GameClear:
		key = "GameClearTitle";
		break;
	}
	title->SetString(STRING_TABLE->Get(key));
}