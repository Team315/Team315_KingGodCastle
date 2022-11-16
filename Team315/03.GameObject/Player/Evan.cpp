#include "Evan.h"

void Evan::Init()
{
    animator.SetTarget(&sprite);

    animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("UpIdle"));
	
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("UpSkill"));

	{
		AnimationEvent ev;
		ev.clipId = "DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

    SetState(AnimStates::Idle);
	Character::Init();
}

void Evan::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "RightIdle" : "LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownIdle" : "UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "DownMove" : "UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "RightMove" : "LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "RightAttack" : "LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownAttack" : "UpAttack");
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "RightSkill" : "LeftSkill");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownSkill" : "UpSkill");
		}
		break;
	}
}

void Evan::UpdateInput()
{
	//if (InputMgr::GetKeyDown(Keyboard::Z))
	//{
	//	SetState(AnimStates::Attack);
	//}
	//if (InputMgr::GetKeyDown(Keyboard::X))
	//{
	//	SetState(AnimStates::Skill);
	//}
	//if (InputMgr::GetKeyDown(Keyboard::C))
	//{
	//	SetState(AnimStates::Move);
	//}
}

void Evan::Update(float dt)
{
	Character::Update(dt);
	UpdateInput();

	direction.x = 0.f;
	direction.y = 0.f;
	//direction.x += Keyboard::isKeyPressed(Keyboard::Right) ? 1 : 0;
	//direction.x += Keyboard::isKeyPressed(Keyboard::Left) ? -1 : 0;
	//direction.y += Keyboard::isKeyPressed(Keyboard::Down) ? 1 : 0;
	//direction.y += Keyboard::isKeyPressed(Keyboard::Up) ? -1 : 0;

	Translate(direction * dt * speed);
	
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

	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
	if (InputMgr::GetKeyDown(Keyboard::Right))
	{

	}
}

void Evan::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Evan::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Evan::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Evan::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Evan::UpdateIdle(float dt)
{
	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Evan::UpdateMoveToIdle(float dt)
{
	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Evan::UpdateMove(float dt)
{
	if (EqualFloat(direction.x, 0.f) && EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "RightMove" : "LeftMove");
	}
	if (!EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "DownMove" : "UpMove");
	}
}

void Evan::UpdateAttack(float dt)
{
	if (!EqualFloat(direction.x, 0.f) && !EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Idle);
	}
}

void Evan::UpdateSkill(float dt)
{
	if (!EqualFloat(direction.x, 0.f) && !EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Idle);
	}
}

bool Evan::EqualFloat(float a, float b)
{
    return fabs(a - b) < numeric_limits<float>::epsilon();
}
