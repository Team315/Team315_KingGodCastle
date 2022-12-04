#include "Character.h"
#include "Item/Item.h"
#include "Skill.h"

Character::Character(int skillTier)
	: destination(0, 0), move(false), attack(false), isAlive(true),
	attackRangeType(false), isBattle(false),
	noSkill(false), ccTimer(0.f), shieldAmount(0.f), astarDelay(0.0f), shieldAmountMin(0.f)
{
	hpBar = new TwoFactorProgress(TILE_SIZE * 0.8f, 5.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 2.f);
	hpBar->SetSecondProgressColor(Color::White);

	star = new Star(skillTier);
	itemGrid.assign(ITEM_LIMIT, nullptr);
	for (auto& grid : itemGrid)
	{
		grid = new SpriteGrid(ITEM_SPRITE_SIZE, ITEM_SPRITE_SIZE);
		grid->SetOutline(Color(255, 255, 255, 100.f), -1.f);
		grid->SetFillColor(Color(0, 0, 0, 0.f));
		grid->SetOrigin(Origins::BC);
		grid->SetActive(false);
	}
}

Character::~Character()
{
	hpBar->Release();
	star->Release();
	if (skill != nullptr)
		skill->Release();

	delete hpBar;
	delete star;
	delete skill;
}

void Character::Init()
{
	GameObj::Init();
	UpgradeCharacterSet();

	SetStatsInit(GAME_MGR->GetCharacterData(name));

	hpBarLocalPos = { -hpBar->GetSize().x * 0.5f, -(float)GetTextureRect().height + 10.f };
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
		stat[StatType::AR].GetModifier(), stat[StatType::AR].GetModifier(), attackRangeType);
}

void Character::Reset()
{
	isBattle = false;
	attack = false;
	move = false;
	isAlive = true;
	direction = { 0.f, 0.f };
	lastDirection = { 0.f, 0.f };
	Stat& hp = stat[StatType::HP];
	hp.ResetStat();
	shieldAmount = shieldAmountMin;
	hpBar->SetRatio(hp.GetModifier(), hp.GetCurrent(), shieldAmount);
	stat[StatType::MP].SetCurrent(0.f);
	SetState(AnimStates::Idle);
}

