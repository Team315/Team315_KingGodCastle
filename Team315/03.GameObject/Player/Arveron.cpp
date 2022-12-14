#include "Arveron.h"
#include "Skill/ArveronSkill.h"

Arveron::Arveron(bool mode, bool useExtraUpgrade, int starGrade)
	: Character(mode, useExtraUpgrade, starGrade)
{
	SetType("Player");
	SetName("Arveron");
	resStringTypes.insert({ ResStringType::Idle,"Arveron_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"Arveron_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"Arveron_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"Arveron_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"Arveron_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"Arveron_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"Arveron_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"Arveron_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"Arveron_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"Arveron_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"Arveron_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"Arveron_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"Arveron_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"Arveron_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"Arveron_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"Arveron_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"Arveron_UpSkill" });

	resStringTypes.insert({ ResStringType::DownAttackEffect,"Arveron_DownAttack_Effect" });
	resStringTypes.insert({ ResStringType::LeftAttackEffect,"Arveron_LeftAttack_Effect" });
	resStringTypes.insert({ ResStringType::RightAttackEffect,"Arveron_RightAttack_Effect" });
	resStringTypes.insert({ ResStringType::UpAttackEffect,"Arveron_UpAttack_Effect" });

	resStringTypes.insert({ ResStringType::DownSkillEffect,"Arveron_Skill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEffect,"Arveron_Skill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEffect,"Arveron_Skill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEffect,"Arveron_Skill_Effect" });

	attackPos.insert({ Dir::Right, { 0.f, 0.f } });
	attackPos.insert({ Dir::Left, { 0.f, 0.f } });
	attackPos.insert({ Dir::Down, { 0.f, 0.f } });
	attackPos.insert({ Dir::Up, { 0.f, 0.f } });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/Arveron_atk.wav" });
}

Arveron::~Arveron()
{
}

void Arveron::Init()
{
	Character::Init();
	skill = new ArveronSkill(GetStarNumber());
}

void Arveron::Update(float dt)
{
	Character::Update(dt);
	skill->GetAnimator()->Update(dt);
}

void Arveron::Draw(RenderWindow& window)
{
	if (!isAlive)
		return;

	Character::Draw(window);
	window.draw(effectSprite);
	if (isBattle)
		skill->Draw(window);

	//SpriteObj::Draw(window);
	//window.draw(effectSprite);

	//if (!isBattle)
	//{
	//	m_floodFill.Draw(window);
	//}
	//

	//hpBar->Draw(window);
	//star->Draw(window);
	//
	//for (auto& grid : itemGrid)
	//{
	//	if (grid->GetActive())
	//		grid->Draw(window);
	//}
}

void Arveron::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}
