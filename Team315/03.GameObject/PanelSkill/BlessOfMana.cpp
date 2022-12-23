#include "BlessOfMana.h"
#include "Character.h"
#include "rapidcsv.h"

BlessOfMana::BlessOfMana()
	:isPlaying(false), m_count(0)
{
}

BlessOfMana::~BlessOfMana()
{
}

void BlessOfMana::Enter()
{
	SetAni();
	SetMana();
	m_count = 0;
}

void BlessOfMana::Init()
{
}

void BlessOfMana::Release()
{
}

void BlessOfMana::Update(float dt)
{
	if (isPlaying)
	{
		m_time -= dt;
		if (m_time < 0.f&& m_count <10)
		{
			ActionSkill();

		}
		else if (m_time < 0.f && m_count == 10)
		{
			isPlaying = false;
		}
		m_BlessOfMana.Update(dt);
	}
}

void BlessOfMana::Draw(RenderWindow& window)
{
	if (!m_BlessOfMana.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}
void BlessOfMana::SetMana()
{
	string panelDataPath = "data/PenalSkillTable.csv";

	rapidcsv::Document PanelDataDoc(panelDataPath, rapidcsv::LabelParams(0, -1));
	vector<float> mana = PanelDataDoc.GetColumn<float>(7);
	m_addMana = mana[0];
}
void BlessOfMana::SetAni()
{
	m_BlessOfMana.SetTarget(&sprite);
	m_BlessOfMana.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_BlessOfMana"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f + 350.f });
	SetScale(12.f, 12.f);
}

void BlessOfMana::SetIsPlaying(bool is)
{
	isPlaying = is;
}

void BlessOfMana::PlayingAni()
{
	isPlaying = true;
	m_count = 0;
	m_BlessOfMana.Play("Fx_BlessOfMana");
}

void BlessOfMana::ActionSkill()
{
	vector<SpriteObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	m_time = 1.f;

	for (auto Player : mainGrid)
	{
		if (Player != nullptr && !Player->GetType().compare("Player"))
		{
			dynamic_cast<Character*>(Player)->AddBlessOfMana(m_addMana);
		}
	}
	++m_count;

	SOUND_MGR->Play("sounds/panel_BlessMana.ogg", 20.f, false);
}

void BlessOfMana::EndSkill()
{

}
