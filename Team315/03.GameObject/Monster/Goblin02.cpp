#include "Goblin02.h"

Goblin02::Goblin02(int starNumber)
	: Character(starNumber)
{
	SetType("Monster");
	SetName("Goblin02");
}

Goblin02::~Goblin02()
{
}

void Goblin02::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin02_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "goblin02_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin02_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin02_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin02_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin02::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Goblin02::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("goblin02_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin02_DownIdle" : "goblin02_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin02_RightIdle" : "goblin02_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "goblin02_DownMove" : "goblin02_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "goblin02_RightMove" : "goblin02_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin02_RightAttack" : "goblin02_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin02_DownAttack" : "goblin02_UpAttack");
		}
		break;
	}
}

void Goblin02::Update(float dt)
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

void Goblin02::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin02::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Goblin02::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Goblin02::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin02::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin02::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "goblin02_DownMove" : "goblin02_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "goblin02_RightMove" : "goblin02_LeftMove");
	}
}

void Goblin02::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}