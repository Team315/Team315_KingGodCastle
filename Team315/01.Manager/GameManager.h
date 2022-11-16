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
	vector<int> prepare;
	queue<int> waitQueue;

public:
	GameManager();
	virtual ~GameManager();

	vector<int>& GetPrepare() { return prepare; }
	void SetPrepare(vector<int>& set) { prepare = set; }
	void AddPrepare(int num)
	{
		bool inputInPrepare = false;
		for (auto& cell : prepare)
		{
			if (cell == 0)
			{
				inputInPrepare = true;
				cell = num;
				break;
			}
		}
		if (!inputInPrepare)
			waitQueue.push(num);
	}
	void UpdatePrepare()
	{
		if (waitQueue.empty())
			return;

		for (auto& cell : prepare)
		{
			if (cell != 0)
			{
				cell = waitQueue.front();
				waitQueue.pop();
				break;
			}
		}
	};
};

#define GAME_MGR (GameManager::GetInstance())