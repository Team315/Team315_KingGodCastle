#include "AStar.h"

constexpr double INF = 1e9 + 7;

AStar::AStar()
	:ROW(7), COL(14), count(0), m_nearLeng(9999)
{
}

AStar::~AStar()
{
}

EnemyInfo AStar::AstarSearch(vector<GameObj*>& map, Vector2i myPos, Vector2i enPos)
{
	enemyInfo.leng = 0;

	SetAstar(map, myPos, enPos);

	bool closedList[14][7];
	memset(closedList, false, sizeof(closedList));

	Cell cellDetails[14][7];

	// 모든 좌표 초기화
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h = INF;
			cellDetails[i][j].parent.x = cellDetails[i][j].parent.y = -1;
		}
	}

	// 시작 좌표 초기화
	int sy = myPos.y;
	int sx = myPos.x;
	cellDetails[sy][sx].f = cellDetails[sy][sx].g = cellDetails[sy][sx].h = 0.0;
	cellDetails[sy][sx].parent.x = sx;
	cellDetails[sy][sx].parent.y = sy;

	using Pair = pair<int, int>;
	using pPair = pair<double, Pair>;

	set<pPair> openList;

	openList.insert({ 0.0,{sy,sx} });

	while (!openList.empty()) 
	{
		pPair p = *openList.begin();// 여기다 본인의 벨류 넣고
		openList.erase(openList.begin());// 담겼던거 지우고

		int y = p.second.first;//여기다가 좌표값 넣어준다
		int x = p.second.second;//
		closedList[y][x] = true;

		double ng, nf, nh;

		// 직선
 		for (int i = 0; i < 4; ++i) 
		{
			int nx = y + crossY1[i];
			int ny = x + crossX1[i];

 			if (isInRange(ny, nx))
			{
				if (isDestination(ny, nx, enPos)) 
				{
					cellDetails[nx][ny].parent.y = y;
					cellDetails[nx][ny].parent.x = x;
					tracePath(cellDetails, enPos);
					return enemyInfo;
				}
				else if (!closedList[nx][ny] && isUnBlocked(grid, ny, nx))
				{
					ng = cellDetails[y][x].g + 1.0;//출발 점부터 이 좌표와의 거리
					nh = GethValue(ny, nx, enPos);
					nf = ng + nh;

					if (cellDetails[nx][ny].f == INF || cellDetails[nx][ny].f > nf) 
					{				
						cellDetails[nx][ny].f = nf;// 현제 간 좌표에 총거리 넣어줌
						cellDetails[nx][ny].g = ng;//시작 지점부터 여기까지의 거리는 넣어줌
						cellDetails[nx][ny].h = nh;// 현재 노드 위치부터 목표점까지의 heuristic한 거리 넣어줌
						cellDetails[nx][ny].parent.x = x;//여기다 시작지점의 좌표를 넣어줌
						cellDetails[nx][ny].parent.y = y; // 여기다 시작지점의 좌표를 넣어줌
						openList.insert({ nf, { nx, ny } });
					}
				}
			}
		}
	}
	enemyInfo.leng = -1;
	return enemyInfo;
}

Vector2i AStar::AstarSearch(vector<GameObj*>& map, Vector2i myPos, vector<Vector2i> GeneralArr)
{
	vector<Vector2i> generalArr = GeneralArr;
	enemyInfo.leng = 0;
	grid.assign(COL, vector<int>(ROW));
	nCount = 0;
	maxNum = 999;

	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			if (map[(i * ROW) + j] == nullptr)
			{
				grid[i][j] = 0;
			}
			else if (map[(i * ROW) + j] != nullptr)
			{
				grid[i][j] = 1;
			}
		}
	}
	grid[myPos.y][myPos.x] = 0;

	bool closedList[14][7];
	memset(closedList, false, sizeof(closedList));

	Cell cellDetails[14][7];

	// 모든 좌표 초기화
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h = INF;
			cellDetails[i][j].parent.x = cellDetails[i][j].parent.y = -1;
		}
	}

	// 시작 좌표 초기화
	int sy = myPos.y;
	int sx = myPos.x;
	cellDetails[sy][sx].f = cellDetails[sy][sx].g = cellDetails[sy][sx].h = 0.0;
	cellDetails[sy][sx].parent.x = sx;
	cellDetails[sy][sx].parent.y = sy;

	using Pair = pair<int, int>;
	using pPair = pair<double, Pair>;

	set<pPair> openList;

	openList.insert({ 0.0,{sy,sx} });

	while (!openList.empty())
	{
		pPair p = *openList.begin();// 여기다 본인의 벨류 넣고
		openList.erase(openList.begin());// 담겼던거 지우고

		int y = p.second.first;//여기다가 좌표값 넣어준다
		int x = p.second.second;//
		closedList[y][x] = true;

		double ng, nf, nh;

		 //직선
		for (int i = 0; i < 4; ++i)
		{
			int nx = y + crossY1[i];
			int ny = x + crossX1[i];

			if (isInRange(ny, nx))
			{
				if (isDestination(ny, nx, generalArr))
				{
					cellDetails[nx][ny].parent.y = y;
					cellDetails[nx][ny].parent.x = x;
					tracePath(cellDetails, generalArr);

					if (generalArr.empty())
						return Vec;
				}
				else if (!closedList[nx][ny] && isUnBlocked(grid, ny, nx))
				{
					cellDetails[nx][ny].parent.x = x;
					cellDetails[nx][ny].parent.y = y;
					openList.insert({ nf, { nx, ny } });
				}
			}
		}
	}

	Vec.x = -1;
	Vec.y = -1;
	enemyInfo.leng = 99999;

	return Vec;
}

