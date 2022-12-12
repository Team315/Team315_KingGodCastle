#include "LeonHeart.h"
#include "Skill/LeonHeartSkill.h"

LeonHeart::LeonHeart(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier)
{
	SetType("Player");
	SetName("LeonHeart");
	resStringTypes.insert({ ResStringType::Idle,"LeonHeart_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"LeonHeart_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"LeonHeart_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"LeonHeart_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"LeonHeart_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"LeonHeart_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"LeonHeart_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"LeonHeart_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"LeonHeart_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"LeonHeart_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"LeonHeart_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"LeonHeart_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"LeonHeart_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"LeonHeart_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"LeonHeart_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"LeonHeart_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"LeonHeart_UpSkill" });

	resStringTypes.insert({ ResStringType::DownAttackEffect,"LeonHeart_DownAttack_Effect" });
	resStringTypes.insert({ ResStringType::LeftAttackEffect,"LeonHeart_LeftAttack_Effect" });
	resStringTypes.insert({ ResStringType::RightAttackEffect,"LeonHeart_RightAttack_Effect" });
	resStringTypes.insert({ ResStringType::UpAttackEffect,"LeonHeart_UpAttack_Effect" });

	resStringTypes.insert({ ResStringType::DownSkillEffect,"LeonHeart_DownSkill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEffect,"LeonHeart_LeftSkill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEffect,"LeonHeart_RightSkill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEffect,"LeonHeart_UpSkill_Effect" });

	attackPos.insert({ Dir::Right, { 40.f, 21.f } });
	attackPos.insert({ Dir::Left, {-40.f, 21.f} });
	attackPos.insert({ Dir::Down, { 0.f, 81.f} });
	attackPos.insert({ Dir::Up, { 0.f, 0.f} });

	skillPos.insert({ Dir::Right, { 40.f, 51.f } });
	skillPos.insert({ Dir::Left, { -40.f, 51.f } });
	skillPos.insert({ Dir::Down, { 0.f, 51.f } });
	skillPos.insert({ Dir::Up, { 0.f, -121.f } });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/LeonHeart_atk.wav" });
}

LeonHeart::~LeonHeart()
{
}

void LeonHeart::Init()
{
	Character::Init();
	skill = new LeonHeartSkill(GetStarNumber());
}

void LeonHeart::Update(float dt)
{
	Character::Update(dt);
}

void LeonHeart::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void LeonHeart::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}
