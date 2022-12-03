#include "ItemPopupWindow.h"
#include "Include.h"

ItemPopupWindow::ItemPopupWindow(float x, float y)
	: SpriteGrid(x, y)
{
	SetOutline(Color::Black, 2.0f);
	SetFillColor(Color(0, 0, 0, 150.f));

	/*SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	SetTextStyle(Color::White, 20, Color::Black, -1.0f);
	SetTextLocalPos(Vector2f(10.f, 10.f));*/
}

ItemPopupWindow::~ItemPopupWindow()
{
}

void ItemPopupWindow::Draw(RenderWindow& window)
{
	SpriteGrid::Draw(window);
}

void ItemPopupWindow::SetOrigin(Origins origin)
{
}

void ItemPopupWindow::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	sprite.setPosition(pos + Vector2f(5.f, 5.f));
}