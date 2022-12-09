#include "Slime02.h"

Slime02::Slime02(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier)
{
	SetType("Monster");
	SetName("Slime02");
	resStringTypes.insert({ ResStringType::Idle,"slime02_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"slime02_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"slime02_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"slime02_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"slime02_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"slime02_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"slime02_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"slime02_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"slime02_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"slime02_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"slime02_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"slime02_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"slime02_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_punch.wav" });
}

Slime02::~Slime02()
{
}

void Slime02::Init()
{
	Character::Init();
}

//void Slime02::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("slime02_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "slime02_DownIdle" : "slime02_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "slime02_RightIdle" : "slime02_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "slime02_DownMove" : "slime02_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "slime02_RightMove" : "slime02_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "slime02_RightAttack" : "slime02_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "slime02_DownAttack" : "slime02_UpAttack");
//		}
//		break;
//	}
//}

void Slime02::Update(float dt)
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

void Slime02::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime02::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Slime02::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Slime02::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime02::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime02::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "slime02_DownMove" : "slime02_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "slime02_RightMove" : "slime02_LeftMove");
//	}
//}
//
//void Slime02::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
