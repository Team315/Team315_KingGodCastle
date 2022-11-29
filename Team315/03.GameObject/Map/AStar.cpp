#include "AStar.h"

constexpr double INF = 1e9 + 7;

AStar::AStar()
	:ROW(7), COL(14), count(0)
{
}

AStar::~AStar()
{
}

EnemyInfo AStar::AstarSearch(vector<Character*>& map, Vector2i myPos, Vector2i enPos)
{
	SetAstar(map, myPos, enPos);

	bool closedList[14][7];
	memset(closedList, false, sizeof(closedList));

	Cell cellDetails[14][7];

	// ��� ��ǥ �ʱ�ȭ
	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h = INF;
			cellDetails[i][j].parent.x = cellDetails[i][j].parent.y = -1;
		}
	}

	// ���� ��ǥ �ʱ�ȭ
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
		pPair p = *openList.begin();// ����� ������ ���� �ְ�
		openList.erase(openList.begin());// ������ �����

		int y = p.second.first;//����ٰ� ��ǥ�� �־��ش�
		int x = p.second.second;//
		closedList[y][x] = true;

		double ng, nf, nh;

		// ����
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
					ng = cellDetails[y][x].g + 1.0;//��� ������ �� ��ǥ���� �Ÿ�
					nh = GethValue(ny, nx, enPos);
					nf = ng + nh;

					if (cellDetails[nx][ny].f == INF || cellDetails[nx][ny].f > nf) 
					{				
						cellDetails[nx][ny].f = nf;// ���� �� ��ǥ�� �ѰŸ� �־���
						cellDetails[nx][ny].g = ng;//���� �������� ��������� �Ÿ��� �־���
						cellDetails[nx][ny].h = nh;// ���� ��� ��ġ���� ��ǥ�������� heuristic�� �Ÿ� �־���
						cellDetails[nx][ny].parent.x = x;//����� ���������� ��ǥ�� �־���
						cellDetails[nx][ny].parent.y = y; // ����� ���������� ��ǥ�� �־���
						openList.insert({ nf, { nx, ny } });
					}
				}
			}
		}
	}

	enemyInfo.leng = -1;
	return enemyInfo;
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
	return (map[col][row] == 0);
}

double AStar::GethValue(int row, int col, Vector2i dst)
{
	return (double)sqrt(pow(row - dst.x, 2) + pow(col - dst.y, 2));
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
		zmap[s.top().x][s.top().y] = '*';
		enemyInfo.leng++;

		if (s.size() == num-1)
		{
			enemyInfo.destPos.x = s.top().y;
			enemyInfo.destPos.y = s.top().x;
		}
		s.pop();
	}
}

void AStar::SetAstar(vector<Character*>& map, Vector2i myPos, Vector2i enPos)
{
	grid.resize(COL,vector<int>(ROW));

	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{

			if (map[(i * ROW) + j] == nullptr )
			{
				grid[i][j] = 0;
			}
			else if (!map[(i * ROW) + j]->GetType().compare("Player"))
			{
				grid[i][j] = 1;
			}
			else if (!map[(i * ROW) + j]->GetType().compare("Obstacle"))
			{
				grid[i][j] = 1;
			}
			else if (!map[(i * ROW) + j]->GetType().compare("Monster"))
			{
				grid[i][j] = 1;
			}
		}
	}

	grid[myPos.y][myPos.x] = 0;
	grid[enPos.y][enPos.x] = 0;

	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			zmap[i][j] = grid[i][j] + '0';
		}
	}

}
