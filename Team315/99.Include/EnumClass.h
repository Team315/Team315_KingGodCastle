#pragma once

enum class ThemeTypes
{
	None = 0,
	Goblin,
	Thief,
	Slime,
};

enum class MonsterTypes
{
	None = 0,
	Monster,
	Boss,
};

enum class ClickMode
{
	None = 0,
	Theme,
	Tile,
	Obstacle,
	Monster,
};

enum class TileTypes
{
	None = 0,
	Obstacle,
	Monster,
	PlayerArea,
};

enum class AnimStates
{
	None = -1,
	Idle,
	MoveToIdle,
	Move,
	Attack,
	Skill,
};

enum class Dir
{
	Up,
	Down,
	Left,
	Right,
};

enum class Stats
{
	None = -1,
	HP, // Health Point
	MP, // Mana Point
	AD, // Attack Damage
	AP, // Ability Power
	AS, // Attack Speed
	AR, // Attack Range
	MS, // Move Speed
	COUNT,
};