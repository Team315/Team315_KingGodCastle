#include "Goblin03.h"

Goblin03::Goblin03(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Goblin03");
}

Goblin03::~Goblin03()
{
}

void Goblin03::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin03_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "goblin03_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin03::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin03_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin03::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin03_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin03::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin03_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin03::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Goblin03::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("goblin03_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin03_DownIdle" : "goblin03_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin03_RightIdle" : "goblin03_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "goblin03_DownMove" : "goblin03_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "goblin03_RightMove" : "goblin03_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin03_RightAttack" : "goblin03_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin03_DownAttack" : "goblin03_UpAttack");
		}
		break;
	}
}

void Goblin03::Update(float dt)
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

void Goblin03::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin03::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Goblin03::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Goblin03::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin03::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin03::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "goblin03_DownMove" : "goblin03_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "goblin03_RightMove" : "goblin03_LeftMove");
	}
}

void Goblin03::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}