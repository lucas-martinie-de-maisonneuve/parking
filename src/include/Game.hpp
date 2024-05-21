#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Boat.hpp"

class Game
{
public:
    Game(SDL_Renderer *_renderer, int screenWidth, int screenHeight);
    ~Game();
    void displayGame();
    int eventHandlerGame();
    void loadGameTextures();
    void unloadGameTexture();
    void displayBoat();
    void drawBoat(char id, int x, int y, int length, bool horizontal);
    Boat myBoat;
    int checkAvailableTiles(BoatA::BoatInfo *boat, char direction);
    void renderText(int x, int y);
    bool gameLoaded = false;
    int x, y;
    std::vector<std::pair<int, int>> availableTiles;
    BoatA::BoatInfo *selectedBoat;

    // click Here
    void displayClickHere();
    bool showClickHere;
    void handleClickHere(int mouseX, int mouseY);


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
    SDL_Rect rectBoat0;
    SDL_Rect textClickRect;
    SDL_Rect winRect;

    // Texture
    SDL_Texture *backgroundTexture;
    SDL_Texture *buttonTexture;
    SDL_Texture *textTexture;
    SDL_Texture *textureBoat0;
    SDL_Texture *boat_Vertical_Texture;
    SDL_Texture *boat_Horizontal_Texture;
    SDL_Texture *textureClick;
    SDL_Texture *winTexture;

    void drawCheckerboard();
    const int ROWS = 8, COLS = 8;
    int squareSize = 50;

    const int padding = 1;

    const int offsetX = (screenWidth - COLS * squareSize) / 2;
    const int offsetY = (screenHeight - ROWS * squareSize) / 2;

    BoatA::BoatInfo *getSelectedBoat(int mouseX, int mouseY);

};

#endif // GAME_HPP
