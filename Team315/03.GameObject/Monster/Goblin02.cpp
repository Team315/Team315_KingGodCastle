#include "Goblin02.h"

Goblin02::Goblin02(bool mode, bool fixedStar, int skillTier)
	: Character(mode, fixedStar, skillTier)
{
	SetType("Monster");
	SetName("Goblin02");
	resStringTypes.insert({ ResStringType::Idle,"goblin02_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"goblin02_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"goblin02_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"goblin02_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"goblin02_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"goblin02_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"goblin02_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"goblin02_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"goblin02_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"goblin02_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"goblin02_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"goblin02_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"goblin02_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_shoot3.wav" });
}

Goblin02::~Goblin02()
{
}

void Goblin02::Init()
{
	Character::Init();
}

//void Goblin02::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("goblin02_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "goblin02_DownIdle" : "goblin02_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "goblin02_RightIdle" : "goblin02_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "goblin02_DownMove" : "goblin02_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "goblin02_RightMove" : "goblin02_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_shoot3.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "goblin02_RightAttack" : "goblin02_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_shoot3.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "goblin02_DownAttack" : "goblin02_UpAttack");
//		}
//		break;
//	}
//}

void Goblin02::Update(float dt)
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

void Goblin02::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin02::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Goblin02::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Goblin02::OnCompleteSkill()
//{
//}
//
//void Goblin02::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin02::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin02::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "goblin02_DownMove" : "goblin02_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "goblin02_RightMove" : "goblin02_LeftMove");
//	}
//}
//
//void Goblin02::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}