#include "SheldaSkill.h"
#include "Character.h"

SheldaSkill::SheldaSkill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 30, 120, 250, 700 };
	animator.SetTarget(&sprite);
}

SheldaSkill::~SheldaSkill()
{
}

void SheldaSkill::Init()
{
	//animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_Skill_Effect"));
}

void SheldaSkill::Update(float dt)
{	
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
	animator.SetTarget(&sprite);
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_Skill_Effect"));
	animator.Play("Shelda_Skill_Effect");
}