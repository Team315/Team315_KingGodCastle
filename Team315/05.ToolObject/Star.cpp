#include "Star.h"
#include "Include.h"
Star::Star()
{
}

Star::~Star()
{
}

void Star::Init()
{
}

void Star::Release()
{
}

void Star::Update(float dt)
{
}

void Star::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Star::SetStar(FloatRect pos, int grade)
{
	m_grade = grade;
	Vector2f vec = { pos.left + (pos.width * 0.5f) ,pos.top + 20.f };
	SetPos(vec);
	SetOrigin(Origins::MC);
	SetTexture(*RESOURCE_MGR->GetTexture(SetPath(grade)));
}

string Star::SetPath(int grade)
{
	string path = "graphics/ToolUi/star/Star_";
	string sNum = to_string(grade / 10) + to_string(grade % 10);
	string png = ".png";

	return path + sNum + png;
}
