#pragma once
#include "Object.h"

class TextObj : public Object
{
protected:
    Text text;

public:
    TextObj() {}
    TextObj(Font& font,
        string textString,
        float posX = 0, float posY = 0,
        Color textColor = Color::White,
        int textSize = 75);
    TextObj(Font& font,
        wstring textString,
        float posX = 0, float posY = 0,
        Color textColor = Color::White,
        int textSize = 75);
    virtual ~TextObj() override;

    virtual void Draw(RenderWindow& window) override;

    void SetOrigin(Origins origin);
    void SetString(string string);
    void SetString(wstring wstring);
    const string& GetString() const;

    FloatRect GetGlobalBounds();
    void SetColor(Color color);
    void SetPos(const Vector2f& pos);
};