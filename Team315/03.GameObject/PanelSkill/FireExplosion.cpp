#include "FireExplosion.h"
#include "Character.h"
#include "rapidcsv.h"
FireExplosion::FireExplosion()
	:isPlaying(false)
{
}

FireExplosion::~FireExplosion()
{
}

void FireExplosion::Enter()
{
	SetAni();
	SetDamege();
}

void FireExplosion::Init()
{
}

void FireExplosion::Release()
{
}

void FireExplosion::Update(float dt)
{
	if (isPlaying)
	m_FireExplosion.Update(dt);
}

void FireExplosion::Draw(RenderWindow& window)
{
	if (!m_FireExplosion.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}

void FireExplosion::SetDamege()
{
	string panelDataPath = "data/PenalSkillTable.csv";

	rapidcsv::Document PanelDataDoc(panelDataPath, rapidcsv::LabelParams(0, -1));
	vector<int> damege = PanelDataDoc.GetColumn<int>(7);
	m_damege = damege[1];

}

void FireExplosion::SetAni()
{
	m_FireExplosion.SetTarget(&sprite);
	m_FireExplosion.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_FireExplosion"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f + 200.f });
	SetScale(3.f, 3.f);
}

void FireExplosion::SetIsPlaying(bool is)
{
	isPlaying = is;
}

void FireExplosion::PlayingAni()
{
	isPlaying = true;
	m_FireExplosion.Play("Fx_FireExplosion");
	ActionSkill();
}

void FireExplosion::ActionSkill()
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	

	for (auto monster : mainGrid)
	{
		if (monster != nullptr && !monster->GetType().compare("Monster"))
		{
			dynamic_cast<Character*>(monster)->TakeDamege((float)m_damege);
		}
	}
}
