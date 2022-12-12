#include "Evan.h"
#include "Skill/EvanSkill.h"

Evan::Evan(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier), skillSpeed(2000.f)
{
	SetType("Player");
	SetName("Evan");
	resStringTypes.insert({ ResStringType::Idle,"Evan_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"Evan_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"Evan_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"Evan_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"Evan_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"Evan_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"Evan_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"Evan_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"Evan_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"Evan_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"Evan_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"Evan_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"Evan_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"Evan_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"Evan_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"Evan_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"Evan_UpSkill" });

	resStringTypes.insert({ ResStringType::DownAttackEffect,"Sword_DownAttack_Effect" });
	resStringTypes.insert({ ResStringType::LeftAttackEffect,"Sword_LeftAttack_Effect" });
	resStringTypes.insert({ ResStringType::RightAttackEffect,"Sword_RightAttack_Effect" });
	resStringTypes.insert({ ResStringType::UpAttackEffect,"Sword_UpAttack_Effect" });

	resStringTypes.insert({ ResStringType::DownSkillEffect,"Evan_DownSkill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEffect,"Evan_LeftSkill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEffect,"Evan_RightSkill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEffect,"Evan_UpSkill_Effect" });

	attackPos.insert({ Dir::Right, { 10.f, 5.f } });
	attackPos.insert({ Dir::Left, { -10.f, 5.f } });
	attackPos.insert({ Dir::Down, { -11.f, 12.f } });
	attackPos.insert({ Dir::Up, { -10.f, 0.f } });

	skillPos.insert({ Dir::Right, { -30.f, -10.f } });
	skillPos.insert({ Dir::Left, { 30.f, -10.f } });
	skillPos.insert({ Dir::Down, { 0.f, -10.f } });
	skillPos.insert({ Dir::Up, { 5.f, 0.f } });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/Evan_atk.wav" });
}

Evan::~Evan()
{
}

void Evan::Init()
{
	Character::Init();
	skill = new EvanSkill(GetStarNumber());
}

void Evan::Update(float dt)
{
	Character::Update(dt);
	SetDir(direction);
	skill->Translate(direction * skillSpeed * dt);
}

void Evan::Draw(RenderWindow& window)
{
	Character::Draw(window);
	if(isBattle)
		skill->Draw(window);
}

void Evan::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}
