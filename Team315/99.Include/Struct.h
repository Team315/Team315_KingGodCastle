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

	Stat(float b = 0.f, float d = 0.f, bool currentFull = true)
		: base(b), delta(0.f), current(0.f)
	{
		Init(b, d, currentFull);
	}

	void Init(float b, float d = 0.f, bool currentFull = true)
	{
		base = b;
		current = currentFull ? base : 0;
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

	void SetCurrent(float c)
	{
		current = c;
		if (current >= modifier)
			current = modifier;
	}

	void SetDelta(float d)
	{
		delta = d;
		UpdateStat();
	}
	void SetModifier(float m) { modifier = m; }

	void TranslateCurrent(float var) { SetCurrent(current + var); }

	float& GetBase() { return base; }
	float& GetCurrent() { return current; }
	float& GetDelta() { return delta; }
	float& GetModifier() { return modifier; }
	float GetCurRatio() { return current / modifier; }

	Stat& GetReference() { return *this; }
};