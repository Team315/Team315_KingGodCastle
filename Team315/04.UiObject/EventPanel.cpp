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

	title = new BackgroundText();
	title->SetTextStyle(Color::White, 25, Color::Black, 1.0f);
	title->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	title->SetTextLocalPos(Vector2f(0, 25.f));
	title->SetOrigin(Origins::TC);

	headLocalPos = Vector2f(GAME_SCREEN_WIDTH * 0.5f, 250.f);

	SetPos(Vector2f(0, GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.5f));
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
		window.draw(head);
		title->Draw(window);
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
	head.setPosition(pos + headLocalPos);
	title->SetPos(pos + Vector2f(GAME_SCREEN_WIDTH * 0.5f, 200.f));
}

void EventPanel::SetEventPanelType(EventType eType)
{
	string key = "";

	switch (eType)
	{
	case EventType::Forge:
		key = "ForgeTitle";
		headLocalPos.y = 250.f;
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_Forge.png"), true);
		title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/BlueRibbon.png"), true);
		break;
	case EventType::Power:
		key = "PowerTitle";
		headLocalPos.y = 250.f;
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_Power.png"), true);
		title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/RedRibbon.png"), true);
		break;
	case EventType::GameOver:
		key = "GameOverTitle";
		headLocalPos.y = 200.f;
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_Defeat.png"), true);
		title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/RedRibbon.png"), true);
		break;
	case EventType::GameClear:
		key = "GameClearTitle";
		headLocalPos.y = 200.f;
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_Clear.png"), true);
		title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/BlueRibbon.png"), true);
		break;
	}

	FloatRect fr = (FloatRect)head.getTextureRect();
	float width = 250 / fr.width;
	float height = 250 / fr.height;
	float min = width > height ? height : width;
	head.setScale(min, min);
	Utils::SetOrigin(head, Origins::BC);

	title->SetString(STRING_TABLE->Get(key));
	title->SetOrigin(Origins::TC);
	SetPos(position);
}