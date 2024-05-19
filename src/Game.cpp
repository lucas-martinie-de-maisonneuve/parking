#include <iostream>
using namespace std;
#include "Boat.hpp"

#include "Game.hpp"

Game::Game(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      font(nullptr), font2(nullptr), textTexture(nullptr)
{
    

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

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    myBoat.grid();
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
    displayBoat();
}

void Game::loadGameTextures()
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(font2, "Jeu du parking", {150, 27, 0, 255});
    if (!textSurface)
    {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture)
    {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
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
        std::cerr << "Failed to load button image: " << IMG_GetError() << std::endl;
    }

    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    if (!buttonTexture)
    {
        std::cerr << "Failed to create button texture: " << SDL_GetError() << std::endl;
    }

    buttonRect = {screenWidth - 60, 25, 60, 20};
    cout << "gameLoaded";
}

 void Game::drawBoat(char id, int x, int y, int length, bool horizontal){
    SDL_Color color;
        switch (id) {
        case '1': color = {255, 0, 0, 255}; break; 
        case '2': color = {0, 255, 0, 255}; break; 
        case '3': color = {0, 0, 255, 255}; break; 
        case '4': color = {255, 255, 0, 255}; break; 
        case '5': color = {255, 165, 0, 255}; break;
        case '6': color = {128, 0, 128, 255}; break; 
        default: color = {255, 255, 255, 255}; break;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < length; ++i) {
        SDL_Rect rect;
        if (horizontal) {
            rect = {x + i * (squareSize +padding), y, squareSize, squareSize};
        } else {
            rect = {x, y + i * (squareSize+padding), squareSize, squareSize};
        }
        SDL_RenderFillRect(renderer, &rect);
    }

 }

void Game::unloadGameTexture()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(textureBoat0);
   
    cout << "gameUnLoaded";
}

void Game::drawCheckerboard()
{

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

void Game::displayBoat()
{  

       struct Boat {
        char id;
        int x, y;
        int length;
        bool horizontal;
    };

    Boat boats[] = {
        {'1', 0, 0, 2, true},
        {'2', 1, 2, 3, false},
        {'3', 4, 4, 2, true},
        {'4', 6, 1, 3, false},
        {'5', 3, 5, 2, true},
        {'6', 7, 6, 3, false}
    };

    for (const auto& boat : boats) {
        drawBoat(boat.id, offsetX + boat.x * (squareSize+padding), offsetY + boat.y * (squareSize+padding), boat.length, boat.horizontal);

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (myBoat.boatList[i][j])
            {
                
            }

            else {

            }
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
