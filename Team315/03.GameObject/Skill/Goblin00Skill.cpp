#include "Goblin00Skill.h"
#include "Character.h"

Goblin00Skill::Goblin00Skill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 0, 0, 0, 0 };

	range.resize(TIER_MAX);

	// square 3x3
	range[0] = { {0, 0},
		{0, -1}, {0, 1}, {-1, 0}, {1, 0},
		{1, -1}, {-1, -1}, {-1, 1}, {1, 1} };

	range[1] = {};
	range[2] = {};
	range[3] = {};

	crowdControlTimer.resize(TIER_MAX);
	crowdControlTimer = { 3.f, 3.f, 3.f, 3.f };
}

Goblin00Skill::~Goblin00Skill()
{
}

void Goblin00Skill::SetSkillRange(Vector2f startPos)
{
	applyArea.resize(0);
	Vector2i startCoord(GAME_MGR->PosToIdx(startPos));

	for (int i = 0; i < skillTier; i++)
	{
		for (auto& coord : range[i])
		{
			Vector2i tempCoord = startCoord + coord;

			if (tempCoord.x < 0 || tempCoord.x >= GAME_TILE_WIDTH ||
				tempCoord.y < 0 || tempCoord.y >= GAME_TILE_HEIGHT)
				continue;

			applyArea.push_back(tempCoord);
		}
	}
}

void Goblin00Skill::CastSkill(Character* caster)
{
	SetSkillRange(caster->GetPos());

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