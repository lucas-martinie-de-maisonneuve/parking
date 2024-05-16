#include "Window.hpp"
#include "Game.hpp"
#include "Menu.hpp"
int pageState = 0;
int screenWidth = 585;
int screenHeight = 750;

int main(int argc, char *argv[])
{
    // Create window
    Window window(screenWidth, screenHeight);
    if (!window.isInitialized())
    {
        std::cerr << "Failed to initialize the window." << std::endl;
        return -1;
    }

    // Get renderer
    SDL_Renderer *renderer = window.getRenderer();

    // Load font
    TTF_Font *font = TTF_OpenFont("assets/fonts/Coffee.ttf", 24);
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return -1;
    }

    // Create game instance
    Game game(renderer, font, screenWidth, screenHeight);
    Menu menu(renderer, font, screenWidth, screenHeight);

    // Main game loop
    bool running = true;
    SDL_Event event;
    while (running)
    {
        // Handle events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (game.handleButtonClick(x, y))
                {
                    pageState = 10;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (pageState == 0)
            game.run();
        else if (pageState == 10)
            menu.run();

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    // Cleanup resources
    TTF_CloseFont(font);

    return 0;
}
