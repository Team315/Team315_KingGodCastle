#include "PanelButton.h"

PanelButton::PanelButton()
{
}

PanelButton::~PanelButton()
{
}

void PanelButton::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/PanelSkill/ManaBlessButton.png"));
	SetPos({100.f,100.f});
	SetOrigin(Origins::MC);

	m_resetButton.SetTexture(*RESOURCE_MGR->GetTexture("graphics/PanelSkill/ResetButton.png"));
	m_resetButton.SetPos({ 100.f,150.f });
	m_resetButton.SetOrigin(Origins::MC);


}

void PanelButton::Release()
{
}

void PanelButton::Update(float dt)
{

}

void PanelButton::Draw(RenderWindow& window)
{
	window.draw(sprite);
	m_resetButton.Draw(window);
	m_skillCount.Draw(window);
	m_resetCount.Draw(window);
}

bool PanelButton::CallResetButton(Vector2f pos)
{
	if (m_resetButton.GetGlobalBounds().contains(pos))
	{
		--m_resetCooldown;
		return true;
	}

	return false;
}

bool PanelButton::CallSkillButton(Vector2f pos)
{
	if (sprite.getGlobalBounds().contains(pos))
	{

		return true;
	}

	return false;
}
