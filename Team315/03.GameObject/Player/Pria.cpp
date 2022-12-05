#include "Pria.h"
#include "Skill/PriaSkill.h"

Pria::Pria(int skillTier)
	: Character(skillTier)
{
	SetType("Player");
	SetName("Pria");
}

Pria::~Pria()
{
}

void Pria::Init()
{
	animator.SetTarget(&sprite);
	effectAnimator.SetTarget(&effectSprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_UpSkill"));

	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_DownAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_LeftAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_RightAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_UpAttack_Effect"));

	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_Skill_Effect"));

	{
		AnimationEvent ev;
		ev.clipId = "Pria_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_DownAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_LeftAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_RightAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_UpAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_Skill_Effect";
		ev.frame = 2;
		ev.onEvent = bind(&Pria::OnCompleteSkill, this);
		effectAnimator.AddEvent(ev);
	}

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

	SetState(AnimStates::Idle);
	Character::Init();
	skill = new PriaSkill(GetStarNumber());
}

void Pria::Update(float dt)
{
	Character::Update(dt);

	/*if (InputMgr::GetKeyDown(Keyboard::Z))
	{
		SetState(AnimStates::Skill);
	}*/

	switch (currState)
	{
	case AnimStates::Idle:
		UpdateIdle(dt);
		break;
	case AnimStates::MoveToIdle:
		UpdateMoveToIdle(dt);
		break;
	case AnimStates::Move:
		UpdateMove(dt);
		break;
	case AnimStates::Attack:
		UpdateAttack(dt);
		break;
	case AnimStates::Skill:
		UpdateSkill(dt);
		break;
	}
	animator.Update(dt);
	effectAnimator.Update(dt);

	//for (int i = 0; i < 25; ++i)
	//{
	//	skillEffect[i]->Update(dt);
	//}

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Pria::Draw(RenderWindow& window)
{
	if (!isAlive)
		return;

	Character::Draw(window);
	window.draw(effectSprite);

	/*if (!isBattle)
	{
		m_floodFill.Draw(window);
	}

	if (GetState() == AnimStates::Skill)
	{
		window.draw(effectSprite);
		SpriteObj::Draw(window);
	}
	else
	{
		SpriteObj::Draw(window);
		window.draw(effectSprite);
	}
	//for (auto skills : skillSprite)
	//{
	//	window.draw(*skills);
	//}
	hpBar->Draw(window);
	star->Draw(window);

	for (auto& grid : itemGrid)
	{
		if (grid->GetActive())
			grid->Draw(window);
	}*/
}

void Pria::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Pria::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("Pria_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Pria_RightIdle" : "Pria_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Pria_DownIdle" : "Pria_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "Pria_DownMove" : "Pria_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "Pria_RightMove" : "Pria_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			SOUND_MGR->Play("sounds/Pria_atk.wav", 20.f, false);
			animator.Play((lastDirection.x > 0.f) ? "Pria_RightAttack" : "Pria_LeftAttack");
			effectAnimator.Play((lastDirection.x > 0.f) ? "Pria_RightAttack_Effect" : "Pria_LeftAttack_Effect");

			Vector2f vec = m_target->GetPos();
			vec.y += 15.f;
			effectSprite.setPosition(vec);
		}
		if (lastDirection.y)
		{
			SOUND_MGR->Play("sounds/Pria_atk.wav", 20.f, false);
			animator.Play((lastDirection.y > 0.f) ? "Pria_DownAttack" : "Pria_UpAttack");
			effectAnimator.Play((lastDirection.y > 0.f) ? "Pria_DownAttack_Effect" : "Pria_UpAttack_Effect");

			Vector2f vec = m_target->GetPos();
			vec.y += 15.f;
			effectSprite.setPosition(vec);
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Pria_RightSkill" : "Pria_LeftSkill");
			//effectAnimator.Play("Pria_Skill_Effect");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Pria_DownSkill" : "Pria_UpSkill");
			//effectAnimator.Play("Pria_Skill_Effect");
		}
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
		break;
	}
}

void Pria::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Pria::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Pria::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Pria::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Pria::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "Pria_RightMove" : "Pria_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "Pria_DownMove" : "Pria_UpMove");
	}
}

void Pria::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Pria::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}