#include "Character.h"
#include "Item/Item.h"
#include "Skill.h"

Character::Character(bool mode, bool useExtraUpgrade, int starNumber)
	: destination(0, 0), move(false), attack(false), isAlive(true),
	attackRangeType(false), isBattle(false), moveSpeed(0.f), noSkill(true),
	ccTimer(0.f), shieldAmount(0.f), astarDelay(0.0f), shieldAmountMin(0.f),
	dirType(Dir::None)
{
	hpBar = new TwoFactorProgress(TILE_SIZE * 0.8f, 3.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 1.f);
	hpBar->SetSecondProgressColor(Color::White);

	star = new Star(mode, useExtraUpgrade, starNumber);
	itemGrid.assign(ITEM_LIMIT, nullptr);
	for (auto& grid : itemGrid)
	{
		grid = new SpriteGrid(ITEM_SPRITE_SIZE, ITEM_SPRITE_SIZE);
		grid->SetOutline(Color(255, 255, 255, 100.f), -1.f);
		grid->SetFillColor(Color(0, 0, 0, 0.f));
		grid->SetOrigin(Origins::BC);
		grid->SetActive(false);
	}

	shadow.setTexture(*RESOURCE_MGR->GetTexture("graphics/Character/Shadow.png"));
	shadow.setScale(0.4f, 0.4f);

	//effectAnimator.SetTarget(&effectSprite);

	//effectAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Crowd_Effect"));
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

	if (mpBar != nullptr)
	{
		mpBar->Release();
		delete mpBar;
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
	if (!noSkill)
	{
		mpBar = new ProgressBar(TILE_SIZE * 0.8f, 3.f);
		mpBar->SetProgressColor(Color(0x00, 0x40, 0xFF));
		mpBar->SetBackgroundColor(Color(0, 0, 0, 100));
		mpBar->SetBackgroundOutline(Color::Black, 1.f);
		mpBar->SetProgressValue(0.f);
	}
	hpBarLocalPos = { -hpBar->GetSize().x * 0.5f, -(float)GetTextureRect().height + 10.f };
	hpBar->SetProgressValue(1.0f);
	starLocalPos = { 0.f, hpBarLocalPos.y };

	Utils::SetOrigin(shadow, Origins::BC);
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
	if (!noSkill)
	{
		stat[StatType::MP].SetCurrent(0.f);
		mpBar->SetProgressValue(0.f);
	}
	SetState(AnimStates::Idle);
	sprite.setColor(Color::White);
}

void Character::Update(float dt)
{
	if (!isAlive)
		return;

	hpBar->Update(dt);
	animator.Update(dt);
	effectAnimator.Update(dt);
	crowdControlAnimator.Update(dt);

	if (!noSkill)
		mpBar->Update(dt);

	if (isBattle)
	{
		if(hit)
		{
			hitDelta -= dt;
			if (hitDelta <= 0.f)
			{
				sprite.setColor(Color::White);
				hit = false;
			}
		}
		if (ccTimer > 0.f)
		{
			ccTimer -= dt;
			if (ccTimer < 0.f)
			{
				ccTimer = 0.f;
			}
			return;
		}

		SetDir(direction);

		switch (currState)
		{
		case AnimStates::Idle:
			UpdateIdle(dt);
			break;
		case AnimStates::MoveToIdle:
			if (name.compare("Slime00"))
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
		if (!move && !attack)
		{
			if (isAttack())
			{
				if (m_attackDelay <= 0.f)
				{
					//m_target = 공격가능할때 가장 가까운 상대 정보
					m_target = m_floodFill.GetNearEnemy(
						GAME_MGR->GetMainGridRef(),
						GAME_MGR->PosToIdx(position), targetType);
					if (!name.compare("Evan") && !attackRangeType)
					{
						attackRangeType = true;
						m_floodFill.SetArrSize(
							stat[StatType::AR].GetModifier(), stat[StatType::AR].GetModifier(), attackRangeType);

						SetState(AnimStates::Skill);
						stat[StatType::MP].SetCurrent(0.f);
						mpBar->SetProgressValue(0.f);
						if (skill != nullptr)
							skill->CastSkill(this);
					}

					if (!noSkill)
					{
						float gain = (!type.compare("Player")) ?
							GAME_MGR->GetManaPerAttack() : GAME_MGR->manaPerAttack;
						stat[StatType::MP].TranslateCurrent(gain);
						mpBar->SetProgressValue(stat[StatType::MP].GetCurRatio());
					}

					//타겟의 포지션

					lastDirection = Utils::Normalize(dynamic_cast<Character*>(m_target)->GetPos() - position);

					direction = lastDirection;
					SetDir(direction);

					SetState(AnimStates::Attack);
					dynamic_cast<Character*>(m_target)->TakeDamage(this);
					attack = true;
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
						//SetState(AnimStates::Move);
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
		//attack = false;

		if (move && !attack)
		{
			direction = destination - position;

			Translate(Utils::Normalize(direction) * dt * moveSpeed);
			if (currState != AnimStates::Move)
				SetState(AnimStates::Move);
			//불릿 힌트
			if (Utils::EqualFloat(Utils::Distance(destination, position), 0.f, dt * moveSpeed))
			{
				SetPos(destination);
				move = false;
				SetState(AnimStates::MoveToIdle);
			}
		}

		if (!noSkill && Utils::EqualFloat(stat[StatType::MP].GetCurRatio(), 1.f))
		{
			int starGrade = GetStarNumber();
			if (!name.compare("Evan") && starGrade <= 2)
			{
				if(attackRangeType)
				{
					m_floodFill.SetArrSize(
						stat[StatType::AR].GetModifier(), stat[StatType::AR].GetModifier(), false);
					attackRangeType = false;
				}
			}
			else
			{
				SetState(AnimStates::Skill);
				stat[StatType::MP].SetCurrent(0.f);
				mpBar->SetProgressValue(0.f);
				if (skill != nullptr)
					skill->CastSkill(this);
			}			
		}

		if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
		{
			lastDirection = direction;
		}
	}
}

void Character::Draw(RenderWindow& window)
{
	if (!isAlive)
		return;

	window.draw(shadow);
	SpriteObj::Draw(window);
	window.draw(effectSprite);
	if (ccTimer > 0.f)
	{
		window.draw(crowdControlSprite);
	}
	hpBar->Draw(window);
	star->Draw(window);
	for (auto& grid : itemGrid)
	{
		if (grid->GetActive())
			grid->Draw(window);
	}
	if (!noSkill)
		mpBar->Draw(window);
}

void Character::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	shadow.setPosition(pos);
	effectSprite.setPosition(pos);
	hpBar->SetPos(pos + hpBarLocalPos);
	star->SetPos(pos + starLocalPos);

	float xDelta = 5.f;
	for (auto& grid : itemGrid)
	{
		grid->SetPos(pos + hpBarLocalPos + Vector2f(xDelta, 25.f));
		xDelta += ITEM_SPRITE_SIZE;
	}

	if (!noSkill)
		mpBar->SetPos(pos + hpBarLocalPos + Vector2f(0, 4.f));
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
			SkillAnimation(skillPos[dirType]);
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
	stat[StatType::AR].SetDeltaMode(true);
	if (stat[StatType::MP].GetBase() > 0.f)
		noSkill = false;

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
	//공격받을때 이펙트
	sprite.setColor({ 255,0,0,180 });
	hit = true;
	hitDelta = 0.05f;

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

	if (!noSkill)
	{
		float gain = (!type.compare("Player")) ?
			GAME_MGR->GetManaPerDamage() : GAME_MGR->manaPerDamage;
		stat[StatType::MP].TranslateCurrent(gain);
		mpBar->SetProgressValue(stat[StatType::MP].GetCurRatio());
	}

	if (stat[StatType::HP].GetCurrent() <= 0.f)
	{
		// death
		isAlive = false;
		if (!attackerCharacter->GetNoSkill() && !attackerCharacter->GetType().compare("Player"))
		{
			Stat attackerMp = attackerCharacter->GetStat(StatType::MP);
			float killReward = attackerMp.GetBase() * (0.01f * GAME_MGR->altarData.gainManaWhenKill);
			attackerMp.TranslateCurrent(killReward);
			attackerCharacter->GetMpBar()->SetProgressValue(stat[StatType::MP].GetCurRatio());
		}
		Item* drop = GAME_MGR->DropItem(this);
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

void Character::TakeBuff(StatType sType, float potential, bool mode, Character* caster)
{
	float tempPtt = 0.f;
	switch (sType)
	{
	case StatType::AD:
		if (mode)
			stat[StatType::AD].AddDelta(potential);
		else
			stat[StatType::AD].AddDelta(-potential);
		break;
	case StatType::AP:
		tempPtt = potential * 0.01f;
		if (mode)
			stat[StatType::AP].AddDelta(tempPtt);
		else
			stat[StatType::AP].AddDelta(-tempPtt);
		break;
	case StatType::AS:
		tempPtt = potential * 0.01f;
		if (mode)
			stat[StatType::AS].AddDelta(tempPtt);
		else
			stat[StatType::AS].AddDelta(-tempPtt);
		break;
	case StatType::AR:
		if (mode)
			stat[StatType::AR].AddDelta(potential);
		else
			stat[StatType::AR].AddDelta(-potential);

		m_floodFill.SetArrSize(
			stat[StatType::AR].GetModifier(), stat[StatType::AR].GetModifier(), attackRangeType);
		break;
	case StatType::MS:
		if (mode)
			stat[StatType::MS].AddDelta(potential);
		else
			stat[StatType::MS].AddDelta(-potential);
		break;
	default:
		break;
	}
}

void Character::UpgradeStar(bool mode, bool useExtraUpgrade)
{
	if (GetStarNumber() == STAR_MAX)
		return;

	bool upgradeTwice = false;
	if (star->CalculateRandomChance(mode, useExtraUpgrade))
	{
		CLOG::Print3String("upgrade 2 level");
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

	//m_attackDelay = 1.f / stat[StatType::AS].GetModifier();
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
		
		newItem->SetActive(false);
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
		else
		{
			itemGrid[i]->SetSpriteTexture(
				*RESOURCE_MGR->GetTexture(items[i]->MakePath()), true);
			itemGrid[i]->SetSpriteScale(ITEM_SPRITE_SIZE, ITEM_SPRITE_SIZE);
			itemGrid[i]->SetOrigin(Origins::BC);
		}
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

void Character::SetCrowdControl(float time)
{
	ccTimer = time;
	crowdControlAnimator.SetTarget(&crowdControlSprite);
	crowdControlAnimator.AddClip(*RESOURCE_MGR->GetAnimationClip("Crowd_Effect"));
	Vector2f ccPos = position;
	ccPos.y -= 40.f;
	crowdControlSprite.setPosition(ccPos);
	crowdControlAnimator.Play("Crowd_Effect");
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

	if (enemyInfo.leng == 99999)
	{
		return false;
	}

	Vector2i coord = GAME_MGR->PosToIdx(GetPos());
	SetDestination(GAME_MGR->IdxToPos(enemyInfo.destPos));
	SetMainGrid(coord.y, coord.x, nullptr);
	SetMainGrid(enemyInfo.destPos.y, enemyInfo.destPos.x, this);
	enemyInfo.leng = 99999;
	//길찾기 성공할경우 트루 반환
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
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpIdle]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownIdle]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftIdle]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightIdle]));

		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpMove]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownMove]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftMove]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightMove]));

		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpAttack]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownAttack]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftAttack]));
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightAttack]));
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::UpAttack];
			ev.frame = 2;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			animator.AddEvent(ev);
		}
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
	}

	if (!noSkill)
	{
		if(name.compare("Slime00"))
		{
			animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpSkill]));
			animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftSkill]));
			animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightSkill]));

			{
				AnimationEvent ev;
				ev.clipId = resStringTypes[ResStringType::UpSkill];
				ev.frame = 2;
				ev.onEvent = bind(&Character::OnCompleteSkill, this);
				animator.AddEvent(ev);
			}
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
		}
		animator.AddClip(*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownSkill]));
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::DownSkill];
			ev.frame = 2;
			ev.onEvent = bind(&Character::OnCompleteSkill, this);
			animator.AddEvent(ev);
		}
	}
	if(!type.compare("Player"))
	{
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpAttackEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownAttackEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftAttackEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightAttackEffect]));
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::UpAttackEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::DownAttackEffect];
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
			ev.clipId = resStringTypes[ResStringType::LeftAttackEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		if(name.compare("Arveron") || name.compare("Daniel") || name.compare("Shelda"))
		{
			effectAnimator.AddClip(
				*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpSkillEffect]));
			effectAnimator.AddClip(
				*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownSkillEffect]));
			effectAnimator.AddClip(
				*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftSkillEffect]));
			effectAnimator.AddClip(
				*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightSkillEffect]));
			{
				AnimationEvent ev;
				ev.clipId = resStringTypes[ResStringType::UpSkillEffect];
				ev.frame = 3;
				ev.onEvent = bind(&Character::OnCompleteAttack, this);
				effectAnimator.AddEvent(ev);
			}
			{
				AnimationEvent ev;
				ev.clipId = resStringTypes[ResStringType::DownSkillEffect];
				ev.frame = 3;
				ev.onEvent = bind(&Character::OnCompleteAttack, this);
				effectAnimator.AddEvent(ev);
			}
			{
				AnimationEvent ev;
				ev.clipId = resStringTypes[ResStringType::LeftSkillEffect];
				ev.frame = 3;
				ev.onEvent = bind(&Character::OnCompleteAttack, this);
				effectAnimator.AddEvent(ev);
			}
			{
				AnimationEvent ev;
				ev.clipId = resStringTypes[ResStringType::RightSkillEffect];
				ev.frame = 3;
				ev.onEvent = bind(&Character::OnCompleteAttack, this);
				effectAnimator.AddEvent(ev);
			}
		}
	}
	else if (!name.compare("Goblin00") || !name.compare("Thief00"))
	{
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::UpSkillEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::DownSkillEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::LeftSkillEffect]));
		effectAnimator.AddClip(
			*RESOURCE_MGR->GetAnimationClip(resStringTypes[ResStringType::RightSkillEffect]));
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::UpSkillEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::DownSkillEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::LeftSkillEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
		}
		{
			AnimationEvent ev;
			ev.clipId = resStringTypes[ResStringType::RightSkillEffect];
			ev.frame = 3;
			ev.onEvent = bind(&Character::OnCompleteAttack, this);
			effectAnimator.AddEvent(ev);
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
	if (lastDirection.y)
	{
		animator.Play((lastDirection.y > 0.f) ? resStringTypes[ResStringType::DownIdle] : resStringTypes[ResStringType::UpIdle]);
	}
	else if (lastDirection.x)
	{
		animator.Play((lastDirection.x > 0.f) ? resStringTypes[ResStringType::RightIdle] : resStringTypes[ResStringType::LeftIdle]);
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
	if (attack)
		return;
	Vector2f temp = direction;
	SOUND_MGR->Play(resStringTypes[ResStringType::atkSound], 20.f, false);
	if (dirType == Dir::Up)
	{
		direction.x = 0.f;
		animator.Play(resStringTypes[ResStringType::UpAttack]);
		if (!type.compare("Player"))
		{
			if (!name.compare("Pria") || !name.compare("Arveron"))
			{
				effectAnimator.Play(resStringTypes[ResStringType::UpAttackEffect]);
				Vector2f tPos = m_target->GetPos();
				tPos.y += 15.f;
				effectSprite.setPosition(tPos);
			}
			else
			{
				effectAnimator.Play(resStringTypes[ResStringType::UpAttackEffect]);
				effectSprite.setPosition(position + attackPos);
			}
		}
	}
	else if (dirType == Dir::Down)
	{
		direction.x = 0.f;
		animator.Play(resStringTypes[ResStringType::DownAttack]);
		if (!type.compare("Player"))
		{
			if (!name.compare("Pria") || !name.compare("Arveron"))
			{
				effectAnimator.Play(resStringTypes[ResStringType::DownAttackEffect]);
				Vector2f tPos = m_target->GetPos();
				tPos.y += 15.f;
				effectSprite.setPosition(tPos);
			}
			else
			{
			effectAnimator.Play(resStringTypes[ResStringType::DownAttackEffect]);
			effectSprite.setPosition(position + attackPos);
			}
		}
		cout << position.x << "," << position.y << endl;
	}
	else if (dirType == Dir::Right)
	{
		direction.y = 0.f;
		animator.Play(resStringTypes[ResStringType::RightAttack]);
		if (!type.compare("Player"))
		{
			if (!name.compare("Pria") || !name.compare("Arveron"))
			{
				effectAnimator.Play(resStringTypes[ResStringType::RightAttackEffect]);
				Vector2f tPos = m_target->GetPos();
				tPos.y += 15.f;
				effectSprite.setPosition(tPos);
			}
			else
			{
				effectAnimator.Play(resStringTypes[ResStringType::RightAttackEffect]);
				effectSprite.setPosition(position + attackPos);
			}
		}
	}
	else if (dirType == Dir::Left)
	{
		direction.y = 0.f;
		animator.Play(resStringTypes[ResStringType::LeftAttack]);
		if (!type.compare("Player"))
		{
			if (!name.compare("Pria") || !name.compare("Arveron"))
			{
				effectAnimator.Play(resStringTypes[ResStringType::LeftAttackEffect]);
				Vector2f tPos = m_target->GetPos();
				tPos.y += 15.f;
				effectSprite.setPosition(tPos);
			}
			else
			{
				effectAnimator.Play(resStringTypes[ResStringType::LeftAttackEffect]);
				effectSprite.setPosition(position + attackPos);
			}
		}
	}
	direction = temp;

}

void Character::SkillAnimation(Vector2f skillPos)
{
	if (lastDirection.y)
	{
		animator.Play(lastDirection.y > 0.f ? resStringTypes[ResStringType::DownSkill] : resStringTypes[ResStringType::UpSkill]);
		if(name.compare("Arveron") || name.compare("Daniel") || name.compare("Shelda"))
		{
			effectAnimator.Play(lastDirection.y > 0.f ? resStringTypes[ResStringType::DownSkillEffect] : resStringTypes[ResStringType::UpSkillEffect]);
			effectSprite.setPosition(position + skillPos);
		}
	}
	else if (lastDirection.x)
	{
		animator.Play(lastDirection.x > 0.f ? resStringTypes[ResStringType::RightSkill] : resStringTypes[ResStringType::LeftSkill]);
		if (name.compare("Arveron") || name.compare("Daniel") || name.compare("Shelda"))
		{
			effectAnimator.Play(lastDirection.x > 0.f ? resStringTypes[ResStringType::RightSkillEffect] : resStringTypes[ResStringType::LeftSkillEffect]);
			effectSprite.setPosition(position + skillPos);
		}
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

	if (!Utils::EqualFloat(direction.y, 0.f) || !Utils::EqualFloat(direction.x, 0.f))
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
	if (!Utils::EqualFloat(direction.y, 0.f) || !Utils::EqualFloat(direction.x, 0.f))
	{
		SetState(AnimStates::Move);
		return;
	}
}

void Character::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.y, 0.f) && Utils::EqualFloat(direction.x, 0.f))
	{
		SetState(AnimStates::MoveToIdle);
		return;
	}
	if (!Utils::EqualFloat(direction.y, lastDirection.y))
	{
		animator.Play((direction.y > 0.f) ? resStringTypes[ResStringType::DownMove] : resStringTypes[ResStringType::UpMove]);
		move = false;
	}
	else if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? resStringTypes[ResStringType::RightMove] : resStringTypes[ResStringType::LeftMove]);
		move = false;
	}
	if (move)
		return;
}

