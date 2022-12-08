#include "Thief00.h"
#include "Skill/Thief00Skill.h"

Thief00::Thief00(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Thief00");
	resStringTypes.insert({ ResStringType::Idle,"thief00_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"thief00_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"thief00_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"thief00_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"thief00_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"thief00_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"thief00_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"thief00_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"thief00_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"thief00_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"thief00_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"thief00_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"thief00_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"thief00_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"thief00_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"thief00_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"thief00_UpSkill" });

	//resStringTypes.insert({ ResStringType::DownSkillEfect,"thief00_Skill_Effect" });
	//resStringTypes.insert({ ResStringType::LeftSkillEfect,"thief00_Skill_Effect" });
	//resStringTypes.insert({ ResStringType::RightSkillEfect,"thief00_Skill_Effect" });
	//resStringTypes.insert({ ResStringType::UpSkillEfect,"thief00_Skill_Effect" });

	Vector2f targetPos = GetTarget()->GetPos();

	attackPos.insert({ Dir::Right, targetPos });
	attackPos.insert({ Dir::Left, targetPos });
	attackPos.insert({ Dir::Down, targetPos });
	attackPos.insert({ Dir::Up, targetPos });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_claw.wav" });
}

Thief00::~Thief00()
{
}

void Thief00::Init()
{
	Character::Init();
	Character::AnimationInit();
	skill = new Thief00Skill(GetStarNumber());
}

void Thief00::Update(float dt)
{
	Character::Update(dt);

	//switch (currState)
	//{
	//case AnimStates::Idle:
	//	UpdateIdle(dt);
	//	break;
	//case AnimStates::MoveToIdle:
	//	UpdateMoveToIdle(dt);
	//	break;
	//case AnimStates::Move:
	//	UpdateMove(dt);
	//	break;
	//case AnimStates::Attack:
	//	UpdateAttack(dt);
	//	break;
	//case AnimStates::Skill:
	//	UpdateSkill(dt);
	//	break;
	//}
	//animator.Update(dt);
	//effectAnimator.Update(dt);
	//
	//if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	//{
	//	lastDirection = direction;
	//}
}

void Thief00::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief00::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Thief00::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("thief00_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "thief00_RightIdle" : "thief00_LeftIdle");
//		}
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "thief00_DownIdle" : "thief00_UpIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "thief00_DownMove" : "thief00_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "thief00_RightMove" : "thief00_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_claw.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "thief00_RightAttack" : "thief00_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_claw.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "thief00_DownAttack" : "thief00_UpAttack");
//		}
//		break;
//	case AnimStates::Skill:
//		Vector2f targetPos = GetTarget()->GetPos();
//		if (lastDirection.x)
//		{
//			//SetPos(targetPos);
//			if (lastDirection.x > 0.f)
//			{
//				animator.Play("thief00_RightSkill");
//				//effectAnimator.Play("thief00_RightSkill_Effect");
//				//Vector2f vec = GetPos();
//				//effectSprite.setPosition(vec);
//			}
//			else if (lastDirection.x < 0.f)
//			{
//				animator.Play("thief00_LeftSkill");
//				//effectAnimator.Play("thief00_LeftSkill_Effect");
//				//Vector2f vec = GetPos();
//				//effectSprite.setPosition(vec);
//			}
//		}
//		if (lastDirection.y)
//		{
//			//SetPos(targetPos);
//			if (lastDirection.y > 0.f)
//			{
//				animator.Play("thief00_DownSkill");
//				//effectAnimator.Play("thief00_DownSkill_Effect");
//				//Vector2f vec = GetPos();
//				//effectSprite.setPosition(vec);
//			}
//			else if (lastDirection.y < 0.f)
//			{
//				animator.Play("thief00_UpSkill");
//				//effectAnimator.Play("thief00_UpSkill_Effect");
//				//Vector2f vec = GetPos();
//				//effectSprite.setPosition(vec);
//			}
//		}
//		break;
//	}
//}

//void Thief00::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Thief00::OnCompleteSkill()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Thief00::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief00::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief00::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "thief00_RightMove" : "thief00_LeftMove");
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "thief00_DownMove" : "thief00_UpMove");
//	}
//}
//
//void Thief00::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void Thief00::UpdateSkill(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}