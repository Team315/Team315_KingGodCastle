#include "Skill.h"
#include "Character.h"

Skill::Skill()
	: damage(0.f), startPos(0.f, 0.f), destPos(0.f, 0.f), starNumber(0)
{
	baseDamage.resize(4);
}

Skill::~Skill()
{
}

void Skill::Init()
{
}

void Skill::Update(float dt)
{
}

void Skill::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Skill::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
}

void Skill::SetState(AnimStates newState)
{
	if (currState == newState)
	{
		return;
	}
	currState = newState;
}

void Skill::CalculateDamage(Character *character)
{
	damage = baseDamage[(starNumber + 1) / 2] * character->GetStat(Stats::AP).GetModifier();
}