#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "Object.h"

class Player;

using namespace std;
using namespace sf;

class UIMgr;

enum class Scenes
{
	/*Dev1,
	Dev2,*/
	Title,
	//Loby,
	Battle,
	Tool,
};

class Scene
{
protected:
	Scenes type;
	list<Object*> objList;
	list<Object*> tileSetList;
	View gameView;
	View uiView;
	View toolView;
	View& currentView;
	
public:
	Scene(Scenes type);
	virtual ~Scene();

	virtual void Init();
	virtual void Release();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	Texture* GetTexture(string id);

	const View& GetWorldView() { return gameView; }
	const View& GetUiView() { return uiView; }

	Vector2f ScreenToWorldPos(Vector2i screenPos);
	Vector2f ScreenToUiPos(Vector2i screenPos);
	Vector2f ScreenToToolPos(Vector2i screenPos);

	Object* FindGameObj(string name);

	void AddGameObj(Object* obj)
	{
		objList.push_back(obj);
	}
};