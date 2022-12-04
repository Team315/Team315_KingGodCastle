#include "Slime05.h"

Slime05::Slime05(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Slime05");
}

Slime05::~Slime05()
{
}

void Slime05::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime05_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "slime05_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Slime05::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime05_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Slime05::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime05_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Slime05::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime05_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Slime05::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Slime05::SetState(AnimStates newState)
{
	Character::SetState(newState);
	
	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("slime05_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "slime05_DownIdle" : "slime05_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "slime05_RightIdle" : "slime05_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "slime05_DownMove" : "slime05_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "slime05_RightMove" : "slime05_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "slime05_RightAttack" : "slime05_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "slime05_DownAttack" : "slime05_UpAttack");
		}
		break;
	}
}

void Slime05::Update(float dt)
{
	Character::Update(dt);

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
	}
	animator.Update(dt);

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
	direction = { 0.f, 0.f };
}

void Slime05::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime05::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Slime05::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Slime05::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Slime05::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Slime05::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "slime05_DownMove" : "slime05_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "slime05_RightMove" : "slime05_LeftMove");
	}
}

void Slime05::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}