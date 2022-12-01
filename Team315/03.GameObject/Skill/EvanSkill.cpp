#include "EvanSkill.h"

EvanSkill::EvanSkill()
{
}

EvanSkill::~EvanSkill()
{
}

void EvanSkill::Init()
{
	Skill::Init();

	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/Effect/player/evan_SkillEffect.png"));
	//sprite.setScale(1.f, 0.3f);
}

void EvanSkill::Update(float dt)
{
	Skill::Update(dt);

}

void EvanSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}

void EvanSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}

void EvanSkill::SetRotation(Vector2f dir)
{
	Skill::SetRotation(dir);
}
