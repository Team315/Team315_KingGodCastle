#include "EventPanel.h"
#include "Include.h"
#include "ItemInfoWindow.h"
#include "SpriteObj.h"

EventPanel::EventPanel()
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
}

void EventPanel::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
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