#include "ItemInfoWindow.h"
#include "Include.h"
#include "BackrectText.h"
#include "Item/Item.h"

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

	additional = new BackrectText(130.f, 25.f);
	additional->SetFillColor(Color(0x08, 0x08, 0x08, 150.f));
	additional->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	additional->SetTextStyle(Color::White, 18, Color::Black, -1.0f);
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
	window.draw(statSprite);
	if (needAdditional)
		additional->Draw(window);
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
	statSprite.setPosition(pos + Vector2f(120.f, 30.f));
	if (needAdditional)
		additional->SetPos(pos + Vector2f(65.f, 59.f));
}

void ItemInfoWindow::SetItem(Item* item)
{
	itemSprite.setTexture(*RESOURCE_MGR->GetTexture(item->MakePath()), true);

	string sTypeSpritePath = "graphics/Character/Stat/StatIcon_0"; 
	StatType sType = item->GetStatType();
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
	case StatType::None:
		sTypeSpritePath += "5.png";
		break;
	}

	statSprite.setTexture(*RESOURCE_MGR->GetTexture(sTypeSpritePath), true);
	statSprite.setScale(0.5f, 0.5f);
	int grade = item->GetGrade();
	string framePath = "graphics/battleScene/Item_Frame_" + to_string(grade) + ".png";
	sprite.setTexture(*RESOURCE_MGR->GetTexture(framePath), true);
	name->SetString(item->GetName());
	float poten = item->GetPotential();
	if (sType == StatType::AP || sType == StatType::AS)
		poten *= 100;

	wstring statusText =
		to_wstring(grade + 1) + L"티어     ";
	
	if (sType == StatType::AP || sType == StatType::AS)
		statusText += (to_wstring((int)(poten * 100)) + "%");
	else if (sType == StatType::None)
		statusText += L"특수";
	else
		statusText += to_wstring((int)poten);
	
	if (item->GetItemType() == ItemType::Book)
		needAdditional = true;
	else needAdditional = false;

	if (needAdditional)
		SetSize(200.f, 88.f);
	else
		SetSize(200.f, 60.f);

	status->SetString(statusText);
	additional->SetString("test");
}