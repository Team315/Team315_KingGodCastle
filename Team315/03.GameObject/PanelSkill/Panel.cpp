#include "Panel.h"

Panel::Panel()
	:m_skillCooldown(0), m_resetCooldown(2), m_skillCost(5), isMouseOn(false), 
	isPlaying(false), isCurrPlaying(false)
{
}

Panel::~Panel()
{

}

void Panel::Init()
{
	//SetTexture(*RESOURCE_MGR->GetTexture(GetRandomSkill()));
	//SetPos({100.f,100.f});
	//SetOrigin(Origins::MC);

	//m_resetButton.SetTexture(*RESOURCE_MGR->GetTexture("graphics/PanelSkill/ResetButton.png"));
	//m_resetButton.SetPos({ 100.f,150.f });
	//m_resetButton.SetOrigin(Origins::MC);
}

void Panel::Release()
{

}

void Panel::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::M))
	{
		m_skillCooldown = 0;
		m_resetCooldown = 9;
		SetSkillCooldown();
		ResetSkill();
	}

	switch (m_PanelTypes)
	{
	case PanelTypes::BlessOfMana:
		m_BlessOfMana.Update(dt);
		break;
	case PanelTypes::FireExplosion:
		m_FireExplosion.Update(dt);
		break;
	case PanelTypes::FingerSnap:
		m_FingerSnap.Update(dt);
		break;
	case PanelTypes::Quagmire:
		m_Quagmire.Update(dt);
		break;
	case PanelTypes::DivineShield:
		m_DivineShield.Update(dt);
		break;
	}
}

void Panel::Draw(RenderWindow& window)
{
	window.draw(sprite);
	if (!isPlaying)
	{
		m_resetButton.Draw(window);
		m_resetCount.Draw(window);
	}
	m_skillCount.Draw(window);

	if (isMouseOn)
	{
		m_BackGround.Draw(window);
		m_NameBackGround.Draw(window);
		m_InfoBackGround.Draw(window);

		m_SkillName.Draw(window);
		m_SkillInfo.Draw(window);
	}
}

void Panel::DrawUp(RenderWindow& window)
{
	m_Quagmire.Draw(window);
}

void Panel::DrawDown(RenderWindow& window)
{
	m_FingerSnap.Draw(window);
	m_BlessOfMana.Draw(window);
	m_DivineShield.Draw(window);
	m_FireExplosion.Draw(window);
}

void Panel::Enter()
{
	m_resetButton.SetTexture(*RESOURCE_MGR->GetTexture("graphics/PanelSkill/ResetButton.png"));
	m_resetButton.SetPos({ GAME_SCREEN_WIDTH * 0.92f,GAME_SCREEN_HEIGHT * 1.1f });
	m_resetButton.SetOrigin(Origins::MC);
	m_resetButton.SetScale(0.8f, 0.8f);
	m_resetCooldown = 2 + GAME_MGR->altarData.rerollCount;

	ResetSkill();
	SetSkillCooldown();
	SetSkillBackGround();
	SetSkillInfo();

	m_Quagmire.Enter();
	m_FingerSnap.Enter();
	m_BlessOfMana.Enter();
	m_DivineShield.Enter();
	m_FireExplosion.Enter();
}

bool Panel::CallResetButton(Vector2f pos)
{
	if (m_resetButton.GetGlobalBounds().contains(pos) && m_resetCooldown > 0)
	{

		if (InputMgr::GetMouseUp(Mouse::Left))
		{
			--m_resetCooldown;
			ResetSkill();
		}
		return true;
	}

	return false;
}

bool Panel::CallSkillButton(Vector2f pos)
{
	if (sprite.getGlobalBounds().contains(pos))
	{
		isMouseOn = true;

		return true;
	}
	else
	{
		isMouseOn = false;
	}

	return false;
}

bool Panel::CallSkillPlayButton(Vector2f pos)
{
	if (sprite.getGlobalBounds().contains(pos))
	{
		if (isPlaying && m_skillCooldown == 0)
		{
			m_skillCooldown += m_skillCost;
			SetSkillCooldown();

			return true;
		}
	}
	return false;
}

void Panel::ResetSkill()
{
	sprite.setTexture(*RESOURCE_MGR->GetTexture(GetRandomSkill()), true);
	SetSkillButtonPos();
	SetOrigin(Origins::MC);
	SetScale(0.8f, 0.8f);

	SetDataTable();
	SetSkillInfo();

	string skillNum = "graphics/PanelSkill/BottomNumber_" + to_string(m_resetCooldown) + ".png";
	Vector2f vec = m_resetButton.GetPos();
	vec += {-28.f, 15.f};
	m_resetCount.SetTexture(*RESOURCE_MGR->GetTexture(skillNum));
	m_resetCount.SetPos(vec);
	m_resetCount.SetOrigin(Origins::MC);
}

void Panel::SetSkillButtonPos()
{
	if (!isPlaying)
	{
		SetPos({ GAME_SCREEN_WIDTH * 0.92f,GAME_SCREEN_HEIGHT * 1.f });
	}
	else
	{
		SetPos({ GAME_SCREEN_WIDTH * 0.88f,GAME_SCREEN_HEIGHT * 0.85f });
	}
}

void Panel::SetSkillCooldown()
{
	string skillNum = "graphics/PanelSkill/BottomNumber_" + to_string(m_skillCooldown) + ".png";
	Vector2f vec = GetPos();
	vec += {-28.f, 35.f};
	m_skillCount.SetTexture(*RESOURCE_MGR->GetTexture(skillNum));
	m_skillCount.SetPos(vec);
	m_skillCount.SetOrigin(Origins::MC);
}

