#include "Evan.h"

Evan::Evan(int starNumber)
	: GameObj(starNumber)
{
	SetType("Player");
	SetName("Evan");
}

Evan::~Evan()
{
}

void Evan::Init()
{
    animator.SetTarget(&sprite);
	attackEffect.SetTarget(&attackSprite);

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

	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_DownAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_LeftAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_RightAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_UpAttack_Effect"));

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
		ev.clipId = "Sword_DownAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_LeftAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_RightAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_UpAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
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
	GameObj::Init();
}

void Evan::SetState(AnimStates newState)
{
	GameObj::SetState(newState);

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
		if (lastDirection.x)
		{
			if (lastDirection.x > 0.f)
			{
				attackEffect.Play("Sword_RightAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 21.f;
				vec.y += 15.f;
				attackSprite.setPosition(vec);
			}
			else if (lastDirection.x < 0.f)
			{
				attackEffect.Play("Sword_LeftAttack_Effect");
				Vector2f vec = GetPos();
				vec.x -= 21.f;
				vec.y += 15.f;
				attackSprite.setPosition(vec);
			}
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownAttack" : "UpAttack");
		}
		if (lastDirection.y)
		{
			if (lastDirection.y > 0.f)
			{
				attackEffect.Play("Sword_DownAttack_Effect");
				//Vector2f vec = GetPos();
				//vec.x += 21.f;
				//vec.y += 15.f;
				//attackSprite.setPosition(vec);
			}
			if (lastDirection.y < 0.f)
			{
				attackEffect.Play("Sword_UpAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 5.f;
				//vec.y += 15.f;
				attackSprite.setPosition(vec);
			}
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

void Evan::Update(float dt)
{
	GameObj::Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::Z))
	{
		SetState(AnimStates::Attack);
	}
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
	attackEffect.Update(dt);

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Evan::Draw(RenderWindow& window)
{
	GameObj::Draw(window);
}

void Evan::SetPos(const Vector2f& pos)
{
	GameObj::SetPos(pos);
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
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Evan::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Evan::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "RightMove" : "LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "DownMove" : "UpMove");
	}
}

void Evan::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Evan::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}