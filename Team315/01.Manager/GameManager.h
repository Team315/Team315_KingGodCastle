#pragma once
#include "Singleton.h"
#include "Constant.h"
#include <vector>
#include <queue>

using namespace std;

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
};

#define GAME_MGR (GameManager::GetInstance())