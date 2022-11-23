#include "Slime02.h"

Slime02::Slime02(int starNumber)
	: Character(starNumber)
{
	SetType("Monster");
	SetName("Slime02");
}

Slime02::~Slime02()
{
}

void Slime02::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime02_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "slime02_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Slime02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime02_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Slime02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime02_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Slime02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime02_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Slime02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Slime02::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("slime02_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "slime02_DownIdle" : "slime02_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "slime02_RightIdle" : "slime02_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "slime02_DownMove" : "slime02_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "slime02_RightMove" : "slime02_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "slime02_RightAttack" : "slime02_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "slime02_DownAttack" : "slime02_UpAttack");
		}
		break;
	}
}

void Slime02::Update(float dt)
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

void Slime02::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime02::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Slime02::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Slime02::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Slime02::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Slime02::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "slime02_DownMove" : "slime02_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "slime02_RightMove" : "slime02_LeftMove");
	}
}

void Slime02::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}