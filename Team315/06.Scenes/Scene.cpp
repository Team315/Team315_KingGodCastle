#include "Scene.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "Constant.h"

Scene::Scene(Scenes type)
	: type(type), currentView(gameView)
{
	Vector2i gameSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	gameView.setSize(gameSize.x, gameSize.y);
	gameView.setCenter(gameSize.x * 0.5f, gameSize.y * 0.5f);

	uiView.setSize(gameSize.x, gameSize.y);
	uiView.setCenter(gameSize.x * 0.5f, gameSize.y * 0.5f);

	Vector2i toolSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	toolView.setSize(toolSize.x, toolSize.y);
	toolView.setCenter(toolSize.x * 0.5f, toolSize.y * 0.5f);
}

Scene::~Scene()
{
	Release();
}

void Scene::Release()
{
	for ( const auto& obj : objList )
	{
		obj->Release();
		delete obj;
	}
	objList.clear();
}

void Scene::Update(float dt)
{
	for ( const auto& obj : objList )
	{
		if ( obj->GetActive() )
		{
			obj->Update(dt);
		}
	}
}

void Scene::Draw(RenderWindow& window)
{
	window.setView(currentView);

	for ( const auto& obj : objList )
	{
		if ( obj->GetActive() )
		{
			obj->Draw(window);
		}
	}
}

Texture* Scene::GetTexture(string id)
{
	return RESOURCE_MGR->GetTexture(id);
}

Vector2f Scene::ScreenToWorldPos(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos, gameView);
}

Vector2f Scene::ScreenToUiPos(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos, uiView);
}

Object* Scene::FindGameObj(string name)
{
	for ( auto obj : objList )
	{
		if ( obj->GetName() == name )
		{
			return obj;
		}
	}
	return nullptr;
}