#pragma once

struct AltarData
{
	int mana;
	int silver;
	int physical;
	int enforce;
	// 마나, 은화, 신체, 강화 제단 순
	AltarData() {}

	void Init(int mana = 0, int silver = 0, int physical = 0, int enforce = 0)
	{
		this->mana = mana;
		this->silver = silver;
		this->physical = physical;
		this->enforce = enforce;
	}
};

struct AccountInfo
{
	int level;
	int exp;
	AccountInfo() : level(1), exp(0)
	{}
	void Load(int level, int exp)
	{
		this->level = level;
		this->exp = exp;
	}

	void AddExp(int adder)
	{
		exp += adder;
	}

	void UpdateLevel(int expLimit)
	{
		level += (exp / expLimit);
		exp %= expLimit;
	}
};

struct WaveReward
{
	int exp;
	int forge;
	int power;

	WaveReward(int exp = 0, int forge = 0, int power = 0)
		: exp(exp), forge(forge), power(power)
	{}
};

struct TileInfo
{
	Vector2i m_arrIndex;
	TileTypes m_TileTypes;
	ThemeTypes m_ThemeTypes;
	int m_pathIndex;
};

struct Stat
{
	float base;			// origin stat
	float current;		// current stat, use hp/mp
	float delta;		// sum of item, buf, debuf etc
	float modifier;		// base + delta
	bool upgradeMode;	// true - calc mode addition, calc mode multiplication
	bool deltaMode;		// true - calc delta addition, calc delta multiplication

	Stat(float b = 0.f, float d = 0.f, bool currentFull = true)
		: base(b), delta(0.f), current(0.f), upgradeMode(false), deltaMode(false)
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
		modifier = deltaMode ? base + delta : base * (1.f + delta);
		ResetStat();
	}

	void UpgradeBase(float upgradeFactor)
	{
		if (upgradeMode)
			base += upgradeFactor;
		else
			base *= upgradeFactor;
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
	void AddDelta(float d) { SetDelta(delta + d); }
	void SetModifier(float m) { modifier = m; }

	void SetUpgradeMode(bool b) { upgradeMode = b; }
	bool GetUpgradeMode() { return upgradeMode; }
	
	void SetDeltaMode(bool d) { deltaMode = d; }
	bool GetDeltaMode() { return deltaMode; }

	void TranslateCurrent(float var) { SetCurrent(current + var); }

	float& GetBase() { return base; }
	float& GetCurrent() { return current; }
	float& GetDelta() { return delta; }
	float& GetModifier() { return modifier; }
	float GetCurRatio() { return current / modifier; }

	Stat& GetReference() { return *this; }
};