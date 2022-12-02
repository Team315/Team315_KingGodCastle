#include "DanielSkill.h"
#include "Character.h"
#include "Player/Daniel.h"

DanielSkill::DanielSkill()
{
}

DanielSkill::~DanielSkill()
{
}

void DanielSkill::Init()
{
	Skill::Init();
	baseDamage = { 50, 60, 70, 80 };
	range.resize(CHARACTER_TIER_MAX);

	for (int i = 0; i < 25; ++i)
	{
		Sprite* skillSpriteArr = new Sprite();
		Animator* skillEffectArr = new Animator();
		skillEffectArr->SetTarget(skillSpriteArr);
		skillEffectArr->AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_Skill_Effect"));
		//{
		//	AnimationEvent ev;
		//	ev.clipId = "Daniel_Skill_Effect";
		//	ev.frame = 8;
		//	ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
		//	skillEffectArr->AddEvent(ev);
		//}
		skillEffect.push_back(skillEffectArr);
		skillSprite.push_back(skillSpriteArr);
	}

}

void DanielSkill::Update(float dt)
{
	Skill::Update(dt);

	for (int i = 0; i < 25; ++i)
	{
		skillEffect[i]->Update(dt);
	}
}

void DanielSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);

	for (auto skills : skillSprite)
	{
		window.draw(*skills);
	}
}

void DanielSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}

void DanielSkill::SetState(AnimStates newState, GameObj* target, String t)
{
	Skill::SetState(newState);

	if (currState == AnimStates::Skill)
	{
		vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
		Vector2i targetPos = GAME_MGR->PosToIdx(GetPos());
		if (mainGrid[targetPos.y * 7 + targetPos.x + 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 1]->GetType().compare(t))
		{
			dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->TakeDamage(this, false);
			Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->GetPos();
			skillSprite[0]->setPosition(pos);
			skillEffect[0]->Play("Daniel_Skill_Effect");
		}
		if (mainGrid[targetPos.y * 7 + targetPos.x - 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 1]->GetType().compare(t))
		{
			dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->TakeDamage(this, false);
			Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->GetPos();
			skillSprite[1]->setPosition(pos);
			skillEffect[1]->Play("Daniel_Skill_Effect");
		}
		if (mainGrid[targetPos.y * 7 + targetPos.x + 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 7]->GetType().compare(t))
		{
			dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->TakeDamage(this, false);
			Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->GetPos();
			skillSprite[2]->setPosition(pos);
			skillEffect[2]->Play("Daniel_Skill_Effect");
		}
		if (mainGrid[targetPos.y * 7 + targetPos.x - 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 7]->GetType().compare(t))
		{
			dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->TakeDamage(this, false);
			Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->GetPos();
			skillSprite[3]->setPosition(pos);
			skillEffect[3]->Play("Daniel_Skill_Effect");
		}
	}
}

void DanielSkill::CastSkill(Character* caster)
{
}
