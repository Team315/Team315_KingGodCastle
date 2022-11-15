#include "Goblin00.h"

void Goblin00::Init()
{
	//SetPos({ 510 - 50, 720 / 2.f });
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

	SetState(States::Idle);
	Character::Init();
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
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "goblin00_DownIdle" : "goblin00_UpIdle");
		}
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "goblin00_RightIdle" : "goblin00_LeftIdle");
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

void Goblin00::Update(float dt)
{
	Character::Update(dt);
	//cout << GetPos().x << " " << GetPos().y << endl;
	if (InputMgr::GetKeyDown(Keyboard::Key::O))
	{
		//cout << "O" << endl;
		isPlaying2 = true;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::P))
	{
		//cout << "P" << endl;
		isPlaying2 = false;
	}
	if(isPlaying2)
	{
		direction = Utils::Normalize(target->GetPos() - GetPos());
		Translate(direction * dt * speed);
	}
	//cout << direction.x << " " << direction.y << endl;

	switch (currState)
	{
	case Goblin00::States::Idle:
		cout << "Idle" << endl;
		UpdateIdle(dt);
		break;
	case Goblin00::States::MoveToIdle:
		cout << "MoveToIdle" << endl;
		UpdateMoveToIdle(dt);
		break;
	case Goblin00::States::Move:
		cout << "Move" << endl;
		UpdateMove(dt);
		break;
	case Goblin00::States::Attack:
		cout << "Attack" << endl;
		UpdateAttack(dt);
		break;
	}
	animator.Update(dt);

	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
	direction = { 0.f, 0.f };
	if (dist > 0.f)
	{
		dist -= dt * speed;
		Translate(direction * speed * dt);
		if (dist <= 0.f)
		{
			StopTranslate();
		}
	}
}

void Goblin00::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin00::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
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
	if (!isPlaying2)
	{
		SetState(States::MoveToIdle);
		return;
	}
	if (EqualFloat(direction.x, 0.f) && EqualFloat(direction.y, 0.f))
	{
		SetState(States::MoveToIdle);
		return;
	}
	if (!EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "goblin00_DownMove" : "goblin00_UpMove");
	}
	if (!EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "goblin00_RightMove" : "goblin00_LeftMove");
	}
}

void Goblin00::UpdateAttack(float dt)
{
	if (!EqualFloat(direction.x, 0.f) && !EqualFloat(direction.y, 0.f))
	{
		SetState(States::MoveToIdle);
	}
}

bool Goblin00::EqualFloat(float a, float b)
{
	return fabs(a - b) < numeric_limits<float>::epsilon();
}

void Goblin00::StopTranslate()
{
	dist = 0.f;
	direction = { 0,0 };
	SetPos(dest);
	SetState(States::MoveToIdle);
	dest = { 0,0 };
}
