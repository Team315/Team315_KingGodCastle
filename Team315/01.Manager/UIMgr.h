#pragma once
#include "Object.h"
#include <list>

class Scene;

class UIMgr : public Object
{
protected:
	list<Object*> uiObjList;
	
	Scene* parentScene;

public:
	UIMgr(Scene* scene);
	virtual ~UIMgr();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void SetPos(const Vector2f& pos) override;
	
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};