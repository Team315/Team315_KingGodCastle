#pragma once
#include "Include.h"
#include <set>
#include <stack>
#include "Character.h"

struct Cell
{
	Vector2i parent;
	double f;// g+h
	double g;//��������� ���� �����ġ���� �Ÿ�
	double h;//���� ��� ��ġ���� ��ǥ�������� heuristic�� �Ÿ�
};

class AStar
{
protected:
	int ROW;
	int COL;
	char zmap[14][7];
	vector<vector<int>> grid;

	int count;

	const int dx1[4] = { 0, 0, 1, -1 };
	const int dy1[4] = { -1, 1, 0, 0 };

	Vector2i m_pair;
	pair<double, Vector2i> m_pPair;
public:
	AStar();
	~AStar();

	int AstarSearch(vector<Character*>& map,Vector2i myPos, Vector2i enPos);

	//������ǥ�� ���������� ��ġ�ϴٸ� ��, �ƴϸ� ������ ��ȯ�ϴ� �Լ�.
	bool isDestination(int row, int col, Vector2i dst);

	//������ǥ�� ��ü �ʾȿ� �����ϸ� , �ƴϸ� ������ ��ȯ�ϴ� �Լ�.
	bool isInRange(int row, int col);

	//������ǥ�� ���̾ƴ϶�� ��, �ƴϸ� ������ ��ȯ�ϴ� �Լ�.
	bool isUnBlocked(vector<vector<int>>& map, int row, int col);

	//������ǥ�κ��� �������������� �Ÿ��� ����ϴ� �Լ�.
	double GethValue(int row, int col, Vector2i dst);

	//backtracking�� �̿��Ͽ� �ִܰ�θ� Ž���ϴ� �Լ�.
	void tracePath(Cell cellDetails[14][7], Vector2i enpos);

	void SetAstar(vector<Character*>& map, Vector2i myPos, Vector2i enPos);
};