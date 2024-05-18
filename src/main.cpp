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

    // Menu
    menu.loadMenuItems();
    

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
            game.displayGame();
            pageState = game.mousePositionGame();
        }

        else if (pageState == 10)
        {
            menu.runMenu();
            pageState = menu.mousePositionMenu();
        }

        else if (pageState == 20)
        {
            option.displayOption();
            pageState = option.mousePositionOption();
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    return 0;
}
