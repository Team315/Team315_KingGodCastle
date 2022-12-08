#include "Thief04.h"

Thief04::Thief04(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Thief04");
	resStringTypes.insert({ ResStringType::Idle,"thief04_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"thief04_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"thief04_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"thief04_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"thief04_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"thief04_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"thief04_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"thief04_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"thief04_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"thief04_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"thief04_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"thief04_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"thief04_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_punch.wav" });
}

Thief04::~Thief04()
{
}

void Thief04::Init()
{
	Character::Init();
}

//void Thief04::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("thief04_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "thief04_DownIdle" : "thief04_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "thief04_RightIdle" : "thief04_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "thief04_DownMove" : "thief04_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "thief04_RightMove" : "thief04_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "thief04_RightAttack" : "thief04_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_punch.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "thief04_DownAttack" : "thief04_UpAttack");
//		}
//		break;
//	}
//}

void Thief04::Update(float dt)
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

void Thief04::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief04::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Thief04::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Thief04::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief04::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Thief04::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "thief04_DownMove" : "thief04_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "thief04_RightMove" : "thief04_LeftMove");
//	}
//}
//
//void Thief04::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}