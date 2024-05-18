#include <iostream>
#include <vector>
using namespace std;

// Load files
#include "Option.hpp"

Option::Option(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      fontOption1(nullptr), fontOption2(nullptr), textTexture(nullptr)
{
    fontOption1 = TTF_OpenFont("assets/fonts/Oswald-Medium.ttf", 18);
    if (!fontOption1)
    {
        cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    fontOption2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!fontOption2)
    {
        cerr << "Failed to load font2: " << TTF_GetError() << endl;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(fontOption2, "Rules", {255, 255, 255, 255});
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
    TTF_SizeText(fontOption2, "Rules", &textWidth, &textHeight);
    textRect = {screenWidth / 2 - textWidth / 2, 40, textWidth, textHeight};

    // Load background image
    SDL_Surface *backgroundSurface = IMG_Load("assets/img/backgroundOption.png");
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

    // Load button image
    SDL_Surface *buttonSurface = IMG_Load("assets/img/buttonmenu.png");
    if (!buttonSurface)
    {
        cerr << "Failed to load button image: " << IMG_GetError() << std::endl;
    }

    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    if (!buttonTexture)
    {
        cerr << "Failed to create button texture: " << SDL_GetError() << endl;
    }

    buttonRect = {screenWidth - 60, 25, 60, 20};


}

Option::~Option()
{
    // Font
    TTF_CloseFont(fontOption1);
    TTF_CloseFont(fontOption2);   

    // Texture
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(lineTexture);
    SDL_DestroyTexture(textureArrow);
  
    TTF_Quit();
    IMG_Quit();
}

void Option::displayOption()
{
    // Background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);   
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);

    textRule();
    keyboardDirection();
}


void Option:: textRule() {

    // Transparent rect
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 120); 
    SDL_RenderFillRect(renderer, &textRulesRect);

    textRulesRect = {screenWidth / 2 - 200, 150, 400, 200};

    vector<string> lines = {
        "Slide the blocking boats in their lanes, until the",
        "path is clear for your boat to escape. Boats can only",
        "slide forward & backward, not sideways. May your",
        "parking skills be sharp and your maneuvers " , 
        "smooth as you navigate the waters !"
          
    };

    int xOffset = textRulesRect.x + 25;    
    int yOffset = textRulesRect.y + 20;
    for (const auto &line : lines)
    {
        SDL_Surface *lineSurface = TTF_RenderText_Solid(fontOption1, line.c_str(), {255, 255, 255, 255});
        lineTexture = SDL_CreateTextureFromSurface(renderer, lineSurface);
        int lineWidth, lineHeight;
        TTF_SizeText(fontOption1, line.c_str(), &lineWidth, &lineHeight);
        lineRect ={xOffset, yOffset, lineWidth, lineHeight};
        SDL_RenderCopy(renderer, lineTexture, nullptr, &lineRect);
        SDL_FreeSurface(lineSurface);
        yOffset += lineHeight + 5;
    }
}


void Option:: keyboardDirection(){

        // Transparent rect
    SDL_Rect transparentRectArrow = {100, 370, 400, 250};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 120); 
    SDL_RenderFillRect(renderer, &transparentRectArrow); 


    vector<string> imagePaths = {"assets/img/ArrowU.png", "assets/img/ArrowD.png", "assets/img/ArrowL.png", "assets/img/ArrowR.png"};

    int xPos = 125;
     
    for (const auto& imagePath : imagePaths) {
        
        // Load image
        SDL_Surface* surfaceArrow = IMG_Load(imagePath.c_str());
        if (!surfaceArrow) {
            cerr << "Failed to load image: " << imagePath << ". Error: " << IMG_GetError() << endl;
        }

//    Texture
        textureArrow = SDL_CreateTextureFromSurface(renderer, surfaceArrow);
        SDL_FreeSurface(surfaceArrow);
        if (!textureArrow) {
            cerr << "Failed to create texture from image: " << imagePath << ". Error: " << SDL_GetError() << endl;
        }

        // Position + size image
        rectArrow = {xPos, 530, 50, 50};
        SDL_RenderCopy(renderer, textureArrow, nullptr, &rectArrow);

        // Increment x position for next image
        xPos += 100;
    }


}




int Option::mousePositionOption()
{
    // Handle events
    while (SDL_PollEvent(&eventOption))
    {
        if (eventOption.type == SDL_QUIT)
        {
            return -1;
        }

        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
            y >= buttonRect.y && y <= buttonRect.y + buttonRect.h)
        {
            buttonRect = {screenWidth - 64, 24, 62, 22}; // Hover effect
            if (eventOption.type == SDL_MOUSEBUTTONDOWN && eventOption.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "Button clicked Option" << std::endl;
                return 10; 
            }
        }
        else
        {
            buttonRect = {screenWidth - 60, 25, 60, 20}; // Normal state
        }
    }
    return 20;
}
