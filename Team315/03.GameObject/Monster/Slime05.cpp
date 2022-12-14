#include "Slime05.h"

Slime05::Slime05(bool mode, bool useExtraUpgrade, int starGrade)
	: Character(mode, useExtraUpgrade, starGrade)
{
	SetType("Monster");
	SetName("Slime05");
	resStringTypes.insert({ ResStringType::Idle,"slime05_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"slime05_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"slime05_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"slime05_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"slime05_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"slime05_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"slime05_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"slime05_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"slime05_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"slime05_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"slime05_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"slime05_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"slime05_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_punch.wav" });
}

Slime05::~Slime05()
{
}

void Slime05::Init()
{
	Character::Init();
}

//void Slime05::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//	
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("slime05_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "slime05_DownIdle" : "slime05_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "slime05_RightIdle" : "slime05_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "slime05_DownMove" : "slime05_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "slime05_RightMove" : "slime05_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "slime05_RightAttack" : "slime05_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "slime05_DownAttack" : "slime05_UpAttack");
//		}
//		break;
//	}
//}

void Slime05::Update(float dt)
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

void Slime05::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime05::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Slime05::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Slime05::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime05::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime05::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "slime05_DownMove" : "slime05_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "slime05_RightMove" : "slime05_LeftMove");
//	}
//}
//
//void Slime05::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
