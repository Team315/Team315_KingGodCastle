#include "Theme.h"
#include "Include.h"

Theme::Theme()
{
}

Theme::~Theme()
{
}

void Theme::Init()
{
}

void Theme::Release()
{
}

void Theme::Update(float dt)
{

}

void Theme::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Theme::SetTheme(Vector2f pos, int index)
{
	m_index = index;
	//SetTexture(*RESOURCE_MGR->GetTexture(SetPath(m_index)));
	sprite.setTexture(*RESOURCE_MGR->GetTexture(SetPath(m_index)));
	sprite.setPosition(pos);
	SetOrigin(Origins::MC);
}

string Theme::SetPath(int num)
{

	string path = "graphics/ToolUi/theme/Themes_Chapter_";
	string sNum = to_string(num);
	string png = ".png";

	return path + sNum + png;
}

