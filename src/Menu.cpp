// Menu.cpp
#include "menu.hpp"

Menu::Menu(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), font(nullptr), font2(nullptr), screenWidth(screenWidth), screenHeight(screenHeight)
{
    // if (TTF_Init() == -1)
    // {
    //     std::cerr << "SDL TTF initialization failed: " << TTF_GetError() << std::endl;
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

    TTF_Font *font = TTF_OpenFont("assets/fonts/Coffee.ttf", 35);
    TTF_Font *font2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!font2)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    SDL_Surface *backgroundSurface = IMG_Load("assets/img/backgroundMenu.jpg");
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
    TTF_CloseFont(font);
}

void Menu::run()
{
    drawBackground();
    drawTitle();

    // Placeholder for additional Menu logic
}

void Menu::drawBackground()
{
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
}

void Menu::drawTitle()
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Boat Parking", {150, 27, 0, 255});
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
    TTF_SizeText(font, "Boat parking", &textWidth, &textHeight);
    SDL_Rect textRect = {screenWidth / 2 - textWidth / 2, 25, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}
