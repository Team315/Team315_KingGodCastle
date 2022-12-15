#include "InfoWindow.h"
#include "RectangleObj.h"
#include "RssProgressWindow.h"
#include "PowerUp/PowerUp.h"

InfoWindow::InfoWindow()
	:isOnOff(false)
{

}

InfoWindow::~InfoWindow()
{
}

void InfoWindow::Enter()
{
	isOnOff = false;

	Vector2f vec0 = m_altar0.GetPos();
	vec0.x += 50.f;
	vec0.y -= 10.f;
	m_Textaltar0.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_Textaltar0.SetString("Lv." + to_string(GAME_MGR->altarData.mana));
	m_Textaltar0.SetColor(Color::White);
	m_Textaltar0.SetOutlineThickness(2.f);
	m_Textaltar0.SetOutlineColor(Color::Black);
	m_Textaltar0.SetCharacterSize(45);
	m_Textaltar0.SetPos(vec0);
	m_Textaltar0.SetOrigin(Origins::MC);

	Vector2f vec1 = m_altar1.GetPos();
	vec1.x += 50.f;
	vec1.y -= 10.f;
	m_Textaltar1.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_Textaltar1.SetString("Lv." + to_string(GAME_MGR->altarData.silver));
	m_Textaltar1.SetColor(Color::White);
	m_Textaltar1.SetOutlineThickness(2.f);
	m_Textaltar1.SetOutlineColor(Color::Black);
	m_Textaltar1.SetCharacterSize(45);
	m_Textaltar1.SetPos(vec1);
	m_Textaltar1.SetOrigin(Origins::MC);

	Vector2f vec2 = m_altar2.GetPos();
	vec2.x += 50.f;
	vec2.y -= 10.f;
	m_Textaltar2.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_Textaltar2.SetString("Lv." + to_string(GAME_MGR->altarData.physical));
	m_Textaltar2.SetColor(Color::White);
	m_Textaltar2.SetOutlineThickness(2.f);
	m_Textaltar2.SetOutlineColor(Color::Black);
	m_Textaltar2.SetCharacterSize(45);
	m_Textaltar2.SetPos(vec2);
	m_Textaltar2.SetOrigin(Origins::MC);

	Vector2f vec3 = m_altar3.GetPos();
	vec3.x += 50.f;
	vec3.y -= 10.f;
	m_Textaltar3.SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	m_Textaltar3.SetString("Lv." + to_string(GAME_MGR->altarData.enforce));
	m_Textaltar3.SetColor(Color::White);
	m_Textaltar3.SetOutlineThickness(2.f);
	m_Textaltar3.SetOutlineColor(Color::Black);
	m_Textaltar3.SetCharacterSize(45);
	m_Textaltar3.SetPos(vec3);
	m_Textaltar3.SetOrigin(Origins::MC);

	// level
	levelBar->SetLevel(GAME_MGR->accountInfo.level);
	// exp
	float value = GAME_MGR->accountInfo.level != 10 ? (float)GAME_MGR->accountInfo.exp / (float)GAME_MGR->accountExpLimit : 1.f;
	levelBar->GetProgressBar().SetProgressValue(value);

	rectangleShapes.resize(3);
	Vector2f spritePos(GAME_SCREEN_WIDTH * 0.3f, GAME_SCREEN_HEIGHT * 0.80f);
	for (auto& rectangleShape : rectangleShapes)
	{
		rectangleShape.setPosition(spritePos);
		rectangleShape.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
		Utils::SetOrigin(rectangleShape, Origins::MC);
		rectangleShape.setFillColor(Color(0x0f, 0x0f, 0x0f, 100.f));
		rectangleShape.setOutlineColor(Color(0xf0, 0xf0, 0xf0));
		rectangleShape.setOutlineThickness(2.0f);
		spritePos.x += GAME_SCREEN_WIDTH * 0.2f;
	}

	powerUpSprites.resize(3);
	spritePos = Vector2f(GAME_SCREEN_WIDTH * 0.3f, GAME_SCREEN_HEIGHT * 0.80f);
	for (auto& powerUpSprite : powerUpSprites)
	{
		powerUpSprite.setPosition(spritePos);
		Utils::SetOrigin(powerUpSprite, Origins::MC);
		powerUpSprite.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/PowerUp/dogfight.png"));
		spritePos.x += GAME_SCREEN_WIDTH * 0.2f;
	}
}

