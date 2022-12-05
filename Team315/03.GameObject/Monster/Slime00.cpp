#include "Slime00.h"
#include "Skill/Slime00Skill.h"

Slime00::Slime00(int skillTier)
	: Character(skillTier), duration(1.0f), mpTimer(duration)
{
	SetType("Monster");
	SetName("Slime00");
}

Slime00::~Slime00()
{
}

void Slime00::Init()
{
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime00_Idle"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("slime00_DownSkill"));
	{
		AnimationEvent ev;
		ev.clipId = "slime00_DownSkill";
		ev.frame = 3;
		ev.onEvent = bind(&Slime00::OnCompleteSkill, this);
		animator.AddEvent(ev);
	}

	SetState(AnimStates::Idle);
	Character::Init();
	skill = new Slime00Skill(GetStarNumber());
}

void Slime00::Reset()
{
	Character::Reset();
	mpTimer = duration;
}

void Slime00::Update(float dt)
{
	//Character::Update(dt);

	if (!isAlive)
		return;

	hpBar->Update(dt);

	if (ccTimer > 0.f)
	{
		ccTimer -= dt;
		if (ccTimer < 0.f)
		{
			ccTimer = 0.f;
		}
		return;
	}
	if (isBattle)
	{
		mpTimer -= dt;
		if (mpTimer < 0)
		{
			mpTimer = duration;
			Stat& mp = stat[StatType::MP];
			mp.TranslateCurrent(15.f);
			
			if (!noSkill && Utils::EqualFloat(mp.GetCurRatio(), 1.f))
			{
				m_target = m_floodFill.GetNearEnemy(
					GAME_MGR->GetMainGridRef(), GAME_MGR->PosToIdx(position), targetType);
				SetState(AnimStates::Skill);
				mp.SetCurrent(0.f);
				if (skill != nullptr)
					skill->CastSkill(this);
			}
		}
	}

	switch (currState)
	{
	case AnimStates::Idle:
		UpdateIdle(dt);
		break;
	case AnimStates::Skill:
		UpdateSkill(dt);
		break;
	}
	animator.Update(dt);
}

void Slime00::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Slime00::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

void Slime00::SetState(AnimStates newState)
{
	Character::SetState(newState);

	switch (currState)
	{
	case AnimStates::Idle:
		animator.Play("slime00_Idle");
		break;
	case AnimStates::Skill:
		animator.Play("slime00_DownSkill");
		break;
	}
}

void Slime00::OnCompleteSkill()
{
	SetState(AnimStates::Idle);
}

void Slime00::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Skill);
		return;
	}
}

void Slime00::UpdateSkill(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Idle);
	}
}