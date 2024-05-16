// Menu.cpp

#include "menu.hpp"


Menu::Menu(SDL_Renderer *_renderer, TTF_Font *_font, int screenWidth, int screenHeight)
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
}

Menu::~Menu()
{
    SDL_DestroyTexture(backgroundTexture);
}

void Menu::run()
{
    drawBackground();
    drawTitle();
    drawCheckerboard();

    // Placeholder for additional Menu logic
}

void Menu::drawBackground()
{
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
}

void Menu::drawTitle()
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Jeu du parking", {150, 27, 0, 255});
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
    SDL_Rect textRect = {screenWidth / 2 - textWidth / 2, 40, textWidth, textHeight}; // Adjusted for a 800x600 window
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_DestroyTexture(textTexture);
}

void Menu::drawCheckerboard()
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
