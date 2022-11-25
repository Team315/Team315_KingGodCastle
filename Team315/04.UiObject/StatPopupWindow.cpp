#include "StatPopupWindow.h"

StatPopupWindow::StatPopupWindow(float x, float y)
	: RectangleObj(x, y)
{
}

StatPopupWindow::~StatPopupWindow()
{
}

void StatPopupWindow::Draw(RenderWindow& window)
{
	RectangleObj::Draw(window);
}

void StatPopupWindow::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
}

void StatPopupWindow::SetOrigin(Origins origin)
{
	RectangleObj::SetOrigin(origin);
}