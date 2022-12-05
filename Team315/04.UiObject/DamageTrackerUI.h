#pragma once
#include "RectangleObj.h"

class BackrectText;

class DamageTrackerUI : public RectangleObj
{
protected:
	BackrectText* onoff;
	BackrectText* selectGiven;
	BackrectText* selectTaken;
	vector<BackrectText*> buttons;
	bool show;
	bool givenOrTaken;

public:
	DamageTrackerUI(float x = 100.f, float y = 200.f);
	virtual ~DamageTrackerUI();

	virtual void Init() override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	vector<BackrectText*>& GetButtons() { return buttons; }

	void ShowWindow();
	void ShowGiven();
	void ShowTaken();
};