#pragma once
#include "Include.h"
#include <set>
#include <stack>
#include "Character.h"

struct Cell
{
	Vector2i parent;
	double f;// g+h
	double g;//출발점부터 현재 노드위치까지 거리
	double h;//현재 노드 위치부터 목표점까지의 heuristic한 거리
};

struct EnemyInfo
{
	int leng;
	Vector2i destPos;
	EnemyInfo() { leng = 0; destPos = { 0,0 }; }
};
class AStar
{
protected:
	int ROW;
	int COL;
	char zmap[14][7];
	vector<vector<int>> grid;

	EnemyInfo enemyInfo;
	int count;

	const int crossX1[4] = { 0, 0, 1, -1 };
	const int crossY1[4] = { -1, 1, 0, 0 };

	Vector2i m_pair;
	pair<double, Vector2i> m_pPair;
public:
	static int counter;

	AStar();
	~AStar();

	EnemyInfo AstarSearch(vector<GameObj*>& map,Vector2i myPos, Vector2i enPos);

	//현재좌표가 도착지점과 일치하다면 참, 아니면 거짓을 반환하는 함수.
	bool isDestination(int row, int col, Vector2i dst);

	//현재좌표가 전체 맵안에 존재하면 , 아니면 거짓을 반환하는 함수.
	bool isInRange(int row, int col);

	//현재좌표가 벽이아니라면 참, 아니면 거짓을 반환하는 함수.
	bool isUnBlocked(vector<vector<int>>& map, int row, int col);

	//현재좌표로부터 도착지점까지의 거리를 계산하는 함수.
	double GethValue(int row, int col, Vector2i dst);

	//backtracking을 이용하여 최단경로를 탐색하는 함수.
	void tracePath(Cell cellDetails[14][7], Vector2i enpos);

	void SetAstar(vector<GameObj*>& map, Vector2i myPos, Vector2i enPos);
};