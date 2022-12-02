#include "AramisSkill.h"
#include "Character.h"

AramisSkill::AramisSkill()
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
	Skill::Update(dt);
}

void AramisSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}

void AramisSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}

void AramisSkill::SetRotation(Vector2f dir)
{
	sprite.setRotation(Utils::Angle(dir));
}

void AramisSkill::SetState(AnimStates newState)
{
	Skill::SetState(newState);
}