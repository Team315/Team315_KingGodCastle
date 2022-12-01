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
	GameObj::Init();
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

void Skill::CalculateDamage(Character* character)
{
	damage = baseDamage[(starNumber + 1) / 2] * character->GetStat(Stats::AP).GetModifier();
}