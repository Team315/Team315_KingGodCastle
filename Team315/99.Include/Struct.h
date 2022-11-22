#pragma once

struct TileInfo
{
	Vector2i m_arrIndex;
	TileTypes m_TileTypes;
	ThemeTypes m_ThemeTypes;
	int m_pathIndex;
};

struct Stat
{
	float base;		// origin stat
	float current;	// current stat, use hp/mp
	float delta;	// sum of item, buf, debuf etc
	float modifier;	// base + delta
	
	Stat(int b = 0) : base(b) {}

	void Init(float b, float d)
	{
		base = b;
		current = base;
		delta = d;
		modifier = base + delta;
	}

	void ResetStat()
	{
		current = base;
	}

	void UpdateStat()
	{
		modifier = base + delta;
	}

	void SetBase(float b)
	{
		base = b;
		UpdateStat();
	}
	void SetCurrent(float c) { current = c; }
	void SetDelta(float d)
	{
		delta = d;
		UpdateStat();
	}
	void SetModifier(float m) { modifier = m; }

	float& GetBase() { return base; }
	float& GetCurrent() { return current; }
	float& GetDelta() { return delta; }
	float& GetModifier() { return modifier; }

	Stat& GetReference() { return *this; }
};