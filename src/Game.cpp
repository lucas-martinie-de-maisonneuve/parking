#include <iostream>
#include "Boat.hpp"
#include "Game.hpp"
using namespace std;

Game::Game(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      font(nullptr), font2(nullptr), textTexture(nullptr), showClickHere(false)
{

    font = TTF_OpenFont("assets/fonts/Oswald-Medium.ttf", 10);
    if (!font)
    {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }

    font2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!font2)
    {
        cerr << "Failed to load font2: " << TTF_GetError() << endl;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

Game::~Game()
{
    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    unloadGameTexture();

    TTF_Quit();
    IMG_Quit();
}

void Game::displayGame()
{
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
    SDL_RenderCopy(renderer, textureFinishLine, nullptr, &rectFinishLine);

    drawCheckerboard();
    if (showClickHere && !myBoat.gameOver)
    {
        displayClickHere();
    }

    if (myBoat.gameOver)
        SDL_RenderCopy(renderer, winTexture, nullptr, &winRect);

    displayBoat();
}

void Game::loadGameTextures()
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(font2, "Parking Boat", {255, 255, 255, 255});
    if (!textSurface)
    {
        cerr << "Failed to render text: " << TTF_GetError() << endl;
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture)
    {
        cerr << "Failed to create text texture: " << SDL_GetError() << endl;
    }

    int textWidth, textHeight;
    TTF_SizeText(font2, "Parking Boat", &textWidth, &textHeight);
    textRect = {screenWidth / 2 - textWidth / 2, 40, textWidth, textHeight};

    SDL_Surface *backgroundSurface = IMG_Load("assets/img/BackgrounGame.png");
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

    SDL_Surface *buttonSurface = IMG_Load("assets/img/buttonmenu.png");
    if (!buttonSurface)
    {
        cerr << "Failed to load button image: " << IMG_GetError() << endl;
    }

    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    if (!buttonTexture)
    {
        cerr << "Failed to create button texture: " << SDL_GetError() << endl;
    }

    buttonRect = {screenWidth - 70, 25, 60, 20};

    SDL_SetTextureBlendMode(boatVerticalTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(boatHorizontalTexture, SDL_BLENDMODE_BLEND);

    // Load boat textures
    SDL_Surface *boat_Vertical_Surface = IMG_Load("assets/img/boat_v.png");
    if (!boat_Vertical_Surface)
    {
        cerr << "Failed to load small boat image: " << IMG_GetError() << endl;
    }
    boatVerticalTexture = SDL_CreateTextureFromSurface(renderer, boat_Vertical_Surface);
    SDL_FreeSurface(boat_Vertical_Surface);
    if (!boatVerticalTexture)
    {
        cerr << "Failed to create small boat texture: " << SDL_GetError() << endl;
    }

    // Load horizontal boat
    SDL_Surface *boat_Horizontal_Surface = IMG_Load("assets/img/boat_h.png");
    if (!boat_Horizontal_Surface)
    {
        cerr << "Failed to load large boat image: " << IMG_GetError() << endl;
    }
    boatHorizontalTexture = SDL_CreateTextureFromSurface(renderer, boat_Horizontal_Surface);
    SDL_FreeSurface(boat_Horizontal_Surface);
    if (!boatHorizontalTexture)
    {
        cerr << "Failed to create large boat texture: " << SDL_GetError() << endl;
    }

    buttonRect = {screenWidth - 80, 25, 60, 20};

    // Load Win image
    SDL_Surface *winSurface = IMG_Load("assets/img/Win_message.png");
    if (!winSurface)
    {
        cerr << "Failed to load win image: " << IMG_GetError() << endl;
    }

    winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
    SDL_FreeSurface(winSurface);
    if (!winTexture)
    {
        cerr << "Failed to create  win texture: " << SDL_GetError() << endl;
    }

    winRect = {screenWidth / 2 - 182, screenHeight - 120, 364, 54};

    // Texture Click Here
    SDL_Surface *surfaceClick = TTF_RenderText_Blended(font, "Click here", {0, 0, 0, 255}); // Rouge pour le texte
    if (!surfaceClick)
    {
        cerr << "Failed to render text: " << TTF_GetError() << endl;
        return;
    }
    textureClick = SDL_CreateTextureFromSurface(renderer, surfaceClick);
    SDL_FreeSurface(surfaceClick);
    if (!textureClick)
    {
        cerr << "Failed to create text texture: " << SDL_GetError() << endl;
        return;
    }

    // Load finish line

    SDL_Surface *surfaceFinishLine = IMG_Load("assets/img/finishLine.png");
    if (!surfaceFinishLine)
    {
        cerr << "Failed to load image: " << surfaceFinishLine << ". Error: " << IMG_GetError() << endl;
    }

    // Create texture from surface
    textureFinishLine = SDL_CreateTextureFromSurface(renderer, surfaceFinishLine);
    SDL_FreeSurface(surfaceFinishLine);
    if (!textureFinishLine)
    {
        cerr << "Failed to create texture from image: " << textureFinishLine << ". Error: " << SDL_GetError() << endl;
    }
    rectFinishLine = {505, 300, 40, 100};
}

void Game::drawBoat(char id, int x, int y, int length, bool horizontal)
{
    SDL_Color color;
    switch (id)
    {
    case '1':
        color = {220, 50, 50, 200}; // Red
        break;
    case '2':
        color = {0, 255, 0, 200}; // Green
        break;
    case '3':
        color = {0, 0, 255, 200}; // Blue
        break;
    case '4':
        color = {255, 255, 0, 200}; // Yellow
        break;
    case '5':
        color = {255, 165, 0, 200}; // Orange
        break;
    case '6':
        color = {128, 50, 100, 200}; // Purple
        break;
    case '7':
        color = {0, 255, 255, 200}; // Cyan
        break;
    case '8':
        color = {255, 0, 255, 200}; // Magenta
        break;
    case '9':
        color = {255, 70, 0, 200};
        break;
    case 'a':
        color = {255, 192, 203, 200}; // Pink
        break;
    case 'b':
        color = {165, 42, 42, 200}; // Brown
        break;
    case 'c':
        color = {0, 127, 255, 200}; // Brown
        break;
    default:
        color = {255, 255, 255, 255}; // White
        break;
    }

    SDL_Texture *texture = horizontal ? boatHorizontalTexture : boatVerticalTexture;

    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(texture, color.a);

    SDL_Rect rect;
    if (horizontal)
    {
        rect = {x + padding, y, squareSize * length, squareSize};
    }
    else
    {
        rect = {x, y + padding, squareSize, squareSize * length};
    }

    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_SetTextureAlphaMod(texture, 255);
}

void Game::unloadGameTexture()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(textureBoat0);
    SDL_DestroyTexture(boatVerticalTexture);
    SDL_DestroyTexture(boatHorizontalTexture);
    SDL_DestroyTexture(textureClick);
    SDL_DestroyTexture(winTexture);
    SDL_DestroyTexture(textureFinishLine);
}

void Game::drawCheckerboard()
{

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            SDL_Rect rect = {j * squareSize + (screenWidth - COLS * squareSize) / 2 + j,
                             i * squareSize + (screenHeight - ROWS * squareSize) / 2 + i,
                             squareSize,
                             squareSize};
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Game::displayBoat()
{
    for (const auto &boat : myBoat.boats)
    {
        drawBoat(boat.id, offsetX + boat.x * (squareSize + padding), offsetY + boat.y * (squareSize + padding), boat.length, boat.horizontal);
        if (boat.id == 's' && boat.x == 6)
        {
            myBoat.gameOver = true;
            myBoat.gameAnimation = true;
        }
        if (myBoat.gameAnimation)
        {
            SDL_Delay(150);
            myBoat.moveRight('s');
            SDL_Delay(150);
            myBoat.moveRight('s');
            myBoat.gameAnimation = false;
            break;
        }
    }
}

BoatA::BoatInfo *Game::getSelectedBoat(int mouseX, int mouseY)
{
    int gridX = (mouseX - offsetX) / (squareSize + padding);
    int gridY = (mouseY - offsetY) / (squareSize + padding);

    if (gridX >= 0 && gridX < COLS && gridY >= 0 && gridY < ROWS)
    {
        return myBoat.getBoatAtPosition(gridX, gridY);
    }
    return nullptr;
}

int Game::checkAvailableTiles(BoatA::BoatInfo *boat, char direction)
{
    int availableTiles = 0;

    auto isOccupied = [&](int row, int col) -> bool
    {
        for (const auto &otherBoat : myBoat.boats)
        {
            if (otherBoat.horizontal)
            {
                if (row == otherBoat.y && col >= otherBoat.x && col < otherBoat.x + otherBoat.length)
                {
                    return true;
                }
            }
            else
            {
                if (col == otherBoat.x && row >= otherBoat.y && row < otherBoat.y + otherBoat.length)
                {
                    return true;
                }
            }
        }
        return false;
    };

    if (boat->horizontal)
    {
        if (direction == 'L')
        {
            // Check tiles to the left of the boat
            for (int col = boat->x - 1; col >= 0; --col)
            {
                if (!isOccupied(boat->y, col))
                {
                    ++availableTiles;
                }
                else
                {
                    break;
                }
            }
        }
        else if (direction == 'R')
        {
            // Check tiles to the right of the boat
            for (int col = boat->x + boat->length; col < COLS; ++col)
            {
                if (!isOccupied(boat->y, col))
                {
                    ++availableTiles;
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        if (direction == 'U')
        {
            // Check tiles above the boat
            for (int row = boat->y - 1; row >= 0; --row)
            {
                if (!isOccupied(row, boat->x))
                {
                    ++availableTiles;
                }
                else
                {
                    break;
                }
            }
        }
        else if (direction == 'D')
        {
            // Check tiles below the boat
            for (int row = boat->y + boat->length; row < ROWS; ++row)
            {
                if (!isOccupied(row, boat->x))
                {
                    ++availableTiles;
                }
                else
                {
                    break;
                }
            }
        }
    }
    return availableTiles;
}

void Game::displayClickHere()
{
    for (const auto &tile : availableTiles)
    {
        int tileX = offsetX + tile.first * (squareSize + padding) + 5;
        int tileY = offsetY + tile.second * (squareSize + padding) + 20;

        renderText(tileX, tileY);
        SDL_RenderCopy(renderer, textureClick, nullptr, &textClickRect);
    }
}

void Game::renderText(int x, int y)
{
    int textWidth, textHeight;
    TTF_SizeText(font, "Click here", &textWidth, &textHeight);
    textClickRect = {x, y, textWidth, textHeight};
}

int Game::eventHandlerGame()
{
    while (SDL_PollEvent(&eventGame))
    {
        if (eventGame.type == SDL_QUIT)
        {
            return -1;
        }
        SDL_GetMouseState(&x, &y);

        if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
            y >= buttonRect.y && y <= buttonRect.y + buttonRect.h)
        {
            buttonRect = {screenWidth - 84, 24, 62, 22};
            if (eventGame.type == SDL_MOUSEBUTTONDOWN && eventGame.button.button == SDL_BUTTON_LEFT)
            {
                return 10;
            }
        }
        else
        {
            buttonRect = {screenWidth - 80, 25, 60, 20};
        }

        if (eventGame.type == SDL_MOUSEBUTTONDOWN && eventGame.button.button == SDL_BUTTON_LEFT && !myBoat.gameOver)
        {
            // Handle "Click here" clicks
            if (showClickHere)
            {
                handleClickHere(x, y);
            }

            // Handle boat selection

            selectedBoat = getSelectedBoat(x, y);
            availableTiles.clear();
            if (selectedBoat)
            {
                showClickHere = true;

                if (selectedBoat->horizontal)
                {
                    int availableLeft = checkAvailableTiles(selectedBoat, 'L');
                    int availableRight = checkAvailableTiles(selectedBoat, 'R');

                    for (int i = 1; i <= availableLeft; ++i)
                    {
                        availableTiles.push_back({selectedBoat->x - i, selectedBoat->y});
                    }
                    for (int i = 1; i <= availableRight; ++i)
                    {
                        availableTiles.push_back({selectedBoat->x + selectedBoat->length - 1 + i, selectedBoat->y});
                    }
                }
                else
                {
                    int availableUp = checkAvailableTiles(selectedBoat, 'U');
                    int availableDown = checkAvailableTiles(selectedBoat, 'D');
                    for (int i = 1; i <= availableUp; ++i)
                    {
                        availableTiles.push_back({selectedBoat->x, selectedBoat->y - i});
                    }
                    for (int i = 1; i <= availableDown; ++i)
                    {
                        availableTiles.push_back({selectedBoat->x, selectedBoat->y + selectedBoat->length - 1 + i});
                    }
                }
            }
            else
            {
                showClickHere = false;
            }
        }
    }

    return 0;
}

void Game::handleClickHere(int mouseX, int mouseY)
{
    int gridX = (mouseX - offsetX) / (squareSize + padding);
    int gridY = (mouseY - offsetY) / (squareSize + padding);

    for (const auto &tile : availableTiles)
    {
        if (tile.first == gridX && tile.second == gridY)
        {
            if (selectedBoat)
            {
                int boatX = selectedBoat->x;
                int boatY = selectedBoat->y;

                if (selectedBoat->horizontal)
                {
                    if (gridX < boatX)
                    {
                        while (boatX > gridX && boatX - 1 >= 0)
                        {
                            myBoat.moveLeft(selectedBoat->id);
                            boatX--;
                        }
                    }
                    else
                    {
                        while (boatX < gridX && boatX + 1 < 7)
                        {
                            myBoat.moveRight(selectedBoat->id);
                            boatX++;
                        }
                    }
                }
                else
                {
                    if (gridY < boatY)
                    {
                        while (boatY > gridY && boatY - 1 >= 0)
                        {
                            myBoat.moveUp(selectedBoat->id);
                            boatY--;
                        }
                    }
                    else
                    {
                        while (boatY < gridY && boatY + 1 < 7)
                        {
                            myBoat.moveDown(selectedBoat->id);
                            boatY++;
                        }
                    }
                }
                availableTiles.clear();
                selectedBoat = nullptr;
                showClickHere = false;
            }
            break;
        }
    }
}

void Game::resetGame()
{
    myBoat.boats = {
        {'1', 0, 0, 2, true},
        {'2', 2, 3, 3, false},
        {'3', 4, 4, 2, true},
        {'4', 6, 2, 3, false},
        {'5', 3, 5, 2, false},
        {'6', 7, 4, 3, false},
        {'s', 0, 3, 2, true}, // Special boat
        {'7', 4, 1, 3, false},
        {'8', 5, 0, 3, true},
        {'9', 4, 6, 3, true},
        {'a', 0, 6, 2, false},
        {'b', 3, 1, 3, false},
        {'c', 5, 1, 3, true}};

    myBoat.gameOver = false;
    showClickHere = false;
}
