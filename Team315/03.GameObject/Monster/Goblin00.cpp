#include "Goblin00.h"
#include "Skill/Goblin00Skill.h"

Goblin00::Goblin00(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier)
{
	SetType("Monster");
	SetName("Goblin00");
	resStringTypes.insert({ ResStringType::Idle,"goblin00_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"goblin00_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"goblin00_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"goblin00_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"goblin00_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"goblin00_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"goblin00_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"goblin00_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"goblin00_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"goblin00_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"goblin00_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"goblin00_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"goblin00_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"goblin00_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"goblin00_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"goblin00_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"goblin00_UpSkill" });

	resStringTypes.insert({ ResStringType::DownSkillEffect,"goblin00_Skill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEffect,"goblin00_Skill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEffect,"goblin00_Skill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEffect,"goblin00_Skill_Effect" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_bash.wav" });
}

Goblin00::~Goblin00()
{
}

void Goblin00::Init()
{
	//for (int i = 0; i < 9; ++i)
	//{
	//	Sprite* skillSpriteArr = new Sprite();
	//	Animator* skillEffectArr = new Animator();
	//	skillEffectArr->SetTarget(skillSpriteArr);
	//	skillEffectArr->AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_Skill_Effect"));
	//	{
	//		AnimationEvent ev;
	//		ev.clipId = "goblin00_Skill_Effect";
	//		ev.frame = 9;
	//		ev.onEvent = bind(&Goblin00::OnCompleteSkill, this);
	//		skillEffectArr->AddEvent(ev);
	//	}
	//	skillEffect.push_back(skillEffectArr);
	//	skillSprite.push_back(skillSpriteArr);
	//}

	Character::Init();
	skill = new Goblin00Skill(GetStarNumber());
}

void Goblin00::Update(float dt)
{
	Character::Update(dt);

	skill->GetAnimator()->Update(dt);

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
	////for (int i = 0; i < 9; ++i)
	////{
	////	skillEffect[i]->Update(dt);
	////}
	//
	//if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	//{
	//	lastDirection = direction;
	//}
}

void Goblin00::Draw(RenderWindow& window)
{
	Character::Draw(window);

	//if (isBattle)
	//	skill->Draw(window);
	//for (auto skills : skillSprite)
	//{
	//	window.draw(*skills);
	//}
}

void Goblin00::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Goblin00::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("goblin00_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightIdle" : "goblin00_LeftIdle");
//		}
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownIdle" : "goblin00_UpIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "goblin00_DownMove" : "goblin00_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "goblin00_RightMove" : "goblin00_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_bash.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightAttack" : "goblin00_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_bash.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownAttack" : "goblin00_UpAttack");
//		}
//		break;
//	case AnimStates::Skill:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightSkill" : "goblin00_LeftSkill");
//		}
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownSkill" : "goblin00_UpSkill");
//		}
//		//Vector2f vec = GetTarget()->GetPos();
//		//vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
//		//Vector2i targetPos = GAME_MGR->PosToIdx(GetPos());
//		//if (mainGrid[targetPos.y * 7 + targetPos.x + 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 1]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->GetPos();
//		//	skillSprite[0]->setPosition(pos);
//		//	skillEffect[0]->Play("goblin00_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x - 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 1]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->GetPos();
//		//	skillSprite[1]->setPosition(pos);
//		//	skillEffect[1]->Play("goblin00_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x + 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 7]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->GetPos();
//		//	skillSprite[2]->setPosition(pos);
//		//	skillEffect[2]->Play("goblin00_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x - 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 7]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->GetPos();
//		//	skillSprite[3]->setPosition(pos);
//		//	skillEffect[3]->Play("goblin00_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x - 8] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 8]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 8])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 8])->GetPos();
//		//	skillSprite[4]->setPosition(pos);
//		//	skillEffect[4]->Play("goblin00_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x - 6] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 6]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 6])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 6])->GetPos();
//		//	skillSprite[5]->setPosition(pos);
//		//	skillEffect[5]->Play("goblin00_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x + 6] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 6]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 6])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 6])->GetPos();
//		//	skillSprite[6]->setPosition(pos);
//		//	skillEffect[6]->Play("goblin00_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x + 8] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 8]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 8])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 8])->GetPos();
//		//	skillSprite[7]->setPosition(pos);
//		//	skillEffect[7]->Play("goblin00_Skill_Effect");
//		//}
//		break;
//	}
//}
//
//void Goblin00::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Goblin00::OnCompleteSkill()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Goblin00::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin00::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin00::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "goblin00_DownMove" : "goblin00_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "goblin00_RightMove" : "goblin00_LeftMove");
//	}
//}
//
//void Goblin00::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void Goblin00::UpdateSkill(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}