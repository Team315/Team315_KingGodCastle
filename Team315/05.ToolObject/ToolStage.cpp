#include "ToolStage.h"
#include "TilePlay.h"

ToolStage::ToolStage()
{
}

ToolStage::~ToolStage()
{
}

void ToolStage::CreateTilePlay(int cols, int rows, float quadWidth, float quadHeight)
{
	m_TilePlayList.assign(cols, vector<TilePlay*>(rows));

	int count = 0;

	TileTypes tileTypes;

	for (int i = 0; i < cols; ++i)
	{
		if (i >= 10)
		{
			tileTypes = TileTypes::PlayerArea;
		}
		else
		{
			tileTypes = TileTypes::None;
		}

		for (int j = 0; j < rows; ++j)
		{
			TilePlay* tilePlay = new TilePlay();
			tilePlay->SetTilePlay({ cols, rows }, 
				{ (WINDOW_WIDTH - (quadWidth * 8)) + (j * quadWidth), quadHeight + (i * quadHeight) }, 
				count++, tileTypes);

			m_TilePlayList[i][j] = tilePlay;
		}
	}
}

TilePlay* ToolStage::GetTileTool(int cols, int rows)
{
    return m_TilePlayList[cols][rows];
}
