#include "Skill.h"
#include "Character.h"

Skill::Skill(int starNumber)
	: startPos(0.f, 0.f), destPos(0.f, 0.f), skillTier(starNumber)
{
	SetSkillTier(starNumber);
	baseDamage.resize(4);
}

Skill::~Skill()
{
}

void Skill::SetRotation(Vector2f dir)
{
	if (dir.y < 0.f)
		sprite.setRotation(90.f);
	else if (dir.y > 0.f)
		sprite.setRotation(270.f);
	else if (dir.x < 0.f)
		sprite.setRotation(0.f);
	else if (dir.x > 0.f)
		sprite.setRotation(180.f);
}

void Skill::SetState(AnimStates newState)
{
	if (currState == newState)
	{
		return;
	}
	currState = newState;
}

float Skill::CalculatePotential(Character* character)
{
	if (character == nullptr || this == nullptr)
		return 0.f;
	return baseDamage[skillTier] + character->GetStat(StatType::AP).GetModifier();
}

void Skill::SetSkillRange(Vector2f startPos)
{
}

void Skill::CastSkill(Character* caster)
{
	// ¿µ¿õº°·Î »ó¼Ó¹Þ¾Æ¼­ ¾¸
	cout << name << " is fire skill" << endl;
}

void Skill::SetSkillTier(int starNumber)
{
	this->skillTier = (starNumber + 1) / 2;
}