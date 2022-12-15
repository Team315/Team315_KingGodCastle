#include "Quagmire.h"
#include "Character.h"
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
	m_Quagmire.Update(dt);
}

void Quagmire::Draw(RenderWindow& window)
{
	//if (isPlaying)
	if(!m_Quagmire.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
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
	
	for (auto monster : mainGrid)
	{
		if (monster != nullptr && !monster->GetType().compare("Monster"))
		{
			dynamic_cast<Character*>(monster)->TakeDamege(99999.f);
			//GAME_MGR->GetBattleTracker()->UpdateData(dynamic_cast<Character*>(monster), 999999.f, false, 0);

		}
	}

}
