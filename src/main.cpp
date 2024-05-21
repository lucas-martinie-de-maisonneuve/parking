using namespace std;

#include "Window.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Option.hpp"

int pageState = 10;
int screenWidth = 600;
int screenHeight = 750;

int main(int argc, char *argv[])
{
    // Create window
    Window window(screenWidth, screenHeight);
    if (!window.isInitialized())
    {
        cerr << "Failed to initialize the window." << endl;
        return -1;
    }

    // Get renderer
    SDL_Renderer *renderer = window.getRenderer();

    // Create game instance
    Game game(renderer, screenWidth, screenHeight);
    Menu menu(renderer, screenWidth, screenHeight);
    Option option(renderer, screenWidth, screenHeight);

    // Main game loop
    bool running = true;

    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (pageState == -1)
            running = false;

        else if (pageState == 0)
        {
            if (!game.gameLoaded)
            {
                game.loadGameTextures();
                game.resetGame();
                game.gameLoaded = true;
            }
            else if (menu.menuLoaded)
            {
                menu.unloadMenuItems();
                menu.menuLoaded = false;
            }
            game.displayGame();
            pageState = game.eventHandlerGame();
        }

        else if (pageState == 10)
        {
            if (!menu.menuLoaded)
            {
                menu.loadMenuItems();
                menu.menuLoaded = true;
            }
            if (game.gameLoaded)
            {
                game.unloadGameTexture();
                game.gameLoaded = false;
            }
            if (option.optionLoaded)
            {
                option.unloadOptionTextures();
                option.optionLoaded = false;
            }

            menu.runMenu();
            pageState = menu.mousePositionMenu();
        }

        else if (pageState == 20)
        {
            if (!option.optionLoaded)
            {
                option.loadOptionTextures();
                option.optionLoaded = true;
            }
            if (menu.menuLoaded)
            {
                menu.unloadMenuItems();
                menu.menuLoaded = false;
            }
            option.displayOption();
            pageState = option.mousePositionOption();
        }
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
    SDL_Quit();
    return 0;
}
