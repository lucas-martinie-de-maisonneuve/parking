// Menu.cpp
#include "Menu.hpp"

using namespace std;

Menu::Menu(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), font1(nullptr), font2(nullptr), screenWidth(screenWidth), screenHeight(screenHeight)
{

    font1 = TTF_OpenFont("assets/fonts/Oswald-Medium.ttf", 35);
    if (!font1)
    {
        cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    font2 = TTF_OpenFont("assets/fonts/Motley Forces.ttf", 50);
    if (!font2)
    {
        cerr << "Failed to load font2: " << TTF_GetError() << std::endl;
    }

    // Load font
    TTF_Font *font1 = TTF_OpenFont("assets/fonts/Oswald-Medium.ttf", 24);
    TTF_Font *font2 = TTF_OpenFont("assets/fonts/Motley Forces.ttf", 50);
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

    // Font
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);

    // Texture
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(textTitle);
    SDL_DestroyTexture(textTexture1);
    SDL_DestroyTexture(textTexture2);
    SDL_DestroyTexture(textTexture3);
}

void Menu::loadMenuItems()
{
    loadTitle();
    loadMenuOptions();
}

void Menu::runMenu()
{
    // Background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    // Title
    SDL_RenderCopy(renderer, textTitle, nullptr, &rectTextTitle);
    // Menu options
    displayMenuOptions();
}

void Menu::loadTitle()
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font2, "Boat Parking", {255, 255, 255, 255});
    if (!textSurface)
    {
        cerr << "Failed to render text m: " << TTF_GetError() << endl;
    }

    textTitle = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTitle)
    {
        cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
    }

    int textWidth, textHeight;
    TTF_SizeText(font2, "Boat parking", &textWidth, &textHeight);
    rectTextTitle = {screenWidth / 2 - textWidth / 2, 25, textWidth, textHeight};
}

void Menu::loadMenuOptions()
{
    // Draw menu items

    menuItem1 = {screenWidth / 2 - 100, 100, 200, 50};
    menuItem2 = {screenWidth / 2 - 100, 170, 200, 50};
    menuItem3 = {screenWidth / 2 - 100, 240, 200, 50};

    // Play
    SDL_Surface *textSurface1 = TTF_RenderText_Solid(font1, "Play", {0, 0, 0, 255});
    textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
    int textWidth1, textHeight1;
    TTF_SizeText(font1, "Play", &textWidth1, &textHeight1);
    textRect1 = {menuItem1.x + menuItem1.w / 2 - textWidth1 / 2, menuItem1.y + menuItem1.h / 2 - textHeight1 / 2, textWidth1, textHeight1};
    SDL_FreeSurface(textSurface1);

    // Options
    SDL_Surface *textSurface2 = TTF_RenderText_Solid(font1, "Options", {0, 0, 0, 255});
    textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
    TTF_SizeText(font1, "Options", &textWidth1, &textHeight1);
    textRect2 = {menuItem2.x + menuItem2.w / 2 - textWidth1 / 2, menuItem2.y + menuItem2.h / 2 - textHeight1 / 2, textWidth1, textHeight1};
    SDL_FreeSurface(textSurface2);

    // Exit
    SDL_Surface *textSurface3 = TTF_RenderText_Solid(font1, "Exit", {0, 0, 0, 255});
    textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
    TTF_SizeText(font1, "Exit", &textWidth1, &textHeight1);
    textRect3 = {menuItem3.x + menuItem3.w / 2 - textWidth1 / 2, menuItem3.y + menuItem3.h / 2 - textHeight1 / 2, textWidth1, textHeight1};
    SDL_FreeSurface(textSurface3);
}

void Menu::displayMenuOptions()
{

    // White Rect
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Play
    SDL_RenderFillRect(renderer, &menuItem1);
    SDL_RenderCopy(renderer, textTexture1, nullptr, &textRect1);

    // Options
    SDL_RenderFillRect(renderer, &menuItem2);
    SDL_RenderCopy(renderer, textTexture2, nullptr, &textRect2);

    // Exit
    SDL_RenderFillRect(renderer, &menuItem3);
    SDL_RenderCopy(renderer, textTexture3, nullptr, &textRect3);
}
