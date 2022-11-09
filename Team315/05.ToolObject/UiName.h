#pragma once
#include "SpriteObj.h"

class TextObj;
class UiName: public SpriteObj
{
protected:
	TextObj* m_Text;

public:
	UiName();
	~UiName();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;


	void SetText(string str);

};

