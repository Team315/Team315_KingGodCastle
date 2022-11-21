#include "Shelda.h"

Shelda::Shelda(int starNumber)
	: Character(starNumber)
{
	SetType("Player");
	SetName("Shelda");
	maxHp = 200;
	hp = maxHp;
	Ad = 15;
	Ap = 40;
	cout << "Shelda" << " " << hp << " " << Ad << " " << Ap << endl;
}

Shelda::~Shelda()
{
}

void Shelda::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_UpSkill"));

	{
		AnimationEvent ev;
		ev.clipId = "Shelda_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Shelda::Update(float dt)
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

void Shelda::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Shelda::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Shelda::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("Shelda_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Shelda_RightIdle" : "Shelda_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Shelda_DownIdle" : "Shelda_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "Shelda_DownMove" : "Shelda_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "Shelda_RightMove" : "Shelda_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Shelda_RightAttack" : "Shelda_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Shelda_DownAttack" : "Shelda_UpAttack");
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Shelda_RightSkill" : "Shelda_LeftSkill");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Shelda_DownSkill" : "Shelda_UpSkill");
		}
		break;
	}
}

void Shelda::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Shelda::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Shelda::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Shelda::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Shelda::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "Shelda_RightMove" : "Shelda_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "Shelda_DownMove" : "Shelda_UpMove");
	}
}

void Shelda::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Shelda::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}