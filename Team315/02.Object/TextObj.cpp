#include "TextObj.h"

TextObj::TextObj(Font& font, string textString,
    float posX, float posY, Color textColor, int textSize)
{
    text.setFont(font);
    text.setString(textString);
    text.setFillColor(textColor);
    text.setCharacterSize(textSize);
    SetPos(Vector2f(posX, posY));
}

TextObj::TextObj(Font& font,  wstring textString,
    float posX, float posY, Color textColor, int textSize)
{
    text.setFont(font);
    text.setString(textString);
    text.setFillColor(textColor);
    text.setCharacterSize(textSize);
    SetPos(Vector2f(posX, posY));
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

void TextObj::SetFont(Font& font)
{
    text.setFont(font);
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

void TextObj::SetCharacterSize(int textSize)
{
    text.setCharacterSize(textSize);
}

void TextObj::SetOutlineThickness(float thickness)
{
    text.setOutlineThickness(thickness);
}

void TextObj::SetOutlineColor(const Color& color)
{
    text.setOutlineColor(color);
}

void TextObj::SetAlhpa(int Alhpa)
{
    Color color = text.getFillColor();
    color.a = Alhpa;
    SetColor(color);
}

void TextObj::SetLetterSpacing(float spacingFactor)
{
    text.setLetterSpacing(spacingFactor);
}
