#include "Slime00Skill.h"
#include "Character.h"

Slime00Skill::Slime00Skill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 30, 45, 60, 75 };

	range.resize(TIER_MAX);

	// cross 5x5
	range[0] = { {0, 0},
		{0, -1}, {0, 1}, {-1, 0}, {1, 0},
		{1, -1}, {-1, -1}, {-1, 1}, {1, 1},
		{0, -2}, {0, 2}, {-2, 0}, {2, 0}
	};

	range[1] = {};
	range[2] = {};
	range[3] = {};
}

Slime00Skill::~Slime00Skill()
{
}

void Slime00Skill::SetSkillRange(Vector2f startPos)
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

void Slime00Skill::CastSkill(Character* caster)
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
		}
	}
}