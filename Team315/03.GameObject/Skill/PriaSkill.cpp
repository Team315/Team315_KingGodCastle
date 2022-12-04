#include "PriaSkill.h"

PriaSkill::PriaSkill(int starNumber)
	: Skill(starNumber)
{
}

PriaSkill::~PriaSkill()
{
}

void PriaSkill::Init()
{
	Skill::Init();

	baseDamage = { 30, 45, 60, 75 };
}

void PriaSkill::Update(float dt)
{
	Skill::Update(dt);
}

void PriaSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}

void PriaSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}