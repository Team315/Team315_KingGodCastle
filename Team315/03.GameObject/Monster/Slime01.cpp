#include "Slime01.h"

Slime01::Slime01(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier)
{
	SetType("Monster");
	SetName("Slime01");
	resStringTypes.insert({ ResStringType::Idle,"slime01_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"slime01_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"slime01_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"slime01_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"slime01_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"slime01_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"slime01_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"slime01_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"slime01_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"slime01_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"slime01_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"slime01_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"slime01_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_punch.wav" });
}

Slime01::~Slime01()
{
}

void Slime01::Init()
{
	Character::Init();
}

//void Slime01::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("slime01_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "slime01_DownIdle" : "slime01_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "slime01_RightIdle" : "slime01_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "slime01_DownMove" : "slime01_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "slime01_RightMove" : "slime01_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "slime01_RightAttack" : "slime01_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "slime01_DownAttack" : "slime01_UpAttack");
//		}
//		break;
//	}
//}

void Slime01::Update(float dt)
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

void Slime01::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime01::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Slime01::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Slime01::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime01::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime01::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "slime01_DownMove" : "slime01_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "slime01_RightMove" : "slime01_LeftMove");
//	}
//}
//
//void Slime01::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
