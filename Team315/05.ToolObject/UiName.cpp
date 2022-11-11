#include "UiName.h"
#include "Include.h"
#include "TextObj.h"

UiName::UiName()
{
	m_Text = new TextObj();
	m_Text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"));
}

UiName::~UiName()
{
	Release();
}

void UiName::Init()
{
}

void UiName::Release()
{
}

void UiName::Update(float dt)
{
}

void UiName::Draw(RenderWindow& window)
{
	window.draw(sprite);
	m_Text->Draw(window);
}

void UiName::SetText(string str)
{
	Vector2f pos = sprite.getPosition();
	pos.y -= 3.f;

	m_Text->SetString(str);
	m_Text->SetCharacterSize(20);
	m_Text->SetColor(Color::White);
	m_Text->SetOutlineThickness(2.5f);
	m_Text->SetOutlineColor(Color::Black);
	m_Text->SetPos(pos);
	m_Text->SetOrigin(Origins::MC);
}

