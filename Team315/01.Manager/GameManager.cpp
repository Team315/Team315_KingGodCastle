#include "GameManager.h"
#include "Map/Tile.h"
#include "GameObj.h"
#include "GameObjHeaders.h"
#include "TileBackground.h"
#include "Item/Item.h"
#include "rapidcsv.h"
#include "CSVWriter.h"

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
	manaPerAttack(15.f), manaPerDamage(5.f), itemDropProbability(10),
	accountExpLimit(6), cumulativeExp(0), oneTimePowerUp(nullptr)
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
	PrintDevInfo();
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
	clearCoinIncrease = gameSetting["ClearCoinIncrease"];
	clearCoinIncreaseTerm = gameSetting["ClearCoinIncreaseTerm"];
	bossStageClearBonus = gameSetting["BossStageClearBonus"];
	characterCost = gameSetting["CharacterCost"];
	expansionCost = gameSetting["ExpansionCost"];
	itemCost = gameSetting["ItemCost"];
	manaPerAttack = gameSetting["ManaPerAttack"];
	manaPerDamage = gameSetting["ManaPerHit"];
	itemDropProbability = gameSetting["ItemDropProbability"];
	accountExpLimit = gameSetting["AccountExpLimit"];

	json statIncreaseRate = initSetting["LevelUpStatIncreaseRate"];
	adIncreaseRate = statIncreaseRate["AdIncreaseRate"];
	apIncreaseRate = statIncreaseRate["ApIncreaseRate"];
	asIncrease = statIncreaseRate["AsIncrease"];
	hpIncreaseRate = statIncreaseRate["HpIncreaseRate"];
	hpIncreaseRate += 1.f;
	adIncreaseRate += 1.f;
	apIncreaseRate += 1.f;

	json ItemStats = initSetting["ItemStat"];
	itemStatMap.insert({ StatType::HP, ItemStats["Armor"] });
	itemStatMap.insert({ StatType::AP, ItemStats["Staff"] });
	itemStatMap.insert({ StatType::AS, ItemStats["Bow"] });
	itemStatMap.insert({ StatType::AD, ItemStats["Sword"] });

	{
		string accInfoPath = "data/accInfo.csv";

		rapidcsv::Document infoDoc(accInfoPath, rapidcsv::LabelParams(0, -1));
		auto level = infoDoc.GetColumn<int>(0);
		auto exp = infoDoc.GetColumn<int>(1);
		accountInfo.Load(level[0], exp[0]);
		accountInfo.UpdateLevel(accountExpLimit);
		infoDoc.Clear();
	}

	{
		string altarDataPath = "data/altarPointData.csv";

		rapidcsv::Document altarDoc(altarDataPath, rapidcsv::LabelParams(0, -1));
		auto mana = altarDoc.GetColumn<int>(0);
		auto silver = altarDoc.GetColumn<int>(1);
		auto physical = altarDoc.GetColumn<int>(2);
		auto enforce = altarDoc.GetColumn<int>(3);
		altarData.Init(mana[0], silver[0], physical[0], enforce[0]);
		altarDoc.Clear();
	}

	{
		string rewardPath = "data/WaveRewardTable.csv";

		rapidcsv::Document rewardDoc(rewardPath, rapidcsv::LabelParams(0, -1));
		auto wave = rewardDoc.GetColumn<string>(0);
		auto exp = rewardDoc.GetColumn<int>(1);
		auto forge = rewardDoc.GetColumn<int>(2);
		auto power = rewardDoc.GetColumn<int>(3);

		for (int j = 0; j < rewardDoc.GetRowCount(); j++)
		{
			waveRewardMap.insert({ wave[j], WaveReward(exp[j], forge[j], power[j]) });
		}
		rewardDoc.Clear();
	}
	LoadAltarEffectFromTable();

	{
		string powerUpPath = "data/PowerUpData.csv";

		rapidcsv::Document powerUpDoc(powerUpPath, rapidcsv::LabelParams(-1, 0));
		auto tier1 = powerUpDoc.GetRow<string>(0);
		auto tier2 = powerUpDoc.GetRow<string>(1);
		auto tier3 = powerUpDoc.GetRow<string>(2);
		auto rows = powerUpDoc.GetRowNames();
		powerUpStringMap.insert({ rows[0], tier1 });
		powerUpStringMap.insert({ rows[1], tier2 });
		powerUpStringMap.insert({ rows[2], tier3 });

		powerUpDoc.Clear();
	}
}

