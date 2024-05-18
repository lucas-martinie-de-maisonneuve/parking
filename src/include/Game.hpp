#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
public:
    Game(SDL_Renderer *_renderer, int screenWidth, int screenHeight);
    ~Game();
    void displayGame();
    int eventHandlerGame();
    void loadGameTextures();
    void unloadGameTexture();
    bool gameLoaded = false;

private:
    SDL_Event eventGame;
    SDL_Renderer *renderer;
    TTF_Font *font;
    TTF_Font *font2;
    int screenWidth;
    int screenHeight;

    // Rect
    SDL_Rect buttonRect;
    SDL_Rect textRect;

    // Texture
    SDL_Texture *backgroundTexture;
    SDL_Texture *buttonTexture;
    SDL_Texture *textTexture;

    void drawCheckerboard();
};

#endif
