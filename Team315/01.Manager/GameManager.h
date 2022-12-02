#pragma once
#include "Include.h"
#include <vector>
#include <queue>
#include "FileManager.h"
#include <unordered_map>

//struct DamageData;
//class BattleTracker;
class Character;
class GameObj;
class Item;
class Tile;
class TileBackground;
class GameManager : public Singleton<GameManager>
{
protected:
	Chapters* m_PlayTileList;
	vector<vector<vector<vector<Tile*>>>> m_tiles;
	vector<TileBackground*> m_TileBackground;
	json BackGroundDatas;

	json characterDatas;

	//vector<GameObj*> presetC;

	// Set monster character locate before battle with data imported from GameManager
	// When the game starts, the characters on the battleGrid are also taken.
	vector<GameObj*>* mainGrid;

	unordered_map<StatType, vector<float>> itemStatMap;

	//BattleTracker* battleTracker;

	// Additional level up probability (Character)
	int extraLevelUpChance;
	// Additional grade up probability (Item)
	int extraGradeUpChance;
	int battleCharacterCount;
	int startCoin;
	int currentCoin;

public:
	GameManager();
	virtual ~GameManager();

	void Init();
	const int GetCharacterCount() { return battleCharacterCount; }
	const int GetExtraLevelUpChance() { return extraLevelUpChance; }
	const int GetExtraGradeUpChance() { return extraGradeUpChance; }

	Vector2i PosToIdx(Vector2f pos);
	Vector2f IdxToPos(Vector2i idx);
	Vector2f SnapToCoord(Vector2f pos);

	void SetTilesData();
	Tile* GetTile(int chap, int stage, int height, int width);
	vector<vector<Tile*>>* GetStage(int chap, int stage) { return &m_tiles[chap][stage]; }
	vector<TileBackground*> GetTileBackgroundList() { return m_TileBackground; };

	void SetBackGroundDatas();
	json GetBackGroundDatas();


	void CreatedTiles();
	void CreatedBackGround();
	Character* SpawnMonster(string name, int grade);
	Character* SpawnPlayer(string name, bool random, bool drawingOnBattle = true);
	Character* SpawnPlayer(bool random, bool drawingOnBattle = true);
	
	Item* SpawnItem(int typeIdx = -1);

	void Reset();

	void SetCharacterDatas();
	json GetCharacterData(string name);

	vector<GameObj*>& GetMainGridRef() { return *mainGrid; }
	void RemoveFromMainGrid(GameObj* gameObj);

	int GetCurrentCoin() { return currentCoin; }
	void TranslateCoin(int coin) { currentCoin += coin; }

	const int characterCost;
	const int itemCost;

	// Stat increase rate when upgrading, (todo: file input)
	const float hpIncreaseRate;
	const float adIncreaseRate;
	const float apIncreaseRate;
	const float asIncrease;

	//BattleTracker*& GetTracker();

	float GetItemStatMapElem(StatType statType, int grade);
};

#define GAME_MGR (GameManager::GetInstance())

//struct DamageData
//{
//	GameObj* character;
//	float given;
//	float receive;
//	DamageData(GameObj* character = nullptr)
//		: character(character), given(0.f), receive(0.f)
//	{
//	}
//};
//
//class BattleTracker
//{
//protected:
//	vector<DamageData> datas;
//
//public:
//	BattleTracker();
//	~BattleTracker();
//
//	void SetDatas();
//};