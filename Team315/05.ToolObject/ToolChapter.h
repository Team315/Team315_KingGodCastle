#pragma once
#include "Include.h"

class ToolStage;
class ToolChapter
{
protected:
	ToolStage* m_ToolStage;

	vector<ToolStage*> ToolStageLIst;

public:
	ToolChapter();
	~ToolChapter();

	void CreateToolStage(int MaxStage, int cols, int rows, float quadWidth, float quadHeight);
	vector<ToolStage*>& GetToolStage();


};

