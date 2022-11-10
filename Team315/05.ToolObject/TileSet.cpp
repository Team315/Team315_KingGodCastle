#include "TileSet.h"

TileSet::TileSet()
{
}

TileSet::~TileSet()
{
}

void TileSet::SetPos(const Vector2f& pos)
{
	Vector2f delta = pos - position;

	for (int i = 0; i < vertexArray.getVertexCount(); i++)
	{
		vertexArray[i].position += delta;
	}
	position = pos;
}



const Vector2f& TileSet::GetPos() const
{
	return position;
}

void TileSet::Update(float dt)
{
}

void TileSet::Draw(RenderWindow& window)
{
	window.draw(vertexArray, texture);
}
