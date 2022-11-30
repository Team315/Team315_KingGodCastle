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
	float isAddition; // true - calc mode addition, calc mode multiplication

	Stat(float b = 0.f, float d = 0.f, bool currentFull = true)
		: base(b), delta(0.f), current(0.f), isAddition(false)
	{
		base = b;
		current = currentFull ? base : 0;
		delta = d;
		modifier = b + d;
	}

	void ResetStat()
	{
		current = modifier;
	}

	void UpdateStat()
	{
		modifier = base + delta;
		ResetStat();
	}

	void UpgradeBase(float upgradeFactor)
	{
		if (isAddition)
			base += upgradeFactor;
		else
			base *= upgradeFactor;
		UpdateStat();
	}

	void UpgradeDelta(float upgradeFactor)
	{
		if (isAddition)
			delta += upgradeFactor;
		else
			delta *= upgradeFactor;
		UpdateStat();
	}

	void SetBase(float b)
	{
		base = b;
		UpdateStat();
	}

	void SetCurrent(float c)
	{
		current = Utils::Clamp(c, 0.f, modifier);
	}

	void SetDelta(float d)
	{
		delta = d;
		UpdateStat();
	}
	void SetModifier(float m) { modifier = m; }

	void SetIsAddition(bool b) { isAddition = b; }
	bool GetIsAddition() { return isAddition; }

	void TranslateCurrent(float var) { SetCurrent(current + var); }

	float& GetBase() { return base; }
	float& GetCurrent() { return current; }
	float& GetDelta() { return delta; }
	float& GetModifier() { return modifier; }
	float GetCurRatio() { return current / modifier; }

	Stat& GetReference() { return *this; }
};