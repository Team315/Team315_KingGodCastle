#pragma once
#include "RectangleObj.h"

class Character;
class FloodFill:public RectangleObj
{
protected:
	vector<RectangleObj*> Areas;
	vector<vector<int>> grid;
	vector<vector<bool>> m_areaArr;

	int m_count;
	int m_Height;
	int m_Width;
	
public:
	FloodFill();
	~FloodFill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	bool FloodFillSearch(vector<Character*>& map, Vector2i myPos, Vector2i enPos, string targetType);
	void SetArrSize(int height, int width, bool attackType);
	void SetFloodFill(vector<Character*>& map, Vector2i myPos, Vector2i enPos, string targetType);

	bool isInRange(int col, int row);
	bool isDestination(int grid);
	bool IsAttack();


	const int crossX[100] = { 0, 0, 0, 1, -1,-1, 1, };
	const int crossY[100] = { 0, -1, 1, 0, 0,-1, -1 };
};

