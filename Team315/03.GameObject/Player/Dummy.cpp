#include "Dummy.h"

void Dummy::Init()
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
		ev.onEvent = bind(&Dummy::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Dummy::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Dummy::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Dummy::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Dummy::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Dummy::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Dummy::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Dummy::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	SetState(States::Idle);
	Character::Init();
}

void Dummy::Update(float dt)
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
	if (isPlaying2)
	{
		//direction = Utils::Normalize(target->GetPos() - GetPos());
		Translate(direction * dt * speed);
	}
	//cout << direction.x << " " << direction.y << endl;

	switch (currState)
	{
	case Dummy::States::Idle:
		//cout << "I" << endl;
		UpdateIdle(dt);
		break;
	case Dummy::States::MoveToIdle:
		//cout << "MTI" << endl;
		UpdateMoveToIdle(dt);
		break;
	case Dummy::States::Move:
		//cout << "M" << endl;
		UpdateMove(dt);
		break;
	case Dummy::States::Attack:
		//cout << "A" << endl;
		UpdateAttack(dt);
		break;
	}
	animator.Update(dt);

	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Dummy::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Dummy::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Dummy::SetTilePos(const Vector2i& tpos)
{
	beforeTile = currTile;
	currTile = tpos;
}

const Vector2i& Dummy::GetTilePos() const
{
	return currTile;
}

void Dummy::SetDest(Vector2f dest)
{
	this->dest = dest;
	direction = Utils::Normalize(dest - position);
	dist = Utils::Distance(dest,position);
}

Vector2f Dummy::GetDest()
{
	return this->dest;
}

void Dummy::SetState(States newState)
{
	if (currState == newState)
	{
		return;
	}
	currState = newState;
	switch (currState)
	{
	case Dummy::States::Idle:
		animator.Play("Idle");
		break;
	case Dummy::States::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "RightIdle" : "LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownIdle" : "UpIdle");
		}
		break;
	case Dummy::States::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "DownMove" : "UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "RightMove" : "LeftMove");
		}
		break;
	case Dummy::States::Attack:
		if(lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "RightAttack" : "LeftAttack");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownAttack" : "UpAttack");
		}
		break;
	case Dummy::States::Skill:
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

void Dummy::OnCompleteAttack()
{
	SetState(States::MoveToIdle);
}

void Dummy::OnCompleteSkill()
{
	SetState(States::MoveToIdle);
}

void Dummy::UpdateIdle(float dt)
{
	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		SetState(States::Move);
		return;
	}
}

void Dummy::UpdateMoveToIdle(float dt)
{
	if (!EqualFloat(direction.x, 0.f) || !EqualFloat(direction.y, 0.f))
	{
		SetState(States::Move);
		return;
	}
}

void Dummy::UpdateMove(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Up))
	{
		for (int i = 0; i < GAME_TILE_HEIGHT; ++i)
		{
			for (int j = 0; j < GAME_TILE_WIDTH; ++j)
			{
				SetPos(moveTile[i+1][j]->GetPos());
			}
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Down))
	{
		MoveDown();
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Left))
	{
		MoveLeft();
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::Right))
	{
		MoveRight();
	}
}

void Dummy::UpdateAttack(float dt)
{
	if (!EqualFloat(direction.x, 0.f) && !EqualFloat(direction.y, 0.f))
	{
		SetState(States::MoveToIdle);
	}
}

bool Dummy::EqualFloat(float a, float b)
{
	return fabs(a - b) < numeric_limits<float>::epsilon();
}

void Dummy::MoveUp()
{
	//direction.x = 0
	//direction.y = -1
	//before [i][j]
	//after [i+0][y-1]
	
}

void Dummy::MoveDown()
{
	//direction.x = 0
	//direction.y = 1
	//before [i][j]
	//after [i+0][y+1]
}

void Dummy::MoveRight()
{
	//direction.x = 1
	//direction.y = 0
	//before [i][j]
	//after [i+1][y+0]
}

void Dummy::MoveLeft()
{
	//direction.x = -1
	//direction.y = 0
	//before [i][j]
	//after [i-1][y+0]
}

void Dummy::StopTranslate()
{
	dist = 0.f;
	direction = { 0,0 };
	SetPos(dest);
	SetState(States::MoveToIdle);
	dest = { 0,0 };
}
