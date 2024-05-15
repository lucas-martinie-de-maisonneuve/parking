#include <iostream>
#include "Element.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

using namespace std;

const int WIDTH = 1000, HEIGHT = 600;
const int ROWS = 6, COLS = 6;
SDL_Renderer *renderer;
TTF_Font *font;

void drawBackground()
{
    // Load background
    SDL_Surface *backgroundSurface = IMG_Load("assets/img/background.jpg");
    if (!backgroundSurface)
    {
        cerr << "Failed to load background image: " << IMG_GetError() << endl;
        return;
    }

    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture)
    {
        cerr << "Failed to create background texture: " << SDL_GetError() << endl;
        return;
    }

    // Display Background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    SDL_DestroyTexture(backgroundTexture);
}


void drawTitle()
{
    // Render text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Jeu du parking", COLOR_BLACK);
    if (!textSurface)
    {
        cerr << "Failed to render text: " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int textWidth, textHeight;
    TTF_SizeText(font, "Jeu du parking", &textWidth, &textHeight);

    SDL_Rect textRect = {WIDTH / 2 - textWidth / 2, 40, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}

void drawCheckerboard()
{
    int squareSize = 70;

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            SDL_Rect rect = {j * squareSize + (WIDTH - COLS * squareSize) / 2 + j,
                             i * squareSize + (HEIGHT - ROWS * squareSize) / 2 + i,
                             squareSize,
                             squareSize};

            SDL_SetRenderDrawColor(renderer, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (TTF_Init() != 0)
    {
        cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
        return 1;
    }

    font = TTF_OpenFont("assets/fonts/Coffee.ttf", 40);
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    drawBackground();
    drawTitle();
    drawCheckerboard();

    SDL_Event windowEvent;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                running = false;
            }
        }
    }
    

    // Free resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
