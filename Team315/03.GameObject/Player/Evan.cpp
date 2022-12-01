#include "Evan.h"
#include "Skill/EvanSkill.h"

Evan::Evan(int starNumber)
	: Character(starNumber), skillSpeed(1500.f)
{
	skill = new EvanSkill;
	SetType("Player");
	SetName("Evan");
}

Evan::~Evan()
{
}

void Evan::Init()
{
    animator.SetTarget(&sprite);
	effectAnimator.SetTarget(&effectSprite);

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

	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_DownAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_LeftAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_RightAttack_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_UpAttack_Effect"));

	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Evan_DownSkill_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Evan_LeftSkill_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Evan_RightSkill_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Evan_UpSkill_Effect"));

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
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_LeftAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_RightAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_UpAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DownSkill";
		ev.frame = 2;
		ev.onEvent = bind(&Evan::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "LeftSkill";
		ev.frame = 2;
		ev.onEvent = bind(&Evan::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "RightSkill";
		ev.frame = 2;
		ev.onEvent = bind(&Evan::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "UpSkill";
		ev.frame = 2;
		ev.onEvent = bind(&Evan::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Evan_DownSkill_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Evan_LeftSkill_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Evan_RightSkill_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Evan_UpSkill_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Evan::OnCompleteAttack, this);
		effectAnimator.AddEvent(ev);
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
			if (lastDirection.x > 0.f)
			{
				effectAnimator.Play("Sword_RightAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 21.f;
				vec.y += 15.f;
				effectSprite.setPosition(vec);
			}
			else if (lastDirection.x < 0.f)
			{
				effectAnimator.Play("Sword_LeftAttack_Effect");
				Vector2f vec = GetPos();
				vec.x -= 21.f;
				vec.y += 15.f;
				effectSprite.setPosition(vec);
			}
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownAttack" : "UpAttack");
			if (lastDirection.y > 0.f)
			{
				effectAnimator.Play("Sword_DownAttack_Effect");
				Vector2f vec = GetPos();
				vec.x -= 11.f;
				vec.y += 12.f;
				effectSprite.setPosition(vec);
			}
			else if (lastDirection.y < 0.f)
			{
				effectAnimator.Play("Sword_UpAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 5.f;
				effectSprite.setPosition(vec);
			}
		}
		break;
	case AnimStates::Skill:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "RightSkill" : "LeftSkill");
			if (lastDirection.x > 0.f)
			{
				effectAnimator.Play("Evan_RightSkill_Effect");
				Vector2f vec = GetPos();
				vec.x -= 30.f;
				vec.y -= 10.f;
				effectSprite.setPosition(vec);
			}
			if (lastDirection.x < 0.f)
			{
				effectAnimator.Play("Evan_LeftSkill_Effect");
				Vector2f vec = GetPos();
				vec.x += 30.f;
				vec.y -= 10.f;
				effectSprite.setPosition(vec);
			}
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "DownSkill" : "UpSkill");
			if (lastDirection.y > 0.f)
			{
				effectAnimator.Play("Evan_DownSkill_Effect");
				Vector2f vec = GetPos();
				vec.y -= 10.f;
				effectSprite.setPosition(vec);
			}
			if (lastDirection.y < 0.f)
			{
				effectAnimator.Play("Evan_UpSkill_Effect");
				Vector2f vec = GetPos();
				vec.x += 5.f;
				effectSprite.setPosition(vec);
			}
		}
		break;
	}
}

void Evan::Update(float dt)
{
	Character::Update(dt);
	skill->Translate(lastDirection * skillSpeed * dt);
	
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
	effectAnimator.Update(dt);

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Evan::Draw(RenderWindow& window)
{
	Character::Draw(window);
	skill->Draw(window);
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
	SetState(AnimStates::Attack);
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
	skill->Init();
	skill->SetRotation(lastDirection);
	Vector2f vec = GetPos();
	if(lastDirection.y < 0.f)
	{
		vec.x += 90.f;
		vec.y -= 100.f;
	}
	else if (lastDirection.y > 0.f)
	{
		vec.x -= 90.f;
		vec.y += 30.f;
	}
	else if (lastDirection.x < 0.f)
	{
		vec.x -= 80.f;
		vec.y -= 120.f;
	}
	else if (lastDirection.x > 0.f)
	{
		vec.x += 80.f;
		vec.y += 65.f;
	}
	skill->SetPos(vec);
	
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}