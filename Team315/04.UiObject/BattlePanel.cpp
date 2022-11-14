#include "BattlePanel.h"
#include "Include.h"

BattlePanel::BattlePanel()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Table.png"));
	
	Vector2f textLocalPos(26.f, 60.f); 
	summon = new SpriteButton();
	summon->SetButton(*RESOURCE_MGR->GetTexture("graphics/battleScene/Button_01.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"영웅소환",
		*RESOURCE_MGR->GetTexture("graphics/battleScene/coin_01.png"),
		textLocalPos.x, textLocalPos.y);

	begin = new SpriteButton();
	begin->SetButton(*RESOURCE_MGR->GetTexture("graphics/battleScene/Button_02.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"전투개시",
		*RESOURCE_MGR->GetTexture("graphics/battleScene/coin_01.png"),
		textLocalPos.x, textLocalPos.y);

	expansion = new SpriteButton();
	expansion->SetButton(*RESOURCE_MGR->GetTexture("graphics/battleScene/Button_03.png"),
		*RESOURCE_MGR->GetFont("fonts/NANUMBARUNGOTHICBOLD.ttf"), L"진영확장",
		*RESOURCE_MGR->GetTexture("graphics/battleScene/coin_01.png"),
		textLocalPos.x, textLocalPos.y);
}

BattlePanel::~BattlePanel()
{
}

void BattlePanel::Draw(RenderWindow& window)
{
	VertexArrayObj::Draw(window);
	summon->Draw(window);
	begin->Draw(window);
	expansion->Draw(window);
}

void BattlePanel::SetPos(const Vector2f& pos)
{
	VertexArrayObj::SetPos(pos);
	summon->SetPos(position + summonLocalPos);
	begin->SetPos(position + beginLocalPos);
	expansion->SetPos(position + expansionLocalPos);
}