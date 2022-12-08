#include "Character.h"
#include "Item/Item.h"
#include "Skill.h"

Character::Character(bool mode, bool fixedStar, int starNumber)
	: destination(0, 0), move(false), attack(false), isAlive(true),
	attackRangeType(false), isBattle(false), moveSpeed(0.f), noSkill(false),
	ccTimer(0.f), shieldAmount(0.f), astarDelay(0.0f), shieldAmountMin(0.f)
{
	hpBar = new TwoFactorProgress(TILE_SIZE * 0.8f, 5.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 2.f);
	hpBar->SetSecondProgressColor(Color::White);

	star = new Star(mode, fixedStar, starNumber);
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
	for (auto& item : items)
	{
		item->Release();
		delete item;
	}

	delete hpBar;
	delete star;
	delete skill;
	items.clear();
}

void Character::Init()
{
	GameObj::Init();
	UpgradeCharacterSet();

	SetStatsInit(GAME_MGR->GetCharacterData(name));

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

	AnimationInit();

	hpBarLocalPos = { -hpBar->GetSize().x * 0.5f, -(float)GetTextureRect().height + 10.f };
	SetHpBarValue(1.f);
	hpBar->SetOrigin(Origins::BC);
	starLocalPos = { 0.f, hpBarLocalPos.y };
	SetPos(position);
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
		if (ccTimer < 0.f)
		{
			ccTimer = 0.f;
		}
		return;
	}

	if (isBattle)
	{
		vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

		if (!move && !attack)
		{
			if (isAttack())
			{
				if (m_attackDelay <= 0.f)
				{
					m_target = m_floodFill.GetNearEnemy(mainGrid, GAME_MGR->PosToIdx(position), targetType);
					lastDirection = Utils::Normalize(dynamic_cast<Character*>(m_target)->GetPos() - position);
					direction = lastDirection;
					SetState(AnimStates::Attack);
					dynamic_cast<Character*>(m_target)->TakeDamage(this);
					attack = true;
					Stat& mp = stat[StatType::MP];
					mp.TranslateCurrent(15.f);

					if (!noSkill && Utils::EqualFloat(mp.GetCurRatio(), 1.f))
					{
						SetState(AnimStates::Skill);
						mp.SetCurrent(0.f);
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
						//move = true;
						SetState(AnimStates::Move);

					}
					else
					{
						move = false;
						SetState(AnimStates::MoveToIdle);
						//astarDelay = 1.0f;
					}
				}
			}
		}

		if (move && !attack)
		{
			direction = destination - position;

			Translate(Utils::Normalize(direction) * dt * moveSpeed);
			if (currState != AnimStates::Move)
				SetState(AnimStates::Move);
			if (Utils::EqualFloat(Utils::Distance(destination, position), 0.f, dt * moveSpeed))
			{
				SetPos(destination);
				move = false;
				SetState(AnimStates::MoveToIdle);
			}
		}
	}

	switch (currState)
	{
	case AnimStates::Idle:
		UpdateIdle(dt);
		break;
	case AnimStates::MoveToIdle:
		if(name.compare("Slime00"))
			UpdateMoveToIdle(dt);
		break;
	case AnimStates::Move:
		if (name.compare("Slime00"))
			UpdateMove(dt);
		break;
	case AnimStates::Attack:
		if (name.compare("Slime00"))
			UpdateAttack(dt);
		break;
	case AnimStates::Skill:
		UpdateSkill(dt);
		break;
	}
	animator.Update(dt);
	effectAnimator.Update(dt);

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		lastDirection = direction;
	}
}

void Character::Draw(RenderWindow& window)
{
	if (!isAlive)
		return;

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

	switch (currState)
	{
	case AnimStates::Idle:
		IdleAnimation();
		break;
	case AnimStates::MoveToIdle:
		if(name.compare("Slime00"))
			MoveToIdleAnimation();
		break;
	case AnimStates::Move:
		if (name.compare("Slime00"))
			MoveAnimation();
		break;
	case AnimStates::Attack:
		if (name.compare("Slime00"))
			AttackAnimation(attackPos[dirType]);
		break;
	case AnimStates::Skill:
		if(!noSkill)
			SkillAnimation(attackPos[dirType]);
		break;
	}
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

	moveSpeed = stat[StatType::MS].GetBase();
	int starNumber = GetStarNumber();
	while (starNumber-- > 1)
	{
		UpgradeStats();
	}
	UpgradeCharacterSet();
	if (skill != nullptr)
		skill->SetSkillTier(GetStarNumber());
}

