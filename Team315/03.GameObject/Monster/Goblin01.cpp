#include "Goblin01.h"

Goblin01::Goblin01(int starNumber)
	: GameObj(starNumber)
{
	SetType("Monster");
	SetName("Goblin01");
}

Goblin01::~Goblin01()
{
}

void Goblin01::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin01_UpAttack"));

	{
		AnimationEvent ev;
		ev.clipId = "goblin01_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin01_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin01_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin01_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin01::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	GameObj::Init();
}

void Goblin01::SetState(AnimStates newState)
{
	GameObj::SetState(newState);
	
	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("goblin01_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin01_DownIdle" : "goblin01_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin01_RightIdle" : "goblin01_LeftIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "goblin01_DownMove" : "goblin01_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "goblin01_RightMove" : "goblin01_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin01_RightAttack" : "goblin01_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin01_DownAttack" : "goblin01_UpAttack");
		}
		break;
	}
}

void Goblin01::Update(float dt)
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

void Goblin01::Draw(RenderWindow& window)
{
	GameObj::Draw(window);
}

void Goblin01::SetPos(const Vector2f& pos)
{
	GameObj::SetPos(pos);
}

void Goblin01::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Goblin01::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin01::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin01::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "goblin01_DownMove" : "goblin01_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "goblin01_RightMove" : "goblin01_LeftMove");
	}
}

void Goblin01::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}