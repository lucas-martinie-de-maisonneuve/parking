#include <iostream>
using namespace std;

// Laod files
#include "Option.hpp"


Option::Option(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      fontOption1(nullptr), fontOption2(nullptr), textTexture(nullptr)
{


    fontOption1 = TTF_OpenFont("assets/fonts/Coffee.ttf", 35);
    if (!fontOption1)
    {
        cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    fontOption2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!fontOption2)
    {
        cerr << "Failed to load font2: " << TTF_GetError() << std::endl;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(fontOption1, "Jeu du parking", {150, 27, 0, 255});
    if (!textSurface)
    {
       cerr << "Failed to render text: " << TTF_GetError() << std::endl;
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture)
    {
        cerr << "Failed to create text texture: " << SDL_GetError() << endl;
    
    }

    int textWidth, textHeight;
    TTF_SizeText(fontOption2, "Jeu du parking", &textWidth, &textHeight);
    textRect = {screenWidth / 2 - textWidth / 2, 40, textWidth, textHeight};

    
    // Load background image
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
        cerr << "Failed to create button texture: " << SDL_GetError() << endl;
    }

    buttonRect = {screenWidth - 60, 25, 60, 20};
}

Option::~Option()
{
    // Font
    TTF_CloseFont(fontOption1);
    TTF_CloseFont(fontOption2);   

    // Texture
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(textTexture);
  
    TTF_Quit();
    IMG_Quit();
}

void Option::displayOption()
{    // Background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
}

int Option::mousePositionOption()
{
    // Handle events
    while (SDL_PollEvent(&eventOption))
    {
        if (eventOption.type == SDL_QUIT)
        {
            return -1;
        }

        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
            y >= buttonRect.y && y <= buttonRect.y + buttonRect.h)

        {
            buttonRect = {screenWidth - 64, 24, 62, 22}; // Hover effect
            if (eventOption.type == SDL_MOUSEBUTTONDOWN && eventOption.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "Button clicked Option" << std::endl;
                return 10; // Button clicked
            }
        }
        else
        {
            buttonRect = {screenWidth - 60, 25, 60, 20}; // Normal state
        }
    }
    return 20;
}