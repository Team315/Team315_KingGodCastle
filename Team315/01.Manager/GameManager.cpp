#include "GameManager.h"
#include "Map/Tile.h"

GameManager::GameManager()
	: prepareSize(0), characterCount(10), extraLevelUpChance(30)
{
	CLOG::Print3String("GameManager Create");
	prepareGrid.resize(PREPARE_SIZE, 0);
	preset.resize(PRESET_SIZE, 0);
	m_tiles.assign(CHAPTER_MAX_COUNT, vector<vector<vector<Tile*>>>(STAGE_MAX_COUNT, vector<vector<Tile*>>(GAME_TILE_HEIGHT, vector<Tile*>(GAME_TILE_WIDTH))));
	
	//vector<Tile*> f(14, vector<Tile*>(0))
}

GameManager::~GameManager()
{
}

void GameManager::EnterBattleScene()
{
	prepareGrid.assign(PREPARE_SIZE, 0);
	prepareSize = 0;
}

void GameManager::SetPresetElem(int idx, int num)
{
	preset[idx] = num;
}

int GameManager::GetPrepareIdx()
{
	for (int idx = 0; idx < PREPARE_SIZE; idx++)
	{
		if (prepareGrid[idx] == 0)
			return idx;
	}
	return -1; // fail
}

void GameManager::SetPrepare(vector<int>& set)
{
	prepareGrid = set;
	int curSize = 0;
	for (auto& cell : prepareGrid)
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
	for (auto& cell : prepareGrid)
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

	int queueFront = 0;
	for (auto& cell : prepareGrid)
	{
		if (cell != 0)
		{
			queueFront = waitQueue.front();
			waitQueue.pop();
			break;
		}
	}
	AddPrepare(queueFront);
}

Vector2i GameManager::PosToIdx(Vector2f pos)
{
	return Vector2i(
		(pos.x / TILE_SIZE) - 2,
		(pos.y / TILE_SIZE) - 1);
}

Vector2f GameManager::IdxToPos(Vector2i idx)
{
	return Vector2f(
		(idx.x + 2) * TILE_SIZE,
		(idx.y + 1) * TILE_SIZE
	);
}

void GameManager::SetTilesData()
{
	FileManager* file = new FileManager();

	m_PlayTileList = new Chapters();

	file->LoadTileData(*m_PlayTileList);

	delete file;
}

Chapters GameManager::GetPlayTiles()
{
	return *m_PlayTileList;
}
Tile* GameManager::GetTiles(int chap, int stage, int height, int width)
{
	return m_tiles[chap][stage][height][width];
}

void GameManager::CreatedTiles()
{
	for (int i = 0; i < m_PlayTileList->data.size(); ++i)
	{
		for (int j = 0; j < m_PlayTileList->data[i].size(); ++j)
		{
			for (int k = 0; k < m_PlayTileList->data[i][j].size(); ++k)
			{
				for (int l = 0; l < m_PlayTileList->data[i][j][k].size(); ++l)
				{
					Tile* tile = new Tile();
					tile->CreateTile(m_PlayTileList->data[i][j][k][l]);
					m_tiles[i][j][k][l]= tile;
				}
			}
		}
	}
}