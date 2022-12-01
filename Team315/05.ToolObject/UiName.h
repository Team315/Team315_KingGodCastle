#pragma once
#include "SpriteObj.h"

class TextObj;
class UiName: public SpriteObj
{
protected:
	TextObj* m_Text;
	String m_string;
public:
	UiName();
	~UiName();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetText(string str);
	String GetStr() { return m_string; };
	TextObj* GetText() { return m_Text; }

	bool CollisionCheck(Vector2f pos, int index);
	bool ChangeSize(bool check);
};

