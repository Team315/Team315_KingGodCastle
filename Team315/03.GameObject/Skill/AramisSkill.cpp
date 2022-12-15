#include "AramisSkill.h"
#include "Character.h"

AramisSkill::AramisSkill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 0, 0, 0, 0 };
}

AramisSkill::~AramisSkill()
{
}

void AramisSkill::Init()
{
	//sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/Effect/player/bullet.png"));
}

void AramisSkill::Update(float dt)
{
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
	target->TakeDamage(caster, AttackTypes::Skill);
}