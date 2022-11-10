#pragma once
#include "VertexArrayObj.h"


class TileSet : public VertexArrayObj
{
protected:

public:
	TileSet();
	~TileSet();
	virtual void SetPos(const Vector2f& pos);
	virtual const Vector2f& GetPos() const;
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);


};

