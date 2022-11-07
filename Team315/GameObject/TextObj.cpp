#include "TextObj.h"

TextObj::TextObj(Font& font, string textString,
    float posX, float posY, Color textColor, int textSize)
{
    text.setFont(font);
    text.setString(textString);
    text.setPosition(posX, posY);
    position = { posX, posY };
    text.setFillColor(textColor);
    text.setCharacterSize(textSize);
}

TextObj::TextObj(Font& font,  wstring textString,
    float posX, float posY, Color textColor, int textSize)
{
    text.setFont(font);
    text.setString(textString);
    text.setPosition(posX, posY);
    position = { posX, posY };
    text.setFillColor(textColor);
    text.setCharacterSize(textSize);
}

TextObj::~TextObj()
{
}

void TextObj::Draw(RenderWindow& window)
{
    window.draw(text);
}

void TextObj::SetOrigin(Origins origin)
{
    Utils::SetOrigin(text, origin);
}

void TextObj::SetString(string string)
{
    text.setString(string);
}

void TextObj::SetString(wstring wstring)
{
    text.setString(wstring);
}

const string& TextObj::GetString() const
{
    return text.getString();
}

FloatRect TextObj::GetGlobalBounds()
{
    return text.getGlobalBounds();
}

void TextObj::SetColor(Color color)
{
    text.setFillColor(color);
}

void TextObj::SetPos(const Vector2f& pos)
{
    Object::SetPos(pos);
    text.setPosition(pos);
}