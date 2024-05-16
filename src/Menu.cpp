// Menu.cpp
#include "Menu.hpp"

using namespace std;

Menu::Menu(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), font1(nullptr), font2(nullptr), screenWidth(screenWidth), screenHeight(screenHeight)
{

    font1 = TTF_OpenFont("assets/fonts/Coffee.ttf", 35);
    if (!font1)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    font2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!font2)
    {
        std::cerr << "Failed to load font2: " << TTF_GetError() << std::endl;
    }
    
 // Load font
    TTF_Font *font1 = TTF_OpenFont("assets/fonts/Coffee.ttf", 24);
    TTF_Font *font2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);

    SDL_Surface *backgroundSurface = IMG_Load("assets/img/backgroundMenu.png");
    if (!backgroundSurface)
    {
        cerr << "Failed to load background image: " << IMG_GetError() << endl;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture)
    {
        cerr << "Failed to create background texture: " << SDL_GetError() << std::endl;
    }
}

Menu::~Menu()
{
    SDL_DestroyTexture(backgroundTexture);

    // Font
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
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
    SDL_Surface *textSurface = TTF_RenderText_Solid(font2, "Boat Parking", {150, 27, 0, 255});
    if (!textSurface)
    {
        cerr << "Failed to render text m: " << TTF_GetError() << endl;
       
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture)
    {
        cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;

    }

    int textWidth, textHeight;
    TTF_SizeText(font2, "Boat parking", &textWidth, &textHeight);
    SDL_Rect textRect = {screenWidth / 2 - textWidth / 2, 25, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}

