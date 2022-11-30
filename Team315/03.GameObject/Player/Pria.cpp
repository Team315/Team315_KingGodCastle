#include "Pria.h"

Pria::Pria(int starNumber)
	: Character(starNumber)
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
	attackEffect.SetTarget(&attackSprite);

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

	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_DownAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_LeftAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_RightAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_UpAttack_Effect"));

	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Pria_Skill_Effect"));

	{
		AnimationEvent ev;
		ev.clipId = "Pria_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_DownAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_LeftAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_RightAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Pria_UpAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Pria::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
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
		animator.AddEvent(ev);
	}


	SetState(AnimStates::Idle);
	Character::Init();
}

void Pria::Update(float dt)
{
	Character::Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::Z))
	{
		SetState(AnimStates::Skill);
	}

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
	attackEffect.Update(dt);

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Pria::Draw(RenderWindow& window)
{
	if (!isAlive)
		return;

	if(GetState() == AnimStates::Skill)
	{
		window.draw(attackSprite);
		SpriteObj::Draw(window);
	}
	else
	{
		SpriteObj::Draw(window);
		window.draw(attackSprite);
	}	
	hpBar->Draw(window);
	star->Draw(window);
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
			animator.Play((lastDirection.x > 0.f) ? "Pria_RightAttack" : "Pria_LeftAttack");
		}
		if (lastDirection.x)
		{
			attackEffect.Play((lastDirection.x > 0.f) ? "Pria_RightAttack_Effect" : "Pria_LeftAttack_Effect");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Pria_DownAttack" : "Pria_UpAttack");
		}
		if (lastDirection.y)
		{
			attackEffect.Play((lastDirection.y > 0.f) ? "Pria_DownAttack_Effect" : "Pria_UpAttack_Effect");
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Pria_RightSkill" : "Pria_LeftSkill");
			attackEffect.Play("Pria_Skill_Effect");
			Vector2f vec = GetPos();
			vec.y += 15.f;
			attackSprite.setPosition(vec);
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Pria_DownSkill" : "Pria_UpSkill");
			attackEffect.Play("Pria_Skill_Effect");
			Vector2f vec = GetPos();
			vec.y += 15.f;
			attackSprite.setPosition(vec);
		}
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
