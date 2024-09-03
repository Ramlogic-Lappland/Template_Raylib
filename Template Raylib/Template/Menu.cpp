#include "Menu.h"


namespace Menu
{

    Button::newButton playBttn;
    Button::newButton instructionsBttn;
    Button::newButton creditsBttn;

    static Image back_ly;
    static Texture2D background;

    float scrollingBack = 0.0f;
    float scrollingFront = 0.0f;

    static Vector2 mousePoint;
    static bool creditsIni = false;

    void InitMenu() // Init
    {

        curScreen.width = 600;
        curScreen.height = 800;
        curScreen.name = "Game";

        InitWindow(curScreen.width, curScreen.height, curScreen.name);


        back_ly = LoadImage("../Resources/Images/bk.png");
        ImageResize(&back_ly, curScreen.width / 2, curScreen.height / 2);
        background = LoadTextureFromImage(back_ly); // background

        UnloadImage(back_ly);
        // UnloadImage(front_ly);

         // playBttn Button
        playBttn.Texture = LoadTexture("../Resources/Button/play-Bttn.png");
        playBttn.FrameHeight = (float)playBttn.Texture.height / NUM_FRAMES;
        playBttn.SourceRec = { 0, 0, (float)playBttn.Texture.width, playBttn.FrameHeight };

        // Define button bounds on screen
        playBttn.Bounds = { curScreen.width / 2.0f - playBttn.Texture.width / 2.0f, curScreen.height / 2.0f - playBttn.Texture.height * 3 / NUM_FRAMES / 2.0f, (float)playBttn.Texture.width, playBttn.FrameHeight };
        playBttn.State = 0;  // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
        playBttn.Action = false;

        // Controls Button
        instructionsBttn.Texture = LoadTexture("../Resources/Button/Controls-Bttn.png");
        instructionsBttn.FrameHeight = (float)instructionsBttn.Texture.height / NUM_FRAMES;
        instructionsBttn.SourceRec = { 0, 0, (float)instructionsBttn.Texture.width, instructionsBttn.FrameHeight };

        instructionsBttn.Bounds = { curScreen.width / 2.0f - instructionsBttn.Texture.width / 2.0f, curScreen.height / 2.0f - instructionsBttn.Texture.height / 2 / NUM_FRAMES / 2.0f, (float)instructionsBttn.Texture.width, instructionsBttn.FrameHeight };
        instructionsBttn.State = 0;
        instructionsBttn.Action = false;

        // creditsBttn Button
        creditsBttn.Texture = LoadTexture("../Resources/Button/Credits-Bttn.png");
        creditsBttn.FrameHeight = (float)playBttn.Texture.height / NUM_FRAMES;
        creditsBttn.SourceRec = { 0, 0, (float)creditsBttn.Texture.width, creditsBttn.FrameHeight };

        creditsBttn.Bounds = { curScreen.width / 2.0f - creditsBttn.Texture.width / 2.0f, curScreen.height / 2.0f + creditsBttn.Texture.height * 2 / NUM_FRAMES / 2.0f, (float)creditsBttn.Texture.width, creditsBttn.FrameHeight };
        creditsBttn.State = 0;
        creditsBttn.Action = false;
       
    }

    void UpdateMenu()
    {
        scrollingBack -= 0.5f;
        scrollingFront -= 0.9f;

        mousePoint = GetMousePosition();

        if (scrollingBack <= -background.width * 2) scrollingBack = 0;

        DrawMenu();

        // Check button state
        if (CheckCollisionPointRec(mousePoint, playBttn.Bounds)) // Play Button
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) playBttn.State = 2;
            else playBttn.State = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) playBttn.Action = true;
        }
        else playBttn.State = 0;

        if (CheckCollisionPointRec(mousePoint, instructionsBttn.Bounds)) // Instructions Button
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) instructionsBttn.State = 2;
            else instructionsBttn.State = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) instructionsBttn.Action = true;
        }
        else instructionsBttn.State = 0;

        if (CheckCollisionPointRec(mousePoint, creditsBttn.Bounds)) // Credits Button
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) creditsBttn.State = 2;
            else creditsBttn.State = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) creditsBttn.Action = true;
        }
        else creditsBttn.State = 0;


        if (playBttn.Action)
        {
            std::cout << "boton playBttn precionado" << "\n";
            playBttn.Action = false;
            Game::InitGame();
            ScreenManagerNam::Screens = ScreenManagerNam::Game;
        }

        if (instructionsBttn.Action)
        {
            std::cout << "boton instructionsBttn precionado" << "\n";
            instructionsBttn.Action = false;
        }

        if (creditsBttn.Action)
        {
            std::cout << "boton creditsBttn precionado" << "\n";
            creditsBttn.Action = false;
            if (creditsIni != true)
            {
                CreditsNmsp::InitCredits();
                CreditsNmsp::InitCredits();
                creditsIni = true;
            }
            std::cout << "opening credits";
            ScreenManagerNam::Screens = ScreenManagerNam::Credits;
        }

        // Calculate button frame rectangle to draw depending on button state
        playBttn.SourceRec.y = playBttn.State * playBttn.FrameHeight;
        instructionsBttn.SourceRec.y = instructionsBttn.State * instructionsBttn.FrameHeight;
        creditsBttn.SourceRec.y = creditsBttn.State * creditsBttn.FrameHeight;
    }

    void DrawMenu() {

        BeginDrawing();

        ClearBackground(GetColor(0x052c46ff));


        DrawTextureEx(background, Vector2{ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, Vector2{ background.width * 2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

        DrawText("Game", curScreen.width / 2 - MeasureText("Game", 40), 40, 80, LIGHTGRAY);

        DrawTextureRec(playBttn.Texture, playBttn.SourceRec, Vector2{ playBttn.Bounds.x, playBttn.Bounds.y }, WHITE);
        DrawTextureRec(instructionsBttn.Texture, instructionsBttn.SourceRec, Vector2{ instructionsBttn.Bounds.x, instructionsBttn.Bounds.y }, WHITE);
        DrawTextureRec(creditsBttn.Texture, creditsBttn.SourceRec, Vector2{ creditsBttn.Bounds.x, creditsBttn.Bounds.y }, WHITE);

        EndDrawing();
    }

    void UnloadMenu()
    {
        UnloadTexture(playBttn.Texture);
        UnloadTexture(instructionsBttn.Texture);
        UnloadTexture(creditsBttn.Texture);
        UnloadTexture(background);
        creditsIni = false;
        std::cout << "Menu Unloaded." << '\n';
    }
}
