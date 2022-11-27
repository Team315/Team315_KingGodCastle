#pragma once
#include "Include.h"
#include <vector>
#include <queue>
#include "FileManager.h"

struct DamageData;
class BattleTracker;
class Character;
class Tile;

class GameManager : public Singleton<GameManager>
{
protected:
	Chapters* m_PlayTileList;
	vector<vector<vector<vector<Tile*>>>> m_tiles;

	json characterDatas;

	vector<Character*> presetC;
	
	vector<Character*>& mainGridRef;

	BattleTracker* battleTracker;

	// additional level up probability
	int extraLevelUpChance;
	int battleCharacterCount;

public:
	GameManager();
	virtual ~GameManager();

	const int GetCharacterCount() { return battleCharacterCount; }
	const int GetExtraLevelUpChance() { return extraLevelUpChance; }

	Vector2i PosToIdx(Vector2f pos);
	Vector2f IdxToPos(Vector2i idx);
	Vector2f SnapToCoord(Vector2f pos);

	void SetTilesData();
	Tile* GetTile(int chap, int stage, int height, int width);
	vector<vector<Tile*>>* GetStage(int chap, int stage) { return &m_tiles[chap][stage]; }

	void CreatedTiles();
	Character* SpawnMonster(string name, int grade);
	Character* SpawnPlayer(string name, bool random, bool drawingOnBattle = true);
	Character* SpawnPlayer(bool random, bool drawingOnBattle = true);
	
	void SetCharacterDatas();
	json GetCharacterData(string name);

	void SetMainGridRef(vector<Character*>& ref);
	vector<Character*>& GetMainGridRef() { return mainGridRef; }

	BattleTracker*& GetTracker();
};

#define GAME_MGR (GameManager::GetInstance())

struct DamageData
{
	Character* character;
	float given;
	float receive;
	DamageData(Character* character = nullptr)
		: character(character), given(0.f), receive(0.f)
	{
	}
};

class BattleTracker
{
protected:
	vector<Character*>& mainGridRef;
	vector<DamageData> datas;

public:
	BattleTracker(vector<Character*>& mainGrid);
	~BattleTracker();

	void SetMainGrid(vector<Character*>& mainGrid);
	void SetDatas();
};