void Character::Update(float dt)
{
	if (!isAlive)
		return;

	hpBar->Update(dt);

	if (ccTimer > 0.f)
	{
		ccTimer -= dt;
		if (ccTimer <= 0.f)
			ccTimer = 0.f;

		return;
	}

	if (isBattle)
	{
		vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

		if (InputMgr::GetKeyDown(Keyboard::Key::L))
		{
			OnOffAttackAreas(true);
		}

		if (!move && !attack)
		{
			if (isAttack())
			{
				if (m_attackDelay <= 0.f)
				{
					m_target = m_floodFill.GetNearEnemy(mainGrid, GAME_MGR->PosToIdx(position), targetType);
					lastDirection = Utils::Normalize(dynamic_cast<Character*>(m_target)->position - position);
					direction = lastDirection;
					SetState(AnimStates::Attack);
					dynamic_cast<Character*>(m_target)->TakeDamage(this);
					attack = true;
					Stat& mp = stat[StatType::MP];
					mp.TranslateCurrent(15.f);

					if (Utils::EqualFloat(mp.GetCurRatio(), 1.f))
					{
						SetState(AnimStates::Skill);
						mp.SetCurrent(0.f);
						//if (!noSkill)
						if (skill != nullptr)
							skill->CastSkill(this);
					}
				}
				m_attackDelay -= dt;
			}
			else
			{
				astarDelay -= dt;
				if (astarDelay <= 0.f)
				{
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

	m_floodFill.Draw(window);
	SpriteObj::Draw(window);
	window.draw(effectSprite);
	hpBar->Draw(window);
	star->Draw(window);
	for (auto& grid : itemGrid)
	{
		if (grid->GetActive())
			grid->Draw(window);
	}
}

void Character::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	effectSprite.setPosition(pos);
	hpBar->SetPos(pos + hpBarLocalPos);
	star->SetPos(pos + starLocalPos);

	float xDelta = 5.f;
	for (auto& grid : itemGrid)
	{
		grid->SetPos(pos + hpBarLocalPos + Vector2f(xDelta, 25.f));
		xDelta += ITEM_SPRITE_SIZE;
	}
}

void Character::SetState(AnimStates newState)
{
	IsSetState(newState);
	GameObj::SetState(newState);
}

void Character::SetStatsInit(json data)
{
	stat.insert({ StatType::HP, Stat(data["HP"]) });
	stat.insert({ StatType::MP, Stat(data["MP"], 0.f, false) });
	stat.insert({ StatType::AD, Stat(data["AD"]) });
	stat.insert({ StatType::AP, Stat(data["AP"]) });
	stat.insert({ StatType::AS, Stat(data["AS"]) });
	stat.insert({ StatType::AR, Stat(data["AR"]) });
	stat.insert({ StatType::MS, Stat(data["MS"]) });
	string arType = data["ARTYPE"];
	attackRangeType = arType.compare("cross") ? true : false;

	stat[StatType::AS].SetUpgradeMode(true);
	stat[StatType::AD].SetDeltaMode(true);
	if (stat[StatType::MP].GetBase() == 0.f)
		noSkill = true;
}

void Character::TakeDamage(GameObj* attacker, bool attackType)
{
	Stat& hp = stat[StatType::HP];
	float damage = 0.f;
	if (attackType)
		damage = dynamic_cast<Character*>(attacker)->GetStat(StatType::AD).GetModifier();
	else
		damage = dynamic_cast<Character*>(attacker)->GetSkill()->CalculatePotential(this);

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
	GAME_MGR->damageUI.Get()->SetDamageUI(position + Vector2f(0, -TILE_SIZE), attackType ? StatType::AD : StatType::AP, damage);

	hp.TranslateCurrent(-damage);
	hpBar->SetRatio(stat[StatType::HP].GetModifier(), stat[StatType::HP].current, shieldAmount);
	if (stat[StatType::HP].GetCurrent() <= 0.f)
	{
		// death
		CLOG::Print3String(name, to_string(GetStarNumber()), " is die");
		isAlive = false;
		GAME_MGR->RemoveFromMainGrid(this);
	}
}

void Character::TakeCare(GameObj* caster, bool careType)
{
	Stat& hp = stat[StatType::HP];
	Character* casterCharacter = dynamic_cast<Character*>(caster);
	float careAmount = casterCharacter->GetSkill()->CalculatePotential(casterCharacter);

	if (careType)
		hp.TranslateCurrent(careAmount);
	else
		shieldAmount += careAmount;

	hpBar->SetRatio(stat[StatType::HP].GetModifier(), stat[StatType::HP].current, shieldAmount);
}

void Character::UpgradeStar()
{
	if (star->CalculateRandomChance())
		CLOG::Print3String("upgrade 2");
	star->UpdateTexture();
	UpgradeCharacterSet();
	UpgradeStats();

	m_attackDelay = 1.f / stat[StatType::AS].GetModifier();
}

void Character::UpgradeCharacterSet()
{
	sprite.setScale({
		1.0f + (GetStarNumber() * 0.05f),
		1.0f + (GetStarNumber() * 0.05f) });
}

void Character::UpgradeStats()
{
	stat[StatType::HP].UpgradeBase(GAME_MGR->hpIncreaseRate);
	stat[StatType::AD].UpgradeBase(GAME_MGR->adIncreaseRate);
	stat[StatType::AP].UpgradeBase(GAME_MGR->apIncreaseRate);
	stat[StatType::AS].UpgradeBase(GAME_MGR->asIncrease);
}

bool Character::SetItem(Item* newItem)
{
	int combineIdx = 0;
	bool isCombine = false;

	for (auto& item : items)
	{
		if (!item->GetName().compare(newItem->GetName()) && (item->GetGrade() == newItem->GetGrade()) && (newItem->GetGrade() != (TIER_MAX - 1)))
		{
			newItem->Upgrade();
			UpdateItemDelta(newItem->GetStatType(), newItem->GetPotential() - item->GetPotential());
			delete item;
			item = newItem;
			isCombine = true;
			break;
		}
		combineIdx++;
	}

	if (!isCombine)
	{
		if (items.size() == ITEM_LIMIT)
			return false;
		
		items.push_back(newItem);
	}

	string path = "graphics/battleScene/Item_";

	ItemType iType = newItem->GetItemType();
	switch (iType)
	{
	case ItemType::Armor:
		path += "Armor";
		break;
	case ItemType::Bow:
		path += "Bow";
		break;
	case ItemType::Staff:
		path += "Staff";
		break;
	case ItemType::Sword:
		path += "Sword";
		break;
		/*case ItemType::Book:
			path += "Book";
			break;*/
	}
	path += (to_string(newItem->GetGrade()) + ".png");
	if (!isCombine)
		UpdateItemDelta(newItem->GetStatType(), newItem->GetPotential());

	itemGrid[combineIdx]->SetActive(true);
	itemGrid[combineIdx]->SetSpriteTexture(*RESOURCE_MGR->GetTexture(path));
	itemGrid[combineIdx]->SetSpriteScale(ITEM_SPRITE_SIZE, ITEM_SPRITE_SIZE);
	itemGrid[combineIdx]->SetOrigin(Origins::BC);
	return true;
}

void Character::UpdateItemDelta(StatType sType, float value)
{
	switch (sType)
	{
	case StatType::HP:
		shieldAmountMin += value;
		shieldAmount += value;
		hpBar->SetRatio(stat[StatType::HP].GetModifier(), stat[StatType::HP].current, shieldAmount);
		break;
	case StatType::AD:
	case StatType::AP:
	case StatType::AS:
		stat[sType].AddDelta(value);
		break;
	}
}

void Character::IsSetState(AnimStates newState)
{
	if (newState != AnimStates::Attack && currState == AnimStates::Attack)
	{
		attack = false;
		m_attackDelay = 1.f / stat[StatType::AS].GetModifier();
	}
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
				return true;
			}
		}
	}

	return false;
}

void Character::OnOffAttackAreas(bool onOff)
{
	m_floodFill.DrawingAttackAreas(GAME_MGR->PosToIdx(position), onOff);
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