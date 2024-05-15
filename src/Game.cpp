// Game.cpp
#include "Game.hpp"
Game::Game(SDL_Renderer *_renderer, TTF_Font *_font) : renderer(_renderer), font(_font)
{
    SDL_Surface *backgroundSurface = IMG_Load("assets/img/background.jpg");
    if (!backgroundSurface)
    {
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture)
    {
        std::cerr << "Failed to create background texture: " << SDL_GetError() << std::endl;
    }
}

Game::~Game()
{
    SDL_DestroyTexture(backgroundTexture);
}

void Game::run()
{
    drawBackground();
    drawTitle();
    drawCheckerboard();

    // Placeholder for additional game logic
}

void Game::drawBackground()
{
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
}

void Game::drawTitle()
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Jeu du parking", {0, 0, 0, 255});
    if (!textSurface)
    {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        // Proper error handling needed, maybe throw an exception
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture)
    {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        // Proper error handling needed, maybe throw an exception
    }

    int textWidth, textHeight;
    TTF_SizeText(font, "Jeu du parking", &textWidth, &textHeight);

    SDL_Rect textRect = {400 - textWidth / 2, 40, textWidth, textHeight}; // Adjusted for a 800x600 window
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_DestroyTexture(textTexture);
}

void Game::drawCheckerboard()
{
    const int ROWS = 8, COLS = 8;
    int squareSize = 70;

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            SDL_Rect rect = {j * squareSize + (1000 - COLS * squareSize) / 2 + j,
                             i * squareSize + (750 - ROWS * squareSize) / 2 + i,
                             squareSize,
                             squareSize};

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
