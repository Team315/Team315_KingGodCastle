#pragma once
#include "Include.h"
#include <set>
#include <stack>
#include "SpriteObj.h"

struct Cell
{
	Vector2i parent;
	double f;// g+h
	double g;//��������� ���� �����ġ���� �Ÿ�
	double h;//���� ��� ��ġ���� ��ǥ�������� heuristic�� �Ÿ�
};

struct EnemyInfo
{
	//���� ����� Ÿ�� ���� �� ������
	int leng;
	//������ ��ĭ�� ����
	Vector2i destPos;
	EnemyInfo() { leng = 0; destPos = { 0,0 }; }
};
class AStar
{
protected:
	int ROW;
	int COL;
	vector<vector<int>> grid;

	EnemyInfo enemyInfo;
	int count;
	int nCount;
	int maxNum;
	Vector2i Vec;
	const int crossX1[4] = { 0, 0, 1, -1 };
	const int crossY1[4] = { -1, 1, 0, 0 };

	Vector2i m_pair;
	pair<double, Vector2i> m_pPair;

	Vector2i m_nearEnPos;
	int m_nearLeng;
public:

	AStar();
	~AStar();

	EnemyInfo AstarSearch(vector<SpriteObj*>& map,Vector2i myPos, Vector2i enPos);
	Vector2i AstarSearch(vector<SpriteObj*>& map, Vector2i myPos, vector<Vector2i> GeneralArr);
	//������ǥ�� ���������� ��ġ�ϴٸ� ��, �ƴϸ� ������ ��ȯ�ϴ� �Լ�.
	bool isDestination(int row, int col, Vector2i dst);
	bool isDestination(int row, int col, vector<Vector2i> GeneralArr);

	//������ǥ�� ��ü �ʾȿ� �����ϸ� , �ƴϸ� ������ ��ȯ�ϴ� �Լ�.
	bool isInRange(int row, int col);

	//������ǥ�� ���̾ƴ϶�� ��, �ƴϸ� ������ ��ȯ�ϴ� �Լ�.
	bool isUnBlocked(vector<vector<int>>& map, int row, int col);

	//������ǥ�κ��� �������������� �Ÿ��� ����ϴ� �Լ�.
	double GethValue(int row, int col, Vector2i dst);
	double GethValue(int row, int col, vector<Vector2i> GeneralArr);

	//backtracking�� �̿��Ͽ� �ִܰ�θ� Ž���ϴ� �Լ�.
	void tracePath(Cell cellDetails[14][7], Vector2i enpos);
	void tracePath(Cell cellDetails[14][7], vector<Vector2i>& GeneralArr);

	void SetAstar(vector<SpriteObj*>& map, Vector2i myPos, Vector2i enPos);
};