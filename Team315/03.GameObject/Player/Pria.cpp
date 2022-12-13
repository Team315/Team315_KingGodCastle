#include "Pria.h"
#include "Skill/PriaSkill.h"

Pria::Pria(bool mode, bool useExtraUpgrade, int skillTier)
	: Character(mode, useExtraUpgrade, skillTier)
{
	SetType("Player");
	SetName("Pria");
	resStringTypes.insert({ ResStringType::Idle,"Pria_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"Pria_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"Pria_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"Pria_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"Pria_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"Pria_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"Pria_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"Pria_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"Pria_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"Pria_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"Pria_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"Pria_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"Pria_UpAttack" });

	resStringTypes.insert({ ResStringType::DownSkill,"Pria_DownSkill" });
	resStringTypes.insert({ ResStringType::LeftSkill,"Pria_LeftSkill" });
	resStringTypes.insert({ ResStringType::RightSkill,"Pria_RightSkill" });
	resStringTypes.insert({ ResStringType::UpSkill,"Pria_UpSkill" });

	resStringTypes.insert({ ResStringType::DownAttackEffect,"Pria_DownAttack_Effect" });
	resStringTypes.insert({ ResStringType::LeftAttackEffect,"Pria_LeftAttack_Effect" });
	resStringTypes.insert({ ResStringType::RightAttackEffect,"Pria_RightAttack_Effect" });
	resStringTypes.insert({ ResStringType::UpAttackEffect,"Pria_UpAttack_Effect" });

	resStringTypes.insert({ ResStringType::DownSkillEffect,"Pria_Skill_Effect" });
	resStringTypes.insert({ ResStringType::LeftSkillEffect,"Pria_Skill_Effect" });
	resStringTypes.insert({ ResStringType::RightSkillEffect,"Pria_Skill_Effect" });
	resStringTypes.insert({ ResStringType::UpSkillEffect,"Pria_Skill_Effect" });

	attackPos.insert({ Dir::Right, { 0.f, 0.f } });
	attackPos.insert({ Dir::Left, { 0.f, 0.f } });
	attackPos.insert({ Dir::Down, { 0.f, 0.f } });
	attackPos.insert({ Dir::Up, { 0.f, 0.f } });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/Pria_atk.wav" });
}

Pria::~Pria()
{
}

void Pria::Init()
{
	//for (int i = 0; i < 25; ++i)
	//{
	//	Sprite* skillSpriteArr = new Sprite();
	//	Animator* skillEffectArr = new Animator();
	//	skillEffectArr->SetTarget(skillSpriteArr);
	//	skillEffectArr->AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_SkillHit_Effect"));
	//	{
	//		AnimationEvent ev;
	//		ev.clipId = "Pria_SkillHit_Effect";
	//		ev.frame = 8;
	//		ev.onEvent = bind(&Pria::OnCompleteSkill, this);
	//		skillEffectArr->AddEvent(ev);
	//	}
	//	skillEffect.push_back(skillEffectArr);
	//	skillSprite.push_back(skillSpriteArr);
	//}
	Character::Init();
	skill = new PriaSkill(GetStarNumber());
}

void Pria::Update(float dt)
{
	Character::Update(dt);

	skill->GetAnimator()->Update(dt);
}

void Pria::Draw(RenderWindow& window)
{
	if (!isAlive)
		return;

	Character::Draw(window);
	//window.draw(effectSprite);
	if (isBattle)
		skill->Draw(window);

	//if (!isBattle)
	//{
	//	m_floodFill.Draw(window);
	//}

	//if (GetState() == AnimStates::Skill)
	//{
	//	window.draw(effectSprite);
	//	SpriteObj::Draw(window);
	//}
	//else
	//{
	//	SpriteObj::Draw(window);
	//	window.draw(effectSprite);
	//}
	//for (auto skills : skillSprite)
	//{
	//	window.draw(*skills);
	//}
	//hpBar->Draw(window);
	//star->Draw(window);

	//for (auto& grid : itemGrid)
	//{
	//	if (grid->GetActive())
	//		grid->Draw(window);
	//}
}

