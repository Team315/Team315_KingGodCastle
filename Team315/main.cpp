#include <SFML/Graphics.hpp>
#include "Include.h"

int main()
{
    //CLOG::WriteCSV("UpIdle", 1, 10, 5, "Charactor/Player/Evan/EvanIdle2", 100, 200, 100, 100, 50, 50, false, 0, 0);
    FRAMEWORK->Init(WINDOW_WIDTH, WINDOW_HEIGHT, "King God Castle");
    FRAMEWORK->Do();

    return 0;
}