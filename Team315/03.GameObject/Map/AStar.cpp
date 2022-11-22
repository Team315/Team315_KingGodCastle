//#include "AStar.h"
//
//AStar::AStar()
//{
//}
//
//AStar::~AStar()
//{
//}
//
//bool AStar::AstarSearch(vector<Character*> grid, Vector2i myPos, Vector2i enPos)
//{
//	bool closedList[14][7];
//	std::memset(closedList, false, sizeof(closedList));
//
//	Cell cellDetails[14][7];
//
//	for (int i = 0; i < ROW; ++i)
//	{
//		for (int j = 0; j < COL; ++j)
//		{
//			cellDetails[i][j].f = cellDetails[i][j].g = cellDetails[i][j].h;
//			cellDetails[i][j].parent_x = cellDetails[i][j].parent_y;
//		}
//	}
//
//	int sy = myPos.x;
//	int sx = myPos.y;
//	cellDetails[sy][sx].f = cellDetails[sy][sx].g = cellDetails[sy][sx].h = 0.0;
//	cellDetails[sy][sx].parent_x = sx;
//	cellDetails[sy][sx].parent_y = sy;
//
//	while (!openList.empty()) {
//		pPair p = *openList.begin();
//		openList.erase(openList.begin());
//
//		int y = p.second.first;
//		int x = p.second.second;
//		closedList[y][x] = true;
//
//		double ng, nf, nh;
//
//		// Á÷¼±
//		for (int i = 0; i < 4; ++i) {
//			int ny = y + dy1[i];
//			int nx = x + dx1[i];
//
//			if (isInRange(ny, nx)) {
//				if (isDestination(ny, nx, dst)) {
//					cellDetails[ny][nx].parent_y = y;
//					cellDetails[ny][nx].parent_x = x;
//					tracePath(cellDetails, dst);
//					return true;
//				}
//
//				else if (!closedList[ny][nx] && isUnBlocked(map, ny, nx))
//				{
//
//					ng = cellDetails[y][x].g + 1.0;
//					nh = GethValue(ny, nx, dst);
//					nf = ng + nh;
//
//					if (cellDetails[ny][nx].f == INF || cellDetails[ny][nx].f > nf) {
//						cellDetails[ny][nx].f = nf;
//						cellDetails[ny][nx].g = ng;
//						cellDetails[ny][nx].h = nh;
//						cellDetails[ny][nx].parent_x = x;
//						cellDetails[ny][nx].parent_y = y;
//						openList.insert({ nf, { ny, nx } });
//					}
//				}
//			}
//		}
//
//	}
//
//	return false;
//
//}
