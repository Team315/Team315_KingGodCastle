#include "Aramis.h"
#include "Bullet.h"

Aramis::Aramis(int starNumber)
	: Character(starNumber)
{
	SetType("Player");
	SetName("Aramis"); 
}

Aramis::~Aramis()
{
}

void Aramis::Init()
{
	animator.SetTarget(&sprite);
	attackEffect.SetTarget(&attackSprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_UpSkill"));

	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_DownAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_LeftAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_RightAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_UpAttack_Effect"));

	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_DownSkill_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_LeftSkill_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_RightSkill_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Aramis_UpSkill_Effect"));

	{
		AnimationEvent ev;
		ev.clipId = "Aramis_DownAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Aramis::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_LeftAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Aramis::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_RightAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Aramis::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_UpAttack";
		ev.frame = 3;
		ev.onEvent = bind(&Aramis::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_DownAttack_Effect";
		ev.frame = 4;
		ev.onEvent = bind(&Aramis::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_LeftAttack_Effect";
		ev.frame = 4;
		ev.onEvent = bind(&Aramis::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_RightAttack_Effect";
		ev.frame = 4;
		ev.onEvent = bind(&Aramis::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_UpAttack_Effect";
		ev.frame = 4;
		ev.onEvent = bind(&Aramis::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Aramis::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Aramis::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Aramis::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Aramis::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_DownSkill_Effect";
		ev.frame = 5;
		ev.onEvent = bind(&Aramis::OnCompleteSkill, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_LeftSkill_Effect";
		ev.frame = 5;
		ev.onEvent = bind(&Aramis::OnCompleteSkill, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_RightSkill_Effect";
		ev.frame = 5;
		ev.onEvent = bind(&Aramis::OnCompleteSkill, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Aramis_UpSkill_Effect";
		ev.frame = 5;
		ev.onEvent = bind(&Aramis::OnCompleteSkill, this);
		attackEffect.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Aramis::Update(float dt)
{
	Character::Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::Z))
	{
		SetState(AnimStates::Skill);
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

void Aramis::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Aramis::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Aramis::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("Aramis_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Aramis_RightIdle" : "Aramis_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Aramis_DownIdle" : "Aramis_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "Aramis_DownMove" : "Aramis_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "Aramis_RightMove" : "Aramis_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Aramis_RightAttack" : "Aramis_LeftAttack");
			if (lastDirection.x > 0.f)
			{
				attackEffect.Play("Aramis_RightAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 81.f;
				vec.y -= 21.f;
				attackSprite.setPosition(vec);
			}
			else if (lastDirection.x < 0.f)
			{
				attackEffect.Play("Aramis_LeftAttack_Effect");
				Vector2f vec = GetPos();
				vec.x -= 81.f;
				vec.y -= 21.f;
				attackSprite.setPosition(vec);
			}
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Aramis_DownAttack" : "Aramis_UpAttack");
			if (lastDirection.y > 0.f)
			{
				attackEffect.Play("Aramis_DownAttack_Effect");
				Vector2f vec = GetPos();
				vec.y -= 31.f;
				attackSprite.setPosition(vec);
			}
			else if (lastDirection.y < 0.f)
			{
				attackEffect.Play("Aramis_UpAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 3.f;
				vec.y -= 71.f;
				attackSprite.setPosition(vec);
			}
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "Aramis_RightSkill" : "Aramis_LeftSkill");
			if (lastDirection.x > 0.f)
			{
				attackEffect.Play("Aramis_RightSkill_Effect");
				Vector2f vec = GetPos();
				vec.x += 81.f;
				vec.y -= 21.f;
				attackSprite.setPosition(vec);
			}
			else if (lastDirection.x < 0.f)
			{
				attackEffect.Play("Aramis_LeftSkill_Effect");
				Vector2f vec = GetPos();
				vec.x -= 81.f;
				vec.y -= 21.f;
				attackSprite.setPosition(vec);
			}
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Aramis_DownSkill" : "Aramis_UpSkill");
			if (lastDirection.y > 0.f)
			{
				attackEffect.Play("Aramis_DownSkill_Effect");
				Vector2f vec = GetPos();
				vec.y -= 31.f;
				attackSprite.setPosition(vec);
			}
			else if (lastDirection.y < 0.f)
			{
				attackEffect.Play("Aramis_UpSkill_Effect");
				Vector2f vec = GetPos();
				vec.x += 3.f;
				vec.y -= 71.f;
				attackSprite.setPosition(vec);
			}
		}
		break;
	}
}

void Aramis::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Aramis::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Aramis::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Aramis::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Aramis::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "Aramis_RightMove" : "Aramis_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "Aramis_DownMove" : "Aramis_UpMove");
	}
}

void Aramis::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Aramis::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}