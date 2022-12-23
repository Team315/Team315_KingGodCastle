#include "ArveronSkill.h"
#include "Character.h"

ArveronSkill::ArveronSkill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 0, 0, 0, 0 };

	range.resize(TIER_MAX);

	// square 3x3
	range[0] = { {0, 0},
		{0, -1}, {0, 1}, {-1, 0}, {1, 0},
		{1, -1}, {-1, -1}, {-1, 1}, {1, 1} };

	// square 5x5
	range[1] = {
		{0, -2}, {0, 2}, {-2, 0}, {2, 0},
		{2, -2}, {2, -1}, {2, 1}, {2, 2},
		{1, -2}, {-1, -2}, {1, 2}, {-1, 2},
		{-2, -2}, {-2, -1}, {-2, 1}, {-2, 2},
	};

	// square 7x7
	range[2] = {
		{-3, 3}, {-2, 3}, {-1, 3}, {0, 3}, {1, 3}, {2, 3}, {3, 3},
		{-3, 2}, {3, 2},
		{-3, 1}, {3, 1},
		{-3, 0}, {3, 0},
		{-3, -1}, {3, -1},
		{-3, -2}, {3, -2},
		{-3, -3}, {-2, -3}, {-1, -3}, {0, -3}, {1, -3}, {2, -3}, {3, -3},
	};

	// square 9x9
	range[3] = {
		{-4, 4}, {-3, 4}, {-2, 4}, {-1, 4}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4},
		{-4, 3}, {4, 3},
		{-4, 2}, {4, 2},
		{-4, 1}, {4, 1},
		{-4, 0}, {4, 0},
		{-4, -1}, {4, -1},
		{-4, -2}, {4, -2},
		{-4, -3}, {4, -3},
		{-4, -4}, {-3, -4}, {-2, -4}, {-1, -4}, {0, -4}, {1, -4}, {2, -4}, {3, -4}, {4, -4},
	};
}

ArveronSkill::~ArveronSkill()
{
}

void ArveronSkill::SetSkillRange(Vector2f startPos)
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

void ArveronSkill::CastSkill(Character* caster)
{
	SpriteObj* startTarget = caster;
	float min = 2.f;
	for (auto& cell : applyArea)
	{
		SpriteObj* target = GAME_MGR->GetSpriteObjInMainGrid(cell);
		if (target != nullptr && !target->GetType().compare(caster->GetType()))
		{
			float curRatio = dynamic_cast<Character*>(target)->GetStat(StatType::HP).GetCurRatio();

			if (min > curRatio)
			{
				min = curRatio;
				startTarget = target;
			}
		}
	}

	SetSkillRange(startTarget->GetPos());

	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Arveron_Skill_Effect"));
	animator.Play("Arveron_Skill_Effect");

	SetPos(caster->GetPos());

	for (auto& cell : applyArea)
	{
		GAME_MGR->rangePreview.Get()->Fire(GAME_MGR->IdxToPos(cell));
		SpriteObj* target = GAME_MGR->GetSpriteObjInMainGrid(cell);
		if (target != nullptr && !target->GetType().compare(caster->GetType()))
		{
			//CLOG::PrintVectorState(GAME_MGR->PosToIdx(target->GetPos()), target->GetName());
			dynamic_cast<Character*>(target)->TakeCare(caster);
		}
	}
}