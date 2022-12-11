#include "GameManager.h"
#include "Map/Tile.h"
#include "GameObj.h"
#include "GameObjHeaders.h"
#include "TileBackground.h"
#include "Item/Item.h"
#include "rapidcsv.h"

void DmgUIOnCreate(DamageText* dmgUI)
{
	dmgUI->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	dmgUI->SetOutlineColor(Color::Black);
	dmgUI->SetOutlineThickness(2.0f);
}

void RangePreviewOnCreate(RangePreview* rangePreview)
{
	rangePreview->SetActive(false);
}

GameManager::GameManager()
	: m_PlayTileList(nullptr), playingBattle(false),
	curChapIdx(0), curStageIdx(0),
	battleCharacterCount(3), extraLevelUpSummon(15),
	extraLevelUpCombinate(30), //extraGradeUpChance(20),
	startCoin(50), stageClearCoin(6),
	characterCost(3), itemCost(5), expansionCost(5), expansionCount(0),
	hpIncreaseRate(1.6f), adIncreaseRate(1.5f),
	apIncreaseRate(1.6f), asIncrease(0.1f),
	manaPerAttack(15.f), manaPerHit(5.f), itemDropProbability(10)
{
	CLOG::Print3String("GameManager Create");
	
	m_tiles.assign(
		CHAPTER_MAX_COUNT,
		vector<vector<vector<Tile*>>>(STAGE_MAX_COUNT,
			vector<vector<Tile*>>(GAME_TILE_HEIGHT,
				vector<Tile*>(GAME_TILE_WIDTH))));
	mainGrid = new vector<GameObj*>();
	battleTracker = new BattleTracker();
	damageUI.OnCreate = DmgUIOnCreate;
	damageUI.Init();
	rangePreview.OnCreate = RangePreviewOnCreate;
	rangePreview.Init(200);
	GMInit();
	GetBalanceDatas();
	PrintDevKey();
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

void GameManager::GMInit()
{
	json initSetting = FILE_MGR->LoadByFilePath("json/InitSetting.json");
	json gameSetting = initSetting["InitialGameSetting"];

	battleCharacterCount = gameSetting["BattleCharacterCount"];
	extraLevelUpSummon = gameSetting["ExtraLevelUpSummon"];
	extraLevelUpCombinate = gameSetting["ExtraLevelUpCombinate"];
	//extraGradeUpChance = gameSetting["ExtraGradeUpChance"];
	startCoin = gameSetting["StartCoin"];
	stageClearCoin = gameSetting["StageClearCoin"];
	characterCost = gameSetting["CharacterCost"];
	expansionCost = gameSetting["ExpansionCost"];
	itemCost = gameSetting["ItemCost"];
	manaPerAttack = gameSetting["ManaPerAttack"];
	manaPerHit = gameSetting["ManaPerHit"];
	itemDropProbability = gameSetting["ItemDropProbability"];

	cout << "부대 배치 제한: " << battleCharacterCount << endl;
	cout << "소환시 2업 확률: " << extraLevelUpSummon << endl;
	cout << "합성시 2업 확률: " << extraLevelUpCombinate << endl;
	//cout << "아이템 2업 확률(X): " << extraGradeUpChance << endl;
	cout << "게임 시작시 코인: " << startCoin << endl;
	cout << "스테이지 클리어시 보상 코인: " << stageClearCoin << endl;
	cout << "캐릭터 뽑기 가격: " << characterCost << endl;
	cout << "부대 확장 초기 가격: " << expansionCost << endl;
	cout << "1티어 아이템 가격: " << itemCost << endl;
	cout << "공격시 마나 획득: " << manaPerAttack << endl;
	cout << "피격시 마나 획득: " << manaPerHit << endl;
	cout << "아이템 드랍 확률(%): " << itemDropProbability << endl;

	json statIncreaseRate = initSetting["LevelUpStatIncreaseRate"];
	adIncreaseRate = statIncreaseRate["AdIncreaseRate"];
	apIncreaseRate = statIncreaseRate["ApIncreaseRate"];
	asIncrease = statIncreaseRate["AsIncrease"];
	hpIncreaseRate = statIncreaseRate["HpIncreaseRate"];
	hpIncreaseRate += 1.f;
	adIncreaseRate += 1.f;
	apIncreaseRate += 1.f;

	cout << "캐릭터 강화 시 체력 상승률: " << hpIncreaseRate << endl;
	cout << "캐릭터 강화 시 공격 상승률: " << adIncreaseRate << endl;
	cout << "캐릭터 강화 시 주문 상승률: " << apIncreaseRate << endl;
	cout << "캐릭터 강화 시 공속 상승치: " << asIncrease << endl;

	json ItemStats = initSetting["ItemStat"];
	itemStatMap.insert({ StatType::HP, ItemStats["Armor"] });
	itemStatMap.insert({ StatType::AP, ItemStats["Staff"] });
	itemStatMap.insert({ StatType::AS, ItemStats["Bow"]});
	itemStatMap.insert({ StatType::AD, ItemStats["Sword"] });

	/*
	ad		25	40	70	 120
	ap		40% 70% 120% 200%
	as		25% 40% 70%  120%
	armor	250 400 700  120
	*/

	//itemStatMap[StatType::AD] = { 25, 40, 70, 120 };			// +
	//itemStatMap[StatType::AP] = { 0.4f, 0.7f, 1.2f, 2.f };	// %
	//itemStatMap[StatType::AS] = { 0.25f, 0.4f, 0.7f, 1.2f };	// %
	//itemStatMap[StatType::HP] = { 250, 400, 700, 1200 };		// +
}

void GameManager::GMReset()
{
	GMInit();
	playingBattle = false;
	currentCoin = startCoin;
	altarData.Init();
	expansionCount = 0;
}

void GameManager::PrintDevKey()
{
	cout << "--- 개발용 치트 키 현황 ---" << endl;
	cout << "ESC - 타이틀 씬으로" << endl;
	cout << "숫자1 - 돈 +100" << endl;
	cout << "숫자2 - 랜덤 1티어 아이템" << endl;
	cout << "숫자3 - 랜덤 2티어 아이템" << endl;
	cout << "숫자4 - 랜덤 3티어 아이템" << endl;
	cout << "F4 - 전투 강제 종료-> 다음 스테이지" << endl;
	cout << "F5 - 다음 스테이지" << endl;
	cout << "F6 - 이전 스테이지" << endl;
	cout << "F7 - Hitbox 스위치" << endl;
	cout << "F8 - 게임 맵 배치 현황" << endl;
	cout << "F9 - 전투 배치, 뽑기 창 현황" << endl;
	cout << "슷자5 - 다음 챕터(+10 스테이지)" << endl;
	cout << "슷자6 - 이전 챕터(-10 스테이지)" << endl;
	cout << "Y - 적 모두 1성 증가" << endl;
	cout << "U - 적 모두 갑옷 1성 주기" << endl;
	cout << "I - 적 모두 칼 1성 주기" << endl;
	cout << "O - 적 모두 스태프 1성 주기" << endl;
	cout << "P - 적 모두 활 1성 주기" << endl;
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
	backGroundDatas = FILE_MGR->LoadByFilePath("json/BackGroundData.json");
	CreatedBackGround();
}

json GameManager::GetBackGroundDatas()
{
	return backGroundDatas;
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
	int n = 0;

	for (int k = 0; k < CHAPTER_MAX_COUNT; ++k)
	{
		for (int i = 0; i < TILE_HEIGHT; ++i)
		{
			//for (int j = 0; j < TILE_WIDTH; ++j)
			for (int j = 9; j >= 0; --j)
			{
				int num = (k * (TILE_HEIGHT * TILE_WIDTH)) + (i * TILE_WIDTH) + j;

				Vector2f pos = { j * TILE_SIZE, i * TILE_SIZE };
				TileBackground* tileBackground = new TileBackground();
				tileBackground->LoadTileBackground(backGroundDatas[n]);
				tileBackground->SetPos(pos);
				m_TileBackground.push_back(tileBackground);
				++n;
			}
		}
	}
	
}

Character* GameManager::SpawnMonster(string name, int grade)
{
	Character* character = nullptr;
	if (!name.compare("Goblin00"))
		character = new Goblin00(false, false, grade);
	else if (!name.compare("Goblin01"))
		character = new Goblin01(false, false, grade);
	else if (!name.compare("Goblin02"))
		character = new Goblin02(false, false, grade);
	else if (!name.compare("Goblin03"))
		character = new Goblin03(false, false, grade);
	else if (!name.compare("Goblin04"))

		character = new Goblin04(false, false, grade);
	else if (!name.compare("Thief00"))
		character = new Thief00(false, false, grade);
	else if (!name.compare("Thief01"))
		character = new Thief01(false, false, grade);
	else if (!name.compare("Thief02"))
		character = new Thief02(false, false, grade);
	else if (!name.compare("Thief03"))
		character = new Thief03(false, false, grade);
	else if (!name.compare("Thief04"))
		character = new Thief04(false, false, grade);

	else if (!name.compare("Slime00"))
		character = new Slime00(false, false, grade);
	else if (!name.compare("Slime01"))
		character = new Slime01(false, false, grade);
	else if (!name.compare("Slime02"))
		character = new Slime02(false, false, grade);
	else if (!name.compare("Slime03"))
		character = new Slime03(false, false, grade);
	else if (!name.compare("Slime04"))
		character = new Slime04(false, false, grade);
	else if (!name.compare("Slime05"))
		character = new Slime05(false, false, grade);
	return character;
}

Character* GameManager::SpawnPlayer(string name, bool random)
{
	Character* character = nullptr;
	int num = random ? Utils::RandomRange(0, CHARACTER_COUNT) : -1;
	//int num = 0;

	if (!name.compare("Aramis") || num == 0)
		character = new Aramis(false, true);
	else if (!name.compare("Arveron") || num == 1)
		character = new Arveron(false, true);
	else if (!name.compare("Daniel") || num == 2)
		character = new Daniel(false, true);
	else if (!name.compare("Evan") || num == 3)
		character = new Evan(false, true);
	else if (!name.compare("LeonHeart") || num == 4)
		character = new LeonHeart(false, true);
	else if (!name.compare("Pria") || num == 5)
		character = new Pria(false, true);
	else if (!name.compare("Shelda") || num == 6)
		character = new Shelda(false, true);

	return character;
}

Character* GameManager::SpawnPlayer(bool random)
{
	return SpawnPlayer("", random);
}

Item* GameManager::SpawnItem(int tier, int typeIdx)
{
	Item* item = nullptr;
	// 0 ~ 4, 1/5 armor, bow, staff, sword, book
	ItemType type = typeIdx == -1 ?
		(ItemType) (Utils::RandomRange(0, ITEM_COUNT)) :
		(ItemType) (typeIdx);

	switch (type)
	{
	case ItemType::Armor:
		item = new Armor(tier);
		break;
	case ItemType::Bow:
		item = new Bow(tier);
		break;
	case ItemType::Staff:
		item = new Staff(tier);
		break;
	case ItemType::Sword:
	default:
		item = new Sword(tier);
		break;
	case ItemType::Book:
		item = new Book(tier);
		break;
	}
	return item;
}

void GameManager::MainGridReset()
{
	mainGrid->assign(GAME_TILE_HEIGHT * GAME_TILE_WIDTH, nullptr);
}

void GameManager::SetCharacterDatas()
{
	characterDatas = FILE_MGR->LoadByFilePath("json/CharacterData.json");
}

json GameManager::GetCharacterData(string name)
{
	return characterDatas[name];
}

GameObj* GameManager::GetGameObjInMainGrid(Vector2i coord)
{
	if (coord.x < 0 || coord.x >= GAME_TILE_WIDTH || coord.y < 0 || coord.y >= GAME_TILE_HEIGHT)
		return nullptr;
	return (*mainGrid)[coord.x + coord.y * GAME_TILE_WIDTH];
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

Item* GameManager::CombineItem(Item* obj1, Item* obj2)
{
	// return null is can't combine
	if (!obj1->GetName().compare("Book") ||
		!obj2->GetName().compare("Book"))
	{
		return nullptr;
	}

	Item* newItem = nullptr;
	if (obj1->GetGrade() != TIER_MAX - 1 && 
		!obj1->GetName().compare(obj2->GetName()) &&
		obj1->GetGrade() == obj2->GetGrade())
	{
		ItemType it = obj1->GetItemType();
		switch (it)
		{
		case ItemType::Armor:
			newItem = new Armor(obj1->GetGrade() + 1);
			break;
		case ItemType::Bow:
			newItem = new Bow(obj1->GetGrade() + 1);
			break;
		case ItemType::Staff:
			newItem = new Staff(obj1->GetGrade() + 1);
			break;
		case ItemType::Sword:
			newItem = new Sword(obj1->GetGrade() + 1);
			break;
		default:
			break;
		}
		return newItem;
	}
	return nullptr;
}

Item* GameManager::DropItem(Character* monster)
{
	if (monster->GetType().compare("Monster"))
		return nullptr;

	bool percent = Utils::RandomRange(0, 100) < itemDropProbability;
	Item* drop = nullptr;
	if (percent)
	{
		int tier = (monster->GetStarNumber() - 1) / 2;
		drop = SpawnItem(tier);
		drop->SetPos(monster->GetPos());
		drops.push_back(drop);
	}
	return drop;
}

void GameManager::GetBalanceDatas()
{
	string filePath = "tables/WaveRewardTable.csv";
	int pathSize = filePath.size();
	for (int i = 0; i < pathSize; i++)
	{
		rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, -1));

		auto key = doc.GetColumn<string>(0);
		auto chap = doc.GetColumn<int>(1);
		auto stage = doc.GetColumn<int>(2);
		auto exp = doc.GetColumn<int>(3);
		auto forge = doc.GetColumn<int>(4);
		auto power = doc.GetColumn<int>(5);

		for (int j = 0; j < doc.GetRowCount(); j++)
		{
			waveRewardMap.insert({ key[j], WaveReward(chap[j], stage[j], exp[j], forge[j], power[j])});
		}
	}
}

