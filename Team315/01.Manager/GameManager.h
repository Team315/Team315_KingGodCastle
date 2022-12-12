#pragma once
#include "Include.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include "FileManager.h"
#include "ObjectPool.h"
#include "DamageText.h"
#include "RangePreview.h"

struct AltarData
{
	// ��ȭ, ��ü, ��ȭ, ���� ���� ��
	AltarData() {}

	void Init(int enhance = 0, int physical = 0, int wealth = 0, int mana = 0)
	{

	}

};

struct WaveReward
{
	int chap;
	int stage;
	int exp;
	int forge;
	int power;
	
	WaveReward(int chap = 0, int stage = 0, int exp = 0, int forge = 0, int power = 0)
		: chap(chap), stage(stage), exp(exp), forge(forge), power(power)
	{}
};

class BattleTracker;
class Character;
class DamageText;
class GameObj;
class Item;
class Skill;
class Tile;
class TileBackground;

class GameManager : public Singleton<GameManager>
{
protected:
	Chapters* m_PlayTileList;
	vector<vector<vector<vector<Tile*>>>> m_tiles;
	vector<TileBackground*> m_TileBackground;
	json backGroundDatas;
	json characterDatas;

	// Set monster character locate before battle with data imported from GameManager
	// When the game starts, the characters on the battleGrid are also taken.
	vector<GameObj*>* mainGrid;

	unordered_map<StatType, vector<float>> itemStatMap;
	map<string, WaveReward> waveRewardMap;

	BattleTracker* battleTracker;

	Skill* panelSkill;

	// Additional level up probability when summon (Character)
	int extraLevelUpSummon;
	// Additional level up probability when combinate (Character)
	int extraLevelUpCombinate;
	// Additional grade up probability (Item)
	// int extraGradeUpChance;
	int battleCharacterCount;
	int startCoin;
	int currentCoin;
	int stageClearCoin;
	int expansionCost;
	int expansionCount;
	int itemDropProbability;

	bool playingBattle;

public:
	GameManager();
	virtual ~GameManager();

	void GMInit();
	void GMReset();
	void PrintDevKey();

	const int GetCharacterCount() { return battleCharacterCount; }
	void SetCharacterCount(int newCharacterCount) { battleCharacterCount = newCharacterCount; }
	const int GetExtraLevelUpSummon() { return extraLevelUpSummon; }
	const int GetExtraLevelUpCombinate() { return extraLevelUpCombinate; }
	//const int GetExtraGradeUpChance() { return extraGradeUpChance; }

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
	Character* SpawnPlayer(string name, bool random);
	Character* SpawnPlayer(bool random);
	
	Item* SpawnItem(int tier = 0, int typeIdx = -1);

	void MainGridReset();

	void SetCharacterDatas();
	json GetCharacterData(string name);

	void SetPlayingBattle(bool val) { playingBattle = val; }
	bool GetPlayingBattle() { return playingBattle; }

	vector<GameObj*>& GetMainGridRef() { return *mainGrid; }
	GameObj* GetGameObjInMainGrid(Vector2i coord);
	void RemoveFromMainGrid(GameObj* gameObj);

	int GetCurrentCoin() { return currentCoin; }
	int GetClearCoin() { return stageClearCoin; }
	void TranslateCoin(int coin) { currentCoin += coin; }
	int GetCurrentExpansionCost() { return expansionCost * pow(2, expansionCount); }
	void TranslateExpansionCount(int val) { expansionCount += val; }

	int curChapIdx;
	int curStageIdx;

	int characterCost;
	int itemCost;

	float hpIncreaseRate;
	float adIncreaseRate;
	float apIncreaseRate;
	float asIncrease;
	float manaPerAttack;
	float manaPerHit;

	ObjectPool<DamageText> damageUI;
	ObjectPool<RangePreview> rangePreview;
	queue<Item*> waitQueue;
	vector<Item*> drops;
	AltarData altarData;

	BattleTracker*& GetBattleTracker() { return battleTracker; }
	float GetItemStatMapElem(StatType statType, int grade);
	Item* CombineItem(Item* obj1, Item* obj2);
	Item* DropItem(Character* monster);
	void GetBalanceDatas();
};

#define GAME_MGR (GameManager::GetInstance())

struct DamageData
{
	Character* character;
	float givenAD;
	float takenAD;
	float givenAP;
	float takenAP;
	DamageData(Character* character = nullptr)
		: character(character), givenAD(0.f), takenAD(0.f),
		givenAP(0.f), takenAP(0.f)
	{ 
	}
};

class BattleTracker
{
protected:
	vector<DamageData> datas;
	bool trackerMode; // true - given / false - taken

public:
	BattleTracker();
	~BattleTracker();

	void SetDatas();
	// true - given, false - taken / true - AD, false - AP
	void UpdateData(Character* character, float damage,
		bool givenOrTaken, bool dmgType);
	void PrintAllData();
	void SetTrackerMode(bool val) { trackerMode = val; }
	bool GetTrackerMode() { return trackerMode; }
	vector<DamageData>* GetDatas() { return &datas; }
	void DataSort();
};