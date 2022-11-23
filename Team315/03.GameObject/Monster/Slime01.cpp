#include "Slime01.h"

Slime01::Slime01(int starNumber)
	: Character(starNumber)
{
	SetType("Monster");
	SetName("Slime01");
}

Slime01::~Slime01()
{
}

void Slime01::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime01_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "slime01_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Slime01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime01_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Slime01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime01_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Slime01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime01_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Slime01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Slime01::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("slime01_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "slime01_DownIdle" : "slime01_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "slime01_RightIdle" : "slime01_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "slime01_DownMove" : "slime01_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "slime01_RightMove" : "slime01_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "slime01_RightAttack" : "slime01_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "slime01_DownAttack" : "slime01_UpAttack");
		}
		break;
	}
}

void Slime01::Update(float dt)
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

void Slime01::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime01::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Slime01::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Slime01::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Slime01::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Slime01::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "slime01_DownMove" : "slime01_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "slime01_RightMove" : "slime01_LeftMove");
	}
}

void Slime01::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}