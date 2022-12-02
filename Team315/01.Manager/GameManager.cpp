#include "GameManager.h"
#include "Map/Tile.h"
#include "GameObj.h"
#include "GameObjHeaders.h"
#include "TileBackground.h"

GameManager::GameManager()
	: battleCharacterCount(8), extraLevelUpChance(0),
	extraGradeUpChance(0), startCoin(50), // 6
	characterCost(3), itemCost(5), currentCoin(startCoin),
	hpIncreaseRate(1.6f), adIncreaseRate(1.5f), apIncreaseRate(1.6f), asIncrease(0.1f)
{
	CLOG::Print3String("GameManager Create");
	m_tiles.assign(
		CHAPTER_MAX_COUNT,
		vector<vector<vector<Tile*>>>(STAGE_MAX_COUNT,
			vector<vector<Tile*>>(GAME_TILE_HEIGHT,
				vector<Tile*>(GAME_TILE_WIDTH))));
	mainGrid = new vector<GameObj*>();

	/*
	ad		25	40	70	 120
	ap		40% 70% 120% 200%
	as		25% 40% 70%  120%
	armor	250 400 700  120
	*/

	itemStatMap[StatType::AD] = { 25, 40, 70, 120 };			// +
	itemStatMap[StatType::AP] = { 0.4f, 0.7f, 1.2f, 2.f };		// %
	itemStatMap[StatType::AS] = { 0.25f, 0.4f, 0.7f, 1.2f };	// %
	itemStatMap[StatType::HP] = { 250, 400, 700, 1200 };		// +
	//battleTracker = new BattleTracker();
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

	for (auto& character : *mainGrid)
	{
		delete character;
	}
	mainGrid->clear();
}

void GameManager::Init()
{
	currentCoin = startCoin;
	extraLevelUpChance = 0;
	extraGradeUpChance = 0;
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

void GameManager::SetBackGroundDatas()
{
	BackGroundDatas = FILE_MGR->LoadBackGroundData();
	CreatedBackGround();
}

json GameManager::GetBackGroundDatas()
{
	return BackGroundDatas;
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

void GameManager::CreatedBackGround()
{
	for (int k = 0; k < CHAPTER_MAX_COUNT; ++k)
	{
		for (int i = 0; i < TILE_HEIGHT; ++i)
		{
			for (int j = 9; j >= 0; --j)
			{
				int num = (k * (TILE_HEIGHT * TILE_WIDTH)) + (i * TILE_WIDTH) + j;

				Vector2f pos = { j * TILE_SIZE, i * TILE_SIZE };
				cout << pos.x << " " << pos.y << endl;
				TileBackground* tileBackground = new TileBackground();
				tileBackground->LoadTileBackground(BackGroundDatas[num]);
				tileBackground->SetPos(pos);
				m_TileBackground.push_back(tileBackground);
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
		character = new Aramis();
	else if (!name.compare("Arveron") || num == 1)
		character = new Arveron();
	else if (!name.compare("Daniel") || num == 2)
		character = new Daniel();
	else if (!name.compare("Evan") || num == 3)
		character = new Evan();
	else if (!name.compare("LeonHeart") || num == 4)
		character = new LeonHeart();
	else if (!name.compare("Pria") || num == 5)
		character = new Pria();
	else if (!name.compare("Shelda") || num == 6)
		character = new Shelda();

	return character;
}

Character* GameManager::SpawnPlayer(bool random, bool drawingOnBattle)
{
	return SpawnPlayer("", random, drawingOnBattle);
}

Item* GameManager::SpawnItem(int typeIdx)
{
	Item* item = nullptr;
	// 0 ~ 8, 2/9 armor, bow, staff, sword / 1/9 book
	ItemType type = typeIdx == -1 ?
		(ItemType) (Utils::RandomRange(0, 2 * ITEM_COUNT) / 2) :
		(ItemType) (typeIdx);

	switch (type)
	{
	case ItemType::Armor:
		item = new Armor();
		break;
	case ItemType::Bow:
		item = new Bow();
		break;
	case ItemType::Staff:
		item = new Staff();
		break;
	case ItemType::Sword:
	default:
		item = new Sword();
		break;
	/*case ItemType::Book:
		item = new Book();
		break;*/
	}
	return item;
}

void GameManager::Reset()
{
	mainGrid->assign(GAME_TILE_HEIGHT * GAME_TILE_WIDTH, nullptr);
}

void GameManager::SetCharacterDatas()
{
	characterDatas = FILE_MGR->LoadCharacterData();
}

json GameManager::GetCharacterData(string name)
{
	return characterDatas[name];
}

void GameManager::RemoveFromMainGrid(GameObj* gameObj)
{
	for (auto& cell : *mainGrid)
	{
		if (cell != nullptr && (cell->GetObjId() == gameObj->GetObjId()))
		{
			cell = nullptr;
			return;
		}
	}
}

float GameManager::GetItemStatMapElem(StatType statType, int grade)
{
	if (statType == StatType::None)
		return -1.f;
	return (itemStatMap[statType])[grade];
}

// Battle Tracker
//BattleTracker::BattleTracker()
//{
//}
//
//BattleTracker::~BattleTracker()
//{
//}
//
//void BattleTracker::SetDatas()
//{
//	vector<GameObj*>& mgref = GAME_MGR->GetMainGridRef();
//	for (auto& character : mgref)
//	{
//		if (character != nullptr && !character->GetType().compare("Player"))
//		{
//			datas.push_back(character);
//		}
//	}
//}
//
//BattleTracker *&GameManager::GetTracker()
//{
//	return battleTracker;
//}