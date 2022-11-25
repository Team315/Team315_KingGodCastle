#include "GameManager.h"
#include "Map/Tile.h"
#include "Character.h"
#include "CharacterHeaders.h"

GameManager::GameManager()
	: battleCharacterCount(10), extraLevelUpChance(0), mainGridRef(presetC)
{
	CLOG::Print3String("GameManager Create");
	m_tiles.assign(
		CHAPTER_MAX_COUNT,
		vector<vector<vector<Tile*>>>(STAGE_MAX_COUNT,
			vector<vector<Tile*>>(GAME_TILE_HEIGHT,
				vector<Tile*>(GAME_TILE_WIDTH))));
}

GameManager::~GameManager()
{
	for (auto& chapter : m_tiles)
	{
		for (auto& stage : chapter)
		{
			for (auto& row : stage)
			{
				for (auto& tile : row)
				{
					delete tile;
				}
				row.clear();
			}
			stage.clear();
		}
		chapter.clear();
	}
	m_tiles.clear();
}

void GameManager::EnterBattleScene()
{
	/*prepareGrid.assign(PREPARE_SIZE, 0);
	prepareSize = 0;*/
}

//void GameManager::SetPresetElem(int idx, int num)
//{
//	preset[idx] = num;
//}
//
//int GameManager::GetPrepareIdx()
//{
//	for (int idx = 0; idx < PREPARE_SIZE; idx++)
//	{
//		if (prepareGrid[idx] == 0)
//			return idx;
//	}
//	return -1; // fail
//}
//
//void GameManager::SetPrepare(vector<int>& set)
//{
//	prepareGrid = set;
//	int curSize = 0;
//	for (auto& cell : prepareGrid)
//	{
//		if (cell != 0)
//			curSize++;
//		else
//			break;
//	}
//	prepareSize = curSize;
//}
//
//void GameManager::AddPrepare(int num)
//{
//	bool inputInPrepare = false;
//	for (auto& cell : prepareGrid)
//	{
//		if (cell == 0)
//		{
//			inputInPrepare = true;
//			cell = num;
//			prepareSize++;
//			break;
//		}
//	}
//	if (!inputInPrepare)
//		waitQueue.push(num);
//}
//
//void GameManager::UpdatePrepare()
//{
//	if (waitQueue.empty())
//		return;
//
//	int queueFront = 0;
//	for (auto& cell : prepareGrid)
//	{
//		if (cell != 0)
//		{
//			queueFront = waitQueue.front();
//			waitQueue.pop();
//			break;
//		}
//	}
//	AddPrepare(queueFront);
//}

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

Vector2f GameManager::SnapToCoord(Vector2f pos)
{
	return IdxToPos(PosToIdx(pos));
}

void GameManager::SetTilesData()
{
	m_PlayTileList = new Chapters();
	FILE_MGR->LoadTileData(*m_PlayTileList);
}

Tile* GameManager::GetTile(int chap, int stage, int height, int width)
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
					m_tiles[i][j][k][l] = tile;
				}
			}
		}
	}
}

Character* GameManager::SpawnMonster(string name, int grade)
{
	Character* character = nullptr;
	if (!name.compare("Goblin00"))
		character = new Goblin00(grade);
	else if (!name.compare("Goblin01"))
		character = new Goblin01(grade);
	else if (!name.compare("Goblin02"))
		character = new Goblin02(grade);
	else if (!name.compare("Goblin03"))
		character = new Goblin03(grade);
	else if (!name.compare("Goblin04"))

		character = new Goblin04(grade);
	else if (!name.compare("Thief00"))
		character = new Thief00(grade);
	else if (!name.compare("Thief01"))
		character = new Thief01(grade);
	else if (!name.compare("Thief02"))
		character = new Thief02(grade);
	else if (!name.compare("Thief03"))
		character = new Thief03(grade);
	else if (!name.compare("Thief04"))
		character = new Thief04(grade);

	else if (!name.compare("Slime00"))
		character = new Slime00(grade);
	else if (!name.compare("Slime01"))
		character = new Slime01(grade);
	else if (!name.compare("Slime02"))
		character = new Slime02(grade);
	else if (!name.compare("Slime03"))
		character = new Slime03(grade);
	else if (!name.compare("Slime04"))
		character = new Slime04(grade);
	else if (!name.compare("Slime05"))
		character = new Slime05(grade);
	return character;
}

Character* GameManager::SpawnPlayer(string name, bool random, bool drawingOnBattle)
{
	Character* character = nullptr;
	int num = random ? Utils::RandomRange(0, CHARACTER_COUNT) : -1;

	if (!name.compare("Aramis") || num == 0)
		character = new Shelda();
	else if (!name.compare("Arveron") || num == 1)
		character = new Shelda();
	else if (!name.compare("Daniel") || num == 2)
		character = new Shelda();
	else if (!name.compare("Evan") || num == 3)
		character = new Shelda();
	else if (!name.compare("LeonHeart") || num == 4)
		character = new Shelda();
	else if (!name.compare("Pria") || num == 5)
		character = new Shelda();
	else if (!name.compare("Shelda") || num == 6)
		character = new Shelda();
	character->SetDrawingOnBattle(drawingOnBattle);
	return character;
}

Character* GameManager::SpawnPlayer(bool random, bool drawingOnBattle)
{
	return SpawnPlayer("", random, drawingOnBattle);
}

void GameManager::SetCharacterDatas()
{
	characterDatas = FILE_MGR->LoadCharacterData();
}

json GameManager::GetCharacterData(string name)
{
	return characterDatas[name];
}