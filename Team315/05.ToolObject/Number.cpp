#include "Number.h"
#include "Include.h"

Number::Number()
{
	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/number/Nuber_Font_Bar.png"));
}

Number::~Number()
{
}

void Number::Init()
{
}

void Number::Release()
{
}

void Number::Update(float dt)
{
	
}

void Number::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	//window.draw(sprite);
	window.draw(m_BeforeNum);
	window.draw(m_AffterNum);
	
}

string Number::SetPath(int num)
{
	string path = "graphics/ToolUi/number/Nuber_Font_";
	string sNum = to_string(num);
	string png = ".png";

	return path + sNum + png;
}

void Number::SetNum(Vector2f pos, int beforeNum, int affterNum, int index)
{
	//sprite.setPosition(pos);
	SetPos(pos);
	SetOrigin(Origins::MC);

	m_BeforeNum.setTexture(*RESOURCE_MGR->GetTexture(SetPath(beforeNum)));
	m_BeforeNum.setPosition(pos);
	Utils::SetOrigin(m_BeforeNum, Origins::MR);

	m_AffterNum.setTexture(*RESOURCE_MGR->GetTexture(SetPath(affterNum)));
	m_AffterNum.setPosition(pos);
	Utils::SetOrigin(m_AffterNum, Origins::ML);
}

bool Number::CollideTest(Vector2f pos)
{
	if (hitbox.getGlobalBounds().contains(pos))
	{
		return true;
	}
	return false;
}

//void Number::SetOrigins(Origins origin)
//{
//
//}
