#include "ScreenManager.h"

namespace ScreenManagerNam
{

	static void Change();

	GameScreen Screens;

	int ScreenManager()
	{
		SetTargetFPS(60);

		Menu::InitMenu();

		while (!WindowShouldClose())
		{
			Change();
		}

		CloseWindow();
		Unloader::UnloadAll();
		return 0;
	}


	static void Change()
	{
		
		switch (Screens)
		{

		case Menu: {
			Menu::UpdateMenu();
		} break;


		case Instructions: {
			Instructions::UpdateInstructions();
		} break;

		case Credits: {
			CreditsNmsp::UpdateCredits();
		} break;

		case Game: {
			Game::UpdateGame();
		} break;

		}


	}
}