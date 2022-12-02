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

	baseDamage = { 20, 35, 50, 65 };
	range.resize(CHARACTER_TIER_MAX);
	range[0] = { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 },
				{ 1, 7 }, { 1, 8 }, { 1, 9 }, { 1, 10 }, { 1, 11 }, { 1, 12 }, { 1, 13 } };

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

void EvanSkill::CastSkill(Character* caster)
{
}