#include "SelectStar.h"

SelectStar::SelectStar()
{
	sprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/ToolUi/star/CoverStar.png"));
}

SelectStar::~SelectStar()
{
}

void SelectStar::Init()
{
}

void SelectStar::Release()
{
}

void SelectStar::Update(float dt)
{
}

void SelectStar::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(m_Edge);
	window.draw(m_star);
}

void SelectStar::SetSelectStar(Vector2f pos, int grade)
{
	m_grade = grade;
	SetPos(pos);
	SetOrigin(Origins::MC);

	FloatRect rect = sprite.getGlobalBounds();
	m_Edge.setSize({ rect.width,rect.height });
	m_Edge.setFillColor({ 0,0,0,0 });
	m_Edge.setPosition(pos);
	m_Edge.setOutlineThickness(-4.f);
	Utils::SetOrigin(m_Edge, Origins::MC);

	m_star.setTexture(*RESOURCE_MGR->GetTexture(SetPath(grade)));
	m_star.setPosition(pos);
	Utils::SetOrigin(m_star, Origins::MC);
}

string SelectStar::SetPath(int grade)
{

	string path = "graphics/ToolUi/star/Star_";
	string sNum = to_string(grade / 10) + to_string(grade % 10);
	string png = ".png";

	return path + sNum + png;
}

int SelectStar::GetIndex()
{
	return m_grade;
}

bool SelectStar::CollisionCheck(Vector2f pos, int index)
{
	return ChangeSize(sprite.getGlobalBounds().contains(pos));
}

bool SelectStar::ChangeSize(bool check)
{
	if (check)
	{
		m_star.setScale({ 1.3f,1.3f });
		return true;
	}
	else
	{
		m_star.setScale({ 1.f,1.f });
		return false;
	}
}

void SelectStar::OnEdge(int index)
{
	if (m_grade == index)
	{
		Color color;


		color.b = 255;

		m_Edge.setOutlineColor(color);

		isEdge = true;
	}
	else
	{
		Color color;

		color.r = 0;
		color.g = 0;
		color.b = 0;

		m_Edge.setOutlineColor(color);

		isEdge = false;
	}
}
