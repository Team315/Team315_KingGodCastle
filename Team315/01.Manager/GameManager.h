#pragma once
#include "Include.h"
#include <vector>
#include <queue>
#include "FileManager.h"

class Character;
class Tile;
class GameManager : public Singleton<GameManager>
{
protected:
	Chapters* m_PlayTileList;
	vector<vector<vector<vector<Tile*>>>> m_tiles;

	json characterDatas;

	vector<Character*> presetC;

	// additional level up probability
	int extraLevelUpChance;
	int battleCharacterCount;

public:
	GameManager();
	virtual ~GameManager();

	void EnterBattleScene();

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
};

#define GAME_MGR (GameManager::GetInstance())