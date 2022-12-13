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
	BackGround,
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

enum class StatType
{
	None = -1,
	HP, // Health Point
	MP, // Mana Point
	AD, // Attack Damage
	AP, // Ability Power
	AS, // Attack Speed
	AR, // Attack Range
	MS, // Move Speed
	ARTYPE, // square, cross
	COUNT,
};

enum class ItemType
{
	None = -1,
	Armor,
	Bow,
	Staff,
	Sword,
	Book,
	Count,
};

enum class EventType
{
	None = -1,
	Forge,
	Power,
	GameOver,
	GameClear,
};

enum class Dir
{
	None = -1,
	Down,
	Up,
	Left,
	Right,
};

enum class AltarOrder
{
	Mana,
	Silver,
	Physical,
	Enforce,
};

enum class ResStringType
{
	Idle,
	DownIdle,
	LeftIdle,
	RightIdle,
	UpIdle,
	DownMove,
	LeftMove,
	RightMove,
	UpMove,
	DownAttack,
	LeftAttack,
	RightAttack,
	UpAttack,
	DownSkill,
	LeftSkill,
	RightSkill,
	UpSkill,
	DownAttackEffect,
	LeftAttackEffect,
	RightAttackEffect,
	UpAttackEffect,
	DownSkillEffect,
	LeftSkillEffect,
	RightSkillEffect,
	UpSkillEffect,
	atkSound,
};