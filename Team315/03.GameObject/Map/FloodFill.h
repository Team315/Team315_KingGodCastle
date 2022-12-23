#pragma once
#include "RectangleObj.h"

class SpriteObj;
class FloodFill:public RectangleObj
{
protected:
	vector<RectangleObj> Areas;
	vector<vector<int>> grid;

	vector<vector<bool>> m_areaArr;//���� ���ݹ���
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

	// �� ���� ���� �ȿ� ���� �ִ��� ã����
	bool FloodFillSearch(vector<SpriteObj*>& map, Vector2i myPos, Vector2i enPos, string targetType);
	
	// ó���� Ÿ�԰� ������ ������
	void SetArrSize(int height, int width, bool attackType);

	//�׸��� �޾ƿͼ� ������
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