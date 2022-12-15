#include "Quagmire.h"
#include "Character.h"
#include "rapidcsv.h"

Quagmire::Quagmire()
	:isPlaying(false)
{
}

Quagmire::~Quagmire()
{
}

void Quagmire::Enter()
{
	SetAni();
	SetAttackSpeed();
}

void Quagmire::Init()
{
}

void Quagmire::Release()
{

}

void Quagmire::Update(float dt)
{
	if (isPlaying)
	{
		m_time -= dt;
		if (m_time < 0.f)
		{
			EndSkill();
			isPlaying = false;
		}
		m_Quagmire.Update(dt);
	}
}

void Quagmire::Draw(RenderWindow& window)
{
	//if (isPlaying)
	if(!m_Quagmire.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}

void Quagmire::SetAttackSpeed()
{
	string panelDataPath = "data/PenalSkillTable.csv";

	rapidcsv::Document PanelDataDoc(panelDataPath, rapidcsv::LabelParams(0, -1));
	vector<float> attackSpeed = PanelDataDoc.GetColumn<float>(7);
	m_attackSpeed = attackSpeed[3];
}

void Quagmire::SetAni()
{
	m_Quagmire.SetTarget(&sprite);
	m_Quagmire.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_Quagmire"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f +100.f});
	SetScale(3.f, 3.f);
}

void Quagmire::SetIsPlaying(bool is)
{
	isPlaying = is;
}

void Quagmire::PlayingAni()
{
	isPlaying = true;
	m_Quagmire.Play("Fx_Quagmire");
	ActionSkill();
}

void Quagmire::ActionSkill()
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
	
	m_time = 10.f;

	for (auto monster : mainGrid)
	{
		if (monster != nullptr && !monster->GetType().compare("Monster"))
		{
			dynamic_cast<Character*>(monster)->TakeBuff(StatType::AS, m_attackSpeed,false);
		}
	}
}

void Quagmire::EndSkill()
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	for (auto monster : mainGrid)
	{
		if (monster != nullptr && !monster->GetType().compare("Monster"))
		{
			dynamic_cast<Character*>(monster)->TakeBuff(StatType::AS, m_attackSpeed, true);
		}
	}
}
