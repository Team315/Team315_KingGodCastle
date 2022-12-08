#include "Aramis.h"
#include "Skill/AramisSkill.h"

Aramis::Aramis(bool mode, bool fixedStar, int skillTier)
	: Character(mode, fixedStar, skillTier), bulletSpeed(2000.f)
{
	SetType("Player");
	SetName("Aramis");
	resStringTypes.insert({ ResStringType::Idle,"Aramis_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"Aramis_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"Aramis_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"Aramis_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"Aramis_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"Aramis_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"Aramis_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"Aramis_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"Aramis_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"Aramis_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"Aramis_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"Aramis_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"Aramis_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"Aramis_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"Aramis_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"Aramis_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"Aramis_UpSkill" });

	resStringTypes.insert({ ResStringType::DownAttackEffect,"Aramis_DownAttack_Effect" });
	resStringTypes.insert({ ResStringType::LeftAttackEffect,"Aramis_LeftAttack_Effect" });
	resStringTypes.insert({ ResStringType::RightAttackEffect,"Aramis_RightAttack_Effect" });
	resStringTypes.insert({ ResStringType::UpAttackEffect,"Aramis_UpAttack_Effect" });

	resStringTypes.insert({ ResStringType::DownSkillEfect,"Aramis_DownSkill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEfect,"Aramis_LeftSkill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEfect,"Aramis_RightSkill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEfect,"Aramis_UpSkill_Effect" });

	attackPos.insert({ Dir::Right, { 81.f, -21.f } });
	attackPos.insert({ Dir::Left, { -81.f, -21.f} });
	attackPos.insert({ Dir::Down, { 0.f, -31.f} });
	attackPos.insert({ Dir::Up, { 3.f, -71.f} });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/Aramis_atk.wav" });
}

Aramis::~Aramis()
{
}

void Aramis::Init()
{
	Character::Init();
	skill = new AramisSkill(GetStarNumber());
}

void Aramis::Update(float dt)
{
	Character::Update(dt);
	
	//skill->Translate(lastDirection * bulletSpeed * dt);
	//
	//if (InputMgr::GetKeyDown(Keyboard::Z))
	//{
	//	SetState(AnimStates::Skill);
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

void Aramis::Draw(RenderWindow& window)
{
	Character::Draw(window);
	//skill->Draw(window);
}

void Aramis::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Aramis::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("Aramis_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "Aramis_RightIdle" : "Aramis_LeftIdle");
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "Aramis_DownIdle" : "Aramis_UpIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "Aramis_DownMove" : "Aramis_UpMove");
//		}
//		else if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "Aramis_RightMove" : "Aramis_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/Aramis_atk.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "Aramis_RightAttack" : "Aramis_LeftAttack");
//			if (lastDirection.x > 0.f)
//			{
//				effectAnimator.Play("Aramis_RightAttack_Effect");
//				Vector2f vec = position;
//				vec.x += 81.f;
//				vec.y -= 21.f;
//				effectSprite.setPosition(vec);
//			}
//			else if (lastDirection.x < 0.f)
//			{
//				effectAnimator.Play("Aramis_LeftAttack_Effect");
//				Vector2f vec = position;
//				vec.x -= 81.f;
//				vec.y -= 21.f;
//				effectSprite.setPosition(vec);
//			}
//		}
//		else if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/Aramis_atk.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "Aramis_DownAttack" : "Aramis_UpAttack");
//			if (lastDirection.y > 0.f)
//			{
//				effectAnimator.Play("Aramis_DownAttack_Effect");
//				Vector2f vec = position;
//				vec.y -= 31.f;
//				effectSprite.setPosition(vec);
//			}
//			else if (lastDirection.y < 0.f)
//			{
//				effectAnimator.Play("Aramis_UpAttack_Effect");
//				Vector2f vec = position;
//				vec.x += 3.f;
//				vec.y -= 71.f;
//				effectSprite.setPosition(vec);
//			}
//		}
//		break;
//	case AnimStates::Skill:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "Aramis_RightSkill" : "Aramis_LeftSkill");
//			//if (lastDirection.x > 0.f)
//			//{
//			//	effectAnimator.Play("Aramis_RightSkill_Effect");
//			//	Vector2f vec = GetPos();
//			//	vec.x += 81.f;
//			//	vec.y -= 21.f;
//			//	effectSprite.setPosition(vec);
//			//}
//			//else if (lastDirection.x < 0.f)
//			//{
//			//	effectAnimator.Play("Aramis_LeftSkill_Effect");
//			//	Vector2f vec = GetPos();
//			//	vec.x -= 81.f;
//			//	vec.y -= 21.f;
//			//	effectSprite.setPosition(vec);
//			//}
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "Aramis_DownSkill" : "Aramis_UpSkill");
//			//if (lastDirection.y > 0.f)
//			//{
//			//	effectAnimator.Play("Aramis_DownSkill_Effect");
//			//	Vector2f vec = GetPos();
//			//	vec.y -= 31.f;
//			//	effectSprite.setPosition(vec);
//			//}
//			//else if (lastDirection.y < 0.f)
//			//{
//			//	effectAnimator.Play("Aramis_UpSkill_Effect");
//			//	Vector2f vec = GetPos();
//			//	vec.x += 3.f;
//			//	vec.y -= 71.f;
//			//	effectSprite.setPosition(vec);
//			//}
//		}
//		break;
//	}
//}
//
//void Aramis::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Aramis::OnCompleteSkill()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Aramis::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Aramis::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Aramis::UpdateMove(float dt)
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
//		animator.Play((direction.x > 0.f) ? "Aramis_RightMove" : "Aramis_LeftMove");
//		move = true;
//	}
//	else if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "Aramis_DownMove" : "Aramis_UpMove");
//		move = true;
//	}
//}
//
//void Aramis::UpdateAttack(float dt)
//{
//	//skill->Init();
//
//	//dynamic_cast<AramisSkill*>(skill)->SetRotation(lastDirection);
//	//Vector2f vec = GetPos();
//
//	//if (lastDirection.y < 0.f)
//	//{
//	//	vec.x -= 5.f;
//	//	vec.y -= 100.f;
//	//}
//	//else if (lastDirection.y > 0.f)
//	//{
//	//	vec.x -= 90.f;
//	//	vec.y += 30.f;
//	//}
//	//else if (lastDirection.x < 0.f)
//	//{
//	//	vec.x -= 80.f;
//	//	vec.y -= 120.f;
//	//}
//	//else if (lastDirection.x > 0.f)
//	//{
//	//	vec.x += 80.f;
//	//	vec.y += 65.f;
//	//}
//	//skill->SetPos(vec);
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void Aramis::UpdateSkill(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}