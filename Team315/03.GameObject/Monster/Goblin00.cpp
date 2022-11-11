#include "Goblin00.h"
#include "Player/Evan.h"

void Goblin00::Init(Evan* evan)
{
	SetPos({ 1280 - 200, 720 / 2.f });
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

	{
		AnimationEvent ev;
		ev.clipId = "goblin00_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Goblin00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Goblin00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Goblin00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "goblin00_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Goblin00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}

	this->evan = evan;
	SpriteObj::Init();
	SetState(States::Idle);
}

void Goblin00::SetState(States newState)
{
	if (currState == newState)
	{
		return;
	}

	currState = newState;
	switch (currState)
	{
	case Goblin00::States::Idle:
		animator.Play("goblin00_Idle");
		break;
	case Goblin00::States::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightIdle" : "goblin00_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownIdle" : "goblin00_UpIdle");
		}
		break;
	case Goblin00::States::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "goblin00_DownMove" : "goblin00_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "goblin00_RightMove" : "goblin00_LeftMove");
		}
		break;
	case Goblin00::States::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightAttack" : "goblin00_LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownAttack" : "goblin00_UpAttack");
		}
		break;
	}
}

void Goblin00::SetBackground(SpriteObj* bk)
{
	background = bk;
}

void Goblin00::UpdateInput()
{
	if (InputMgr::GetKeyDown(Keyboard::Q))
	{
		SetState(States::Attack);
	}
}

void Goblin00::Update(float dt)
{
	SpriteObj::Update(dt);
	UpdateInput();

	
	direction.x = 0.f;
	direction.y = 0.f;
	direction.x += Keyboard::isKeyPressed(Keyboard::D) ? 1 : 0;
	direction.x += Keyboard::isKeyPressed(Keyboard::A) ? -1 : 0;
	direction.y += Keyboard::isKeyPressed(Keyboard::S) ? 1 : 0;
	direction.y += Keyboard::isKeyPressed(Keyboard::W) ? -1 : 0;

	direction = Utils::Normalize(evan->GetPos() - GetPos());
	Translate(direction * dt * speed);

	switch (currState)
	{
	case Goblin00::States::Idle:
		UpdateIdle(dt);
		break;
	case Goblin00::States::MoveToIdle:
		UpdateMoveToIdle(dt);
		break;
	case Goblin00::States::Move:
		UpdateMove(dt);
		break;
	case Goblin00::States::Attack:
		UpdateAttack(dt);
		break;
	}
	animator.Update(dt);

	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Goblin00::Draw(RenderWindow& window)
{
	window.draw(sprite);
	SpriteObj::Draw(window);
}

void Goblin00::OnCompleteAttack()
{
	SetState(States::MoveToIdle);
}

void Goblin00::UpdateIdle(float dt)
{
	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		SetState(States::Move);
		return;
	}
}

void Goblin00::UpdateMoveToIdle(float dt)
{
	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		SetState(States::Move);
		return;
	}
}

void Goblin00::UpdateMove(float dt)
{
	if (EqualFloat(direction.x, 0.f) && EqualFloat(direction.y, 0.f))
	{
		SetState(States::MoveToIdle);
		return;
	}
	if (!EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "goblin00_RightMove" : "goblin00_LeftMove");
	}
	if (!EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "goblin00_DownMove" : "goblin00_UpMove");
	}
}

void Goblin00::UpdateAttack(float dt)
{
	if (!EqualFloat(direction.x, 0.f) && !EqualFloat(direction.y, 0.f))
	{
		SetState(States::Idle);
	}
}

bool Goblin00::EqualFloat(float a, float b)
{
	return fabs(a - b) < numeric_limits<float>::epsilon();
}
