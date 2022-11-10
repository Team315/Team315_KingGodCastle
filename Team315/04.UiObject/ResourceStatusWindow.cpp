#include "ResourceStatusWindow.h"

ResourceStatusWindow::ResourceStatusWindow()
{
}

ResourceStatusWindow::~ResourceStatusWindow()
{
}

void ResourceStatusWindow::Draw(RenderWindow& window)
{
	window.draw(shape);
	window.draw(sprite);

	Object::Draw(window);
}

void ResourceStatusWindow::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	shape.setPosition(pos + shapeLocalPos);
	sprite.setPosition(pos + spriteLocalPos);
}

void ResourceStatusWindow::SetSpriteLocalPos(Vector2f sprPos)
{
	spriteLocalPos = sprPos;
}

void ResourceStatusWindow::SetShapeLocalPos(Vector2f shapePos)
{
	shapeLocalPos = shapePos;
}

void ResourceStatusWindow::SetTexture(Texture& tex)
{
	sprite.setTexture(tex);
}

void ResourceStatusWindow::SetShapeColor(Color color)
{
	shape.setFillColor(color);
}