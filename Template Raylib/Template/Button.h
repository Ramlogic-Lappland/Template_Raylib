#pragma once
#include "ScreenManager.h"

namespace Button
{
    struct   newButton
    {
        Texture2D Texture;
        Rectangle SourceRec;
        Rectangle Bounds;
        float FrameHeight;
        int State;
        bool Action;
    };


    class NewButtonx
    {
    public:
        Rectangle Bounds;
        bool Action;

        
        void setBounds(float width_a, float height_a, float x_a, float y_a)
        {
            Bounds.width = width_a;
            Bounds.height = height_a;
            Bounds.x = x_a;
            Bounds.y = y_a;
        }
    };

    class NewMenuButton : public NewButtonx
    {
    public:
        Texture2D Texture;
        Rectangle SourceRec;
        float FrameHeight;
        int State;


        void setMenuButton(Texture2D texture, float frameheight, float a, float b, float c, int state)
        {
            Texture = texture;
            FrameHeight = frameheight;
            SourceRec = { a,  b,  c,  frameheight};
            State = state;
        }
        void drawThisButton()
        {
            DrawTextureRec(Texture, SourceRec, Vector2{ Bounds.x, Bounds.y }, WHITE);
        }
        void calcButtonState()
        {
            SourceRec.y = State * FrameHeight;
        }

    };

    
    class ReturnButton : public NewMenuButton
    {
        /*
            public: 
        void executeButton()
        {
            std::cout << "boton Credits pressed" << "\n";
            Action = false;
            ScreenManagerNam::Screens = ScreenManagerNam::Menu;
        }
        */

    };

    class NewCreditButton : public NewButtonx
    {
    public: 
        Color btnColor;
        const char* btnUrl;
        const char* name;
        float frame = 3.5f;

        void setCreditButton(Color a, const char* url, const char* nam)
        {
            btnColor = a;
            btnUrl = url;
            name = nam;     
        }

        void changeColor(Color a)
        {
            btnColor = a;
        }

        void openUrl()
        {
            std::cout << "boton dev pressed" << "\n";
            Action = false;
            OpenURL(btnUrl);
        }
    };
}
