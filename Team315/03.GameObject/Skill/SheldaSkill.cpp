#include "SheldaSkill.h"

SheldaSkill::SheldaSkill()
{
}

SheldaSkill::~SheldaSkill()
{
}

void SheldaSkill::Init()
{
	Skill::Init();
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_Skill_Effect"));
}

void SheldaSkill::Update(float dt)
{	
  	Skill::Update(dt);

	
	//animator.Play("Shelda_Skill_Effect");
	
	animator.Update(dt);
}

void SheldaSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}
