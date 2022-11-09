#include "MainSceneUI.h"
#include "Include.h"

MainSceneUI::MainSceneUI(Scene* scene)
	: UIMgr(scene)
{
}

MainSceneUI::~MainSceneUI()
{
}

void MainSceneUI::Init()
{
	
}

void MainSceneUI::Release()
{
	UIMgr::Release();
}

void MainSceneUI::Reset()
{
}

void MainSceneUI::Update(float dt)
{
	UIMgr::Update(dt);
}

void MainSceneUI::Draw(RenderWindow& window)
{
	UIMgr::Draw(window);
}