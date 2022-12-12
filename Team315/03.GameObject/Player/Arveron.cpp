#include "Arveron.h"
#include "Skill/ArveronSkill.h"

Arveron::Arveron(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier)
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
}

void Arveron::Draw(RenderWindow& window)
{
	if (!isAlive)
		return;

	SpriteObj::Draw(window);
	window.draw(effectSprite);

	//Character::Draw(window);
	//window.draw(effectSprite);

	//if (!isBattle)
	//{
	//	m_floodFill.Draw(window);
	//}
	//

	hpBar->Draw(window);
	star->Draw(window);
	
	for (auto& grid : itemGrid)
	{
		if (grid->GetActive())
			grid->Draw(window);
	}
}

void Arveron::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Arveron::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("Arveron_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "Arveron_RightIdle" : "Arveron_LeftIdle");
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "Arveron_DownIdle" : "Arveron_UpIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "Arveron_DownMove" : "Arveron_UpMove");
//		}
//		else if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "Arveron_RightMove" : "Arveron_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/Arveron_atk.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "Arveron_RightAttack" : "Arveron_LeftAttack");
//			effectAnimator.Play((lastDirection.x > 0.f) ? "Arveron_RightAttack_Effect" : "Arveron_LeftAttack_Effect");
//
//			Vector2f vec = m_target->GetPos();
//			vec.y += 15.f;
//			effectSprite.setPosition(vec);
//		}
//		else if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/Arveron_atk.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "Arveron_DownAttack" : "Arveron_UpAttack");
//			effectAnimator.Play((lastDirection.y > 0.f) ? "Arveron_DownAttack_Effect" : "Arveron_UpAttack_Effect");
//
//			Vector2f vec = m_target->GetPos();
//			vec.y += 15.f;
//			effectSprite.setPosition(vec);
//		}
//		break;
//	case AnimStates::Skill:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "Arveron_RightSkill" : "Arveron_LeftSkill");
//			//effectAnimator.Play("Arveron_Skill_Effect");
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "Arveron_DownSkill" : "Arveron_UpSkill");
//			//effectAnimator.Play("Arveron_Skill_Effect");
//		}
//		break;
//	}
//}
//
//void Arveron::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Arveron::OnCompleteSkill()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Arveron::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Arveron::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Arveron::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (move)
//		return;
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "Arveron_RightMove" : "Arveron_LeftMove");
//		move = true;
//	}
//	else if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "Arveron_DownMove" : "Arveron_UpMove");
//		move = true;
//	}
//}
//
//void Arveron::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void Arveron::UpdateSkill(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}