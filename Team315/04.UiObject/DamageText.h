#pragma once
#include "FloatingObj.h"
#include "Include.h"

class DamageText : public FloatingObj
{
protected:

public:
	DamageText();
	virtual ~DamageText();

	void SetDamageUI(Vector2f pos, StatType sType, float damage);
};