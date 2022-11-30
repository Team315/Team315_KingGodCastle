#include "Goblin00.h"

Goblin00::Goblin00(int starNumber)
	: Character(starNumber)
{
	SetType("Monster");
	SetName("Goblin00");
}

Goblin00::~Goblin00()
{
}

void Goblin00::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("goblin00_UpSkill"));

	{
		AnimationEvent ev;
		ev.clipId = "goblin00_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Goblin00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Goblin00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Goblin00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Goblin00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Goblin00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	GameObj::Init();
}

void Goblin00::Update(float dt)
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
	case AnimStates::Skill:
		UpdateSkill(dt);
		break;
	}
	animator.Update(dt);

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Goblin00::Draw(RenderWindow& window)
{
	GameObj::Draw(window);
}

void Goblin00::SetPos(const Vector2f& pos)
{
	GameObj::SetPos(pos);
}

void Goblin00::SetState(AnimStates newState)
{
	GameObj::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("goblin00_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightIdle" : "goblin00_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownIdle" : "goblin00_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "goblin00_DownMove" : "goblin00_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "goblin00_RightMove" : "goblin00_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightAttack" : "goblin00_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownAttack" : "goblin00_UpAttack");
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightSkill" : "goblin00_LeftSkill");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownSkill" : "goblin00_UpSkill");
		}
		break;
	}
}

void Goblin00::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Goblin00::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Goblin00::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin00::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Goblin00::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "goblin00_DownMove" : "goblin00_UpMove");
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "goblin00_RightMove" : "goblin00_LeftMove");
	}
}

void Goblin00::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Goblin00::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}