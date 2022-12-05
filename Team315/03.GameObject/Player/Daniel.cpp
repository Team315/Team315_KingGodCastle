#include "Daniel.h"
#include "Skill/DanielSkill.h"

Daniel::Daniel(int starNumber)
	: Character(starNumber)
{
	SetType("Player");
	SetName("Daniel");
}

Daniel::~Daniel()
{
}

void Daniel::Init()
{
	animator.SetTarget(&sprite);
	effectAnimator.SetTarget(&effectSprite);
	
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpSkill"));

	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpAttack_Effect"));
	
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_DownAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_LeftAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_RightAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_UpAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	for (int i = 0; i < 25; ++i)
	{
		Sprite* skillSpriteArr = new Sprite();
		Animator* skillEffectArr = new Animator();
		skillEffectArr->SetTarget(skillSpriteArr);
		skillEffectArr->AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_Skill_Effect"));
		{
			AnimationEvent ev;
			ev.clipId = "Daniel_Skill_Effect";
			ev.frame = 8;
			ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
			skillEffectArr->AddEvent(ev);
		}
		skillEffect.push_back(skillEffectArr);
		skillSprite.push_back(skillSpriteArr);
	}

	//skill->Init();
	SetState(AnimStates::Idle);
	Character::Init();
	skill = new DanielSkill(GetStarNumber());
}

void Daniel::Update(float dt)
{
	Character::Update(dt);

	//if (InputMgr::GetKeyDown(Keyboard::Z))
	//{
	//	SetState(AnimStates::Attack);
	//}

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
	//skill->Update(dt);
	for (int i = 0; i < 25; ++i)
	{
		skillEffect[i]->Update(dt);
	}

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Daniel::Draw(RenderWindow& window)
{
	Character::Draw(window);
	//skill->Draw(window);
	for (auto skills : skillSprite)
	{
		window.draw(*skills);
	}
}

void Daniel::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
	//skill->SetPos(pos);
}

void Daniel::SetState(AnimStates newState)
{
	Character::SetState(newState);
	//cout << (int)currState << endl;
	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("Daniel_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightIdle" : "Daniel_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownIdle" : "Daniel_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "Daniel_DownMove" : "Daniel_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "Daniel_RightMove" : "Daniel_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			SOUND_MGR->Play("sounds/Daniel_atk.wav", 20.f, false);
			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightAttack" : "Daniel_LeftAttack");
			if (lastDirection.x > 0.f)
			{
				effectAnimator.Play("Daniel_RightAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 40.f;
				effectSprite.setPosition(vec);
			}
			else if (lastDirection.x < 0.f)
			{
				effectAnimator.Play("Daniel_LeftAttack_Effect");
				Vector2f vec = GetPos();
				vec.x -= 40.f;
				effectSprite.setPosition(vec);
			}
		}
		if (lastDirection.y)
		{
			SOUND_MGR->Play("sounds/Daniel_atk.wav", 20.f, false);
			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownAttack" : "Daniel_UpAttack");
			if (lastDirection.y > 0.f)
			{
				effectAnimator.Play("Daniel_DownAttack_Effect");
				Vector2f vec = GetPos();
				effectSprite.setPosition(vec);
			}
			if (lastDirection.y < 0.f)
			{
				effectAnimator.Play("Daniel_UpAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 3.f;
				vec.y -= 51.f;
				effectSprite.setPosition(vec);
			}
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightSkill" : "Daniel_LeftSkill");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownSkill" : "Daniel_UpSkill");
		}
		//dynamic_cast<DanielSkill*>(skill)->SetState(AnimStates::Skill, GetTarget(), targetType);
		//Vector2f vec = GetTarget()->GetPos();
		//vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
		//Vector2i targetPos = GAME_MGR->PosToIdx(GetPos());
		//if (mainGrid[targetPos.y * 7 + targetPos.x + 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 1]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->TakeDamage(this, false);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->GetPos();
		//	skillSprite[0]->setPosition(pos);
		//	skillEffect[0]->Play("Daniel_Skill_Effect");
		//}
		//if (mainGrid[targetPos.y * 7 + targetPos.x - 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 1]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->TakeDamage(this, false);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->GetPos();
		//	skillSprite[1]->setPosition(pos);
		//	skillEffect[1]->Play("Daniel_Skill_Effect");
		//}
		//if (mainGrid[targetPos.y * 7 + targetPos.x + 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 7]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->TakeDamage(this, false);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->GetPos();
		//	skillSprite[2]->setPosition(pos);
		//	skillEffect[2]->Play("Daniel_Skill_Effect");
		//}
		//if (mainGrid[targetPos.y * 7 + targetPos.x - 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 7]->GetType().compare(targetType))
		//{
		//	dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->TakeDamage(this, false);
		//	Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->GetPos();
		//	skillSprite[3]->setPosition(pos);
		//	skillEffect[3]->Play("Daniel_Skill_Effect");
		//}
		break;
	}
}

void Daniel::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Daniel::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Daniel::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Daniel::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Daniel::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "Daniel_RightMove" : "Daniel_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "Daniel_DownMove" : "Daniel_UpMove");
	}
}

void Daniel::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Daniel::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}