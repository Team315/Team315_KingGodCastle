#include "Thief00Skill.h"
#include "Character.h"

Thief00Skill::Thief00Skill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 0, 0, 0, 0 };
	
	range.resize(TIER_MAX);
	// cross 5x5
	range[0] = {
		{0, -1}, {0, 1}, {-1, 0}, {1, 0},
		{1, -1}, {-1, -1}, {-1, 1}, {1, 1},
		{0, -2}, {0, 2}, {-2, 0}, {2, 0} };

	range[1] = {};
	range[2] = {};
	range[3] = {};
}

Thief00Skill::~Thief00Skill()
{
}

void Thief00Skill::SetSkillRange(Vector2f startPos)
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

void Thief00Skill::CastSkill(Character* caster)
{
	SetSkillRange(caster->GetPos());

	SpriteObj* targetCharacter = caster->GetTarget();
	float min = 2.f;

	for (auto& cell : applyArea)
	{
		SpriteObj* target = GAME_MGR->GetSpriteObjInMainGrid(cell);
		if (target != nullptr && !target->GetType().compare(caster->GetTarget()->GetType()))
		{
			float targetRatio = dynamic_cast<Character*>(target)->GetStat(StatType::HP).GetCurRatio();
			if (min > targetRatio)
			{
				min = targetRatio;
				targetCharacter = target;
			}
		}
	}

	Vector2i temp =
		GAME_MGR->PosToIdx(targetCharacter->GetPos()) - 
		GAME_MGR->PosToIdx(caster->GetPos());

	Vector2i targetBackPos = GAME_MGR->PosToIdx(targetCharacter->GetPos()) + temp;

	if (GAME_MGR->GetSpriteObjInMainGrid(targetBackPos) == nullptr)
	{
		GAME_MGR->RemoveFromMainGrid(caster);
		caster->SetMainGrid(targetBackPos.y, targetBackPos.x, caster);
		caster->SetPos(GAME_MGR->IdxToPos(targetBackPos));
	}

	GAME_MGR->rangePreview.Get()->Fire(targetCharacter->GetPos());
	dynamic_cast<Character*>(targetCharacter)->TakeDamage(caster, AttackTypes::Skill);
}