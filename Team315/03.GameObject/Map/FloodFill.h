#pragma once
#include "RectangleObj.h"

class SpriteObj;
class FloodFill:public RectangleObj
{
protected:
	vector<RectangleObj> Areas;
	vector<vector<int>> grid;

	vector<vector<bool>> m_areaArr;//본인 공격범위
	vector<Vector2i> m_arr;

	int m_count;
	int m_Height;
	int m_Width;

	int m_isAttackAreas;
	
public:
	FloodFill();
	~FloodFill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	// 내 공격 범위 안에 적이 있는지 찾아줌
	bool FloodFillSearch(vector<SpriteObj*>& map, Vector2i myPos, Vector2i enPos, string targetType);
	
	// 처음에 타입과 사이즈 정해줌
	void SetArrSize(int height, int width, bool attackType);

	//그리드 받아와서 셋해줌
	void SetFloodFill(vector<SpriteObj*>& map, Vector2i myPos, Vector2i enPos, string targetType);


	/////////////////////////////////////////


	void SetGeneralArr(vector<SpriteObj*>& map, string targetType);
	vector<Vector2i> GetGeneralInfo(vector<SpriteObj*>& map, string targetType);

	SpriteObj* GetNearEnemy(vector<SpriteObj*>& map, Vector2i myPos, string targetType);

	void SetAttackAreas(int count);
	void DrawingAttackAreas(bool onOff, Vector2i myPos);

	bool isInRange(int col, int row);
	bool isDestination(int grid);
	bool GetIsAttackAreas() { return m_isAttackAreas; };

	vector<RectangleObj>* GetAreas() { return &Areas; }
};