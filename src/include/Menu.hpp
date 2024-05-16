// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Menu
{
public:
    Menu(SDL_Renderer *renderer,  int screenWidth, int screenHeight);
    ~Menu();
    void run();

private:
    SDL_Renderer *renderer;
    TTF_Font *font;
    TTF_Font *font2;
    SDL_Texture *backgroundTexture;

    void drawBackground();
    void drawTitle();
    void drawCheckerboard();
    int screenWidth;
    int screenHeight;
};

#endif // Menu_HPP
