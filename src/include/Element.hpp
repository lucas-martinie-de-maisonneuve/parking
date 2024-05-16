#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <iostream>
using namespace std;

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

//***** RENDERER

SDL_Renderer *renderer;

//***** COLORS
const SDL_Color COLOR_BLACK = {0, 0, 0, 255};
const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
const SDL_Color COLOR_BLUE = {50, 100, 150, 255};

//***** IMAGES

// Game
SDL_Surface* surfaceBackground;

//***** TEXTURE

// Game
SDL_Texture* textureBackground;


//***** METHODES

void unloadImgGame() {
    SDL_DestroyTexture(textureBackground);

}


// Display background
void displayBackground(SDL_Renderer *renderer, SDL_Surface *&surface, SDL_Texture *surfaceTexture, const char *path)
{
    surface = IMG_Load(path);
    if (!surface)
    {
        cerr << "Failed to load image: " << surface << IMG_GetError() << endl;
    }
    surfaceTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!surfaceTexture)
    {
        cerr << "Failed to create texture for background " << surfaceTexture << SDL_GetError() << endl;
    }

    SDL_RenderCopy(renderer, surfaceTexture, nullptr, nullptr);
}


// Display Image
SDL_Texture* loadTexture(const std::string& imagePath, SDL_Renderer* renderer) {

    // Load image
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        cerr << "Failed to load image: " << imagePath << ". Error: " << IMG_GetError() << endl;
        return nullptr;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        cerr << "Failed to create texture from image: " << imagePath << ". Error: " << SDL_GetError() << endl;
        return nullptr;
    }

    return texture;
}

// Function to render an image
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int width, int height) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}




#endif

