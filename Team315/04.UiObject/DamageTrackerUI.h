#pragma once
#include "RectangleObj.h"
#include "ObjectPool.h"

class BackrectText;
class BattleTracker;
class TrackerProfile;

class DamageTrackerUI : public RectangleObj
{
protected:
	BackrectText* onoff;
	BackrectText* selectGiven;
	BackrectText* selectTaken;
	vector<BackrectText*> buttons;
	bool show;
	bool givenOrTaken;
	ObjectPool<TrackerProfile> profiles;
	BattleTracker* tracker;

public:
	DamageTrackerUI(float x = 160.f, float y = 300.f);
	virtual ~DamageTrackerUI();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
	vector<BackrectText*>& GetButtons() { return buttons; }

	void ShowWindow();
	void ShowWindow(bool value);
	void ShowGiven();
	void ShowTaken();
	void ProfileSetPos();
	void ProfilesReturn();
};