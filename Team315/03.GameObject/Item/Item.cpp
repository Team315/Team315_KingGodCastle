#include "Item.h"

Item::Item(int grade, bool useExtraChance, ItemType iType)
	: grade(grade), itemType(iType), potential(0.f), move(false),
	statType(StatType::None), delta(0.f), moveSpeed(300.f)
{
	/*bool extraUpgrade =
		Utils::RandomRange(0, 100) < GAME_MGR->GetExtraGradeUpChance();
	if (useExtraChance && extraUpgrade && (grade + 1) != TIER_MAX)
	{
		cout << "item 2 upgrade" << endl;
		this->grade = grade + 1;
	}
	else */
	this->grade = grade;
	if (iType == ItemType::Book && this->grade >= TIER_MAX - 1)
		this->grade = 2;

	SetType("Item");
	sprite.setTexture(*RESOURCE_MGR->GetTexture(MakePath()), true);
	SetOrigin(Origins::BC);
	shadow.setScale(0.4f, 0.4f);

	switch (itemType)
	{
	case ItemType::Armor:
		statType = StatType::HP;
		break;
	case ItemType::Bow:
		statType = StatType::AS;
		break;
	case ItemType::Staff:
		statType = StatType::AP;
		break;
	case ItemType::Sword:
		statType = StatType::AD;
		break;
	case ItemType::Book:
		statType = StatType::None;
		break;
	}
	if (itemType != ItemType::Book)
		potential = GAME_MGR->GetItemStatMapElem(statType, this->grade);

	shadow.setTexture(*RESOURCE_MGR->GetTexture("graphics/Character/Shadow.png"));
	spriteLocalPos = Vector2f(0, -10.f);
}

Item::~Item()
{
}

void Item::Init()
{
	Vector2f hitboxSize(
		GetTextureRect().width * 0.5f < TILE_SIZE ? TILE_SIZE : GetTextureRect().width * 0.5f,
		GetTextureRect().height * 0.5f < TILE_SIZE ? TILE_SIZE : GetTextureRect().height * 0.5f);

	SetHitbox(FloatRect(0, 0, hitboxSize.x, hitboxSize.y), Origins::BC);
	Object::Init();
}

void Item::Update(float dt)
{
	if (!enabled)
		return;

	spriteLocalPos.y += cos(delta) * 0.02f; // amplitude
	SetPos(position);
	delta += (dt * 3.f); // floating speed

	if (move)
	{
		Translate(Utils::Normalize(destination - position) * dt * moveSpeed);
		if (Utils::EqualFloat(Utils::Distance(destination, position), 0.f, dt * moveSpeed))
		{
			SetPos(destination);
			move = false;
			SetHitBoxActive(true);
		}
	}
}

void Item::Draw(RenderWindow& window)
{
	window.draw(shadow);
	SpriteObj::Draw(window);
}

void Item::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(position + spriteLocalPos);
	shadow.setPosition(position);
	Utils::SetOrigin(shadow, Origins::BC);
}

string Item::MakePath()
{
	string path = "graphics/battleScene/Item_";

	switch (itemType)
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
	case ItemType::Book:
		path += "Book";
		break;
	default:
		cout << "fail" << endl;
		return "fail";
	}
	path += (to_string(grade) + ".png");
	return path;
}

string Item::GetStatTypeString()
{
	string str = "";

	switch (statType)
	{
	case StatType::HP:
		str = "HP";
		break;
	case StatType::AD:
		str = "AD";
		break;
	case StatType::AP:
		str = "AP";
		break;
	case StatType::AS:
		str = "AS";
		break;
	}
	return str;
}

bool Item::Upgrade()
{
	int gradeLimit = TIER_MAX - 1;
	bool ret = false;
	if (grade < gradeLimit)
	{
		ret = true;
		grade++;
		sprite.setTexture(*RESOURCE_MGR->GetTexture(MakePath()), true);
		SetOrigin(Origins::BC);
		potential = GAME_MGR->GetItemStatMapElem(statType, grade);
	}
	return ret;
}

void Item::SetDestination(Vector2f dest)
{
	move = true;
	destination = dest;
	SetHitBoxActive(false);
}