void Character::UpdateAttack(float dt)
{
	if (Utils::EqualFloat(direction.y, 0.f) && Utils::EqualFloat(direction.x, 0.f))
	{
		//SetState(AnimStates::MoveToIdle);
		//attack = false;
	}
}

void Character::UpdateSkill(float dt)
{
	move = false;
	if (!name.compare("Slime00"))
	{
		if (!Utils::EqualFloat(direction.y, 0.f) && !Utils::EqualFloat(direction.x, 0.f))
		{
			SetState(AnimStates::Idle);
		}
	}
	else
	{
		if (!Utils::EqualFloat(direction.y, 0.f) && !Utils::EqualFloat(direction.x, 0.f))
		{
			SetState(AnimStates::MoveToIdle);
		}
	}
}

void Character::SetDir(Vector2f direction)
{
	if (abs(direction.x) < abs(direction.y)|| abs(direction.x) == abs(direction.y))
	{
		if (direction.y > 0.f)
		{
			dirType = Dir::Down;
		}
		else if (direction.y < 0.f)
		{
			dirType = Dir::Up;
		}
	}
	else
	{
		if (direction.x > 0.f)
		{
			dirType = Dir::Right;
		}
		else if (direction.x < 0.f)
		{
			dirType = Dir::Left;
		}
	}

	//if (dirType == Dir::Down)
	//	direction = { 0,1 };
	//else if (dirType == Dir::Up)
	//	direction = { 0,-1 };
	//else if (dirType == Dir::Left)
	//	direction = { -1,0 };
	//else if (dirType == Dir::Right)
	//	direction = { 1,0 };
}
