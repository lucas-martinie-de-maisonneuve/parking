#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
public:
    Game(SDL_Renderer *_renderer, TTF_Font *_font, int screenWidth, int screenHeight);
    ~Game();
    void run();
    int handleButtonClick(int x, int y); 

private:
    SDL_Renderer *renderer;
    TTF_Font *font;
    int screenWidth;
    int screenHeight;

    SDL_Texture *backgroundTexture;
    SDL_Texture *buttonTexture;
    SDL_Rect buttonRect;

    void drawBackground();
    void drawTitle();
    void drawCheckerboard();
    void drawButton();
};

#endif
