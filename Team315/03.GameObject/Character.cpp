#include "Character.h"

Character::Character(int starNumber)
	: destination(0, 0), move(false), attack(false), isAlive(false),
	currState(AnimStates::None), drawingOnBattle(false),
	attackRangeType(false), isBattle(false)
{
	hpBar = new ProgressBar();
	hpBarLocalPos = { -TILE_SIZE_HALF * 0.5f, -TILE_SIZE_HALF - TILE_SIZE };
	hpBar->SetSize(TILE_SIZE_HALF, 5.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 2.f);
	hpBar->SetProgressValue(1.f);
	hpBar->SetOrigin(Origins::BC);

	star = new Star(starNumber);
	starLocalPos = { 0, -TILE_SIZE * 1.5f };
}

Character::~Character()
{
}

void Character::Init()
{
	SetHitbox(FloatRect(0, 0, TILE_SIZE, TILE_SIZE), Origins::BC);
	UpgradeCharacterSet();
	Object::Init();
	
	SetStatsInit(GAME_MGR->GetCharacterData(name));


	//battle
	enemyInfo.leng = 99999;

	if (!type.compare("Player"))
		targetType = "Monster";
	else if (!type.compare("Monster"))
		targetType = "Monster";
	else
		targetType = "None";

	m_floodFill.SetArrSize(2, 2, false);
}

void Character::Update(float dt)
{
	if (isBattle)
	{
		if (!move && !attack && isAttack())
		{

		}
		else if (!move && !attack)
			SetTargetDistance();

		if (move && !attack)
		{
			SetState(AnimStates::Move);
			direction = destination - position;
			Translate(Utils::Normalize(direction));
			if (destination == position)
			{
				move = false;
				//isBattle = false;
				SetState(AnimStates::MoveToIdle);
			}
		}
	}
	hpBar->Update(dt);
	if (move)
	{
		SetState(AnimStates::Move);
		direction = destination - position;
		Translate(Utils::Normalize(direction));

		if (destination == position)
		{
			move = false;
			SetState(AnimStates::MoveToIdle);

		}
	}
}

void Character::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	if (drawingOnBattle)
	{
		hpBar->Draw(window);
		star->Draw(window);
	}
}

void Character::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	hpBar->SetPos(pos + hpBarLocalPos);
	star->SetPos(pos + starLocalPos);
}

void Character::SetState(AnimStates newState)
{
	if (currState == newState)
	{
		return;
	}
	currState = newState;
}

void Character::SetTarget(Character* target)
{
	this->target = target;
}

void Character::SetStatsInit(json data)
{
	stat.insert({ Stats::HP, Stat(data["HP"])});
	stat.insert({ Stats::MP, Stat(data["MP"]) });
	stat.insert({ Stats::AD, Stat(data["AD"]) });
	stat.insert({ Stats::AP, Stat(data["AP"]) });
	stat.insert({ Stats::AS, Stat(data["AS"]) });
	stat.insert({ Stats::AR, Stat(data["AR"]) });
	stat.insert({ Stats::MS, Stat(data["MS"]) });
	string arType = data["ARTYPE"];
	attackRangeType = arType.compare("cross") ? true : false;
}

void Character::TakeDamage(float damage)
{
	Stat& hp = stat[Stats::HP];
	hp.SetCurrent(hp.GetCurrent() -= damage);
	hpBar->SetProgressValue(hp.GetCurRatio());
}

void Character::UpgradeStar()
{
	if (star->CalculateRandomChance())
		CLOG::Print3String("upgrade 2");
	star->UpdateTexture();
	UpgradeCharacterSet();
}

void Character::UpgradeCharacterSet()
{
	sprite.setScale({
		1.0f + (GetStarNumber() * 0.05f),
		1.0f + (GetStarNumber() * 0.05f) });
	// 성급 올라갈때 공격력,마력,체력 증가
	// 별 색 바뀔때 스킬 범위 증가 1 3 5 7
}

void Character::PrintStats()
{
	cout << "---------------" << endl;
	cout << "name: " << name << " / star: " << GetStarNumber() << endl;
	cout << "HP: " << stat[Stats::HP].base << endl;
	cout << "MP: " << stat[Stats::MP].base << endl;
	cout << "AD: " << stat[Stats::AD].base << endl;
	cout << "AP: " << stat[Stats::AP].base << endl;
	cout << "AS: " << stat[Stats::AS].base << endl;
	cout << "AR: " << stat[Stats::AR].base << endl;
	cout << "MS: " << stat[Stats::MS].base << endl;
	cout << (attackRangeType ? "square" : "cross") << endl;
	cout << "---------------" << endl;
}

unordered_map<Stats, Stat> Character::GetStat()
{
	return stat;
}

bool Character::isAttack()
{
	vector<Character*> mainGrid = GAME_MGR->GetMainGridRef();

	for (auto& target : mainGrid)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i mypos = GAME_MGR->PosToIdx(GetPos());
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());
			EnemyInfo nowEnemyInfo = m_aStar.AstarSearch(mainGrid, mypos, enpos);

			if (m_floodFill.FloodFillSearch(mainGrid, mypos, enpos))
				return true;
		}
	}

	return false;
}

void Character::PlayAstar()
{

}

void Character::SetTargetDistance()
{
	move = true;

	vector<Character*> mainGrid = GAME_MGR->GetMainGridRef();

	for (auto& target : mainGrid)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i mypos = GAME_MGR->PosToIdx(GetPos());
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());
			EnemyInfo nowEnemyInfo = m_aStar.AstarSearch(mainGrid, mypos, enpos);

			if (enemyInfo.leng > nowEnemyInfo.leng)
			{
				enemyInfo = nowEnemyInfo;
			}
		}
	}

	Vector2i coord = GAME_MGR->PosToIdx(GetPos());
	SetDestination(GAME_MGR->IdxToPos(enemyInfo.destPos));
	SetMainGrid(coord.y, coord.x, nullptr);
	SetMainGrid(enemyInfo.destPos.y, enemyInfo.destPos.x, this);
	enemyInfo.leng = 99999;
}

void Character::SetMainGrid(int r, int c, Character* character)
{
	vector<Character*> mainGrid = GAME_MGR->GetMainGridRef();

	int idx = r * GAME_TILE_WIDTH + c;
	mainGrid[idx] = character;
}
