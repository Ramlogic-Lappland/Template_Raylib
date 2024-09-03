#include "Game.h"

namespace Game
{

    void InitGame() // Init
    {

    }

    void UpdateGame()
    {
        DrawGame();

    }

    void DrawGame() {

        BeginDrawing();



        EndDrawing();
    }

    void UnloadGame()
    {
        std::cout << "Game Unloaded." << '\n';
    }
}
