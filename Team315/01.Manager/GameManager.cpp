#include "GameManager.h"

GameManager::GameManager()
	: prepareSize(0), characterCount(10)
{
	CLOG::Print3String("GameManager Create");
	prepare.resize(PREPARE_SIZE, 0);
	preset.resize(PRESET_SIZE, 0);
}

GameManager::~GameManager()
{
}

void GameManager::EnterBattleScene()
{
	prepare.assign(PREPARE_SIZE, 0);
	prepareSize = 0;
}

void GameManager::SetPresetElem(int idx, int num)
{
	preset[idx] = num;
}

void GameManager::SetPrepare(vector<int>& set)
{
	prepare = set;
	int curSize = 0;
	for (auto& cell : prepare)
	{
		if (cell != 0)
			curSize++;
		else
			break;
	}
	prepareSize = curSize;
}

void GameManager::AddPrepare(int num)
{
	bool inputInPrepare = false;
	for (auto& cell : prepare)
	{
		if (cell == 0)
		{
			inputInPrepare = true;
			cell = num;
			prepareSize++;
			break;
		}
	}
	if (!inputInPrepare)
		waitQueue.push(num);
}

void GameManager::UpdatePrepare()
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
}

Vector2i GameManager::PosToIdx(Vector2f pos)
{
	return Vector2i(
		((pos.x) / TILE_SIZE) - 2,
		((pos.y) / TILE_SIZE) - 1);
}

Vector2f GameManager::IdxToPos(Vector2i idx)
{
	return Vector2f(
		lt.x + ((float)idx.x + 0.5f) * TILE_SIZE,
		lt.y + (idx.y + 1) * TILE_SIZE
	);
}

