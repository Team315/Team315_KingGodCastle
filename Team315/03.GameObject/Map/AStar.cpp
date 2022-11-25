#include "AStar.h"

constexpr double INF = 1e9 + 7;

AStar::AStar()
{
}

AStar::~AStar()
{
}

bool AStar::AstarSearch(vector<vector<int>>& map, Vector2i myPos, Vector2i enPos)
{
	bool closedList[14][7];
	std::memset(closedList, false, sizeof(closedList));

	Cell cellDetails[14][7];

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h;
			cellDetails[i][j].parent.x = cellDetails[i][j].parent.y;
		}
	}

	
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
		pPair p = *openList.begin();
		openList.erase(openList.begin());

		int y = p.second.first;
		int x = p.second.second;
		closedList[y][x] = true;

		double ng, nf, nh;

		// Á÷¼±
		for (int i = 0; i < 4; ++i) {
			int ny = y + dy1[i];
			int nx = x + dx1[i];

			if (isInRange(ny, nx)) {
				if (isDestination(ny, nx, enPos)) 
				{
					cellDetails[ny][nx].parent.y = y;
					cellDetails[ny][nx].parent.x = x;
					tracePath(cellDetails, enPos);
					return true;
				}

				else if (!closedList[ny][nx] && isUnBlocked(map, ny, nx))
				{

					ng = cellDetails[y][x].g + 1.0;
					nh = GethValue(ny, nx, enPos);
					nf = ng + nh;

					if (cellDetails[ny][nx].f == INF || cellDetails[ny][nx].f > nf) {
						cellDetails[ny][nx].f = nf;
						cellDetails[ny][nx].g = ng;
						cellDetails[ny][nx].h = nh;
						cellDetails[ny][nx].parent.x = x;
						cellDetails[ny][nx].parent.y = y;
						openList.insert({ nf, { ny, nx } });
					}
				}
			}
		}

	}

	return false;
}

bool AStar::isDestination(int row, int col, Vector2i dst)
{
	if (row == dst.x && col == dst.y) return true;
	return false;
}

bool AStar::isInRange(int row, int col)
{
	return (row >= 0 && row < ROW && col >= 0 && col < COL);
}

bool AStar::isUnBlocked(vector<vector<int>>& map, int row, int col)
{
	return (map[row][col] == 0);
}

double AStar::GethValue(int row, int col, Vector2i dst)
{
	return (double)sqrt(pow(row - dst.x, 2) + pow(col - dst.y, 2));
}

void AStar::tracePath(Cell cellDetails[14][7], Vector2i dst)
{
	stack<Vector2i> s;
	int y = dst.x;
	int x = dst.y;

	s.push({ y, x });
	while (!(cellDetails[y][x].parent.x == x && cellDetails[y][x].parent.y == y)) {
		int tempy = cellDetails[y][x].parent.y;
		int tempx = cellDetails[y][x].parent.x;
		y = tempy;
		x = tempx;
		s.push({ y, x });
	}

	while (!s.empty()) {
		zmap[s.top().x][s.top().y] = '*';
		s.pop();
	}
}
