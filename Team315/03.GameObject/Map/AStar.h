#pragma once
#include "Include.h"
#include <set>
#include <stack>
#include "Character.h"

struct Cell
{
	Vector2i parent;
	double f, g, h;
};

class AStar
{
protected:
	int ROW;
	int COL;
	char zmap[14][7];

	const int dx1[4] = { 0, 0, 1, -1 };
	const int dy1[4] = { -1, 1, 0, 0 };

	Vector2i m_pair;
	pair<double, Vector2i> m_pPair;
public:
	AStar();
	~AStar();

	bool AstarSearch(vector<vector<int>>& map,Vector2i myPos, Vector2i enPos);
	bool isDestination(int row, int col, Vector2i dst);
	bool isInRange(int row, int col);
	bool isUnBlocked(vector<vector<int>>& map, int row, int col);
	double GethValue(int row, int col, Vector2i dst);
	void tracePath(Cell cellDetails[14][7], Vector2i dst);
};