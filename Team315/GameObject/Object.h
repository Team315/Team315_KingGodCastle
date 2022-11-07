#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Framework/Utils.h"

using namespace std;
using namespace sf;

class Object
{
protected:
	int id;
	string name;
	string type;
	bool enabled;

	Vector2f position;
	float rotation;
	Vector2f scale;

	static int objCount;
	
	RectangleShape hitbox;
	FloatRect hitBoxRect;

public:
	Object();
	virtual ~Object();

	int GetObjId()const;
	const string& GetName() const { return name; }
	void SetName(const string& n) { name = n; }
	const string& GetType() const { return type; }
	void SetType(const string& t) { type = t; }

	virtual void SetActive(bool active);
	virtual bool GetActive();

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void SetPos(const Vector2f& pos);
	virtual const Vector2f& GetPos() const;
	virtual void Translate(const Vector2f delta);

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetHitbox(const FloatRect rect, Origins origin);
	virtual void SetHitboxScale(float x, float y);
	virtual RectangleShape GetHitbox() const;
};