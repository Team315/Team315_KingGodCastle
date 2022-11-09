#include "UiName.h"
#include "Include.h"
#include "TextObj.h"

UiName::UiName()
{
	m_Text = new TextObj(*RESOURCE_MGR->GetFont("fonts/NotoSans-Bold.ttf"),
		"",	0.f, 0.f, Color::Black, 0.f);
}

UiName::~UiName()
{
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
	m_Text->SetString(str);
	m_Text->SetCharacterSize(20);
	m_Text->SetColor(Color::White);
	m_Text->SetPos(sprite.getPosition());
	m_Text->SetOrigin(Origins::BC);

}

