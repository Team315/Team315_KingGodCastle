#include "Slime04.h"

Slime04::Slime04(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Slime04");
	resStringTypes.insert({ ResStringType::Idle,"slime04_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"slime04_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"slime04_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"slime04_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"slime04_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"slime04_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"slime04_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"slime04_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"slime04_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"slime04_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"slime04_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"slime04_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"slime04_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_punch.wav" });
}

Slime04::~Slime04()
{
}

void Slime04::Init()
{
	Character::Init();
}

//void Slime04::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("slime04_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "slime04_DownIdle" : "slime04_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "slime04_RightIdle" : "slime04_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "slime04_DownMove" : "slime04_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "slime04_RightMove" : "slime04_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "slime04_RightAttack" : "slime04_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "slime04_DownAttack" : "slime04_UpAttack");
//		}
//		break;
//	}
//}

void Slime04::Update(float dt)
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

void Slime04::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime04::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Slime04::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Slime04::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime04::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Slime04::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "slime04_DownMove" : "slime04_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "slime04_RightMove" : "slime04_LeftMove");
//	}
//}
//
//void Slime04::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
