#include "Skill.h"
#include "Character.h"

Skill::Skill(int starNumber)
	: skillTier(starNumber)
{
	SetSkillTier(starNumber);
	baseDamage.resize(TIER_MAX);

	
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
	animator.Update(dt);
}

void Skill::Reset()
{
}

void Skill::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

//void Skill::SetRotation(Vector2f dir)
//{
//	if (dir.y < 0.f)
//		sprite.setRotation(90.f);
//	else if (dir.y > 0.f)
//		sprite.setRotation(270.f);
//	else if (dir.x < 0.f)
//		sprite.setRotation(0.f);
//	else if (dir.x > 0.f)
//		sprite.setRotation(180.f);
//}

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
	if (character == nullptr)
		return 0.f;
	return baseDamage[skillTier - 1] + character->GetStat(StatType::AP).GetModifier();
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