#pragma once
#include "Include.h"

class TilePlay;
class ToolStage
{
protected:
	TilePlay* m_TilePlay;

	vector<vector<TilePlay*>> m_TilePlayList;

public:
	ToolStage();
	~ToolStage();

	void CreateTilePlay(int cols, int rows, float quadWidth, float quadHeight);
	TilePlay* GetTileTool(int cols, int rows);
};

