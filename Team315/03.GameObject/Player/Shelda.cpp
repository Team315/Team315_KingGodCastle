#include "Shelda.h"
#include "Skill/SheldaSkill.h"

Shelda::Shelda(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier)
{
	SetType("Player");
	SetName("Shelda");
	resStringTypes.insert({ ResStringType::Idle,"Shelda_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"Shelda_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"Shelda_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"Shelda_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"Shelda_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"Shelda_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"Shelda_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"Shelda_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"Shelda_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"Shelda_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"Shelda_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"Shelda_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"Shelda_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"Shelda_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"Shelda_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"Shelda_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"Shelda_UpSkill" });

	resStringTypes.insert({ ResStringType::DownAttackEffect,"Sword_DownAttack_Effect" });
	resStringTypes.insert({ ResStringType::LeftAttackEffect,"Sword_LeftAttack_Effect" });
	resStringTypes.insert({ ResStringType::RightAttackEffect,"Sword_RightAttack_Effect" });
	resStringTypes.insert({ ResStringType::UpAttackEffect,"Sword_UpAttack_Effect" });

	resStringTypes.insert({ ResStringType::DownSkillEffect,"Shelda_Skill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEffect,"Shelda_Skill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEffect,"Shelda_Skill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEffect,"Shelda_Skill_Effect" });

	attackPos.insert({ Dir::Right, { 10.f, 5.f } });
	attackPos.insert({ Dir::Left, { -10.f, 5.f} });
	attackPos.insert({ Dir::Down, {-11.f,12.f} });
	attackPos.insert({ Dir::Up, { -10.f,0.f} });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/Shelda_atk.wav" });
}

Shelda::~Shelda()
{
}

void Shelda::Init()
{
	Character::Init();
	skill = new SheldaSkill(star->GetStarNumber());

	// shelda skill init
	//{
	//	AnimationEvent ev;
	//	ev.clipId = "Shelda_HUSkill_Effect";
	//	ev.frame = 5;
	//	ev.onEvent = bind(&Shelda::OnCompleteSkill, this);
	//	skill->GetAnimator()->AddEvent(ev);
	//}
	//skill->GetAnimator()->AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_HUSkill_Effect"));
}

void Shelda::Update(float dt)
{
	Character::Update(dt);

	//if (InputMgr::GetKeyDown(Keyboard::Z))
	//{
	//	SetState(AnimStates::Skill);
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
	////skill->Update(dt);
	//
	//if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	//{
	//	lastDirection = direction;
	//}
}

void Shelda::Draw(RenderWindow& window)
{
	Character::Draw(window);
	//skill->Draw(window);
}

void Shelda::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Shelda::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Shelda::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Shelda::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (move)
//		return;
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "Shelda_RightMove" : "Shelda_LeftMove");
//		move = true;
//	}
//	else if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "Shelda_DownMove" : "Shelda_UpMove");
//		move = true;
//	}
//}
//
//void Shelda::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void Shelda::UpdateSkill(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
