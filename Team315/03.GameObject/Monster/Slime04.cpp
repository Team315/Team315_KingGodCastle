#include "Slime04.h"

Slime04::Slime04(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Slime04");
}

Slime04::~Slime04()
{
}

void Slime04::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime04_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "slime04_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Slime04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime04_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Slime04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime04_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Slime04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "slime04_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Slime04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Slime04::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("slime04_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "slime04_DownIdle" : "slime04_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "slime04_RightIdle" : "slime04_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "slime04_DownMove" : "slime04_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "slime04_RightMove" : "slime04_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "slime04_RightAttack" : "slime04_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "slime04_DownAttack" : "slime04_UpAttack");
		}
		break;
	}
}

void Slime04::Update(float dt)
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

void Slime04::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime04::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Slime04::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Slime04::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Slime04::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Slime04::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "slime04_DownMove" : "slime04_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "slime04_RightMove" : "slime04_LeftMove");
	}
}

void Slime04::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}