void GameManager::GMReset()
{
	GMInit();
	playingBattle = false;
	currentCoin = startCoin + altarData.startCoin;
	expansionCount = 0;
	cumulativeExp = 0;
	oneTimePowerUp = nullptr;
	standingPowerUps.clear();
	for (auto& drop : drops)
	{
		if (drop != nullptr)
			delete drop;
	}
	drops.clear();

	// panelSkill = ?
}

void GameManager::GameEnd()
{
	string accInfoPath = "data/accInfo.csv";

	CSVWriter csv(",");
	csv.newRow() << "level" << "exp";
	csv.newRow() << accountInfo.level << accountInfo.exp;

	csv.writeToFile(accInfoPath);
}

void GameManager::SaveAltarData(int mana, int silver, int physical, int enforce)
{
	// altar point save
	string accInfoPath = "data/altarPointData.csv";

	CSVWriter csv(",");
	csv.newRow() << "mana" << "silver" << "physical" << "enforce";
	csv.newRow() << mana << silver << physical << enforce;
	altarData.Init(mana, silver, physical, enforce);

	csv.writeToFile(accInfoPath);
}

void GameManager::PrintDevInfo()
{
	cout << "부대 배치 제한: " << battleCharacterCount << endl;
	cout << "소환시 2업 확률(%): " << extraLevelUpSummon << endl;
	cout << "합성시 2업 확률(%): " << extraLevelUpCombinate << endl;
	//cout << "아이템 2업 확률(X): " << extraGradeUpChance << endl;
	cout << "게임 시작시 코인: " << startCoin << endl;
	cout << "스테이지 보상 코인: " << stageClearCoin << endl;
	cout << "스테이지 보상 코인 증가량: " << clearCoinIncrease << endl;
	cout << "스테이지 보상 코인 증가 간격(턴): " << clearCoinIncreaseTerm << endl;
	cout << "보스 스테이지 보너스 코인: " << bossStageClearBonus << endl;
	cout << "캐릭터 뽑기 가격: " << characterCost << endl;
	cout << "부대 확장 초기 가격: " << expansionCost << endl;
	cout << "1티어 아이템 가격: " << itemCost << endl;
	cout << "공격시 마나 획득: " << manaPerAttack << endl;
	cout << "피격시 마나 획득: " << manaPerDamage << endl;
	cout << "아이템 드랍 확률(%): " << itemDropProbability << endl;
	cout << "레벨당 필요 경험치량: " << accountExpLimit << endl;
	cout << "캐릭터 강화 시 체력 상승률: " << hpIncreaseRate << endl;
	cout << "캐릭터 강화 시 공격 상승률: " << adIncreaseRate << endl;
	cout << "캐릭터 강화 시 주문 상승률: " << apIncreaseRate << endl;
	cout << "캐릭터 강화 시 공속 상승치: " << asIncrease << endl;

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

	cout << "계정 레벨: " << accountInfo.level << endl;
	cout << "계정 expr: " << accountInfo.exp << endl;
	cout << "마나 제단 point: " << altarData.mana << endl;
	cout << "은화 제단 point: " << altarData.silver << endl;
	cout << "신체 제단 point: " << altarData.physical << endl;
	cout << "강화 제단 point: " << altarData.enforce << endl;
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

Character* GameManager::SpawnPlayer(int grade, bool random, int idx)
{
	Character* character = nullptr;
	int num = random ? Utils::RandomRange(0, CHARACTER_COUNT) : idx;
	//int num = 3;

	if (num == 0)
		character = new Aramis(false, true, grade);
	else if (num == 1)
		character = new Arveron(false, true, grade);
	else if (num == 2)
		character = new Daniel(false, true, grade);
	else if (num == 3)
		character = new Evan(false, true, grade);
	else if (num == 4)
		character = new LeonHeart(false, true, grade);
	else if (num == 5)
		character = new Pria(false, true, grade);
	else if (num == 6)
		character = new Shelda(false, true, grade);

	return character;
}

Item* GameManager::SpawnItem(int tier, int typeIdx)
{
	Item* item = nullptr;
	// 0 ~ 4, 1/5 armor, bow, staff, sword, book
	ItemType type = typeIdx == -1 ?
		(ItemType)(Utils::RandomRange(0, ITEM_COUNT)) :
		(ItemType)(typeIdx);

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

GameObj* GameManager::GeneratePowerUp(PowerUpTypes puType, int tier)
{
	GameObj* power = nullptr;

	switch (puType)
	{
	case PowerUpTypes::Comrade:
		power = new Comrade(tier, puType);
		break;
	case PowerUpTypes::ContractWithTheDevil:
		power = new ContractWithTheDevil(tier, puType);
		break;
	case PowerUpTypes::CounterAttack:
		power = new CounterAttack(tier, puType);
		break;
	case PowerUpTypes::DogFight:
		power = new DogFight(tier, puType);
		break;
	case PowerUpTypes::ExecutionerSoul:
		power = new ExecutionerSoul(tier, puType);
		break;
	case PowerUpTypes::HeroOfSalvation:
		power = new HeroOfSalvation(tier, puType);
		break;
	case PowerUpTypes::Meditation:
		power = new Meditation(tier, puType);
		break;
	case PowerUpTypes::Nobility:
		power = new Nobility(tier, puType);
		break;
	case PowerUpTypes::QuickHand:
		power = new QuickHand(tier, puType);
		break;
	case PowerUpTypes::RuneShield:
		power = new RuneShield(tier, puType);
		break;
	case PowerUpTypes::Vampire:
		power = new Vampire(tier, puType);
		break;
	case PowerUpTypes::WarriorsHeart:
		power = new WarriorsHeart(tier, puType);
		break;
	case PowerUpTypes::WeAreTheOne:
		power = new WeAreTheOne(tier, puType);
		break;
	default:
		break;
	}

	return power;
}

GameObj* GameManager::GeneratePowerUpbyMap(int idx, int tier)
{
	auto strVec = GetPowerUpStrings(tier);
	string value = strVec[idx];
	int newTier = -1;
	if (isdigit(value.back()))
	{
		newTier = value.back() - '0';
		value.pop_back();
	}
	else newTier = tier;
	//cout << strVec[idx] << " / " << value << " / " << newTier << endl;

	PowerUpTypes puType = PowerUpTypes::None;
	// temp..
	if (!value.compare("Comrade"))
	{
		puType = PowerUpTypes::Comrade;
		//cout << "Comrade type" << endl;
	}
	else if (!value.compare("ContractWithTheDevil"))
	{
		puType = PowerUpTypes::ContractWithTheDevil;
		//cout << "ContractWithTheDevil type" << endl;
	}
	else if (!value.compare("CounterAttack"))
	{
		puType = PowerUpTypes::CounterAttack;
		//cout << "CounterAttack type" << endl;
	}
	else if (!value.compare("DogFight"))
	{
		puType = PowerUpTypes::DogFight;
		//cout << "DogFight type" << endl;
	}
	else if (!value.compare("ExecutionerSoul"))
	{
		puType = PowerUpTypes::ExecutionerSoul;
		//cout << "ExecutionerSoul type" << endl;
	}
	else if (!value.compare("HeroOfSalvation"))
	{
		puType = PowerUpTypes::HeroOfSalvation;
		//cout << "HeroOfSalvation type" << endl;
	}
	else if (!value.compare("Meditation"))
	{
		puType = PowerUpTypes::Meditation;
		//cout << "Meditation type" << endl;
	}
	else if (!value.compare("Nobility"))
	{
		puType = PowerUpTypes::Nobility;
		//cout << "Nobility type" << endl;
	}
	else if (!value.compare("QuickHand"))
	{
		puType = PowerUpTypes::QuickHand;
		//cout << "QuickHand type" << endl;
	}
	else if (!value.compare("RuneShield"))
	{
		puType = PowerUpTypes::RuneShield;
		//cout << "RuneShield type" << endl;
	}
	else if (!value.compare("Vampire"))
	{
		puType = PowerUpTypes::Vampire;
		//cout << "Vampire type" << endl;
	}
	else if (!value.compare("WarriorsHeart"))
	{
		puType = PowerUpTypes::WarriorsHeart;
		//cout << "WarriorsHeart type" << endl;
	}
	else if (!value.compare("WeAreTheOne"))
	{
		puType = PowerUpTypes::WeAreTheOne;
		//cout << "WeAreTheOne type" << endl;
	}

	return GeneratePowerUp(puType, newTier);
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

int GameManager::GetClearCoin()
{
	int clearCoin = stageClearCoin + altarData.startCoin +
		(curStageIdx / clearCoinIncreaseTerm) * clearCoinIncrease;
	// boss stage
	if (curStageIdx == STAGE_MAX_COUNT - 1)
		clearCoin += bossStageClearBonus;

	cout << curStageIdx << "클리어! " << clearCoin << "획득" << endl;
	return clearCoin;
}

float GameManager::GetItemStatMapElem(StatType statType, int grade)
{
	if (statType == StatType::None)
		return -1.f;
	return (itemStatMap[statType])[grade];
}

const vector<string>& GameManager::GetPowerUpStrings(int tier)
{
	string key = "Tier"	+ to_string(tier);
	return powerUpStringMap[key];
}

const WaveReward& GameManager::GetWaveRewardMapElem()
{
	string key =
		(curChapIdx + 1 > 9 ? "" : "0") + to_string(curChapIdx + 1) +
		(curStageIdx + 1 > 9 ? "" : "0") + to_string(curStageIdx + 1);
	return waveRewardMap[key];
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

void GameManager::LoadAltarEffectFromTable()
{
	string altarEffectTablePath = "data/altarEffectTable.csv";
	rapidcsv::Document doc(altarEffectTablePath, rapidcsv::LabelParams(0, 0));

	vector<string> colNames = doc.GetColumnNames();

	string manaId = altarData.GetManaKey();
	altarData.SetManaAltarEffect(
		doc.GetCell<int>(colNames[0], manaId),
		doc.GetCell<int>(colNames[1], manaId),
		doc.GetCell<int>(colNames[2], manaId)
	);

	string silverId = altarData.GetSilverKey();
	altarData.SetSilverAltarEffect(
		doc.GetCell<int>(colNames[3], silverId),
		doc.GetCell<int>(colNames[4], silverId),
		doc.GetCell<int>(colNames[5], silverId)
	);

	string physicalId = altarData.GetPhysicalKey();
	altarData.SetPhysicalAltarEffect(
		doc.GetCell<int>(colNames[6], physicalId),
		doc.GetCell<int>(colNames[7], physicalId),
		doc.GetCell<int>(colNames[8], physicalId)
	);

	string enforceId = altarData.GetEnforceKey();
	altarData.SetEnforceAltarEffect(
		doc.GetCell<int>(colNames[9], enforceId),
		doc.GetCell<int>(colNames[10], enforceId),
		doc.GetCell<int>(colNames[11], enforceId)
	);
}

bool GameManager::FindPowerUpByName(string name)
{
	for (auto& powerUp : standingPowerUps)
	{
		if (!powerUp->GetName().compare(name))
			return true;
	}
	return false;
}

PowerUp* GameManager::GetPowerUpByName(string name)
{
	for (auto& powerUp : standingPowerUps)
	{
		if (!powerUp->GetName().compare(name))
			return powerUp;
	}
	return nullptr;
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