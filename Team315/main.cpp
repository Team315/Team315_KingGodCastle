#include <SFML/Graphics.hpp>
#include "Include.h"

int main()
{
    CLOG::WriteCSV("UpMove", 1, 10, 4, "Charactor/Monster/Chap1/Chap1-1Move", 80, 160, 80, 80, 40, 40, false);
    FRAMEWORK->Init(WINDOW_WIDTH, WINDOW_HEIGHT, "King God Castle");
    FRAMEWORK->Do();

    return 0;
}