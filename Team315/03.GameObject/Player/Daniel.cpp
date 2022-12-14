#include "Daniel.h"
#include "Skill/DanielSkill.h"

Daniel::Daniel(bool mode, bool useExtraUpgrade, int starGrade)
	: Character(mode, useExtraUpgrade, starGrade)
{
	SetType("Player");
	SetName("Daniel");
	resStringTypes.insert({ ResStringType::Idle,"Daniel_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"Daniel_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"Daniel_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"Daniel_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"Daniel_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"Daniel_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"Daniel_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"Daniel_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"Daniel_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"Daniel_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"Daniel_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"Daniel_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"Daniel_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"Daniel_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"Daniel_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"Daniel_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"Daniel_UpSkill" });

	resStringTypes.insert({ ResStringType::DownAttackEffect,"Daniel_DownAttack_Effect" });
	resStringTypes.insert({ ResStringType::LeftAttackEffect,"Daniel_LeftAttack_Effect" });
	resStringTypes.insert({ ResStringType::RightAttackEffect,"Daniel_RightAttack_Effect" });
	resStringTypes.insert({ ResStringType::UpAttackEffect,"Daniel_UpAttack_Effect" });

	resStringTypes.insert({ ResStringType::DownSkillEffect,"Daniel_Skill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEffect,"Daniel_Skill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEffect,"Daniel_Skill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEffect,"Daniel_Skill_Effect" });

	attackPos.insert({ Dir::Right, { 40.f, 0.f } });
	attackPos.insert({ Dir::Left, { -40.f, 0.f} });
	attackPos.insert({ Dir::Down, { 0.f, 51.f} });
	attackPos.insert({ Dir::Up, { 3.f, -51.f} });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/Daniel_atk.wav" });
}

Daniel::~Daniel()
{
}

void Daniel::Init()
{
	//for (int i = 0; i < 25; ++i)
	//{
	//	Sprite* skillSpriteArr = new Sprite();
	//	Animator* skillEffectArr = new Animator();
	//	skillEffectArr->SetTarget(skillSpriteArr);
	//	skillEffectArr->AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_Skill_Effect"));
	//	{
	//		AnimationEvent ev;
	//		ev.clipId = "Daniel_Skill_Effect";
	//		ev.frame = 8;
	//		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
	//		skillEffectArr->AddEvent(ev);
	//	}
	//	skillEffect.push_back(skillEffectArr);
	//	skillSprite.push_back(skillSpriteArr);
	//}
	Character::Init();
	skill = new DanielSkill(GetStarNumber());
}

void Daniel::Update(float dt)
{
	Character::Update(dt);
	skill->GetAnimator()->Update(dt);
}

void Daniel::Draw(RenderWindow& window)
{
	Character::Draw(window);
	if (isBattle)
		skill->Draw(window);
}

void Daniel::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
	//skill->SetPos(pos);
}

//void Daniel::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("Daniel_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightIdle" : "Daniel_LeftIdle");
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownIdle" : "Daniel_UpIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "Daniel_DownMove" : "Daniel_UpMove");
//		}
//		else if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "Daniel_RightMove" : "Daniel_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/Daniel_atk.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightAttack" : "Daniel_LeftAttack");
//			if (lastDirection.x > 0.f)
//			{
//				effectAnimator.Play("Daniel_RightAttack_Effect");
//				Vector2f vec = GetPos();
//				vec.x += 40.f;
//				effectSprite.setPosition(vec);
//			}
//			else if (lastDirection.x < 0.f)
//			{
//				effectAnimator.Play("Daniel_LeftAttack_Effect");
//				Vector2f vec = GetPos();
//				vec.x -= 40.f;
//				effectSprite.setPosition(vec);
//			}
//		}
//		else if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/Daniel_atk.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownAttack" : "Daniel_UpAttack");
//			if (lastDirection.y > 0.f)
//			{
//				effectAnimator.Play("Daniel_DownAttack_Effect");
//				Vector2f vec = GetPos();
//				effectSprite.setPosition(vec);
//			}
//			else if (lastDirection.y < 0.f)
//			{
//				effectAnimator.Play("Daniel_UpAttack_Effect");
//				Vector2f vec = GetPos();
//				vec.x += 3.f;
//				vec.y -= 51.f;
//				effectSprite.setPosition(vec);
//			}
//		}
//		break;
//	case AnimStates::Skill:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightSkill" : "Daniel_LeftSkill");
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownSkill" : "Daniel_UpSkill");
//		}
//		//dynamic_cast<DanielSkill*>(skill)->SetState(AnimStates::Skill, GetTarget(), targetType);
//		//Vector2f vec = GetTarget()->GetPos();
//		//vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
//		//Vector2i targetPos = GAME_MGR->PosToIdx(GetPos());
//		//if (mainGrid[targetPos.y * 7 + targetPos.x + 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 1]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->GetPos();
//		//	skillSprite[0]->setPosition(pos);
//		//	skillEffect[0]->Play("Daniel_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x - 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 1]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->GetPos();
//		//	skillSprite[1]->setPosition(pos);
//		//	skillEffect[1]->Play("Daniel_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x + 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 7]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->GetPos();
//		//	skillSprite[2]->setPosition(pos);
//		//	skillEffect[2]->Play("Daniel_Skill_Effect");
//		//}
//		//if (mainGrid[targetPos.y * 7 + targetPos.x - 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 7]->GetType().compare(targetType))
//		//{
//		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->TakeDamage(this, false);
//		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->GetPos();
//		//	skillSprite[3]->setPosition(pos);
//		//	skillEffect[3]->Play("Daniel_Skill_Effect");
//		//}
//		break;
//	}
//}
//
//void Daniel::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Daniel::OnCompleteSkill()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Daniel::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Daniel::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Daniel::UpdateMove(float dt)
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
//		animator.Play((direction.x > 0.f) ? "Daniel_RightMove" : "Daniel_LeftMove");
//		move = true;
//	}
//	else if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "Daniel_DownMove" : "Daniel_UpMove");
//		move = true;
//	}
//}
//
//void Daniel::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void Daniel::UpdateSkill(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}