void Character::TakeDamage(GameObj* attacker, bool attackType)
{
	Stat& hp = stat[StatType::HP];
	float damage = 0.f;
	Character* attackerCharacter = dynamic_cast<Character*>(attacker);
	if (attackType)
		damage = attackerCharacter->GetStat(StatType::AD).GetModifier();
	else
		damage = attackerCharacter->GetSkill()->CalculatePotential(attackerCharacter);

	GAME_MGR->GetBattleTracker()->UpdateData(this, damage, false, attackType);
	GAME_MGR->GetBattleTracker()->UpdateData(attackerCharacter, damage, true, attackType);

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
		//CLOG::Print3String(name, to_string(GetStarNumber()), " is die");
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

void Character::UpgradeStar(bool useExtraUpgrade)
{
	if (GetStarNumber() == STAR_MAX)
		return;

	bool upgradeTwice = false;
	if (star->CalculateRandomChance(useExtraUpgrade))
	{
		CLOG::Print3String("upgrade 2");
		upgradeTwice = true;
	}
	star->UpdateTexture();
	UpgradeCharacterSet();
	UpgradeStats();
	if (upgradeTwice)
	{
		UpgradeCharacterSet();
		UpgradeStats();
	}

	if (skill != nullptr)
		skill->SetSkillTier(GetStarNumber());

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

	Item* combineItem = nullptr;
	for (auto& item : items)
	{
		combineItem = GAME_MGR->CombineItem(item, newItem);
		if (combineItem != nullptr)
		{
			PutItem(item);
			delete newItem;
			return SetItem(combineItem);
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

void Character::PutItem(Item* putItem)
{
	int i = 0;
	for (auto it = items.begin(); it != items.end();)
	{
		if (putItem->GetObjId() == (*it)->GetObjId())
		{
			UpdateItemDelta((*it)->GetStatType(), -(*it)->GetPotential());
			delete *it;
			it = items.erase(it);
		}
		else it++;
		i++;
	}
}

void Character::UpdateItems()
{
	int curSize = items.size();

	for (int i = 0; i < ITEM_LIMIT; i++)
	{
		if (i >= curSize)
			itemGrid[i]->SetActive(false);
	}
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
	m_floodFill.DrawingAttackAreas(onOff, GAME_MGR->PosToIdx(position + Vector2f(TILE_SIZE_HALF, TILE_SIZE_HALF)));
}

bool Character::PlayAstar()
{
	Vector2i goingPos;
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
	m_GeneralArr = m_floodFill.GetGeneralInfo(mainGrid, targetType);
	Vector2i mypos = GAME_MGR->PosToIdx(position);

	//m_GeneralArr = m_floodFill.GetGeneralInfo(mainGrid, targetType);
	goingPos = m_aStar.AstarSearch(mainGrid, mypos, m_GeneralArr);


	if (goingPos.x == -1.f)// && goingPos.x == -1.f)
	{
		return false;
	}

	Vector2i coord = GAME_MGR->PosToIdx(position);
	SetDestination(GAME_MGR->IdxToPos(goingPos));
	SetMainGrid(coord.y, coord.x, nullptr);
	SetMainGrid(goingPos.y, goingPos.x, this);

	return true;
}

bool Character::SetTargetDistance()
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();
	Vector2i mypos = GAME_MGR->PosToIdx(position);

	m_GeneralArr = m_floodFill.GetGeneralInfo(mainGrid, targetType);

	for (auto& target : m_GeneralArr)
	{
		EnemyInfo nowEnemyInfo = m_aStar.AstarSearch(mainGrid, mypos, target);

		if (enemyInfo.leng > nowEnemyInfo.leng && !(nowEnemyInfo.leng == -1))
		{
			enemyInfo = nowEnemyInfo;
		}
	}

	if (enemyInfo.leng == -1)
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

void Character::AnimationInit()
{
	animator.SetTarget(&sprite);
	effectAnimator.SetTarget(&effectSprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::Idle]));
	if(name.compare("Slime00"))
	{
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownIdle]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftIdle]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightIdle]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpIdle]));

		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownMove]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftMove]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightMove]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpMove]));

		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftAttack]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightAttack]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpAttack]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownAttack]));
	}


	if (!noSkill)
	{
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownSkill]));
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::DownSkill];
			ev.frame = 2;
			ev.onEvent = bind(&Character::OnCompleteSkill, this);
			animator.AddEvent(ev);
		}
		if(name.compare("Slime00"))
		{
			animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftSkill]));
			animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightSkill]));
			animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpSkill]));

			{
				AnimationEvent ev;
				ev.clipId = resStringTypes[ResStringType::LeftSkill];
				ev.frame = 2;
				ev.onEvent = bind(&Character::OnCompleteSkill, this);
				animator.AddEvent(ev);
			}
			{
				AnimationEvent ev;
				ev.clipId = resStringTypes[ResStringType::RightSkill];
				ev.frame = 2;
				ev.onEvent = bind(&Character::OnCompleteSkill, this);
				animator.AddEvent(ev);
			}
			{
				AnimationEvent ev;
				ev.clipId = resStringTypes[ResStringType::UpSkill];
				ev.frame = 2;
				ev.onEvent = bind(&Character::OnCompleteSkill, this);
				animator.AddEvent(ev);
			}
		}
	}
	if(!type.compare("Player"))
	{
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownAttackEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftAttackEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightAttackEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpAttackEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownSkillEfect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftSkillEfect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightSkillEfect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpSkillEfect]));
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::DownAttackEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::LeftAttackEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::RightAttackEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::UpAttackEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::DownSkillEfect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::LeftSkillEfect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::RightSkillEfect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::UpSkillEfect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
	}
	if(name.compare("Slime00"))
	{
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::DownAttack];
			ev.frame = 2;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			animator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::LeftAttack];
			ev.frame = 2;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			animator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::RightAttack];
			ev.frame = 2;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			animator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::UpAttack];
			ev.frame = 2;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			animator.AddEvent(ev);
		}
	}

	SetState(AnimStates::Idle);
}

