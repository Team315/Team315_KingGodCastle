#include "Thief03.h"

Thief03::Thief03(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Thief03");
	resStringTypes.insert({ ResStringType::Idle,"thief03_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"thief03_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"thief03_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"thief03_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"thief03_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"thief03_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"thief03_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"thief03_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"thief03_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"thief03_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"thief03_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"thief03_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"thief03_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_shoot3.wav" });
}

Thief03::~Thief03()
{
}

void Thief03::Init()
{
	Character::Init();
	Character::AnimationInit();
}

//void Thief03::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("thief03_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "thief03_DownIdle" : "thief03_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "thief03_RightIdle" : "thief03_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "thief03_DownMove" : "thief03_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "thief03_RightMove" : "thief03_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_shoot3.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "thief03_RightAttack" : "thief03_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_shoot3.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "thief03_DownAttack" : "thief03_UpAttack");
//		}
//		break;
//	}
//}

void Thief03::Update(float dt)
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

void Thief03::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief03::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Thief03::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Thief03::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief03::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief03::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "thief03_DownMove" : "thief03_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "thief03_RightMove" : "thief03_LeftMove");
//	}
//}
//
//void Thief03::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}