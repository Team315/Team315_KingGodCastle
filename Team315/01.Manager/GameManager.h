#pragma once
#include "Include.h"
#include <vector>
#include <queue>
#include "FileManager.h"

class Tile;
class GameManager : public Singleton<GameManager>
{
protected:
	Chapters* m_PlayTileList;
	vector<vector<vector<vector<Tile*>>>> m_tiles;

	// element == 0 is empty cell
	vector<int> preset;
	vector<int> prepareGrid;
	queue<int> waitQueue;
	int prepareSize;
	int characterCount;

	int extraLevelUpChance; // additional level up probability

public:
	GameManager();
	virtual ~GameManager();

	void EnterBattleScene();

	vector<int>& GetPreset() { return preset; }
	void SetPreset(vector<int>& set) { preset = set; }
	int GetPresetElem(int idx) { return preset[idx]; };
	void SetPresetElem(int idx, int num);

	vector<int>& GetPrepare() { return prepareGrid; }
	int GetPrepareIdx();
	void SetPrepare(vector<int>& set);
	void AddPrepare(int num);
	void UpdatePrepare();

	queue<int>& GetWaitQueue() { return waitQueue; }

	const int GetPrepareSize() { return prepareSize; }
	const int GetCharacterCount() { return characterCount; }
	const int GetExtraLevelUpChance() { return extraLevelUpChance; }

	Vector2i PosToIdx(Vector2f pos);
	Vector2f IdxToPos(Vector2i idx);

	void SetTilesData();
	Chapters GetPlayTiles();
	Tile* GetTiles(int chap, int stage, int height, int width);

	void CreatedTiles();
	//GameManager GetGameManager() { return *this; }
};

#define GAME_MGR (GameManager::GetInstance())