#include "LeonHeart.h"

LeonHeart::LeonHeart(int starNumber)
	: Character(starNumber)
{
	SetType("Player");
	SetName("LeonHeart");
}

LeonHeart::~LeonHeart()
{
}

void LeonHeart::Init()
{

	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeonHeart_UpSkill"));

	{
		AnimationEvent ev;
		ev.clipId = "LeonHeart_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&LeonHeart::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeonHeart_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&LeonHeart::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeonHeart_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&LeonHeart::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeonHeart_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&LeonHeart::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeonHeart_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&LeonHeart::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeonHeart_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&LeonHeart::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeonHeart_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&LeonHeart::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeonHeart_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&LeonHeart::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void LeonHeart::Update(float dt)
{
	Character::Update(dt);

	direction.x = 0.f;
	direction.y = 0.f;

	Translate(direction * dt * moveSpeed);

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

void LeonHeart::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void LeonHeart::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void LeonHeart::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("LeonHeart_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "LeonHeart_RightIdle" : "LeonHeart_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "LeonHeart_DownIdle" : "LeonHeart_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "LeonHeart_DownMove" : "LeonHeart_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "LeonHeart_RightMove" : "LeonHeart_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "LeonHeart_RightAttack" : "LeonHeart_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "LeonHeart_DownAttack" : "LeonHeart_UpAttack");
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "LeonHeart_RightSkill" : "LeonHeart_LeftSkill");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "LeonHeart_DownSkill" : "LeonHeart_UpSkill");
		}
		break;
	}
}

void LeonHeart::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void LeonHeart::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void LeonHeart::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void LeonHeart::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void LeonHeart::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "LeonHeart_RightMove" : "LeonHeart_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "LeonHeart_DownMove" : "LeonHeart_UpMove");
	}
}

void LeonHeart::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void LeonHeart::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}
