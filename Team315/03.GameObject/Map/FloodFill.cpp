#include "FloodFill.h"
#include "Include.h"
#include "GameObj.h"
#include "Character.h"

FloodFill::FloodFill()
	:m_count(0), m_isAttackAreas(false)
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
	//for (auto areas : Areas)
	//{
	//	areas.Update(dt);
	//}
}

void FloodFill::Draw(RenderWindow& window)
{
	for (auto areas : Areas)
	{
		if (areas.GetActive())
		{
			areas.Draw(window);
		}
	}
}

bool FloodFill::FloodFillSearch(vector<GameObj*>& map, Vector2i myPos, Vector2i enPos, string targetType)
{
	SetFloodFill(map, myPos, enPos, targetType);

	vector<vector<Vector2i>> areas;

	areas.resize(m_Height, vector<Vector2i>(m_Width));

	Vector2i pos = myPos;
	pos.y -= (m_Height / 2);
	pos.x -= (m_Width / 2);

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
	m_count = 0;

	//m_areaArr.resize(Height, vector<bool>(Width, false));

	if (attackType == true)
	{
		m_areaArr.resize(Height, vector<bool>(Width, true));
		m_count = Height * Width;
		/*for (int i = 0; i < Height; ++i)
		{
			for (int j = 0; j < Width; ++j)
			{

				m_areaArr[i][j] = true;
				++m_count;
			}
		}*/
	}
	else if (attackType == false)
	{
		int begin = 0;
		int end = 0;
		int center = height;
		int max = Height;
		m_areaArr.resize(Height, vector<bool>(Width, false));

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
			for (int j = begin; j <= end; ++j)
			{
				m_areaArr[i][j] = true;
				++m_count;
			}
		}
	}
	SetAttackAreas(m_count);
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
}

void FloodFill::SetGeneralArr(vector<GameObj*>& map, string targetType)
{
	grid.resize(GAME_TILE_HEIGHT, vector<int>(GAME_TILE_WIDTH));

	vector<int> vec;


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
}

vector<Vector2i> FloodFill::GetGeneralInfo(vector<GameObj*>& map, string targetType)
{
	grid.assign(GAME_TILE_HEIGHT, vector<int>(GAME_TILE_WIDTH, 0));


	vector<Vector2i> targetArrs;

	for (auto& target : map)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			int attackRange = dynamic_cast<Character*>(target)->GetStat(StatType::AR).GetBase();
			bool attackType = dynamic_cast<Character*>(target)->GetAttackRangeType();

			vector<vector<bool>> areaArr;

			vector<vector<Vector2i>> areas;
			areas.resize(m_Height, vector<Vector2i>(m_Width));

			Vector2f posf = target->GetPos();
			Vector2i pos = { (int)((posf.x / TILE_SIZE) - 2), (int)(posf.y / TILE_SIZE) - 1 };

			pos.y -= (m_Height / 2);
			pos.x -= (m_Width / 2);

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

			for (int i = 0; i < m_Height; ++i)
			{
				for (int j = 0; j < m_Width; ++j)
				{
					if (isInRange(areas[i][j].y, areas[i][j].x))
					{
						if (m_areaArr[i][j] == true)
						{
							grid[areas[i][j].y][areas[i][j].x] = 1;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < GAME_TILE_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_TILE_WIDTH; ++j)
		{
			if (map[(GAME_TILE_WIDTH * i) + j] != nullptr)
			{
				grid[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < GAME_TILE_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_TILE_WIDTH; ++j)
		{
			if (grid[i][j] == 1)
			{
				targetArrs.push_back({ j,i });
			}
		}
	}

	return targetArrs;
}

GameObj* FloodFill::GetNearEnemy(vector<GameObj*>& map, Vector2i myPos, string targetType)
{
	float minDistance = 99999.f;
	float nowDistance = 0.f;
	auto nearGameObj = map[0];

	for (auto& target : map)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());
			nowDistance = Utils::Distance(enpos, myPos);

			if (minDistance > nowDistance)
			{
				minDistance = nowDistance;
				nearGameObj = target;
			}
		}
	}

	return nearGameObj;
}

void FloodFill::SetAttackAreas(int count)
{
	Areas.resize(count);

	for (int i = 0; i < count; ++i)
	{
		Areas[i].SetSize(TILE_SIZE, TILE_SIZE);
		Areas[i].SetFillColor(Color::Red);
		Areas[i].SetFillColorAlpha(100);
		Areas[i].SetOutline(Color::Red, -1.f);
		Areas[i].SetOrigin(Origins::TC);
		Areas[i].SetActive(false);
	}
	

	for (int i = 0, y = -(m_Height / 2); i < m_Height; ++i,++y)
	{
		for (int j = 0, x = -(m_Width / 2); j < m_Width; ++j,++x)
		{
			if (m_areaArr[i][j])
			{
				m_arr.push_back({ x ,y });
			}
		}
	}
}

void FloodFill::DrawingAttackAreas(Vector2i myPos, bool onOff)
{
	m_isAttackAreas = onOff;

	if (!m_isAttackAreas)
	{
		for (int i = 0; i < m_count; ++i)
		{
			Areas[i].SetActive(false);
		}
		return;
	}

	for (int i = 0; i < m_count; ++i)
	{
		Vector2i  pos = m_arr[i];
		pos.x += myPos.x /*- (m_Width / 2)*/;
		pos.y += myPos.y-1 /*- (m_Height / 2)*/;

		if (isInRange(pos.y, pos.x))
		{
			Areas[i].SetActive(true);
			Areas[i].SetPos(GAME_MGR->IdxToPos(pos));
		}
		else
		{
			Areas[i].SetActive(false);
		}
	}
}

bool FloodFill::isInRange(int col, int row)
{
	return (row >= 0 && row < GAME_TILE_WIDTH&& col >= 0 && col < GAME_TILE_HEIGHT);
}

bool FloodFill::isDestination(int grid)
{
	if (grid == 1)
		return true;

	return false;
}
