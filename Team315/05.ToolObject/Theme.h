#pragma once
#include "SpriteObj.h"


class Theme : public SpriteObj
{
protected:
	RectangleShape m_background;
	int m_index;
	bool isEdge;

public:
	Theme(int index);
	~Theme();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetTheme(Vector2f pos, int index);
	string SetPath(int num);

	int GetIndex();

	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeColor(bool check);
	void OnEdge(int index);
};

