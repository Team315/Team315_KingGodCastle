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

	// ��� ��ǥ �ʱ�ȭ
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h = INF;
			cellDetails[i][j].parent.x = cellDetails[i][j].parent.y = -1;
		}
	}

	// ���� ��ǥ �ʱ�ȭ
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
		pPair p = *openList.begin();// ����� ������ ���� �ְ�
		openList.erase(openList.begin());// ������ �����

		int y = p.second.first;//����ٰ� ��ǥ�� �־��ش�
		int x = p.second.second;//
		closedList[y][x] = true;

		double ng, nf, nh;

		// ����
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
					ng = cellDetails[y][x].g + 1.0;//��� ������ �� ��ǥ���� �Ÿ�
					nh = GethValue(ny, nx, enPos);
					nf = ng + nh;

					if (cellDetails[ny][nx].f == INF || cellDetails[ny][nx].f > nf) 
					{
						cellDetails[ny][nx].f = nf;// ���� �� ��ǥ�� �ѰŸ� �־���
						cellDetails[ny][nx].g = ng;//���� �������� ��������� �Ÿ��� �־���
						cellDetails[ny][nx].h = nh;// ���� ��� ��ġ���� ��ǥ�������� heuristic�� �Ÿ� �־���
						cellDetails[ny][nx].parent.x = x;//����� ���������� ��ǥ�� �־���
						cellDetails[ny][nx].parent.y = y; // ����� ���������� ��ǥ�� �־���
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