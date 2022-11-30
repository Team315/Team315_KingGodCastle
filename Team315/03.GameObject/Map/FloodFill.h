#pragma once
#include "RectangleObj.h"

class GameObj;
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

	// 내 공격 범위 안에 적이 있는지 찾아줌
	bool FloodFillSearch(vector<GameObj*>& map, Vector2i myPos, Vector2i enPos, string targetType);
	
	// 처음에 타입과 사이즈 정해줌
	void SetArrSize(int height, int width, bool attackType);

	//그리드 받아와서 셋해줌
	void SetFloodFill(vector<GameObj*>& map, Vector2i myPos, Vector2i enPos, string targetType);

	bool isInRange(int col, int row);
	bool isDestination(int grid);
	bool IsAttack();


	const int crossX[100] = { 0, 0, 0, 1, -1,-1, 1, };
	const int crossY[100] = { 0, -1, 1, 0, 0,-1, -1 };
};

