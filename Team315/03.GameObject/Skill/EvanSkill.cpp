#include "EvanSkill.h"

EvanSkill::EvanSkill()
{
	
}

EvanSkill::~EvanSkill()
{
}

void EvanSkill::Init()
{
	Skill::Init();

	SetTexture(*RESOURCE_MGR->GetTexture("graphics/Effect/player/evan_SkillEffect.png"));
}

void EvanSkill::Update(float dt)
{
	Skill::Update(dt);

}

void EvanSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}

void EvanSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}

void EvanSkill::SetState(AnimStates newState)
{
	Skill::SetState(newState);
}
