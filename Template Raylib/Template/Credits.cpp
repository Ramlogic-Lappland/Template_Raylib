#include "Credits.h"
//using namespace Button;

namespace CreditsNmsp
{

    static Button::NewCreditButton lib;
    static Button::NewCreditButton dev;
    static Button::ReturnButton returnBttnx;

    static Image logo;
    static Image creditsImg;
    static Image background;

    static Texture2D backgroundCred;
    static Texture2D backgroundTex;
    static Texture2D logoTex;
    static Texture2D rtn;

    static Vector2 mousePoint;

    void InitCredits() // Init
    {
        curScreen.width = 600;
        curScreen.height = 800;
        curScreen.name = "Game - Credits";
        SetWindowSize(curScreen.width, curScreen.height);
        SetWindowTitle(curScreen.name);


        dev.setBounds(curScreen.width / 1.2, curScreen.height / 14, (curScreen.width / 2) - (dev.Bounds.width / 2), (curScreen.height / 15) * 4 /*height based on the division of the screen*/);
        dev.setCreditButton({ 80, 80, 80, 255 }/*DARKGRAY*/, "https://github.com/BadAssGo4t/Template", "Game Made By: Estanislao");

        lib.setBounds(curScreen.width / 1.2, curScreen.height / 14, (curScreen.width / 2) - (dev.Bounds.width / 2), (curScreen.height / 15) * 8);
        lib.setCreditButton({ 80, 80, 80, 255 }/*DARKGRAY*/, "https://www.raylib.com/index.html", "Made Using: Raylib");

        rtn = LoadTexture("../Resources/Button/Return.png");
        returnBttnx.setMenuButton(rtn, (float)returnBttnx.Texture.height / NUM_FRAMES, 0.0f, 0.0f, (float)returnBttnx.Texture.width, 0);
        returnBttnx.setBounds((float)returnBttnx.Texture.width, (float)returnBttnx.Texture.height, curScreen.width - returnBttnx.Texture.width * 3 / 2.0f, curScreen.height - returnBttnx.Texture.height * 3 / NUM_FRAMES / 2.0f);
        

        background = LoadImage("../Resources/Images/bk.png");
        ImageResize(&background, curScreen.width, curScreen.height);
        backgroundTex = LoadTextureFromImage(background); // background
        UnloadImage(background);

        creditsImg = LoadImage("../Resources/Credits/CreditsWhite.png");
        ImageResize(&creditsImg, curScreen.width, curScreen.height);

        logo = LoadImage("../Resources/Images/SymBlack.png");
        ImageResize(&logo, 50, 50);

        backgroundCred = LoadTextureFromImage(creditsImg);

        logoTex = LoadTextureFromImage(logo);


        std::cout << "finished credits init";
    }

    void UpdateCredits()
    {
        DrawCredits();

        mousePoint = GetMousePosition();


        if (CheckCollisionPointRec(mousePoint, dev.Bounds)) //Checks state of the DEV BTTN
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))dev.changeColor({ 255, 203, 0, 255 });
            else dev.changeColor({ 200, 200, 200, 255 });

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) dev.Action = true;
        }
        else dev.changeColor({ 80, 80, 80, 255 });

        if (CheckCollisionPointRec(mousePoint, lib.Bounds)) //Checks state of the DEV BTTN
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))lib.changeColor({ 255, 203, 0, 255 });
            else lib.changeColor({ 200, 200, 200, 255 });

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) lib.Action = true;
        }
        else lib.changeColor({ 80, 80, 80, 255 });

   
        if (CheckCollisionPointRec(mousePoint, returnBttnx.Bounds)) //Checks state of the RETURN BTTN
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) returnBttnx.State = 2;
            else returnBttnx.State = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) returnBttnx.Action = true;
        }
        else returnBttnx.State = 0;
      

        if (returnBttnx.Action) // Button RETURN PRESSED
        {
            std::cout << "boton Credits pressed" << "\n";
            returnBttnx.Action = false;
            ScreenManagerNam::Screens = ScreenManagerNam::Menu;
        }

        if (dev.Action)
        {
            dev.openUrl();
        }

        if (lib.Action)
        {
            lib.openUrl();
        }

        returnBttnx.calcButtonState();
    }

    void DrawCredits() 
    {
        BeginDrawing();

        ClearBackground(GetColor(0x052c46ff));

        DrawTexture(backgroundTex, 0.0f, 2.0f, WHITE);

        DrawTexture(backgroundCred, 0, 0, WHITE);
        DrawTexture(logoTex, 0 + logoTex.width, curScreen.height - logoTex.height*2, WHITE);

       
        DrawRectangleRec(dev.Bounds, dev.btnColor);
        DrawRectangleLinesEx(dev.Bounds, dev.frame, BLACK);
        DrawText(dev.name, curScreen.width / 2 - MeasureText(dev.name, 30) / 2, dev.Bounds.y + 15, 30, BLACK);

        DrawRectangleRec(lib.Bounds, lib.btnColor);
        DrawRectangleLinesEx(lib.Bounds, lib.frame, BLACK);
        DrawText(lib.name, curScreen.width / 2 - MeasureText(lib.name, 30) / 2, lib.Bounds.y + 15, 30, BLACK); 

        DrawTextureRec(returnBttnx.Texture, returnBttnx.SourceRec, Vector2{ returnBttnx.Bounds.x, returnBttnx.Bounds.y }, WHITE);

        EndDrawing();
    }

    void UnloadCredits()
    {
        UnloadTexture(rtn);
        UnloadTexture(backgroundCred);
        UnloadTexture(backgroundTex);
        UnloadTexture(logoTex);
        UnloadImage(creditsImg);
        std::cout << "Credits Unloaded." << '\n';
    }
}
