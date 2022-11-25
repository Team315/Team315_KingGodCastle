#include "Daniel.h"

Daniel::Daniel(int starNumber)
	: Character(starNumber)
{
	SetType("Player");
	SetName("Daniel");
}

Daniel::~Daniel()
{
}

void Daniel::Init()
{

	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_UpSkill"));

	{
		AnimationEvent ev;
		ev.clipId = "Daniel_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Daniel_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Daniel::Update(float dt)
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

void Daniel::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Daniel::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Daniel::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("Daniel_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightIdle" : "Daniel_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownIdle" : "Daniel_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "Daniel_DownMove" : "Daniel_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "Daniel_RightMove" : "Daniel_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightAttack" : "Daniel_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownAttack" : "Daniel_UpAttack");
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Daniel_RightSkill" : "Daniel_LeftSkill");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Daniel_DownSkill" : "Daniel_UpSkill");
		}
		break;
	}
}

void Daniel::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Daniel::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Daniel::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Daniel::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Daniel::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "Daniel_RightMove" : "Daniel_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "Daniel_DownMove" : "Daniel_UpMove");
	}
}

void Daniel::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Daniel::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}
