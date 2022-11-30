#include "Shelda.h"

Shelda::Shelda(int starNumber)
	: Character(starNumber)
{
	//skill = new SheldaSkill();
	SetType("Player");
	SetName("Shelda");
}

Shelda::~Shelda()
{
}

void Shelda::Init()
{
	animator.SetTarget(&sprite);
	attackEffect.SetTarget(&attackSprite);

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

	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_DownAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_LeftAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_RightAttack_Effect"));
	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Sword_UpAttack_Effect"));

	attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_Skill_Effect"));

	//attackEffect.AddClip(*RESOURCE_MGR->GetAnimationClip("Shelda_HUSkill_Effect"));

	//skill->Init();

	{
		AnimationEvent ev;
		ev.clipId = "Shelda_DownAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_LeftAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_RightAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_UpAttack";
		ev.frame = 2;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_DownAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_LeftAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_RightAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "Sword_UpAttack_Effect";
		ev.frame = 3;
		ev.onEvent = bind(&Shelda::OnCompleteAttack, this);
		attackEffect.AddEvent(ev);
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
	//{
	//	AnimationEvent ev;
	//	ev.clipId = "Shelda_Skill_Effect";
	//	ev.frame = 5;
	//	ev.onEvent = bind(&Shelda::OnCompleteSkill, this);
	//	skill->GetSkillAnimator().AddEvent(ev);
	//}
	{
		AnimationEvent ev;
		ev.clipId = "Shelda_Skill_Effect";
		ev.frame = 5;
		ev.onEvent = bind(&Shelda::OnCompleteSkill, this);
		attackEffect.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
}

void Shelda::Update(float dt)
{
	Character::Update(dt);

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
	//skill->Update(dt);

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Shelda::Draw(RenderWindow& window)
{
	Character::Draw(window);
	//skill->Draw(window);
	//cout<<skill->GetPos().y << endl;
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
			animator.Play((lastDirection.y > 0.f) ? "Shelda_DownAttack" : "Shelda_UpAttack");
			if (lastDirection.y > 0.f)
			{
				attackEffect.Play("Sword_DownAttack_Effect");
				Vector2f vec = GetPos();
				attackSprite.setPosition(vec);
			}
			if (lastDirection.y < 0.f)
			{
				attackEffect.Play("Sword_UpAttack_Effect");
				Vector2f vec = GetPos();
				vec.x += 5.f;
				attackSprite.setPosition(vec);
			}
		}
		break;
	case AnimStates::Skill:
		if(lastDirection.x)
		{
			animator.Play((lastDirection.x >0.f) ? "Shelda_RightSkill" : "Shelda_LeftSkill");
			//attackEffect.Play("Shelda_HUSkill_Effect");
			//skill->GetSkillAnimator().Play("Shelda_Skill_Effect");
			//skill->SetPos(GetPos());
			attackEffect.Play("Shelda_Skill_Effect");
			Vector2f vec = GetPos();
			attackSprite.setPosition(vec);
		}
		if (lastDirection.y)
		{
			animator.Play((lastDirection.y > 0.f) ? "Shelda_DownSkill" : "Shelda_UpSkill");
			attackEffect.Play("Shelda_Skill_Effect");
			Vector2f vec = GetPos();
			attackSprite.setPosition(vec);
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
