#include "Character.h"

Character::Character(int starNumber)
	: destination(0, 0), move(false), attack(false), isAlive(false),
	currState(AnimStates::None), drawingOnBattle(false),
	attackRangeType(false), isBattle(false), noSkill(false)
{
	hpBar = new ProgressBar(TILE_SIZE * 0.8f, 5.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 2.f);

	star = new Star(starNumber);
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

	hpBarLocalPos = { -hpBar->GetSize().x * 0.5f, -(float)GetTextureRect().height + 20.f};
	hpBar->SetOrigin(Origins::BC);
	hpBar->SetProgressValue(stat[Stats::HP].GetCurRatio());
	starLocalPos = { 0, hpBarLocalPos.y };
	SetPos(position);

	//battle
	enemyInfo.leng = 99999;

	if (!type.compare("Player"))
		targetType = "Monster";
	else if (!type.compare("Monster"))
		targetType = "Player";
	else
		targetType = "None";

	m_floodFill.SetArrSize(
		stat[Stats::AR].GetModifier(),
		stat[Stats::AR].GetModifier(),
		attackRangeType);
}

void Character::Update(float dt)
{
	if (isBattle)
	{
		if (!move && !attack && isAttack())
		{
			SetState(AnimStates::Attack);
			Stat& mp = stat[Stats::MP];
			mp.TranslateCurrent(15.f);
			attack = true;
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
}

void Character::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(attackSprite);
	if (drawingOnBattle)
	{
		hpBar->Draw(window);
		star->Draw(window);
	}
}

void Character::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	attackSprite.setPosition(GetPos());
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
	stat.insert({ Stats::MP, Stat(data["MP"], 0.f, false) });
	stat.insert({ Stats::AD, Stat(data["AD"]) });
	stat.insert({ Stats::AP, Stat(data["AP"]) });
	stat.insert({ Stats::AS, Stat(data["AS"]) });
	stat.insert({ Stats::AR, Stat(data["AR"]) });
	stat.insert({ Stats::MS, Stat(data["MS"]) });
	string arType = data["ARTYPE"];
	attackRangeType = arType.compare("cross") ? true : false;
}

void Character::TakeDamage(Character* attacker, bool attackType)
{
	Stat& hp = stat[Stats::HP];
	float damage = 0.f;
	if (attackType)
		damage = attacker->GetStat(Stats::AD).GetModifier();
	else
		damage = attacker->GetStat(Stats::AP).GetModifier();

	hp.TranslateCurrent(-damage);
	// hp.SetCurrent(hp.GetCurrent() -= damage);
	float curRatio = hp.GetCurRatio();
	hpBar->SetProgressValue(curRatio);
	if (curRatio <= 0.f)
	{
		// death
		CLOG::Print3String(name, to_string(GetStarNumber()), " is die");
	}
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
	cout << "HP: " << stat[Stats::HP].GetBase() << endl;
	cout << "MP: " << stat[Stats::MP].GetBase() << endl;
	cout << "AD: " << stat[Stats::AD].GetBase() << endl;
	cout << "AP: " << stat[Stats::AP].GetBase() << endl;
	cout << "AS: " << stat[Stats::AS].GetBase() << endl;
	cout << "AR: " << stat[Stats::AR].GetBase() << endl;
	cout << "MS: " << stat[Stats::MS].GetBase() << endl;
	cout << (attackRangeType ? "square" : "cross") << endl;
	cout << "---------------" << endl;
}

unordered_map<Stats, Stat>& Character::GetStat()
{
	return stat;
}

bool Character::isAttack()
{
	vector<Character*>& mainGrid = GAME_MGR->GetMainGridRef();

	for (auto& target : mainGrid)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i mypos = GAME_MGR->PosToIdx(GetPos());
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());
			//EnemyInfo nowEnemyInfo = m_aStar.AstarSearch(mainGrid, mypos, enpos);

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
	//move = true;

	vector<Character*>& mainGrid = GAME_MGR->GetMainGridRef();

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
	vector<Character*>& mainGrid = GAME_MGR->GetMainGridRef();

	int idx = r * GAME_TILE_WIDTH + c;
	mainGrid[idx] = character;
}