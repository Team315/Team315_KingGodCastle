#include "Goblin03.h"

Goblin03::Goblin03(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Goblin03");
	resStringTypes.insert({ ResStringType::Idle,"goblin03_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"goblin03_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"goblin03_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"goblin03_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"goblin03_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"goblin03_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"goblin03_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"goblin03_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"goblin03_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"goblin03_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"goblin03_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"goblin03_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"goblin03_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_greatsword.wav" });
}

Goblin03::~Goblin03()
{
}

void Goblin03::Init()
{
	Character::Init();
}

//void Goblin03::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("goblin03_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "goblin03_DownIdle" : "goblin03_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "goblin03_RightIdle" : "goblin03_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "goblin03_DownMove" : "goblin03_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "goblin03_RightMove" : "goblin03_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_greatsword.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "goblin03_RightAttack" : "goblin03_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_greatsword.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "goblin03_DownAttack" : "goblin03_UpAttack");
//		}
//		break;
//	}
//}

void Goblin03::Update(float dt)
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

void Goblin03::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin03::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Goblin03::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Goblin03::OnCompleteSkill()
//{
//}
//
//void Goblin03::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin03::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin03::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "goblin03_DownMove" : "goblin03_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "goblin03_RightMove" : "goblin03_LeftMove");
//	}
//}
//
//void Goblin03::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}