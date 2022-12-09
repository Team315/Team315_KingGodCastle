#include "Thief01.h"

Thief01::Thief01(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier)
{
	SetType("Monster");
	SetName("Thief01");
	resStringTypes.insert({ ResStringType::Idle,"thief01_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"thief01_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"thief01_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"thief01_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"thief01_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"thief01_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"thief01_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"thief01_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"thief01_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"thief01_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"thief01_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"thief01_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"thief01_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_sword.wav" });
}

Thief01::~Thief01()
{
}

void Thief01::Init()
{
	Character::Init();
}

//void Thief01::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("thief01_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "thief01_DownIdle" : "thief01_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "thief01_RightIdle" : "thief01_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "thief01_DownMove" : "thief01_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "thief01_RightMove" : "thief01_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_sword.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "thief01_RightAttack" : "thief01_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_sword.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "thief01_DownAttack" : "thief01_UpAttack");
//		}
//		break;
//	}
//}

void Thief01::Update(float dt)
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

void Thief01::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief01::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Thief01::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Thief01::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief01::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief01::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "thief01_DownMove" : "thief01_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "thief01_RightMove" : "thief01_LeftMove");
//	}
//}
//
//void Thief01::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}