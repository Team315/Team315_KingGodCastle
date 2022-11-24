#include "Thief03.h"

Thief03::Thief03(int starNumber)
	: Character(starNumber)
{
	SetType("Monster");
	SetName("Thief03");
}

Thief03::~Thief03()
{
}

void Thief03::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief03_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "thief03_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Thief03::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief03_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Thief03::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief03_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Thief03::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief03_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Thief03::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Thief03::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("thief03_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief03_DownIdle" : "thief03_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief03_RightIdle" : "thief03_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "thief03_DownMove" : "thief03_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "thief03_RightMove" : "thief03_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief03_RightAttack" : "thief03_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief03_DownAttack" : "thief03_UpAttack");
		}
		break;
	}
}

void Thief03::Update(float dt)
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

void Thief03::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief03::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Thief03::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Thief03::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief03::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief03::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "thief03_DownMove" : "thief03_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "thief03_RightMove" : "thief03_LeftMove");
	}
}

void Thief03::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}