string Panel::GetRandomSkill()
{
	int num = Utils::RandomRange(1, 5);

	num = 3;

	if (num == 1)
	{
		m_PanelTypes = PanelTypes::BlessOfMana;
		return"graphics/PanelSkill/ManaBlessButton.png";
	}
	else if (num == 2)
	{
		m_PanelTypes = PanelTypes::FireExplosion;
		return"graphics/PanelSkill/MeteorButton.png";
	}
	else if (num == 3)
	{
		m_PanelTypes = PanelTypes::FingerSnap;
		return"graphics/PanelSkill/PingerSnapButton.png";
	}
	else if (num == 4)
	{
		m_PanelTypes = PanelTypes::Quagmire;
		return"graphics/PanelSkill/QuagmireButton.png";
	}
	else if (num == 5)
	{
		m_PanelTypes = PanelTypes::DivineShield;
		return"graphics/PanelSkill/ShieldButton.png";
	}
}

void Panel::SetSkillBackGround()
{
	m_BackGround.SetSize(240.f, 150.f);
	m_BackGround.SetFillColor(Color::Black);
	m_BackGround.SetFillColorAlpha(100);
	m_BackGround.SetOrigin(Origins::MC);
	m_BackGround.SetPos({ GAME_SCREEN_WIDTH * 0.5f , GAME_SCREEN_HEIGHT});

	Vector2f vec = m_BackGround.GetPos();
	vec.y -= 45.f;

	m_NamePos = vec;
	m_NamePos.y -= 5.f;
	m_NameBackGround.SetSize(220.f, 40.f);;
	m_NameBackGround.SetFillColor(Color::Black);
	m_NameBackGround.SetFillColorAlpha(200);
	m_NameBackGround.SetOrigin(Origins::MC);
	m_NameBackGround.SetPos(vec);

	vec.y += 70.f;

	m_InfoPos = vec;
	m_InfoPos.y -= 5;
	m_InfoBackGround.SetSize(220.f, 80.f);;
	m_InfoBackGround.SetFillColor(Color::Black);
	m_InfoBackGround.SetFillColorAlpha(200);
	m_InfoBackGround.SetOrigin(Origins::MC);
	m_InfoBackGround.SetPos(vec);
}

void Panel::SetSkillInfo()
{
	m_SkillName.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_SkillName.SetString(m_SkillNameStr);
	m_SkillName.SetNewline();
	m_SkillName.SetColor(Color::White);
	m_SkillName.SetCharacterSize(25);
	m_SkillName.SetPos(m_NamePos);
	m_SkillName.SetOrigin(Origins::MC);

	m_SkillInfo.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_SkillInfo.SetString(m_SkillInfoStr);
	m_SkillInfo.SetNewline();
	m_SkillInfo.SetColor(Color::White);
	m_SkillInfo.SetCharacterSize(18);
	m_SkillInfo.SetPos(m_InfoPos);
	m_SkillInfo.SetOrigin(Origins::MC);
}

void Panel::SetDataTable()
{
	string panelDataPath = "data/PenalSkillTable.csv";

	rapidcsv::Document PanelDataDoc(panelDataPath, rapidcsv::LabelParams(0, -1));
	vector<string> panel_name = PanelDataDoc.GetColumn<string>(1);
	vector<string> panel_info = PanelDataDoc.GetColumn<string>(2);
	vector<int> cooldown = PanelDataDoc.GetColumn<int>(8);

	m_SkillNameStr = panel_name[(int)m_PanelTypes];
	m_SkillInfoStr = panel_info[(int)m_PanelTypes];
	m_skillCost = cooldown[(int)m_PanelTypes];
}

void Panel::SetIsPlay(bool isplay)
{
	isCurrPlaying = isplay;

	if (isPlaying != isCurrPlaying)
	{
		isPlaying = isCurrPlaying;

		if (!isPlaying && m_skillCooldown > 0)
			--m_skillCooldown;

		SetSkillButtonPos();
		SetSkillCooldown();
	}
}

void Panel::SetIsSkillPlaying(bool isplay)
{
	switch (m_PanelTypes)
	{
	case PanelTypes::BlessOfMana:
		m_BlessOfMana.SetIsPlaying(isplay);
		break;
	case PanelTypes::FireExplosion:
		m_FireExplosion.SetIsPlaying(isplay);
		break;
	case PanelTypes::FingerSnap:
		m_FingerSnap.SetIsPlaying(isplay);
		break;
	case PanelTypes::Quagmire:
		m_Quagmire.SetIsPlaying(isplay);
		break;
	case PanelTypes::DivineShield:
		m_DivineShield.SetIsPlaying(isplay);
		break;
	}
}

void Panel::PlayingAni()
{
	switch (m_PanelTypes)
	{
	case PanelTypes::BlessOfMana:
		m_BlessOfMana.PlayingAni();
		break;
	case PanelTypes::FireExplosion:
		m_FireExplosion.PlayingAni();
		break;
	case PanelTypes::FingerSnap:
		m_FingerSnap.PlayingAni();
		break;
	case PanelTypes::Quagmire:
		m_Quagmire.PlayingAni();
		break;
	case PanelTypes::DivineShield:
		m_DivineShield.PlayingAni();
		break;
	}
}
