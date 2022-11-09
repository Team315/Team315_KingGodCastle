#include "SceneMgr.h"
//#include "SceneDev1.h"
//#include "SceneDev2.h"
#include "TitleScene.h"
#include "LobyScene.h"
#include "BattleScene.h"
#include "ToolScene.h"

Scenes SceneMgr::GetCurrScene() const
{
	return currScene;
}

Scene* SceneMgr::GetScene(Scenes scene)
{
	return sceneMap[scene];
}

bool SceneMgr::Init()
{
	sceneMap[Scenes::Title] = new TitleScene();
	sceneMap[Scenes::Loby] = new LobyScene();
	sceneMap[Scenes::Battle] = new BattleScene();
	sceneMap[Scenes::Tool] = new ToolScene();

	for (auto i : sceneMap)
		i.second->Init();

	currScene = Scenes::Title;
	sceneMap[currScene]->Enter();
	return false;
}

void SceneMgr::ChangeScene(Scenes scene)
{
	sceneMap[currScene]->Exit();
	currScene = scene;
	sceneMap[currScene]->Enter();
}

void SceneMgr::Update(float dt)
{
	sceneMap[currScene]->Update(dt);
}

void SceneMgr::Draw(RenderWindow& window)
{
	sceneMap[currScene]->Draw(window);
}