#include "Game.hpp"

Game::Game(SDL_Renderer *_renderer, TTF_Font *_font, int screenWidth, int screenHeight)
    : renderer(_renderer), font(_font), screenWidth(screenWidth), screenHeight(screenHeight)
{
    SDL_Surface *backgroundSurface = IMG_Load("assets/img/background1.png");
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

    // Load button image
    SDL_Surface *buttonSurface = IMG_Load("assets/img/buttonmenu.png");
    if (!buttonSurface)
    {
        std::cerr << "Failed to load button image: " << IMG_GetError() << std::endl;
    }

    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    if (!buttonTexture)
    {
        std::cerr << "Failed to create button texture: " << SDL_GetError() << std::endl;
    }

    // Set button position and size
    buttonRect = {screenWidth - 60, 25, 60, 20};
}

Game::~Game()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
}

void Game::run()
{
    drawBackground();
    drawTitle();
    drawCheckerboard();
    drawButton();
}

void Game::drawBackground()
{
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
}

void Game::drawTitle()
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Jeu du parking", {150, 27, 0, 255});
    if (!textSurface)
    {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture)
    {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
    }

    int textWidth, textHeight;
    TTF_SizeText(font, "Jeu du parking", &textWidth, &textHeight);
    SDL_Rect textRect = {screenWidth / 2 - textWidth / 2, 40, textWidth, textHeight}; // Adjusted for a 800x600 window
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_DestroyTexture(textTexture);
}

void Game::drawCheckerboard()
{
    const int ROWS = 8, COLS = 8;
    int squareSize = 50;

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            SDL_Rect rect = {j * squareSize + (screenWidth - COLS * squareSize) / 2 + j,
                             i * squareSize + (screenHeight - ROWS * squareSize) / 2 + i,
                             squareSize,
                             squareSize};
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 185);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Game::drawButton()
{
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
}

int Game::handleButtonClick(int x, int y)
{
    if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
        y >= buttonRect.y && y <= buttonRect.y + buttonRect.h)
    {
        return 10;
    }
    return 0;
}
