#include "Thief00.h"

Thief00::Thief00(int starNumber)
	: Character(starNumber)
{
	SetType("Player");
	SetName("Thief00");
	maxHp = 250;
	hp = maxHp;
	Ad = 15;
	Ap = 25;
	cout << "Thief00" << " " << hp << " " << Ad << " " << Ap << endl;
}

Thief00::~Thief00()
{
}

void Thief00::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpSkill"));

	{
		AnimationEvent ev;
		ev.clipId = "thief00_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Thief00::Update(float dt)
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

void Thief00::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief00::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Thief00::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("thief00_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief00_RightIdle" : "thief00_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief00_DownIdle" : "thief00_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "thief00_DownMove" : "thief00_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "thief00_RightMove" : "thief00_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief00_RightAttack" : "thief00_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief00_DownAttack" : "thief00_UpAttack");
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief00_RightSkill" : "thief00_LeftSkill");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief00_DownSkill" : "thief00_UpSkill");
		}
		break;
	}
}

void Thief00::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Thief00::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Thief00::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief00::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief00::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "thief00_RightMove" : "thief00_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "thief00_DownMove" : "thief00_UpMove");
	}
}

void Thief00::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Thief00::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}