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
    Menu(SDL_Renderer *renderer, int screenWidth, int screenHeight);
    ~Menu();

    void loadMenuItems();
    void unloadMenuItems();

    void runMenu();
    int mousePositionMenu();

    bool menuLoaded = false;

private:
    SDL_Renderer *renderer;

    // Font
    TTF_Font *font1;
    TTF_Font *font2;

    // Texture
    SDL_Texture *backgroundTexture;
    SDL_Texture *textTexture1;
    SDL_Texture *textTexture2;
    SDL_Texture *textTexture3;
    SDL_Texture *textTitle;

    // Rect
    SDL_Rect rectTextTitle;
    SDL_Rect textRect1;
    SDL_Rect textRect2;
    SDL_Rect textRect3;

    SDL_Rect menuItem1;
    SDL_Rect menuItem2;
    SDL_Rect menuItem3;

    // Event
    SDL_Event eventMenu;

    void loadTitle();
    void loadMenuOptions();
    void displayMenuOptions();
    void loadBackground();

    int screenWidth;
    int screenHeight;
};

#endif // Menu_HPP
