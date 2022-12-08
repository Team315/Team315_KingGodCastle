#include "Slime03.h"

Slime03::Slime03(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Slime03");
	resStringTypes.insert({ ResStringType::Idle,"slime03_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"slime03_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"slime03_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"slime03_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"slime03_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"slime03_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"slime03_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"slime03_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"slime03_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"slime03_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"slime03_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"slime03_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"slime03_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_punch.wav" });
}

Slime03::~Slime03()
{
}

void Slime03::Init()
{
	Character::Init();
	Character::AnimationInit();
}

//void Slime03::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("slime03_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "slime03_DownIdle" : "slime03_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "slime03_RightIdle" : "slime03_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "slime03_DownMove" : "slime03_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "slime03_RightMove" : "slime03_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "slime03_RightAttack" : "slime03_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "slime03_DownAttack" : "slime03_UpAttack");
//		}
//		break;
//	}
//}

void Slime03::Update(float dt)
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

void Slime03::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime03::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Slime03::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Slime03::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime03::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime03::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "slime03_DownMove" : "slime03_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "slime03_RightMove" : "slime03_LeftMove");
//	}
//}
//
//void Slime03::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
