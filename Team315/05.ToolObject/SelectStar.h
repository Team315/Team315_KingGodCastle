#pragma once
#include "SpriteObj.h"
#include "Include.h"

class SelectStar : public SpriteObj
{
protected:
	Sprite m_star;
	RectangleShape m_Edge;
	int m_grade;
	bool isEdge;
public:
	SelectStar();
	~SelectStar();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetSelectStar(Vector2f pos, int grade);
	string SetPath(int grade);

	int GetIndex();

	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeSize(bool check);
	void OnEdge(int index);
};

