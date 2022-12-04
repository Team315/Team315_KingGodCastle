#include "Thief02.h"

Thief02::Thief02(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Thief02");
}

Thief02::~Thief02()
{
}

void Thief02::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief02_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "thief02_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief02_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief02_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief02_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Thief02::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("thief02_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief02_DownIdle" : "thief02_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief02_RightIdle" : "thief02_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "thief02_DownMove" : "thief02_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "thief02_RightMove" : "thief02_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief02_RightAttack" : "thief02_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief02_DownAttack" : "thief02_UpAttack");
		}
		break;
	}
}

void Thief02::Update(float dt)
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

void Thief02::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief02::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Thief02::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Thief02::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief02::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief02::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "thief02_DownMove" : "thief02_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "thief02_RightMove" : "thief02_LeftMove");
	}
}

void Thief02::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}