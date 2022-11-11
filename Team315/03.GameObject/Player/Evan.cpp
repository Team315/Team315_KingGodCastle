#include "Evan.h"

void Evan::Init()
{
    SetPos({ 200, 720 / 2.f });
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

    SpriteObj::Init();
    SetState(States::Idle);
}

void Evan::SetState(States newState)
{
	cout << (int)currState << endl;
	if (currState == newState)
	{
		return;
	}

	currState = newState;
	switch (currState)
	{
	case Evan::States::Idle:
		animator.Play("Idle");
		break;
	case Evan::States::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "RightIdle" : "LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownIdle" : "UpIdle");
		}
		break;
	case Evan::States::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "DownMove" : "UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "RightMove" : "LeftMove");
		}
		break;
	case Evan::States::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "RightAttack" : "LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownAttack" : "UpAttack");
		}
		break;
	case Evan::States::Skill:
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

void Evan::SetBackground(SpriteObj* bk)
{
	background = bk;
}

void Evan::UpdateInput()
{
	if (InputMgr::GetKeyDown(Keyboard::Z))
	{
		SetState(States::Attack);
	}
	if (InputMgr::GetKeyDown(Keyboard::X))
	{
		SetState(States::Skill);
	}
	if (InputMgr::GetKeyDown(Keyboard::C))
	{
		SetState(States::Move);
	}
}

void Evan::Update(float dt)
{
	SpriteObj::Update(dt);
	UpdateInput();

	direction.x = 0.f;
	direction.y = 0.f;
	direction.x += Keyboard::isKeyPressed(Keyboard::Right) ? 1 : 0;
	direction.x += Keyboard::isKeyPressed(Keyboard::Left) ? -1 : 0;
	direction.y += Keyboard::isKeyPressed(Keyboard::Down) ? 1 : 0;
	direction.y += Keyboard::isKeyPressed(Keyboard::Up) ? -1 : 0;

	Translate(direction * dt * speed);

	switch (currState)
	{
	case Evan::States::Idle:
		UpdateIdle(dt);
		break;
	case Evan::States::MoveToIdle:
		UpdateMoveToIdle(dt);
		break;
	case Evan::States::Move:
		UpdateMove(dt);
		break;
	case Evan::States::Attack:
		UpdateAttack(dt);
		break;
	case Evan::States::Skill:
		UpdateSkill(dt);
		break;
	}
	animator.Update(dt);

	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Evan::Draw(RenderWindow& window)
{
	window.draw(sprite);
	SpriteObj::Draw(window);
}

void Evan::OnCompleteAttack()
{
	SetState(States::MoveToIdle);
}

void Evan::OnCompleteSkill()
{
	SetState(States::MoveToIdle);
}

void Evan::UpdateIdle(float dt)
{
	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		SetState(States::Move);
		return;
	}
}

void Evan::UpdateMoveToIdle(float dt)
{
	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		SetState(States::Move);
		return;
	}
}

void Evan::UpdateMove(float dt)
{
	if (EqualFloat(direction.x, 0.f) && EqualFloat(direction.y, 0.f))
	{
		SetState(States::MoveToIdle);
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
		SetState(States::Idle);
	}
}

void Evan::UpdateSkill(float dt)
{
	if (!EqualFloat(direction.x, 0.f) && !EqualFloat(direction.y, 0.f))
	{
		SetState(States::Idle);
	}
}

bool Evan::EqualFloat(float a, float b)
{
    return fabs(a - b) < numeric_limits<float>::epsilon();
}