void Pria::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Pria::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("Pria_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "Pria_RightIdle" : "Pria_LeftIdle");
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "Pria_DownIdle" : "Pria_UpIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "Pria_DownMove" : "Pria_UpMove");
//		}
//		else if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "Pria_RightMove" : "Pria_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/Pria_atk.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "Pria_RightAttack" : "Pria_LeftAttack");
//			effectAnimator.Play((lastDirection.x > 0.f) ? "Pria_RightAttack_Effect" : "Pria_LeftAttack_Effect");
//
//			Vector2f vec = m_target->GetPos();
//			vec.y += 15.f;
//			effectSprite.setPosition(vec);
//		}
//		else if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/Pria_atk.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "Pria_DownAttack" : "Pria_UpAttack");
//			effectAnimator.Play((lastDirection.y > 0.f) ? "Pria_DownAttack_Effect" : "Pria_UpAttack_Effect");
//
//			Vector2f vec = m_target->GetPos();
//			vec.y += 15.f;
//			effectSprite.setPosition(vec);
//		}
//		break;
//	case AnimStates::Skill:
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "Pria_RightSkill" : "Pria_LeftSkill");
//			//effectAnimator.Play("Pria_Skill_Effect");
//		}
//		else if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "Pria_DownSkill" : "Pria_UpSkill");
//			//effectAnimator.Play("Pria_Skill_Effect");
//		}
		//Vector2f vec = GetTarget()->GetPos();
		//vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
		//Vector2i targetPos = GAME_MGR->PosToIdx(vec);
		//if (mainGrid[targetPos.y * 7 + targetPos.x + 0] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 0]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 0])->TakeDamage(this);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 0])->GetPos();
		//	skillSprite[4]->setPosition(pos);
		//	skillEffect[4]->Play("Pria_SkillHit_Effect");
		//}
		//if (mainGrid[targetPos.y * 7 + targetPos.x + 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 1]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->TakeDamage(this);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->GetPos();
		//	skillSprite[0]->setPosition(pos);
		//	skillEffect[0]->Play("Pria_SkillHit_Effect");
		//}
		//if (mainGrid[targetPos.y * 7 + targetPos.x - 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 1]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->TakeDamage(this);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->GetPos();
		//	skillSprite[1]->setPosition(pos);
		//	skillEffect[1]->Play("Pria_SkillHit_Effect");
		//}
		//if (mainGrid[targetPos.y * 7 + targetPos.x + 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 7]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->TakeDamage(this);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->GetPos();
		//	skillSprite[2]->setPosition(pos);
		//	skillEffect[2]->Play("Pria_SkillHit_Effect");
		//}
		//if (mainGrid[targetPos.y * 7 + targetPos.x - 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 7]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->TakeDamage(this);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->GetPos();
		//	skillSprite[3]->setPosition(pos);
		//	skillEffect[3]->Play("Pria_SkillHit_Effect");
		//}
//		break;
//	}
//}
//
//void Pria::AnimationInit()
//{
//}
//
//void Pria::Idle()
//{
//}
//
//void Pria::MoveToIdle()
//{
//}
//
//void Pria::Move()
//{
//}
//
//void Pria::Attack(Vector2f delta)
//{
//}
//
//void Pria::Skill(Vector2f delta)
//{
//}
//
//void Pria::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Pria::OnCompleteSkill()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Pria::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Pria::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Pria::UpdateMove(float dt)
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
//		animator.Play((direction.x > 0.f) ? "Pria_RightMove" : "Pria_LeftMove");
//		move = true;
//	}
//	else if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "Pria_DownMove" : "Pria_UpMove");
//		move = true;
//	}
//}
//
//void Pria::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}
//
//void Pria::UpdateSkill(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}