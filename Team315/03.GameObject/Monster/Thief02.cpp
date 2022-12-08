#include "Thief02.h"

Thief02::Thief02(bool mode, bool fixedStar, int skillTier)
	: Character(mode, fixedStar, skillTier)
{
	SetType("Monster");
	SetName("Thief02");
	resStringTypes.insert({ ResStringType::Idle,"thief02_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"thief02_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"thief02_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"thief02_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"thief02_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"thief02_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"thief02_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"thief02_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"thief02_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"thief02_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"thief02_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"thief02_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"thief02_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_sword.wav" });
}

Thief02::~Thief02()
{
}

void Thief02::Init()
{
	Character::Init();
}

//void Thief02::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("thief02_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "thief02_DownIdle" : "thief02_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "thief02_RightIdle" : "thief02_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "thief02_DownMove" : "thief02_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "thief02_RightMove" : "thief02_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_sword.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "thief02_RightAttack" : "thief02_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_sword.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "thief02_DownAttack" : "thief02_UpAttack");
//		}
//		break;
//	}
//}

void Thief02::Update(float dt)
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
	//}
	//animator.Update(dt);
	//
	//if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	//{
	//	lastDirection = direction;
	//}
	//direction = { 0.f, 0.f };
}

void Thief02::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief02::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Thief02::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Thief02::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief02::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief02::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "thief02_DownMove" : "thief02_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "thief02_RightMove" : "thief02_LeftMove");
//	}
//}
//
//void Thief02::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}