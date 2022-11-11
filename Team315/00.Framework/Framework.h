#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include <string>

using namespace sf;

class Framework : public Singleton<Framework>
{
protected:
	RenderWindow window;
	Vector2u windowSize;

	//TimeMgr
	Clock clock;
	Time deltaTime;
	float timeScale;

public:
	Framework();
	virtual ~Framework();

	float GetDT() const;
	float GetRealDT() const;
	void SetWindowSize(int width, int height);
	const Vector2u& GetWindowSize() const;
	RenderWindow& GetWindow();

	bool Init(int width, int height, std::string title);
	bool Do();

	bool devMode;
};

#define FRAMEWORK (Framework::GetInstance())