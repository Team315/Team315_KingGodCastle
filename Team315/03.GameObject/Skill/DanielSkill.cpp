#include "DanielSkill.h"

DanielSkill::DanielSkill()
{
}

DanielSkill::~DanielSkill()
{
}

void DanielSkill::Init()
{
	Skill::Init();
	baseDamage = { 50, 60, 70, 80 };
}

void DanielSkill::Update(float dt)
{
	Skill::Update(dt);
}

void DanielSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}

void DanielSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}
