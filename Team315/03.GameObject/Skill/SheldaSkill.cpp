#include "SheldaSkill.h"
#include "Character.h"

SheldaSkill::SheldaSkill(int starNumber)
	: Skill(starNumber)
{
}

SheldaSkill::~SheldaSkill()
{
}

void SheldaSkill::Init()
{
	animator.SetTarget(&sprite);
	//animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_Skill_Effect"));
	
	baseDamage = { 30, 120, 250, 700 };
}

void SheldaSkill::Update(float dt)
{	
	animator.Update(dt);
}

void SheldaSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}

void SheldaSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}

void SheldaSkill::CastSkill(Character* caster)
{
	caster->TakeCare(caster, false);
}