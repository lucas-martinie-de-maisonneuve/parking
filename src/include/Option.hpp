#ifndef OPTION_HPP
#define OPTION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Option
{
public:
    Option(SDL_Renderer *_renderer, int screenWidth, int screenHeight);
    ~Option();
    void displayOption();
    int mousePositionOption(); 

private:
// event
SDL_Event eventOption;
    SDL_Renderer *renderer;
    TTF_Font *fontOption1;
    TTF_Font *fontOption2;
    int screenWidth;
    int screenHeight;

    // Rect 
    SDL_Rect buttonRect;
    SDL_Rect textRect;

    // Texture
    SDL_Texture *backgroundTexture;
    SDL_Texture *buttonTexture;
    SDL_Texture *textTexture;
};

#endif
