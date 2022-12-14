#include "EvanSkill.h"
#include "Character.h"

EvanSkill::EvanSkill(int skillTier)
	: Skill(skillTier), skillSpeed(1000.f)
{
	baseDamage = { 20, 35, 50, 65 };
	range.resize(TIER_MAX);
	
	// 1, infinite
	range[0] = {
		{ 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 }, { 6, 0 }, { 7, 0 },
		{ 8, 0 }, { 9, 0 }, { 10, 0 }, { 11, 0 }, { 12, 0 }, { 13, 0 }, { 14, 0 },
	};

	// 3, infinite
	range[1] = {
		{ 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 5, 1 }, { 6, 1 }, { 7, 1 },
		{ 8, 1 }, { 9, 1 }, { 10, 1 }, { 11, 1 }, { 12, 1 }, { 13, 1 }, { 14, 1 },
		{ 1, -1 }, { 2, -1 }, { 3, -1 }, { 4, -1 }, { 5, -1 }, { 6, -1 }, { 7, -1 },
		{ 8, -1 }, { 9, -1 }, { 10, -1 }, { 11, -1 }, { 12, -1 }, { 13, -1 }, { 14, -1 },
	};

	// 5, infinite
	range[2] = {
		{ 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 }, { 5, 2 }, { 6, 2 }, { 7, 2 },
		{ 8, 2 }, { 9, 2 }, { 10, 2 }, { 11, 2 }, { 12, 2 }, { 13, 2 }, { 14, 2 },
		{ 1, -2 }, { 2, -2 }, { 3, -2 }, { 4, -2 }, { 5, -2 }, { 6, -2 }, { 7, -2 },
		{ 8, -2 }, { 9, -2 }, { 10, -2 }, { 11, -2 }, { 12, -2 }, { 13, -2 }, { 14, -2 },
	};

	// 7, infinite
	range[3] = {
		{ 1, 3 }, { 2, 3 }, { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 },
		{ 8, 3 }, { 9, 3 }, { 10, 3 }, { 11, 3 }, { 12, 3 }, { 13, 3 }, { 14, 3 },
		{ 1, -3 }, { 2, -3 }, { 3, -3 }, { 4, -3 }, { 5, -3 }, { 6, -3 }, { 7, -3 },
		{ 8, -3 }, { 9, -3 }, { 10, -3 }, { 11, -3 }, { 12, -3 }, { 13, -3 }, { 14, -3 },
	};
}

EvanSkill::~EvanSkill()
{
}

void EvanSkill::Init()
{
	Skill::Init();
}

void EvanSkill::Update(float dt)
{
	Skill::Update(dt);
	
	if (dir == Dir::Up)
	{
		direction = { 0,-1 };
		Translate(direction * skillSpeed * dt);
	}
	else if (dir == Dir::Down)
	{
		direction = { 0,1 };
		Translate(direction * skillSpeed * dt);
	}
	else if (dir == Dir::Left)
	{
		direction = { -1,0 };
		Translate(direction * skillSpeed * dt);
	}
	else if (dir == Dir::Right)
	{
		direction = { 1,0 };
		Translate(direction * skillSpeed * dt);
	}
}

void EvanSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);
}

void EvanSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}

void EvanSkill::SetSkillRange(Vector2f startPos)
{
	applyArea.resize(0);
	Vector2i startCoord(GAME_MGR->PosToIdx(startPos));

	for (int i = 0; i < skillTier; i++)
	{
		for (auto& coord : range[i])
		{
			Vector2i modCoord = coord;
			if (dir == Dir::Left)
			{
				modCoord = { -coord.x, coord.y };
			}
			else if (dir == Dir::Down)
			{
				modCoord = { -coord.y, coord.x };
			}
			else if (dir == Dir::Up)
			{
				modCoord = { coord.y, -coord.x };
			}

			Vector2i tempCoord = startCoord + modCoord;

			if (tempCoord.x < 0 || tempCoord.x >= GAME_TILE_WIDTH ||
				tempCoord.y < 0 || tempCoord.y >= GAME_TILE_HEIGHT)
				continue;

			applyArea.push_back(tempCoord);
			sprite.setScale(1.f,0.33f+i);
		}
	}
}

void EvanSkill::CastSkill(Character* caster)
{
	SetDir(caster->GetTarget()->GetPos() - caster->GetPos());
	SetSkillRange(caster->GetPos());

	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/Effect/player/evan_SkillEffect.png"));
	SetOrigin(Origins::MC);
	if(dir == Dir::Up || dir == Dir::Down)
	{
		Vector2f sPos = caster->GetPos();
		sPos.x += 15.f;
		SetPos(caster->GetPos());
	}
	else if (dir == Dir::Left || dir == Dir::Right)
	{
		Vector2f sPos = caster->GetPos();
		sPos.y -= 30.f;
		SetPos(sPos);
	}

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

void EvanSkill::SetDir(Vector2f direction)
{
	if (direction.y < 0.f)
	{
		dir = Dir::Up;
		sprite.setRotation(90.f);
	}
	else if (direction.y > 0.f)
	{
		dir = Dir::Down;
		sprite.setRotation(270.f);
	}
	else if (direction.x > 0.f)
	{
		dir = Dir::Right;
		sprite.setRotation(180.f);
	}
	else if (direction.x < 0.f)
	{
		dir = Dir::Left;
		sprite.setRotation(0.f);
	}
}

