#ifndef OPTION_HPP
#define OPTION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;

class Option
{
public:
    Option(SDL_Renderer *_renderer, int screenWidth, int screenHeight);
    ~Option();
    void displayOption();
    int mousePositionOption();
    void loadOptionTextures();
    void unloadOptionTextures();
    bool optionLoaded = false;

private:
    void textRule();
    void renderTextRules();
    void keyboardDirection();
    void renderKeyboardDirections();
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
    SDL_Rect textRulesRect;
    SDL_Rect textArrowRect;

    // Texture
    SDL_Texture *backgroundTexture;
    SDL_Texture *buttonTexture;
    SDL_Texture *textTexture;

    // Textures and rects for rules
    std::vector<SDL_Texture*> lineTextures;
    std::vector<SDL_Rect> lineRects;

    // Textures and rects for keyboard directions
    std::vector<SDL_Texture*> arrowTextures;
    std::vector<SDL_Rect> arrowRects;
    std::vector<SDL_Texture*> lineArrowTextures;
    std::vector<SDL_Rect> lineArrowRects;
};

#endif
