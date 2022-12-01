#include "Character.h"

Character::Character(int starNumber)
	: destination(0, 0), move(false), attack(false), isAlive(true),
	attackRangeType(false), isBattle(false),
	noSkill(false), ccTimer(0.f), shieldAmount(0.f), astarDelay(0.0f), shieldAmountMin(0.f)
{
	hpBar = new TwoFactorProgress(TILE_SIZE * 0.8f, 5.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 2.f);
	hpBar->SetSecondProgressColor(Color::White);

	star = new Star(starNumber);
}

Character::~Character()
{
}

void Character::Init()
{
	GameObj::Init();
	UpgradeCharacterSet();

	SetStatsInit(GAME_MGR->GetCharacterData(name));

	hpBarLocalPos = { -hpBar->GetSize().x * 0.5f, -(float)GetTextureRect().height + 20.f };
	SetHpBarValue(1.f);
	hpBar->SetOrigin(Origins::BC);
	starLocalPos = { 0.f, hpBarLocalPos.y };
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

void Character::Reset()
{
	isBattle = false;
	attack = false;
	move = false;
	isAlive = true;
	Stat& hp = stat[Stats::HP];
	hp.ResetStat();
	shieldAmount = shieldAmountMin;
	hpBar->SetRatio(hp.GetModifier(), hp.GetCurrent(), shieldAmount);
	stat[Stats::MP].SetCurrent(0.f);
	SetState(AnimStates::Idle);
}

void Character::Update(float dt)
{
	if (!isAlive)
		return;

	hpBar->Update(dt);
	// Dev key start
	{
		if (InputMgr::GetKeyDown(Keyboard::Key::S))
		{
			TakeCare(this, false);
			hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::A))
		{
			TakeDamage(this);
			hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::D))
		{
			TakeCare(this);
			hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
		}
	}
	// Dev key end

	if (isBattle)
	{
		vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
		Vector2i mypos = GAME_MGR->PosToIdx(GetPos());

		if (!move && !attack && isAttack())
		{
			if (m_attackDelay <= 0.f)
			{
				SetState(AnimStates::Attack);
				dynamic_cast<Character*>(m_floodFill.GetNearEnemy(mainGrid, mypos, targetType))->TakeDamage(this);

				attack = true;
				Stat& mp = stat[Stats::MP];
				mp.TranslateCurrent(15.f);
				dynamic_cast<Character*>(this->target)->TakeDamage(this);

				if (Utils::EqualFloat(mp.GetCurRatio(), 1.f))
				{
					cout << name << " fire skill !" << endl;
					SetState(AnimStates::Skill);
					mp.SetCurrent(0.f);
				}
			}
			m_attackDelay -= dt;
		}
		else if (!move && !attack)
		{
			astarDelay -= dt;
			if (astarDelay <= 0.f)
			{
				//destination = GetPos();
				if (SetTargetDistance())
				{
					move = true;
				}
				else
				{
					move = false;
					astarDelay = 0.1f;
				}
			}
		}

		if (move && !attack)
		{
			SetState(AnimStates::Move);
			direction = destination - position;
			Translate(Utils::Normalize(direction) * 0.5f);
			if (destination == position)
			{
				move = false;
				SetState(AnimStates::MoveToIdle);
			}
		}
	}
}

void Character::Draw(RenderWindow& window)
{
	if (!isAlive)
		return;

	SpriteObj::Draw(window);
	window.draw(attackSprite);
	hpBar->Draw(window);
	star->Draw(window);
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
	IsSetState(newState);
	GameObj::SetState(newState);
}

void Character::SetStatsInit(json data)
{
	stat.insert({ Stats::HP, Stat(data["HP"]) });
	stat.insert({ Stats::MP, Stat(data["MP"], 0.f, false) });
	stat.insert({ Stats::AD, Stat(data["AD"]) });
	stat.insert({ Stats::AP, Stat(data["AP"]) });
	stat.insert({ Stats::AS, Stat(data["AS"]) });
	stat.insert({ Stats::AR, Stat(data["AR"]) });
	stat.insert({ Stats::MS, Stat(data["MS"]) });
	string arType = data["ARTYPE"];
	attackRangeType = arType.compare("cross") ? true : false;

	stat[Stats::AS].SetIsAddition(true);
}

void Character::TakeDamage(GameObj* attacker, bool attackType)
{
	Stat& hp = stat[Stats::HP];
	float damage = 0.f;
	if (attackType)
		damage = dynamic_cast<Character*>(attacker)->GetStat(Stats::AD).GetModifier();
	else
		damage = dynamic_cast<Character*>(attacker)->GetStat(Stats::AP).GetModifier();

	if (shieldAmount > 0.f)
	{
		float damageTemp = damage;
		damage -= shieldAmount;
		shieldAmount -= damageTemp;

		if (shieldAmount < 0.f)
			shieldAmount = 0.f;
		if (damage < 0.f)
			damage = 0.f;
	}

	hp.TranslateCurrent(-damage);
	hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
	if (stat[Stats::HP].GetCurrent() <= 0.f)
	{
		// death
		CLOG::Print3String(name, to_string(GetStarNumber()), " is die");
		isAlive = false;
		GAME_MGR->RemoveFromMainGrid(this);
	}
}

