#include "LeonHeartSkill.h"
#include "Character.h"

LeonHeartSkill::LeonHeartSkill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 30, 40, 50, 60 };

	range.resize(TIER_MAX);



	crowdControlTimer.resize(TIER_MAX);
	crowdControlTimer = { 1.5f, 2.f, 2.5f, 3.f };
}

LeonHeartSkill::~LeonHeartSkill()
{
}

void LeonHeartSkill::SetSkillRange(Vector2f startPos)
{
	applyArea.resize(0);
	Vector2i startCoord(GAME_MGR->PosToIdx(startPos));

	for (int i = 0; i < skillTier; i++)
	{
		for (auto& delta : range[i])
		{
			Vector2i tempCoord = startCoord + delta;

			if (tempCoord.x < 0 || tempCoord.x >= GAME_TILE_WIDTH ||
				tempCoord.y < 0 || tempCoord.y >= GAME_TILE_HEIGHT)
				continue;

			applyArea.push_back(tempCoord);
		}
	}
}

void LeonHeartSkill::CastSkill(Character* caster)
{
	SetSkillRange(caster->GetTarget()->GetPos());

	for (auto& cell : applyArea)
	{
		GAME_MGR->rangePreview.Get()->Fire(GAME_MGR->IdxToPos(cell));
		GameObj* target = GAME_MGR->GetGameObjInMainGrid(cell);
		if (target != nullptr && !target->GetType().compare(caster->GetTarget()->GetType()))
		{
			//CLOG::PrintVectorState(GAME_MGR->PosToIdx(target->GetPos()), target->GetName());
			dynamic_cast<Character*>(target)->TakeDamage(caster, false);
			dynamic_cast<Character*>(target)->SetCrowdControl(crowdControlTimer[skillTier - 1]);
		}
	}
}