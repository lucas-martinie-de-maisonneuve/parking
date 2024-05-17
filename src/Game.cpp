#include "Game.hpp"
#include <iostream>
using namespace std;

Game::Game(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      font(nullptr), font2(nullptr), textTexture(nullptr)
{
    // Initialize SDL TTF
    // if (TTF_Init() == -1)
    // {
    //     std::cerr << "SDL TTF initialization failed: " << TTF_GetError() << std::endl;
    //     // Handle initialization failure
    // }

    font = TTF_OpenFont("assets/fonts/Coffee.ttf", 35);
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    font2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!font2)
    {
        std::cerr << "Failed to load font2: " << TTF_GetError() << std::endl;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(font2, "Jeu du parking", {150, 27, 0, 255});
    if (!textSurface)
    {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        // Handle text rendering failure
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture)
    {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        // Handle text texture creation failure
    }

    int textWidth, textHeight;
    TTF_SizeText(font2, "Jeu du parking", &textWidth, &textHeight);
    textRect = {screenWidth / 2 - textWidth / 2, 40, textWidth, textHeight};

    
    // Load background image
    SDL_Surface *backgroundSurface = IMG_Load("assets/img/backgroundGame.jpeg");
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

    buttonRect = {screenWidth - 60, 25, 60, 20};
}

Game::~Game()
{
    // Font
    TTF_CloseFont(font);
    TTF_CloseFont(font2);   

    // Texture
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(textTexture);
  
    TTF_Quit();
    IMG_Quit();
}

void Game::displayGame()
{
    // Background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
    drawCheckerboard();
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


int Game::mousePositionGame()
{
    // Handle events
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
            buttonRect = {screenWidth - 64, 24, 62, 22}; // Hover effect
            if (eventGame.type == SDL_MOUSEBUTTONDOWN && eventGame.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "Button clicked" << std::endl;
                return 10; // Button clicked
            }
        }
        else
        {
            buttonRect = {screenWidth - 60, 25, 60, 20}; // Normal state
        }
    }
    return 0;
}