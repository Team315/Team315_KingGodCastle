#include "Goblin01.h"

Goblin01::Goblin01(bool mode, bool fixedStar, int skillTier)
	: Character(mode, fixedStar, skillTier)
{
	SetType("Monster");
	SetName("Goblin01");
	resStringTypes.insert({ ResStringType::Idle,"goblin01_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"goblin01_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"goblin01_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"goblin01_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"goblin01_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"goblin01_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"goblin01_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"goblin01_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"goblin01_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"goblin01_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"goblin01_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"goblin01_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"goblin01_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_sword.wav" });
}

Goblin01::~Goblin01()
{
}

void Goblin01::Init()
{
	Character::Init();
}

//void Goblin01::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//	
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("goblin01_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "goblin01_DownIdle" : "goblin01_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "goblin01_RightIdle" : "goblin01_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "goblin01_DownMove" : "goblin01_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "goblin01_RightMove" : "goblin01_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_sword.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "goblin01_RightAttack" : "goblin01_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_sword.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "goblin01_DownAttack" : "goblin01_UpAttack");
//		}
//		break;
//	}
//}

void Goblin01::Update(float dt)
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

void Goblin01::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin01::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Goblin01::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Goblin01::OnCompleteSkill()
//{
//}
//
//void Goblin01::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin01::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin01::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "goblin01_DownMove" : "goblin01_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "goblin01_RightMove" : "goblin01_LeftMove");
//	}
//}
//
//void Goblin01::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}