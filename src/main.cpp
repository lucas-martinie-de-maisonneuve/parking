// main.cpp
#include "Game.hpp"
#include "Window.hpp"
int screenWidth = 1000;
int screenHeight = 750;

int main(int argc, char *argv[]) {
    // Create window
    Window window(screenWidth, screenHeight);
    if (!window.isInitialized()) {
        std::cerr << "Failed to initialize the window." << std::endl;
        return -1;
    }

    // Get renderer
    SDL_Renderer *renderer = window.getRenderer();

    // Load font
    TTF_Font *font = TTF_OpenFont("assets/fonts/Coffee.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return -1;
    }

    // Create game instance
    Game game(renderer, font);

    // Main game loop
    bool running = true;
    SDL_Event event;
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // window.update();
        game.run();

        SDL_RenderPresent(renderer);

        // Delay for stable frame rate
        SDL_Delay(16); // Adjust this value for desired frame rate
    }

    // Cleanup resources
    TTF_CloseFont(font);

    return 0;
}
