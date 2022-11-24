#include "AStar.h"

constexpr double INF = 1e9 + 7;

AStar::AStar()
	:ROW(14), COL(7), count(0)
{
}

AStar::~AStar()
{
}

int AStar::AstarSearch(vector<Character*>& map, Vector2i myPos, Vector2i enPos)
{
	bool closedList[14][7];
	std::memset(closedList, false, sizeof(closedList));

	Cell cellDetails[14][7];

	// 모든 좌표 초기화
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h = INF;
			cellDetails[i][j].parent.x = cellDetails[i][j].parent.y = -1;
		}
	}

	// 시작 좌표 초기화
	int sy = myPos.x;
	int sx = myPos.y;
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
			int ny = y + dy1[i];
			int nx = x + dx1[i];

			if (isInRange(ny, nx)) 
			{
				if (isDestination(ny, nx, enPos)) 
				{
					cellDetails[ny][nx].parent.y = y;
					cellDetails[ny][nx].parent.x = x;
					tracePath(cellDetails, enPos);
					return count;
				}
				else if (!closedList[ny][nx] && isUnBlocked(map, ny, nx))
				{
					ng = cellDetails[y][x].g + 1.0;//출발 점부터 이 좌표와의 거리
					nh = GethValue(ny, nx, enPos);
					nf = ng + nh;

					if (cellDetails[ny][nx].f == INF || cellDetails[ny][nx].f > nf) 
					{
						cellDetails[ny][nx].f = nf;// 현제 간 좌표에 총거리 넣어줌
						cellDetails[ny][nx].g = ng;//시작 지점부터 여기까지의 거리는 넣어줌
						cellDetails[ny][nx].h = nh;// 현재 노드 위치부터 목표점까지의 heuristic한 거리 넣어줌
						cellDetails[ny][nx].parent.x = x;//여기다 시작지점의 좌표를 넣어줌
						cellDetails[ny][nx].parent.y = y; // 여기다 시작지점의 좌표를 넣어줌
						openList.insert({ nf, { ny, nx } });
					}
				}
			}
		}
	}

	return count;
}

bool AStar::isDestination(int row, int col, Vector2i dst)
{
	if (row == dst.x && col == dst.y) 
		return true;

	return false;
}

bool AStar::isInRange(int row, int col)
{
	return (row >= 0 && row < ROW && col >= 0 && col < COL);
}

bool AStar::isUnBlocked(vector<Character*>& map, int row, int col)
{
	int idx = col * GAME_TILE_WIDTH + row;
	return (map[idx]->GetType() == "Obstacle");
}

double AStar::GethValue(int row, int col, Vector2i dst)
{
	return (double)sqrt(pow(row - dst.x, 2) + pow(col - dst.y, 2));
}

void AStar::tracePath(Cell cellDetails[14][7], Vector2i enpos)
{
	stack<Vector2i> s;
	int y = enpos.x;
	int x = enpos.y;

	s.push({ y, x });
	while (!(cellDetails[y][x].parent.x == x && cellDetails[y][x].parent.y == y)) 
	{
		int tempy = cellDetails[y][x].parent.y;
		int tempx = cellDetails[y][x].parent.x;
		y = tempy;
		x = tempx;
		s.push({ y, x });
	}

	while (!s.empty()) 
	{
		zmap[s.top().x][s.top().y] = '*';
		count++;
		s.pop();
	}
}