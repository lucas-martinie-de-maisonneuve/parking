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
    void runGame();
    void loadMenuItems();

private:
    SDL_Renderer *renderer;

    // Font
    TTF_Font *font1;
    TTF_Font *font2;

    // Texture
    SDL_Texture *backgroundTexture;
    SDL_Texture *textTitleGame;

    // Rect
    SDL_Rect textRect;

    void loadTitleGame();
    void drawBackground();
    void drawCheckerboard();
    int screenWidth;
    int screenHeight;

};

#endif // GAME_HPP
