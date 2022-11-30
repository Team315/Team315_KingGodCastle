#include "Item.h"

Item::Item(int grade, ItemType type)
	: grade(grade), type(type)
{
	SetType("Item");
	SetTexture(*RESOURCE_MGR->GetTexture(MakePath()));
	SetOrigin(Origins::BC);
}

Item::~Item()
{
}

void Item::Init()
{
	GameObj::Init();
}

void Item::Update(float dt)
{
}

void Item::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Item::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(position + Vector2f(0, -10.f));
}

string Item::MakePath()
{
	string path = "graphics/battleScene/Item_";

	switch (type)
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