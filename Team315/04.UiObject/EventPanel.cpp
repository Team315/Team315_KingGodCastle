#include "EventPanel.h"
#include "Include.h"
#include "ItemInfoWindow.h"
#include "SpriteObj.h"

EventPanel::EventPanel()
{
	SetSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	SetFillColor(Color(0x0f, 0x0f, 0x0f, 60.f));
	SetPos(Vector2f(0, GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.5f));

	previewButton = new SpriteObj();
	previewButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Pagedown.png"));
	//previewButton.sethi
	previewButton->Init();
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
}