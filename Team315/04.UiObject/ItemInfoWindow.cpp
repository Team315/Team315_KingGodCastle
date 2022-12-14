#include "ItemInfoWindow.h"
#include "Include.h"
#include "BackrectText.h"
#include "Item/Item.h"
#include "PowerUp/PowerUp.h"
#include "DataTableMgr.h"
#include "StringTable.h"

ItemInfoWindow::ItemInfoWindow(float x, float y)
	: SpriteGrid(x, y), needAdditional(false)
{
	SetOutline(Color::Black, 2.0f);
	SetFillColor(Color(0x1f, 0x1f, 0x1f, 180.f));

	name = new BackrectText(130.f, 25.f);
	name->SetFillColor(Color(0x08, 0x08, 0x08, 150.f));
	name->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	name->SetTextStyle(Color::White, 18, Color::Black, -1.0f);
	name->SetTextLocalPos(Vector2f(0.f, 0.f));

	status = new BackrectText(130.f, 25.f);
	status->SetFillColor(Color(0x08, 0x08, 0x08, 150.f));
	status->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	status->SetTextStyle(Color::White, 18, Color::Black, -1.0f);
	status->SetTextLocalPos(Vector2f(10.f, 0.f));

	additional = new BackrectText(190.f, 35.f);
	additional->SetFillColor(Color(0x08, 0x08, 0x08, 150.f));
	additional->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	additional->SetTextStyle(Color::White, 13, Color::Black, -1.0f);
	additional->SetTextLocalPos(Vector2f(10.f, 0.f));
}

ItemInfoWindow::~ItemInfoWindow()
{
}

void ItemInfoWindow::Draw(RenderWindow& window)
{
	SpriteGrid::Draw(window);
	name->Draw(window);
	status->Draw(window);
	window.draw(itemSprite);
	if (needAdditional)
		additional->Draw(window);
	else
		window.draw(statSprite);
}

void ItemInfoWindow::SetOrigin(Origins origin)
{
}

void ItemInfoWindow::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	sprite.setPosition(pos);
	itemSprite.setPosition(pos + Vector2f(30.f, 30.f));
	Utils::SetOrigin(itemSprite, Origins::MC);
	name->SetPos(pos + Vector2f(130.f, 3.f));
	name->SetOrigin(Origins::TC);
	status->SetPos(pos + Vector2f(65.f, 31.f));
	if (needAdditional)
		additional->SetPos(pos + Vector2f(5.f, 62.f));
	else
		statSprite.setPosition(pos + Vector2f(120.f, 30.f));
}

void ItemInfoWindow::SetItem(Item* item)
{
	itemSprite.setTexture(*RESOURCE_MGR->GetTexture(item->MakePath()), true);

	int grade = item->GetGrade();
	string framePath = "graphics/battleScene/Item_Frame_" + to_string(grade) + ".png";
	sprite.setTexture(*RESOURCE_MGR->GetTexture(framePath), true);
	name->SetString(STRING_TABLE->Get( item->GetName() + to_string(grade) ) );
	float poten = item->GetPotential();

	StatType sType = item->GetStatType();
	wstring statusText =
		to_wstring(grade + 1) + STRING_TABLE->Get("Tier");
	
	if (sType == StatType::AP || sType == StatType::AS)
		statusText += ("    " + to_wstring((int)(poten * 100)) + "%");
	else if (sType == StatType::None)
		statusText += STRING_TABLE->Get("SpecialItem");
	else
		statusText += ("    " + to_wstring((int)poten));
	status->SetString(statusText);

	if (item->GetItemType() == ItemType::Book)
	{
		needAdditional = true;
		SetSize(200.f, 100.f);
		wstring temp = STRING_TABLE->Get("book_explain" + to_string(grade + 1));
		additional->SetSize(190.f, 35.f);
		additional->SetString(Utils::ReplaceNewLine(temp));
	}
	else
	{
		needAdditional = false;
		SetSize(200.f, 60.f);

		string sTypeSpritePath = "graphics/Character/Stat/StatIcon_0";
		switch (sType)
		{
		case StatType::AD:
			sTypeSpritePath += "1.png";
			break;
		case StatType::AP:
			sTypeSpritePath += "2.png";
			break;
		case StatType::AS:
			sTypeSpritePath += "3.png";
			break;
		case StatType::HP:
			sTypeSpritePath += "4.png";
			break;
		}

		statSprite.setTexture(*RESOURCE_MGR->GetTexture(sTypeSpritePath), true);
		statSprite.setScale(0.5f, 0.5f);
	}
}

void ItemInfoWindow::SetPowerUp(PowerUp* power)
{
	itemSprite.setTexture(*RESOURCE_MGR->GetTexture(power->MakePath()), true);
	
	int grade = power->GetGrade();
	string framePath = "graphics/battleScene/Item_Frame_" + to_string(grade) + ".png";
	sprite.setTexture(*RESOURCE_MGR->GetTexture(framePath), true);
	name->SetString(STRING_TABLE->Get( power->GetName() ));

	wstring statusText = to_string(grade) + STRING_TABLE->Get("Tier") + " " + STRING_TABLE->Get("PowerUp");
	status->SetString(statusText);
	
	needAdditional = true;
	SetSize(200.f, 125.f);
	wstring temp = STRING_TABLE->Get(power->GetName() + (power->isUnique() ? "" : to_string(power->GetGrade())) + "Explain");
	additional->SetString(Utils::ReplaceNewLine(temp));
	additional->SetSize(190.f, 55.f);
}