// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
public:
    Game(SDL_Renderer *renderer, int screenWidth, int screenHeight);
    ~Game();
    void run();

private:
    SDL_Renderer *renderer;
    TTF_Font *font1;
     TTF_Font *font2;
    SDL_Texture *backgroundTexture;

    void drawBackground();
    void drawTitle();
    void drawCheckerboard();
    int screenWidth;
    int screenHeight;
};

#endif // GAME_HPP
