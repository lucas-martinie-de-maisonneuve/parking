// Game.cpp

using namespace std;

#include "Game.hpp"


Game::Game(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), font1(nullptr), font2(nullptr), screenWidth(screenWidth), screenHeight(screenHeight)
{

    // Load font
    font1 = TTF_OpenFont("assets/fonts/Coffee.ttf", 24);
    if (!font1)
    {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }

    font2 = TTF_OpenFont("assets/fonts/Oswald-Medium.ttf", 50);
       if (!font2)
    {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }

    SDL_Surface *backgroundSurface = IMG_Load("assets/img/backgroundGame.jpeg");
    if (!backgroundSurface)
    {
        cerr << "Failed to load background image: " << IMG_GetError() << endl;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture)
    {
        cerr << "Failed to create background texture: " << SDL_GetError() << endl;
    }
}

Game::~Game()
{
    // Font
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);   

    // Texture
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(textTitleGame);
 
}

void Game::runGame()
{
    // Background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    
    // Title
    SDL_RenderCopy(renderer, textTitleGame, nullptr, &textRect);

    // Functions Game
    loadTitleGame();
    drawCheckerboard();
}


void Game:: loadMenuItems(){
    loadTitleGame();
}

void Game::loadTitleGame()
{
    SDL_Surface *surfaceTitleGame = TTF_RenderText_Solid(font2, "Jeu du parking", {255, 225, 255, 255});
    if (!surfaceTitleGame )
    {
        cerr << "Failed to render text G: " << TTF_GetError() << endl;
    }

    textTitleGame = SDL_CreateTextureFromSurface(renderer, surfaceTitleGame );
    SDL_FreeSurface(surfaceTitleGame);
    if (!textTitleGame)
    {
        cerr << "Failed to create text texture: " << SDL_GetError() << endl;
    }

    int textWidth, textHeight;
    TTF_SizeText(font2, "Jeu du parking", &textWidth, &textHeight);
    textRect = {screenWidth / 2 - textWidth / 2, 20, textWidth, textHeight}; 
}

void Game::drawCheckerboard()
{
    const int ROWS = 8, COLS = 8;
    int squareSize = 70;

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            SDL_Rect rect = {j * squareSize + (1000 - COLS * squareSize) / 2 + j,
                             i * squareSize + (750 - ROWS * squareSize) / 2 + i,
                             squareSize,
                             squareSize};

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
