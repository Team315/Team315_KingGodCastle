#include "AramisSkill.h"
#include "Character.h"

AramisSkill::AramisSkill(int starNumber)
	: Skill(starNumber)
{
}

AramisSkill::~AramisSkill()
{
}

void AramisSkill::Init()
{
	Skill::Init();
	baseDamage = { 0, 0, 0, 0 };

	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/Effect/player/bullet.png"));
}

void AramisSkill::Update(float dt)
{
	animator.Update(dt);
}

void AramisSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}

void AramisSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}

void AramisSkill::CastSkill(Character* caster)
{
	Character* target = dynamic_cast<Character*>(caster->GetTarget());
	target->TakeDamage(caster, false);
}