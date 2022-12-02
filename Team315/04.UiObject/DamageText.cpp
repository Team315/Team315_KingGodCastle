#include "DamageText.h"

DamageText::DamageText()
{
}

DamageText::~DamageText()
{
}

void DamageText::SetDamageUI(Vector2f pos, StatType sType, float damage)
{
	switch (sType)
	{
	case StatType::AD:
		SetColor(Color::Red);
		break;
	case StatType::AP:
		SetColor(Color::Blue);
		break;
	}
	float cSize = 12 + sqrt(damage) * 0.15f;

	SetCharacterSize(cSize);
	
	/*if (damage <= 100.f)
		SetCharacterSize(15.f);
	else
		SetCharacterSize(20.f);*/

	SetString(to_string((int)damage));
	Fire(pos);
}