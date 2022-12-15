#include "LeonHeartSkill.h"
#include "Character.h"

LeonHeartSkill::LeonHeartSkill(int starNumber)
	: Skill(starNumber), dir(Dir::Down)
{
	baseDamage = { 30, 40, 50, 60 };

	range.resize(TIER_MAX);

	// front 1 x 3
	range[0] = { {-1, 1}, {0, 1}, {1, 1}, };

	// front 1 x 3
	range[1] = { };

	// front 1 x 5
	range[2] = { {-2, 1}, {1, 2} };

	// front 2 x 5
	range[3] = { {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2},
		
	};

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
		for (auto& coord : range[i])
		{
			Vector2i modCoord;
			if (dir == Dir::Up)
			{
				modCoord = { coord.x, -coord.y };
			}
			else if (dir == Dir::Left)
			{
				modCoord = { -coord.y, coord.x };
			}
			else if (dir == Dir::Right)
			{
				modCoord = { coord.y, coord.x };
			}

			Vector2i tempCoord = startCoord + modCoord;

			if (tempCoord.x < 0 || tempCoord.x >= GAME_TILE_WIDTH ||
				tempCoord.y < 0 || tempCoord.y >= GAME_TILE_HEIGHT)
				continue;

			applyArea.push_back(tempCoord);
		}
	}
}

void LeonHeartSkill::CastSkill(Character* caster)
{
	SetDir(caster->GetTarget()->GetPos() - caster->GetPos());
	SetSkillRange(caster->GetPos());

	for (auto& cell : applyArea)
	{
		GAME_MGR->rangePreview.Get()->Fire(GAME_MGR->IdxToPos(cell));
		GameObj* target = GAME_MGR->GetGameObjInMainGrid(cell);
		if (target != nullptr && !target->GetType().compare(caster->GetTarget()->GetType()))
		{
			//CLOG::PrintVectorState(GAME_MGR->PosToIdx(target->GetPos()), target->GetName());
			dynamic_cast<Character*>(target)->SetCrowdControl(crowdControlTimer[skillTier - 1]);
			dynamic_cast<Character*>(target)->TakeDamage(caster, AttackTypes::Skill);
		}
	}
}

void LeonHeartSkill::SetDir(Vector2f direction)
{
	if (direction.x > 0.f)
		dir = Dir::Right;
	else if (direction.x < 0.f)
		dir = Dir::Left;
	else if (direction.y > 0.f)
		dir = Dir::Down;
	else if (direction.y < 0.f)
		dir = Dir::Up;
}