#pragma once
#include "SpriteObj.h"

class Number : public SpriteObj
{
protected:
	Sprite m_BeforeNum;
	Sprite m_AffterNum;

	RectangleShape m_edge;
	//FloatRect Edge;
	int m_index;
	bool isEdge;
public:
	Number(int index);
	~Number();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	string SetPath(int num);
	void SetNum(Vector2f pos, int beforeNum, int affterNum, int index);
	int GetIndex();
	//void SetOrigins(Origins origin);

	bool CollideTest(Vector2f pos);
	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeColor(bool check);
	void OnEdge(int index);
};
