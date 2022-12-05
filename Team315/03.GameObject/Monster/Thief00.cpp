#include "Thief00.h"
#include "Skill/Thief00Skill.h"

Thief00::Thief00(int skillTier)
	: Character(skillTier)
{
	SetType("Monster");
	SetName("Thief00");
}

Thief00::~Thief00()
{
}

void Thief00::Init()
{
	animator.SetTarget(&sprite);
	effectAnimator.SetTarget(&effectSprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightIdle"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpIdle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightMove"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpMove"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightAttack"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpAttack"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightSkill"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpSkill"));

	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_DownSkill_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_LeftSkill_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_RightSkill_Effect"));
	effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("thief00_UpSkill_Effect"));

	{
		AnimationEvent ev;
		ev.clipId = "thief00_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Thief00::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_LeftSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_RightSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_UpSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_DownSkill_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_LeftSkill_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_RightSkill_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		effectAnimator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "thief00_UpSkill_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Thief00::OnCompleteSkill, this);
		effectAnimator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
	skill = new Thief00Skill(GetStarNumber());
}

void Thief00::Update(float dt)
{
	Character::Update(dt);

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

void Thief00::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Thief00::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Thief00::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("thief00_Idle");
		break;
	case AnimStates::MoveToIdle:
		if (lastDirection.x)
		{
			animator.Play((lastDirection.x > 0.f) ? "thief00_RightIdle" : "thief00_LeftIdle");
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "thief00_DownIdle" : "thief00_UpIdle");
		}
		break;
	case AnimStates::Move:
		if (direction.y)
		{
			animator.Play((direction.y > 0.f) ? "thief00_DownMove" : "thief00_UpMove");
		}
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "thief00_RightMove" : "thief00_LeftMove");
		}
		break;
	case AnimStates::Attack:
		if (lastDirection.x)
		{
			SOUND_MGR->Play("sounds/monster_claw.wav", 20.f, false);
			animator.Play((lastDirection.x > 0.f) ? "thief00_RightAttack" : "thief00_LeftAttack");
		}
		if (lastDirection.y)
		{
			SOUND_MGR->Play("sounds/monster_claw.wav", 20.f, false);
			animator.Play((lastDirection.y > 0.f) ? "thief00_DownAttack" : "thief00_UpAttack");
		}
		break;
	case AnimStates::Skill:
		Vector2f targetPos = GetTarget()->GetPos();
		if (lastDirection.x)
		{
			//SetPos(targetPos);
			if (lastDirection.x > 0.f)
			{
				animator.Play("thief00_RightSkill");
				//effectAnimator.Play("thief00_RightSkill_Effect");
				//Vector2f vec = GetPos();
				//effectSprite.setPosition(vec);
			}
			else if (lastDirection.x < 0.f)
			{
				animator.Play("thief00_LeftSkill");
				//effectAnimator.Play("thief00_LeftSkill_Effect");
				//Vector2f vec = GetPos();
				//effectSprite.setPosition(vec);
			}
		}
		if (lastDirection.y)
		{
			//SetPos(targetPos);
			if (lastDirection.y > 0.f)
			{
				animator.Play("thief00_DownSkill");
				//effectAnimator.Play("thief00_DownSkill_Effect");
				//Vector2f vec = GetPos();
				//effectSprite.setPosition(vec);
			}
			else if (lastDirection.y < 0.f)
			{
				animator.Play("thief00_UpSkill");
				//effectAnimator.Play("thief00_UpSkill_Effect");
				//Vector2f vec = GetPos();
				//effectSprite.setPosition(vec);
			}
		}
		break;
	}
}

void Thief00::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Thief00::OnCompleteSkill()
{
	SetState(AnimStates::MoveToIdle);
}

void Thief00::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief00::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Thief00::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "thief00_RightMove" : "thief00_LeftMove");
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? "thief00_DownMove" : "thief00_UpMove");
	}
}

void Thief00::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Thief00::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}