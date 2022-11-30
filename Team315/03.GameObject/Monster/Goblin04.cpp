#include "Goblin04.h"

Goblin04::Goblin04(int starNumber)
	: Character(starNumber)
{
	SetType("Monster");
	SetName("Goblin04");
}

Goblin04::~Goblin04()
{
}

void Goblin04::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin04_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "goblin04_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin04_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin04_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin04_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Goblin04::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("goblin04_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin04_DownIdle" : "goblin04_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin04_RightIdle" : "goblin04_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "goblin04_DownMove" : "goblin04_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "goblin04_RightMove" : "goblin04_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin04_RightAttack" : "goblin04_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin04_DownAttack" : "goblin04_UpAttack");
		}
		break;
	}
}

void Goblin04::Update(float dt)
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

void Goblin04::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin04::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Goblin04::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Goblin04::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin04::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin04::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "goblin04_DownMove" : "goblin04_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "goblin04_RightMove" : "goblin04_LeftMove");
	}
}

void Goblin04::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}