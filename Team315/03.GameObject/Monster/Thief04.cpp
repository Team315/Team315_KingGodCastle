#include "Thief04.h"

Thief04::Thief04(int starNumber)
	: Character(starNumber)
{
	SetType("Monster");
	SetName("Thief04");
}

Thief04::~Thief04()
{
}

void Thief04::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief04_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "thief04_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief04_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief04_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief04_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief04::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	GameObj::Init();
}

void Thief04::SetState(AnimStates newState)
{
	GameObj::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("thief04_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief04_DownIdle" : "thief04_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief04_RightIdle" : "thief04_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "thief04_DownMove" : "thief04_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "thief04_RightMove" : "thief04_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief04_RightAttack" : "thief04_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief04_DownAttack" : "thief04_UpAttack");
		}
		break;
	}
}

void Thief04::Update(float dt)
{
	GameObj::Update(dt);

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

void Thief04::Draw(RenderWindow& window)
{
	GameObj::Draw(window);
}

void Thief04::SetPos(const Vector2f& pos)
{
	GameObj::SetPos(pos);
}

void Thief04::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Thief04::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief04::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief04::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "thief04_DownMove" : "thief04_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "thief04_RightMove" : "thief04_LeftMove");
	}
}

void Thief04::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}