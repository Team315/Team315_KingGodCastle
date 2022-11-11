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
	window.draw(m_star);
}

void SelectStar::SetSelectStar(Vector2f pos, int grade)
{
	SetPos(pos);
	SetOrigin(Origins::MC);

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
