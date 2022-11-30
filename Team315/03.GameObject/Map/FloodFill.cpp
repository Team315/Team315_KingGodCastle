#include "FloodFill.h"
#include "Include.h"
#include "GameObj.h"

FloodFill::FloodFill()
{
}

FloodFill::~FloodFill()
{
}

void FloodFill::Init()
{
}

void FloodFill::Update(float dt)
{
}

void FloodFill::Draw(RenderWindow& window)
{
}

bool FloodFill::FloodFillSearch(vector<GameObj*>& map, Vector2i myPos, Vector2i enPos, string targetType)
{
	SetFloodFill(map, myPos, enPos, targetType);

	vector<vector<Vector2i>> areas;

	areas.resize(m_Height, vector<Vector2i>(m_Width));

	Vector2i pos = myPos;
	pos.y -= (m_Height / 2);
	pos.x -= (m_Width/ 2);

	for (int i = 0; i < m_Height; ++i)
	{
		for (int j = 0; j < m_Width; ++j)
		{
			if (m_areaArr[i][j] == true)
			{
				areas[i][j].y = pos.y + i;
				areas[i][j].x = pos.x + j;

			}
			else
			{
				areas[i][j].y = -1;
				areas[i][j].x = -1;
			}
		}
	}

	int sy = myPos.y;
	int sx = myPos.x;


	for (int i = 0; i < m_Height; ++i)
	{
		for (int j = 0; j < m_Width; ++j)
		{
			if (isInRange(areas[i][j].y, areas[i][j].x))
			{
				if (m_areaArr[i][j] == true)
				{
					if (isDestination(grid[areas[i][j].y][areas[i][j].x]) == true)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
void FloodFill::SetArrSize(int height, int width, bool attackType)
{
	int Height = m_Height = height * 2 + 1;
	int Width = m_Width = width * 2 + 1;

	m_areaArr.resize(Height, vector<bool>(Width, false));

	if (attackType == true)
	{
		for (int i = 0; i < Height; ++i)
		{
			for (int j = 0; j < Width; ++j)
			{
				m_areaArr[i][j] = true;
			}
		}
	}
	else if (attackType == false)
	{
		int begin = 0;
		int end = 0;
		int center = height;
		int max = Height;

		for (int i = 0; i < Height; ++i)
		{
			if (i <= center)
			{
				begin = center - i;
				end = i + center;
			}
			if (i > center)
			{
				begin = i - center;
				end = (max + center - 1) - i;
			}
			for (int j = begin; j <=end; ++j)
			{
				m_areaArr[i][j] = true;
			}
		}
	}
}

void FloodFill::SetFloodFill(vector<GameObj*>& map, Vector2i myPos, Vector2i enPos, string targetType)
{
	grid.resize(GAME_TILE_HEIGHT, vector<int>(GAME_TILE_WIDTH));

	for (int i = 0; i < GAME_TILE_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_TILE_WIDTH; ++j)
		{

			if (map[(i * GAME_TILE_WIDTH) + j] == nullptr)
			{
				grid[i][j] = 0;
			}
			else if (map[(i * GAME_TILE_WIDTH) + j]->GetType().compare("Obstacle") && 
				map[(i * GAME_TILE_WIDTH) + j]->GetType().compare(targetType))
			{
				grid[i][j] = 0;
			}
			else if (!map[(i * GAME_TILE_WIDTH) + j]->GetType().compare(targetType))
			{
				grid[i][j] = 1;
			}
		}
	}
	//grid[myPos.y][myPos.x] = 2;
	//grid[enPos.y][enPos.x] = 3;

	//for (int i = 0; i < GAME_TILE_HEIGHT; ++i)
	//{
	//	for (int j = 0; j < GAME_TILE_WIDTH; ++j)
	//	{
	//		if (m_areaArr[i][j] == 2)
	//		{
	//			m_areaArr[myPos.y][myPos.x] = 0;
	//		}
	//		if (m_areaArr[i][j] == 1)
	//		{
	//			m_areaArr[enPos.y][enPos.x] = 0;
	//		}
	//	}
	//}
}

bool FloodFill::isInRange(int col, int row)
{
	return (row >= 0 && row < GAME_TILE_WIDTH&& col >= 0 && col < GAME_TILE_HEIGHT);
}

bool FloodFill::isDestination(int grid)
{
	if (grid==1)
		return true;

	return false;
}

bool FloodFill::IsAttack()
{
	/*if (m_Width == dst.x && col == dst.y)
		return true;*/

	return false;
}
