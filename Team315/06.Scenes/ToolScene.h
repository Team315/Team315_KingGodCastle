#pragma once
#include "Scene.h"

class UiName;
class TileSet;
class ToolScene : public Scene
{
protected:

	TileSet* m_TileSet;
	list<UiName*> UiNameList;

public:
	ToolScene();
	virtual ~ToolScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void CreateTileSet(int cols, int rows, float quadWidth, float quadHeight);
	void CreateUiName();
};