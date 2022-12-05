#pragma once
#include "RectangleObj.h"
#include "Constant.h"

class RangePreview : public RectangleObj
{
protected:
	float timer;

public:
	RangePreview(float x = TILE_SIZE - 1, float y = TILE_SIZE - 1);
	virtual ~RangePreview();

	virtual void Reset() override;
	virtual void Update(float dt) override;

	void Fire(const Vector2f pos, float timer = 0.25f);
};