void Character::IdleAnimation()
{
	animator.Play(resStringTypes[ResStringType::Idle]);
}

void Character::MoveToIdleAnimation()
{
	if (lastDirection.x)
	{
		animator.Play((lastDirection.x > 0.f) ? resStringTypes[ResStringType::RightIdle] : resStringTypes[ResStringType::LeftIdle]);
	}
	else if (lastDirection.y)
	{
		animator.Play((lastDirection.y > 0.f) ? resStringTypes[ResStringType::DownIdle] : resStringTypes[ResStringType::UpIdle]);
	}
}

void Character::MoveAnimation()
{
	if (direction.y)
	{
		animator.Play((direction.y > 0.f) ? resStringTypes[ResStringType::DownMove] : resStringTypes[ResStringType::UpMove]);
	}
	else if (direction.x)
	{
		animator.Play((direction.x > 0.f) ? resStringTypes[ResStringType::RightMove] : resStringTypes[ResStringType::LeftMove]);
	}
}

void Character::AttackAnimation(Vector2f attackPos)
{
	SOUND_MGR->Play(resStringTypes[ResStringType::atkSound], 20.f, false);
	if (lastDirection.x > 0.f)
	{
		animator.Play(resStringTypes[ResStringType::RightAttack]);
		if(!type.compare("Player"))
		{
			effectAnimator.Play(resStringTypes[ResStringType::RightAttackEffect]);
			effectSprite.setPosition(position + attackPos);
		}
	}
	else if (lastDirection.x < 0.f)
	{
		animator.Play(resStringTypes[ResStringType::LeftAttack]);
		if (!type.compare("Player"))
		{
			effectAnimator.Play(resStringTypes[ResStringType::LeftAttackEffect]);
			effectSprite.setPosition(position + attackPos);
		}
	}
	else if (lastDirection.y > 0.f)
	{
		animator.Play(resStringTypes[ResStringType::DownAttack]);
		if (!type.compare("Player"))
		{
			effectAnimator.Play(resStringTypes[ResStringType::DownAttackEffect]);
			effectSprite.setPosition(position + attackPos);
		}
	}
	else if (lastDirection.y < 0.f)
	{
		animator.Play(resStringTypes[ResStringType::UpAttack]);
		if (!type.compare("Player"))
		{
			effectAnimator.Play(resStringTypes[ResStringType::UpAttackEffect]);
			effectSprite.setPosition(position + attackPos);
		}
	}
}

void Character::SkillAnimation(Vector2f skillPos)
{
	if (lastDirection.y)
	{
		animator.Play(lastDirection.y > 0.f ? resStringTypes[ResStringType::DownSkill] : resStringTypes[ResStringType::UpSkill]);
		effectAnimator.Play(lastDirection.y > 0.f ? resStringTypes[ResStringType::DownSkillEfect] : resStringTypes[ResStringType::UpSkillEfect]);
		effectSprite.setPosition(position + skillPos);	
	}
	else if (lastDirection.x)
	{
		animator.Play(lastDirection.x > 0.f ? resStringTypes[ResStringType::RightSkill] : resStringTypes[ResStringType::LeftSkill]);
		effectAnimator.Play(lastDirection.x > 0.f ? resStringTypes[ResStringType::RightSkillEfect] : resStringTypes[ResStringType::LeftSkillEfect]);		
		effectSprite.setPosition(position + skillPos);
	}
	else
	{
		animator.Play(resStringTypes[ResStringType::DownSkill]);
	}
}

void Character::OnCompleteAttack()
{
	SetState(AnimStates::MoveToIdle);
}

void Character::OnCompleteSkill()
{
	if (!name.compare("Slime00"))
	{
		SetState(AnimStates::Idle);
	}
	else
	{
		SetState(AnimStates::Attack);
	}
}

void Character::UpdateIdle(float dt)
{

	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		if (!name.compare("Slime00"))
		{
			SetState(AnimStates::Skill);
		}
		else
			SetState(AnimStates::Move);
		return;
	}

}

void Character::UpdateMoveToIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Character::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::Idle);
		return;
	}
	if (move)
		return;
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? resStringTypes[ResStringType::RightMove] : resStringTypes[ResStringType::LeftMove]);
		move = true;
	}
	else if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? resStringTypes[ResStringType::DownMove] : resStringTypes[ResStringType::UpMove]);
		move = true;
	}
}

void Character::UpdateAttack(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
	}
}

void Character::UpdateSkill(float dt)
{
	if (!name.compare("Slime00"))
	{
		if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
		{
			SetState(AnimStates::Idle);
		}
	}
	else
	{
		if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
		{
			SetState(AnimStates::MoveToIdle);
		}
	}
}
