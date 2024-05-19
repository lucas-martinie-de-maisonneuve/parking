#include "Game.hpp"
// #include "Boat.hpp"
#include <iostream>
using namespace std;

Game::Game(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      font(nullptr), font2(nullptr), textTexture(nullptr)
{
    font = TTF_OpenFont("assets/fonts/Coffee.ttf", 35);
    if (!font)
    {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }

    font2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!font2)
    {
        cerr << "Failed to load font2: " << TTF_GetError() << endl;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

Game::~Game()
{
    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    unloadGameTexture();

    TTF_Quit();
    IMG_Quit();
}

void Game::displayGame()
{
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
    drawCheckerboard();
}

void Game::loadGameTextures()
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(font2, "Jeu du parking", {150, 27, 0, 255});
    if (!textSurface)
    {
        cerr << "Failed to render text: " << TTF_GetError() << endl;
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture)
    {
        cerr << "Failed to create text texture: " << SDL_GetError() << endl;
    }

    int textWidth, textHeight;
    TTF_SizeText(font2, "Jeu du parking", &textWidth, &textHeight);
    textRect = {screenWidth / 2 - textWidth / 2, 40, textWidth, textHeight};

    SDL_Surface *backgroundSurface = IMG_Load("assets/img/BackgrounGame.png");
    if (!backgroundSurface)
    {
        cerr << "Failed to load background image: " << IMG_GetError() << endl;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture)
    {
        cerr << "Failed to create background texture: " << SDL_GetError() << endl;
    }

    SDL_Surface *buttonSurface = IMG_Load("assets/img/buttonmenu.png");
    if (!buttonSurface)
    {
        cerr << "Failed to load button image: " << IMG_GetError() << endl;
    }

    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    if (!buttonTexture)
    {
        cerr << "Failed to create button texture: " << SDL_GetError() << endl;
    }

    buttonRect = {screenWidth - 60, 25, 60, 20};
}

void Game::unloadGameTexture()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
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

int Game::eventHandlerGame()
{
    while (SDL_PollEvent(&eventGame))
    {
        if (eventGame.type == SDL_QUIT)
        {
            return -1;
        }

        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
            y >= buttonRect.y && y <= buttonRect.y + buttonRect.h)
        {
            buttonRect = {screenWidth - 64, 24, 62, 22};
            if (eventGame.type == SDL_MOUSEBUTTONDOWN && eventGame.button.button == SDL_BUTTON_LEFT)
            {
                return 10; 
            }
        }
        else
        {
            buttonRect = {screenWidth - 60, 25, 60, 20};
        }
    }
    return 0;
}
