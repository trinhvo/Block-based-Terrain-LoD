#include <ctime>
#include <cstdlib>
#include "Game.h"

int main() {
    srand(time(NULL));
    CGame& Game = CGame::Get();

    Game.Init();
    Game.Start();
    Game.End();

    return 0;
}
