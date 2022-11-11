#pragma once
#include "SpriteObj.h"
#include "ProgressBar.h"

class RssProgressWindow : public SpriteObj
{
protected:
	ProgressBar progress;
	Text		levelText;

	Vector2f	progressLocalPos;
	Vector2f	levelTextLocalPos;
	int			level;
	int			levelTextX;

public:
	RssProgressWindow();
	virtual ~RssProgressWindow();

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	void SetSize(Vector2f size);
	void SetProgressLocalPos(Vector2f pos);
	void SetLevelTextLocalPos(Vector2f pos);
	void SetColor(Color backColor, Color prgColor, Color prgBackColor = Color::Black, float thickness = 0.f);
	void SetLevel(int level = -1);
	ProgressBar& GetProgressBar() { return progress; }
};