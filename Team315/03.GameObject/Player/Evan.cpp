#include "Evan.h"
#include "Skill/EvanSkill.h"

Evan::Evan(int skillTier)
	: Character(skillTier), skillSpeed(1500.f)
{
	SetType("Player");
	SetName("Evan");
	resStringTypes.insert({ ResStringType::Idle,"Evan_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"Evan_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"Evan_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"Evan_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"Evan_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"Evan_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"Evan_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"Evan_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"Evan_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"Evan_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"Evan_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"Evan_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"Evan_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"Evan_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"Evan_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"Evan_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"Evan_UpSkill" });

	resStringTypes.insert({ ResStringType::DownAttackEffect,"Sword_DownAttack_Effect" });
	resStringTypes.insert({ ResStringType::LeftAttackEffect,"Sword_LeftAttack_Effect" });
	resStringTypes.insert({ ResStringType::RightAttackEffect,"Sword_RightAttack_Effect" });
	resStringTypes.insert({ ResStringType::UpAttackEffect,"Sword_UpAttack_Effect" });

	resStringTypes.insert({ ResStringType::DownSkillEfect,"Evan_DownSkill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEfect,"Evan_LeftSkill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEfect,"Evan_RightSkill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEfect,"Evan_UpSkill_Effect" });

	attackPos.insert({ Dir::Right, { 21.f, 15.f } });
	attackPos.insert({ Dir::Left, {-21.f, 15.f} });
	attackPos.insert({ Dir::Down, {-11.f,12.f} });
	attackPos.insert({ Dir::Up, {5.f,0.f} });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/Evan_atk.wav" });
}

Evan::~Evan()
{
}

void Evan::Init()
{
	Character::Init();
	//skill = new EvanSkill(GetStarNumber());
}

void Evan::Update(float dt)
{
	Character::Update(dt);
	//skill->Translate(lastDirection * skillSpeed * dt);
	//
	//if (InputMgr::GetKeyDown(Keyboard::Z))
	//{
	//	SetState(AnimStates::Attack);
	//}
	//
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
	//case AnimStates::Skill:
	//	UpdateSkill(dt);
	//	break;
	//}
	//animator.Update(dt);
	//effectAnimator.Update(dt);
	//
	//if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	//{
	//	lastDirection = direction;
	//}
}

void Evan::Draw(RenderWindow& window)
{
	Character::Draw(window);
	//skill->Draw(window);
}

void Evan::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Evan::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Evan::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Evan::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Idle);
//		return;
//	}
//	if (move)
//		return;
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "Evan_RightMove" : "Evan_LeftMove");
//		move = true;
//	}
//	else if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "Evan_DownMove" : "Evan_UpMove");
//		move = true;
//	}
//}
//
//void Evan::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void Evan::UpdateSkill(float dt)
//{
//	//skill->SetRotation(lastDirection);
//	//Vector2f vec = position;
//	//if(lastDirection.y < 0.f)
//	//{
//	//	vec.x += 90.f;
//	//	vec.y -= 100.f;
//	//}
//	//else if (lastDirection.y > 0.f)
//	//{
//	//	vec.x -= 90.f;
//	//	vec.y += 30.f;
//	//}
//	//else if (lastDirection.x < 0.f)
//	//{
//	//	vec.x -= 80.f;
//	//	vec.y -= 120.f;
//	//}
//	//else if (lastDirection.x > 0.f)
//	//{
//	//	vec.x += 80.f;
//	//	vec.y += 65.f;
//	//}
//	//skill->SetPos(vec);
//	
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
