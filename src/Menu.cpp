#include "Menu.hpp"
#include <iostream>

using namespace std;

Menu::Menu(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), font1(nullptr), font2(nullptr), screenWidth(screenWidth), screenHeight(screenHeight)
{
    font1 = TTF_OpenFont("assets/fonts/Oswald-Medium.ttf", 35);
    if (!font1)
    {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }

    font2 = TTF_OpenFont("assets/fonts/Motley Forces.ttf", 50);
    if (!font2)
    {
        cerr << "Failed to load font2: " << TTF_GetError() << endl;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

Menu::~Menu()
{
    unloadMenuItems();
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
}

void Menu::loadBackground()
{
    SDL_Surface *backgroundSurface = IMG_Load("assets/img/backgroundMenu.png");
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
}

void Menu::loadMenuItems()
{
    loadTitle();
    loadMenuOptions();
    loadBackground();
}

void Menu::unloadMenuItems()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(textTitle);
    SDL_DestroyTexture(textTexture1);
    SDL_DestroyTexture(textTexture2);
    SDL_DestroyTexture(textTexture3);
}

void Menu::runMenu()
{
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    SDL_RenderCopy(renderer, textTitle, nullptr, &rectTextTitle);
    displayMenuOptions();
}

void Menu::loadTitle()
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(font2, "Boat Parking", {255, 255, 255, 255});
    if (!textSurface)
    {
        cerr << "Failed to render text: " << TTF_GetError() << endl;
    }

    textTitle = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTitle)
    {
        cerr << "Failed to create text texture: " << SDL_GetError() << endl;
    }

    int textWidth, textHeight;
    TTF_SizeText(font2, "Boat Parking", &textWidth, &textHeight);
    rectTextTitle = {screenWidth / 2 - textWidth / 2, 25, textWidth, textHeight};
}

void Menu::loadMenuOptions()
{
    menuItem1 = {screenWidth / 2 - 100, 100, 200, 50};
    menuItem2 = {screenWidth / 2 - 100, 170, 200, 50};
    menuItem3 = {screenWidth / 2 - 100, 240, 200, 50};

    // Play
    SDL_Surface *textSurface1 = TTF_RenderText_Blended(font1, "Play", {0, 0, 0, 255});
    if (!textSurface1)
    {
        cerr << "Failed to render text: " << TTF_GetError() << endl;
    }
    textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
    int textWidth1, textHeight1;
    TTF_SizeText(font1, "Play", &textWidth1, &textHeight1);
    textRect1 = {menuItem1.x + menuItem1.w / 2 - textWidth1 / 2, menuItem1.y + menuItem1.h / 2 - textHeight1 / 2, textWidth1, textHeight1};
    SDL_FreeSurface(textSurface1);

    // Options
    SDL_Surface *textSurface2 = TTF_RenderText_Blended(font1, "Rules", {0, 0, 0, 255});
    if (!textSurface2)
    {
        cerr << "Failed to render text: " << TTF_GetError() << endl;
    }
    textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
    int textWidth2, textHeight2;
    TTF_SizeText(font1, "Rules", &textWidth2, &textHeight2);
    textRect2 = {menuItem2.x + menuItem2.w / 2 - textWidth2 / 2, menuItem2.y + menuItem2.h / 2 - textHeight2 / 2, textWidth2, textHeight2};
    SDL_FreeSurface(textSurface2);

    // Exit
    SDL_Surface *textSurface3 = TTF_RenderText_Blended(font1, "Exit", {0, 0, 0, 255});
    if (!textSurface3)
    {
        cerr << "Failed to render text: " << TTF_GetError() << endl;
    }
    textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
    int textWidth3, textHeight3;
    TTF_SizeText(font1, "Exit", &textWidth3, &textHeight3);
    textRect3 = {menuItem3.x + menuItem3.w / 2 - textWidth3 / 2, menuItem3.y + menuItem3.h / 2 - textHeight3 / 2, textWidth3, textHeight3};
    SDL_FreeSurface(textSurface3);
}

void Menu::displayMenuOptions()
{
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

int Menu::mousePositionMenu()
{
    while (SDL_PollEvent(&eventMenu))
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (eventMenu.type == SDL_QUIT)
        {
            return -1;
        }
        else if (eventMenu.type == SDL_MOUSEBUTTONDOWN && eventMenu.button.button == SDL_BUTTON_LEFT)
        {
            if (x >= menuItem3.x && x <= menuItem3.x + menuItem3.w &&
                y >= menuItem3.y && y <= menuItem3.y + menuItem3.h)
            {
                return -1;
            }

            if (x >= menuItem1.x && x <= menuItem1.x + menuItem1.w &&
                y >= menuItem1.y && y <= menuItem1.y + menuItem1.h)
            {
                return 0;
            }

            if (x >= menuItem2.x && x <= menuItem2.x + menuItem2.w &&
                y >= menuItem2.y && y <= menuItem2.y + menuItem2.h)
            {
                return 20;
            }
        }
    }
    return 10;
}
