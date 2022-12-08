#include "LeonHeart.h"
#include "Skill/LeonHeartSkill.h"

LeonHeart::LeonHeart(int skillTier)
	: Character(skillTier)
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

	resStringTypes.insert({ ResStringType::DownSkillEfect,"LeonHeart_DownSkill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEfect,"LeonHeart_LeftSkill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEfect,"LeonHeart_RightSkill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEfect,"LeonHeart_UpSkill_Effect" });

	attackPos.insert({ Dir::Right, { 40.f, 21.f } });
	attackPos.insert({ Dir::Left, {-40.f, 21.f} });
	attackPos.insert({ Dir::Down, { 0.f, 81.f} });
	attackPos.insert({ Dir::Up, { 0.f, 0.f} });

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

	//if (InputMgr::GetKeyDown(Keyboard::Z))
	//{
	//	SetState(AnimStates::Attack);
	//}
	//
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

void LeonHeart::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void LeonHeart::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void LeonHeart::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("LeonHeart_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "LeonHeart_RightIdle" : "LeonHeart_LeftIdle");
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "LeonHeart_DownIdle" : "LeonHeart_UpIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "LeonHeart_DownMove" : "LeonHeart_UpMove");
//		}
//		else if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "LeonHeart_RightMove" : "LeonHeart_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/LeonHeart_atk.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "LeonHeart_RightAttack" : "LeonHeart_LeftAttack");
//			if (lastDirection.x > 0.f)
//			{
//				effectAnimator.Play("LeonHeart_RightAttack_Effect");
//				Vector2f vec = GetPos();
//				vec.x += 40.f;
//				vec.y += 21.f;
//				effectSprite.setPosition(vec);
//			}
//			else if (lastDirection.x < 0.f)
//			{
//				effectAnimator.Play("LeonHeart_LeftAttack_Effect");
//				Vector2f vec = GetPos();
//				vec.x -= 40.f;
//				vec.y += 21.f;
//				effectSprite.setPosition(vec);
//			}
//		}
//		else if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/LeonHeart_atk.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "LeonHeart_DownAttack" : "LeonHeart_UpAttack");
//			if (lastDirection.y > 0.f)
//			{
//				effectAnimator.Play("LeonHeart_DownAttack_Effect");
//				Vector2f vec = GetPos();
//				vec.y -= 81.f;
//				effectSprite.setPosition(vec);
//			}
//			else if (lastDirection.y < 0.f)
//			{
//				effectAnimator.Play("LeonHeart_UpAttack_Effect");
//				Vector2f vec = GetPos();
//				effectSprite.setPosition(vec);
//			}
//		}
//		break;
//	case AnimStates::Skill:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "LeonHeart_RightSkill" : "LeonHeart_LeftSkill");
//			//if (lastDirection.x > 0.f)
//			//{
//			//	effectAnimator.Play("LeonHeart_RightSkill_Effect");
//			//	Vector2f vec = GetPos();
//			//	vec.x += 40.f;
//			//	vec.y += 51.f;
//			//	effectSprite.setPosition(vec);
//			//}
//			//else if (lastDirection.x < 0.f)
//			//{
//			//	effectAnimator.Play("LeonHeart_LeftSkill_Effect");
//			//	Vector2f vec = GetPos();
//			//	vec.x -= 40.f;
//			//	vec.y += 51.f;
//			//	effectSprite.setPosition(vec);
//			//}
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "LeonHeart_DownSkill" : "LeonHeart_UpSkill");
//			//if (lastDirection.y > 0.f)
//			//{
//			//	effectAnimator.Play("LeonHeart_DownSkill_Effect");
//			//	Vector2f vec = GetPos();
//			//	vec.y += 51.f;
//			//	effectSprite.setPosition(vec);
//			//}
//			//if (lastDirection.y < 0.f)
//			//{
//			//	effectAnimator.Play("LeonHeart_UpSkill_Effect");
//			//	Vector2f vec = GetPos();
//			//	vec.y -= 121.f;
//			//	effectSprite.setPosition(vec);
//			//}
//		}
//		break;
//	}
//}

//void LeonHeart::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void LeonHeart::OnCompleteSkill()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void LeonHeart::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void LeonHeart::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void LeonHeart::UpdateMove(float dt)
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
//		animator.Play((direction.x > 0.f) ? "LeonHeart_RightMove" : "LeonHeart_LeftMove");
//		move = true;
//	}
//	else if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "LeonHeart_DownMove" : "LeonHeart_UpMove");
//		move = true;
//	}
//}
//
//void LeonHeart::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void LeonHeart::UpdateSkill(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
