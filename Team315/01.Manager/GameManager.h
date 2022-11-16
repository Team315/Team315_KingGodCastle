#pragma once
#include "Include.h"
#include <vector>
#include <queue>

class GameManager : public Singleton<GameManager>
{
protected:
	// element == 0 is empty cell
	vector<int> preset;
	vector<int> prepare;
	queue<int> waitQueue;
	int prepareSize;
	int characterCount;

public:
	GameManager();
	virtual ~GameManager();

	void EnterBattleScene();

	vector<int>& GetPreset() { return preset; }
	void SetPreset(vector<int>& set) { preset = set; }
	int GetPresetElem(int idx) { return preset[idx]; };
	void SetPresetElem(int idx, int num);

	vector<int>& GetPrepare() { return prepare; }
	int GetPrepareIdx();
	void SetPrepare(vector<int>& set);
	void AddPrepare(int num);
	void UpdatePrepare();

	queue<int>& GetWaitQueue() { return waitQueue; }

	const int GetPrepareSize() { return prepareSize; }
	const int GetCharacterCount() { return characterCount; }

	Vector2i PosToIdx(Vector2f pos);
	Vector2f IdxToPos(Vector2i idx);
	Vector2f SnapToCoord(Vector2f pos);
};

#define GAME_MGR (GameManager::GetInstance())