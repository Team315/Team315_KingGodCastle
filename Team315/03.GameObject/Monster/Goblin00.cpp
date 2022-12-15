#include "Goblin00.h"
#include "Skill/Goblin00Skill.h"

Goblin00::Goblin00(bool mode, bool useExtraUpgrade, int starGrade)
	: Character(mode, useExtraUpgrade, starGrade)
{
	SetType("Monster");
	SetName("Goblin00");
	resStringTypes.insert({ ResStringType::Idle,"goblin00_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"goblin00_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"goblin00_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"goblin00_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"goblin00_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"goblin00_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"goblin00_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"goblin00_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"goblin00_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"goblin00_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"goblin00_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"goblin00_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"goblin00_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"goblin00_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"goblin00_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"goblin00_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"goblin00_UpSkill" });

	resStringTypes.insert({ ResStringType::DownSkillEffect,"goblin00_Skill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEffect,"goblin00_Skill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEffect,"goblin00_Skill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEffect,"goblin00_Skill_Effect" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_bash.wav" });
}

Goblin00::~Goblin00()
{
}

void Goblin00::Init()
{
	Character::Init();
	skill = new Goblin00Skill(GetStarNumber());
}

void Goblin00::Update(float dt)
{
	Character::Update(dt);

	skill->GetAnimator()->Update(dt);
}

void Goblin00::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin00::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}
