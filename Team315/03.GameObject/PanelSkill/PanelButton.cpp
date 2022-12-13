#include "PanelButton.h"

PanelButton::PanelButton()
{
}

PanelButton::~PanelButton()
{
}

void PanelButton::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture(GetRandomSkill()));
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

string PanelButton::GetRandomSkill()
{

	int num = Utils::RandomRange(1, 5);
	if (num == 1)
	{
		m_PanelTypes = PanelTypes::ManaBless;
		return"graphics/PanelSkill/ManaBlessButton.png";
	}
	else if (num == 2)
	{
		m_PanelTypes = PanelTypes::Meteor;
		return"graphics/PanelSkill/MeteorButton.png";
	}
	else if (num == 3)
	{
		m_PanelTypes = PanelTypes::PingerSnap;
		return"graphics/PanelSkill/PingerSnapButton.png";
	}
	else if (num == 4)
	{
		m_PanelTypes = PanelTypes::Quagmire;
		return"graphics/PanelSkill/QuagmireButton.png";
	}
	else if (num == 5)
	{
		m_PanelTypes = PanelTypes::Shield;
		return"graphics/PanelSkill/ShieldButton.png";
	}
}
