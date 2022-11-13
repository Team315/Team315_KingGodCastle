#include "Number.h"
#include "Include.h"

Number::Number(int index)
	:isEdge(false), m_index(index)
{
	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/number/Number_Font_Bar.png"));
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



	if (isEdge)
	{
		window.draw(m_edge);
	}

	//window.draw(sprite);
	window.draw(m_BeforeNum);
	window.draw(m_AffterNum);
	
}

string Number::SetPath(int num)
{
	string path = "graphics/ToolUi/number/Number_Font_";
	string sNum = to_string(num);
	string png = ".png";

	return path + sNum + png;
}

void Number::SetNum(Vector2f pos, int beforeNum, int affterNum, int index)
{
	//sprite.setPosition(pos);
	SetPos(pos);
	SetOrigin(Origins::MC);

	FloatRect rect = sprite.getGlobalBounds();
	m_edge.setSize({ rect.width, rect.height });
	m_edge.setPosition(pos);
	Utils::SetOrigin(m_edge, Origins::MC);
	m_edge.setOutlineThickness(3.f);
	m_edge.setOutlineColor(Color::Blue);
	m_edge.setFillColor({0, 0, 0, 0});

	m_BeforeNum.setTexture(*RESOURCE_MGR->GetTexture(SetPath(beforeNum)));
	m_BeforeNum.setPosition(pos);
	Utils::SetOrigin(m_BeforeNum, Origins::MR);

	m_AffterNum.setTexture(*RESOURCE_MGR->GetTexture(SetPath(affterNum)));
	m_AffterNum.setPosition(pos);
	Utils::SetOrigin(m_AffterNum, Origins::ML);
}

int Number::GetIndex()
{
	return m_index;
}

bool Number::CollideTest(Vector2f pos)
{
	if (hitbox.getGlobalBounds().contains(pos))
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

bool Number::CollisionCheck(Vector2f pos, int index)
{

	/*FloatRect rect = sprite.getGlobalBounds();

	if (rect.contains(pos))
		sprite.getGlobalBounds().contains(pos);*/

	return ChangeColor(sprite.getGlobalBounds().contains(pos));
}

bool Number::ChangeColor(bool check)
{
	if (check) 
	{
		Color color = sprite.getColor();

		color.r = 0;
		//color.g = 0;
		color.b = 255;

		sprite.setColor(color);

		return true;
	}
	else
	{
		Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;

		sprite.setColor(color);

		return false;
	}
	
}

void Number::OnEdge(int index)
{
	if (m_index == index)
	{
		isEdge = true;
	}
	else
	{
		isEdge = false;
	}
}