void Character::TakeCare(GameObj* caster, bool careType)
{
	Stat& hp = stat[Stats::HP];
	float careAmount = dynamic_cast<Character*>(caster)->GetStat(Stats::AP).GetModifier();

	if (careType)
		hp.TranslateCurrent(careAmount);
	else
		shieldAmount += careAmount;

	hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
}

void Character::UpgradeStar()
{
	if (star->CalculateRandomChance())
		CLOG::Print3String("upgrade 2");
	star->UpdateTexture();
	UpgradeCharacterSet();
	UpgradeStats();

	m_attackDelay = 1.f / stat[Stats::AS].GetModifier();
}

void Character::UpgradeCharacterSet()
{
	sprite.setScale({
		1.0f + (GetStarNumber() * 0.05f),
		1.0f + (GetStarNumber() * 0.05f) });
}

void Character::UpgradeStats()
{
	stat[Stats::HP].UpgradeBase(GAME_MGR->hpIncreaseRate);
	stat[Stats::AD].UpgradeBase(GAME_MGR->adIncreaseRate);
	stat[Stats::AP].UpgradeBase(GAME_MGR->apIncreaseRate);
	stat[Stats::AS].UpgradeBase(GAME_MGR->asIncrease);
}

void Character::IsSetState(AnimStates newState)
{
	if (newState != AnimStates::Attack && currState == AnimStates::Attack)
	{
		attack = false;
		m_attackDelay = 1.f / stat[Stats::AS].GetModifier();
	}
}

void Character::SetGeneralArr()
{

	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	//for (auto& target : mainGrid)
	//{
	//	if (target != nullptr && !target->GetType().compare(targetType))
	//	{

			m_GeneralArr = m_floodFill.GetGeneralInfo(mainGrid, targetType);

	//	}
	//}
}

unordered_map<Stats, Stat>& Character::GetStat()
{
	return stat;
}

bool Character::isAttack()
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	for (auto& target : mainGrid)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i mypos = GAME_MGR->PosToIdx(GetPos());
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());

			if (m_floodFill.FloodFillSearch(mainGrid, mypos, enpos, targetType))
			{
				this->target = target;
				return true;
			}
		}
	}

	return false;
}

bool Character::PlayAstar()
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	for (auto& target : mainGrid)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i mypos = GAME_MGR->PosToIdx(GetPos());
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());
			EnemyInfo nowEnemyInfo = m_aStar.AstarSearch(mainGrid, mypos, enpos);



			if (enemyInfo.leng > nowEnemyInfo.leng && !(nowEnemyInfo.leng == -1))
			{
				enemyInfo = nowEnemyInfo;
			}
		}
	}

	if (enemyInfo.leng == 99999)
	{
		return false;
	}

	Vector2i coord = GAME_MGR->PosToIdx(GetPos());
	SetDestination(GAME_MGR->IdxToPos(enemyInfo.destPos));
	SetMainGrid(coord.y, coord.x, nullptr);
	SetMainGrid(enemyInfo.destPos.y, enemyInfo.destPos.x, this);
	enemyInfo.leng = 99999;
	return true;
}

bool Character::SetTargetDistance()
{
	//move = true;

	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	for (auto& target : mainGrid)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i mypos = GAME_MGR->PosToIdx(GetPos());
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());
			EnemyInfo nowEnemyInfo = m_aStar.AstarSearch(mainGrid, mypos, enpos);

			m_GeneralArr = m_floodFill.GetGeneralInfo(mainGrid, targetType);

			if (enemyInfo.leng > nowEnemyInfo.leng && !(nowEnemyInfo.leng == -1))
			{
				enemyInfo = nowEnemyInfo;
			}
		}
	}

	if (enemyInfo.leng == 99999)
	{
		return false;
	}

	Vector2i coord = GAME_MGR->PosToIdx(GetPos());
	SetDestination(GAME_MGR->IdxToPos(enemyInfo.destPos));
	SetMainGrid(coord.y, coord.x, nullptr);
	SetMainGrid(enemyInfo.destPos.y, enemyInfo.destPos.x, this);
	enemyInfo.leng = 99999;
	return true;
}

void Character::SetMainGrid(int r, int c, GameObj* character)
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	int idx = r * GAME_TILE_WIDTH + c;
	mainGrid[idx] = character;
}