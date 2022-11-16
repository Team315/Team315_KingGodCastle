#include "ToolChapter.h"
#include "ToolStage.h"

ToolChapter::ToolChapter()
{
}

ToolChapter::~ToolChapter()
{
}

void ToolChapter::CreateToolStage(int MaxStage, int cols, int rows, float quadWidth, float quadHeight)
{
	for (int i = 0; i < MaxStage; i++)
	{
		m_ToolStage = new ToolStage();
		m_ToolStage->CreateTilePlay(cols, rows, quadWidth, quadHeight);
		ToolStageLIst.push_back(m_ToolStage);
	}
}

vector<ToolStage*>& ToolChapter::GetToolStage()
{
    return ToolStageLIst;
}