void InfoWindow::Init()
{
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/InfoWindow/Info_Button.png"));
	SetScale(1.7f, 1.7f);
	SetOrigin(Origins::TR);
	SetPos({ GAME_SCREEN_WIDTH -20.f ,10.f });

	m_Background.SetSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	m_Background.SetFillColor(Color::Black);
	m_Background.SetFillColorAlpha(200);
	m_Background.SetOrigin(Origins::TR);
	m_Background.SetPos({ GAME_SCREEN_WIDTH ,0.f });
	
	m_backButton.SetTexture(*RESOURCE_MGR->GetTexture("graphics/InfoWindow/InfoBackButton.png"));
	m_backButton.SetOrigin(Origins::TR);
	m_backButton.SetPos({ GAME_SCREEN_WIDTH - 20.f ,10.f });


	m_altar0.SetTexture(*RESOURCE_MGR->GetTexture("graphics/InfoWindow/Info_Altar_00.png"));
	m_altar0.SetOrigin(Origins::MC);
	m_altar0.SetPos({ GAME_SCREEN_WIDTH * 0.5, GAME_SCREEN_HEIGHT * 0.15f });

	m_altar1.SetTexture(*RESOURCE_MGR->GetTexture("graphics/InfoWindow/Info_Altar_01.png"));
	m_altar1.SetOrigin(Origins::MC);
	m_altar1.SetPos({ GAME_SCREEN_WIDTH * 0.5, GAME_SCREEN_HEIGHT * 0.3f });

	m_altar2.SetTexture(*RESOURCE_MGR->GetTexture("graphics/InfoWindow/Info_Altar_02.png"));
	m_altar2.SetOrigin(Origins::MC);
	m_altar2.SetPos({ GAME_SCREEN_WIDTH * 0.5, GAME_SCREEN_HEIGHT * 0.45f });

	m_altar3.SetTexture(*RESOURCE_MGR->GetTexture("graphics/InfoWindow/Info_Altar_03.png"));
	m_altar3.SetOrigin(Origins::MC);
	m_altar3.SetPos({ GAME_SCREEN_WIDTH * 0.5, GAME_SCREEN_HEIGHT * 0.60f });

	levelBar = new RssProgressWindow();
	levelBar->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/Icon_Level.png"));
	IntRect texRect = levelBar->GetTextureRect();
	levelBar->SetSize(Vector2f(120, texRect.height * 0.5f));
	levelBar->SetColor(Color(0, 0, 0, 100), Color::Green, Color::Black, 2.f);
	levelBar->SetProgressLocalPos(Vector2f(texRect.width * 0.5f, texRect.height * 0.25f));
	levelBar->SetLevelTextLocalPos(Vector2f(texRect.width * 0.5f + 4, texRect.height * 0.5f + 6));
	levelBar->SetPos(Vector2f(10, 10));
}

void InfoWindow::Release()
{
}

void InfoWindow::Update(float dt)
{
	
}

void InfoWindow::Draw(RenderWindow& window)
{
	if(!isOnOff)
		SpriteObj::Draw(window);

	if (isOnOff)
	{
		m_Background.Draw(window);

		m_altar0.Draw(window);
		m_altar1.Draw(window);
		m_altar2.Draw(window);
		m_altar3.Draw(window);

		m_Textaltar0.Draw(window);
		m_Textaltar1.Draw(window);
		m_Textaltar2.Draw(window);
		m_Textaltar3.Draw(window);

		m_backButton.Draw(window);

		levelBar->Draw(window);

		for (auto& rectangleShape : rectangleShapes)
			window.draw(rectangleShape);

		for (int i = 0; i < GAME_MGR->standingPowerUps.size(); i++)
			window.draw(powerUpSprites[i]);

	/*	for (auto& powerUpSprite : powerUpSprites)
			window.draw(powerUpSprite);*/
	}
}

bool InfoWindow::CollCall(Vector2f mousepos)
{
	if (!isOnOff && sprite.getGlobalBounds().contains(mousepos) && InputMgr::GetMouseUp(Mouse::Left))
	{
		Enter();
		isOnOff = true;
		vector<PowerUp*>& powerups = GAME_MGR->standingPowerUps;

		for (int i = 0; i < GAME_MGR->standingPowerUps.size(); i++)
		{
			powerUpSprites[i].setTexture(*RESOURCE_MGR->GetTexture(powerups[i]->MakePath()));
		}
		return true;
	}
	return false;
}

bool InfoWindow::CollBackButton(Vector2f mousepos)
{
	if (m_backButton.GetGlobalBounds().contains(mousepos) && InputMgr::GetMouseUp(Mouse::Left))
	{
		isOnOff = false;

		return true;
	}
		return false;
}