// Battle Tracker
BattleTracker::BattleTracker()
	: trackerMode(true)
{
}

BattleTracker::~BattleTracker()
{
}


void BattleTracker::SetDatas()
{
	datas.clear();
	vector<GameObj*>& mgref = GAME_MGR->GetMainGridRef();
	for (auto& character : mgref)
	{
		if (character != nullptr && !character->GetType().compare("Player"))
		{
			datas.push_back(dynamic_cast<Character*>(character));
		}
	}
}

bool ascendGiven(DamageData a, DamageData b)
{
	return (a.givenAD + a.givenAP) > (b.givenAD + b.givenAP);
}

bool ascendTaken(DamageData a, DamageData b)
{
	return (a.takenAD + a.takenAP) > (b.takenAD + b.takenAP);
}

void BattleTracker::UpdateData(Character* character, float damage,
	bool givenOrTaken, bool dmgType)
{
	for (auto& data : datas)
	{
		if (data.character->GetObjId() == character->GetObjId())
		{
			if (givenOrTaken)
			{
				(dmgType) ?
					data.givenAD += damage :
					data.givenAP += damage;
			}
			else
			{
				(dmgType) ? 
					data.takenAD += damage :
					data.takenAP += damage;
			}
			break;
		}
	}
	DataSort();
}

void BattleTracker::PrintAllData()
{
	for (auto& data : datas)
	{
		cout << data.character->GetName() << data.character->GetStarNumber() << endl;
		cout << "givenAD: " << data.givenAD << endl;
		cout << "givenAP: " << data.givenAP << endl;
		cout << "givenTotal: " << data.givenAD + data.givenAP << endl;
		cout << "takenAD: " << data.takenAD << endl;
		cout << "takenAP: " << data.takenAP << endl;
		cout << "takenTotal: " << data.takenAD + data.takenAP << endl;
	}
}

void BattleTracker::DataSort()
{
	if (trackerMode)
		sort(datas.begin(), datas.end(), ascendGiven);
	else
		sort(datas.begin(), datas.end(), ascendTaken);
}