bool AStar::isDestination(int row, int col, Vector2i dst)
{
	if (row == dst.x && col == dst.y) return true;
	return false;
}

bool AStar::isDestination(int row, int col, vector<Vector2i> GeneralArr)
{
	for (int i = 0; i < GeneralArr.size(); ++i)
	{
		if (row == GeneralArr[i].x && col == GeneralArr[i].y)
		{
			nCount = i;
			return true;
		}
	}

	return false;
}

bool AStar::isInRange(int row, int col)
{
	return (row >= 0 && row < ROW && col >= 0 && col < COL);
}

bool AStar::isUnBlocked(vector<vector<int>>& map, int row, int col)
{
	return (map[col][row] == 0);
}

double AStar::GethValue(int row, int col, Vector2i dst)
{
	return (double)sqrt(pow(row - dst.x, 2) + pow(col - dst.y, 2));
}

double AStar::GethValue(int row, int col, vector<Vector2i> GeneralArr)
{
	return 0.0;
}

void AStar::tracePath(Cell cellDetails[14][7], Vector2i enpos)
{
	stack<Vector2i> s;
	int x = enpos.x;
	int y = enpos.y;

	s.push({ y, x });
	while (!(cellDetails[y][x].parent.x == x && cellDetails[y][x].parent.y == y)) 
	{
		int tempy = cellDetails[y][x].parent.y;
		int tempx = cellDetails[y][x].parent.x;
		y = tempy;
		x = tempx;
		s.push({ y, x });
	}

	int num = (int)s.size();

	while (!s.empty()) 
	{
		enemyInfo.leng++;

		if (s.size() == num-1)
		{
			enemyInfo.destPos.x = s.top().y;
			enemyInfo.destPos.y = s.top().x;
		}
		s.pop();
	}
}

void AStar::tracePath(Cell cellDetails[14][7], vector<Vector2i>& GeneralArr)
{
	stack<Vector2i> s;
	int x = GeneralArr[nCount].x;
	int y = GeneralArr[nCount].y;
	auto it = GeneralArr.begin() + nCount;
	GeneralArr.erase(it);

	s.push({ y, x });

	while (!(cellDetails[y][x].parent.x == x && cellDetails[y][x].parent.y == y))
	{
		int tempy = cellDetails[y][x].parent.y;
		int tempx = cellDetails[y][x].parent.x;
		y = tempy;
		x = tempx;
		s.push({ x, y });
	}

	if (maxNum > (int)s.size())
	{
		maxNum = (int)s.size();
		s.pop();
		Vec = s.top();
		//Vec.x = s.top().x;
		//Vec.y = s.top().y;
	}

	//int num = (int)s.size();

	//while (!s.empty())
	//{
	//	enemyInfo.leng++;

	//	if (s.size() == num - 1)
	//	{
	//		enemyInfo.destPos.x = s.top().y;
	//		enemyInfo.destPos.y = s.top().x;
	//	}
	//	s.pop();
	//}

}

void AStar::SetAstar(vector<GameObj*>& map, Vector2i myPos, Vector2i enPos)
{
	grid.assign(COL,vector<int>(ROW));

	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			if (map[(i * ROW) + j] == nullptr )
			{
				grid[i][j] = 0;
			}
			else if (map[(i * ROW) + j] != nullptr)
			{
				grid[i][j] = 1;
			}
		}
	}

	grid[myPos.y][myPos.x] = 0;
	grid[enPos.y][enPos.x] = 0;
}
