#include "PriaSkill.h"
#include "Character.h"

PriaSkill::PriaSkill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 30, 45, 60, 75 };

	range.resize(TIER_MAX);

	// square 3x3
	range[0] = { {0, 0},
		{0, -1}, {0, 1}, {-1, 0}, {1, 0},
		{1, -1}, {-1, -1}, {-1, 1}, {1, 1} };

	// cross 5x5
	range[1] = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };

	// square 5x5
	range[2] = {
		{2, -2}, {2, -1}, {2, 1}, {2, 2},
		{1, -2}, {-1, -2}, {1, 2}, {-1, 2},
		{-2, -2}, {-2, -1}, {-2, 1}, {-2, 2},
	};

	// cross 9x9
	range[3] = {
		{0, 4}, {-1, 3}, {0, 3}, {1, 3},
		{0, -4}, {-1, -3}, {0, -3}, {1, -3},
		{4, 0}, {3, -1}, {3, 0}, {3, 1},
		{-4, 0}, {-3, -1}, {-3, 0}, {-3, 1},
	};

	crowdControlTimer.resize(TIER_MAX);
	crowdControlTimer = { 1.f, 1.33f, 1.66f, 2.f };
}

PriaSkill::~PriaSkill()
{
}

void PriaSkill::SetSkillRange(Vector2f startPos)
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

void PriaSkill::CastSkill(Character* caster)
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