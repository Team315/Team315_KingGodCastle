#include "Thief01.h"

Thief01::Thief01(int starNumber)
	: Character(starNumber)
{
	SetType("Monster");
	SetName("Thief01");
}

Thief01::~Thief01()
{
}

void Thief01::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief01_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "thief01_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief01_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief01_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief01_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Thief01::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("thief01_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief01_DownIdle" : "thief01_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief01_RightIdle" : "thief01_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "thief01_DownMove" : "thief01_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "thief01_RightMove" : "thief01_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief01_RightAttack" : "thief01_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief01_DownAttack" : "thief01_UpAttack");
		}
		break;
	}
}

void Thief01::Update(float dt)
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

void Thief01::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief01::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Thief01::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Thief01::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief01::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief01::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "thief01_DownMove" : "thief01_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "thief01_RightMove" : "thief01_LeftMove");
	}
}

void Thief01::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}