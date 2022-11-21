#include "Arveron.h"

Arveron::Arveron(int starNumber)
	: Character(starNumber)
{
	SetType("Player");
	SetName("Arveron");
	maxHp = 120;
	hp = maxHp;
	Ad = 10;
	Ap = 40;
	cout << "Arveron" << " " << hp << " " << Ad << " " << Ap << endl;
}

Arveron::~Arveron()
{
}

void Arveron::Init()
{

	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_UpSkill"));

	{
		AnimationEvent ev;
		ev.clipId = "Arveron_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Arveron::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Arveron_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Arveron::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Arveron_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Arveron::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Arveron_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Arveron::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Arveron_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Arveron::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Arveron_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Arveron::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Arveron_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Arveron::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Arveron_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Arveron::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Arveron::Update(float dt)
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

void Arveron::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Arveron::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Arveron::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("Arveron_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Arveron_RightIdle" : "Arveron_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Arveron_DownIdle" : "Arveron_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "Arveron_DownMove" : "Arveron_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "Arveron_RightMove" : "Arveron_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Arveron_RightAttack" : "Arveron_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Arveron_DownAttack" : "Arveron_UpAttack");
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Arveron_RightSkill" : "Arveron_LeftSkill");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Arveron_DownSkill" : "Arveron_UpSkill");
		}
		break;
	}
}

void Arveron::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Arveron::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Arveron::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Arveron::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Arveron::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "Arveron_RightMove" : "Arveron_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "Arveron_DownMove" : "Arveron_UpMove");
	}
}

void Arveron::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Arveron::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}