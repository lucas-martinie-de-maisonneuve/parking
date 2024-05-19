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
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }

    font2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!font2)
    {
        cerr << "Failed to load font2: " << TTF_GetError() << endl;
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
    cout << "gameLoaded";

    SDL_SetTextureBlendMode(boat_Vertical_Texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(boat_Horizontal_Texture, SDL_BLENDMODE_BLEND);
    // Load boat textures
    SDL_Surface *boat_Vertical_Surface = IMG_Load("assets/img/boat_v.png");
    if (!boat_Vertical_Surface)
    {
        cerr << "Failed to load small boat image: " << IMG_GetError() << endl;
    }
    boat_Vertical_Texture = SDL_CreateTextureFromSurface(renderer, boat_Vertical_Surface);
    SDL_FreeSurface(boat_Vertical_Surface);
    if (!boat_Vertical_Texture)
    {
        cerr << "Failed to create small boat texture: " << SDL_GetError() << endl;
    }

    SDL_Surface *boat_Horizontal_Surface = IMG_Load("assets/img/boat_h.png");
    if (!boat_Horizontal_Surface)
    {
        cerr << "Failed to load large boat image: " << IMG_GetError() << endl;
    }
    boat_Horizontal_Texture = SDL_CreateTextureFromSurface(renderer, boat_Horizontal_Surface);
    SDL_FreeSurface(boat_Horizontal_Surface);
    if (!boat_Horizontal_Texture)
    {
        cerr << "Failed to create large boat texture: " << SDL_GetError() << endl;
    }

    buttonRect = {screenWidth - 60, 25, 60, 20};
    cout << "gameLoaded";
}

void Game::drawBoat(char id, int x, int y, int length, bool horizontal)
{
    SDL_Color color;
    switch (id)
    {
    case '1':
        color = {220, 50, 50, 200}; // Red
        break;
    case '2':
        color = {0, 255, 0, 200}; // Green
        break;
    case '3':
        color = {0, 0, 255, 200}; // Blue
        break;
    case '4':
        color = {255, 255, 0, 200}; // Yellow
        break;
    case '5':
        color = {255, 165, 0, 200}; // Orange
        break;
    case '6':
        color = {128, 50, 100, 200}; // Purple
        break;
    default:
        color = {255, 255, 255, 200}; // White
        break;
    }

    SDL_Texture* texture = horizontal ? boat_Horizontal_Texture : boat_Vertical_Texture;

    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(texture, color.a);

    SDL_Rect rect;
    if (horizontal)
    {
        rect = {x + padding, y, squareSize * length, squareSize};
    }
    else
    {
        rect = {x, y + padding, squareSize, squareSize * length};
    }

    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    // Réinitialiser les modulations de couleur et d'alpha après le rendu
    SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_SetTextureAlphaMod(texture, 255);
}

void Game::unloadGameTexture()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(textureBoat0);
    SDL_DestroyTexture(boat_Vertical_Texture);
    SDL_DestroyTexture(boat_Horizontal_Texture);
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
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Game::displayBoat()
{
    for (const auto &boat : boats)
    {
        drawBoat(boat.id, offsetX + boat.x * (squareSize + padding), offsetY + boat.y * (squareSize + padding), boat.length, boat.horizontal);

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                if (myBoat.boatList[i][j])
                    ;
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
