#include "Theme.h"
#include "Include.h"

Theme::Theme(int index)
	:m_index(index), isEdge(false)
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
	window.draw(m_background);
	window.draw(sprite);
}

void Theme::SetTheme(Vector2f pos, int index)
{
	m_index = index;
	//SetTexture(*RESOURCE_MGR->GetTexture(SetPath(m_index)));
	sprite.setTexture(*RESOURCE_MGR->GetTexture(SetPath(m_index)));
	sprite.setPosition(pos);
	SetOrigin(Origins::MC);

	FloatRect rect = sprite.getGlobalBounds();
	m_background.setSize({rect.width,rect.height});
	m_background.setFillColor(Color::White);
	m_background.setPosition(pos);
	m_background.setOutlineThickness(-4.f);
	Utils::SetOrigin(m_background,Origins::MC);
}

string Theme::SetPath(int num)
{

	string path = "graphics/ToolUi/theme/Themes_Chapter_";
	string sNum = to_string(num);
	string png = ".png";

	return path + sNum + png;
}

int Theme::GetIndex()
{
	return m_index;
}

bool Theme::CollisionCheck(Vector2f pos, int index)
{
	/*FloatRect rect = sprite.getGlobalBounds();

	if (rect.contains(pos))
		sprite.getGlobalBounds().contains(pos);*/

	return ChangeColor(sprite.getGlobalBounds().contains(pos));
}

bool Theme::ChangeColor(bool check)
{
	if (check)
	{
		Color color;

		color.r = 255;
		color.g = 255;
		color.b = 255;

		m_background.setFillColor(color);
		return true;
	}
	else
	{
		Color color;
		color.r = 0;
		color.g = 0;
		color.b = 0;

		m_background.setFillColor(color);

		return false;
	}
}

void Theme::OnEdge(int index)
{
	if (m_index == index)
	{
		Color color;

		//color.r = 255;
		//color.g = 255;
		color.b = 255;

		m_background.setOutlineColor(color);

		isEdge = true;
	}
	else
	{
		Color color;

		color.r = 0;
		color.g = 0;
		color.b = 0;

		m_background.setOutlineColor(color);

		isEdge = false;
	}
}

