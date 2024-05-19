#include "Option.hpp"

Option::Option(SDL_Renderer *_renderer, int screenWidth, int screenHeight)
    : renderer(_renderer), screenWidth(screenWidth), screenHeight(screenHeight),
      fontOption1(nullptr), fontOption2(nullptr), textTexture(nullptr)
{
    fontOption1 = TTF_OpenFont("assets/fonts/Oswald-Medium.ttf", 18);
    if (!fontOption1)
    {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
    }

    fontOption2 = TTF_OpenFont("assets/fonts/Coffee.ttf", 50);
    if (!fontOption2)
    {
        cerr << "Failed to load font2: " << TTF_GetError() << endl;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

Option::~Option()
{
    // Font
    TTF_CloseFont(fontOption1);
    TTF_CloseFont(fontOption2);

    // Texture
    unloadOptionTextures();

    TTF_Quit();
    IMG_Quit();
}

void Option::displayOption()
{
    // Background
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);

    renderTextRules();
    renderKeyboardDirections();
}

void Option::loadOptionTextures()
{

    SDL_Surface *textSurface = TTF_RenderText_Blended(fontOption2, "Rules", {255, 255, 255, 255});
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
        cerr << "Failed to load button image: " << IMG_GetError() << endl;
    }

    buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);
    if (!buttonTexture)
    {
        cerr << "Failed to create button texture: " << SDL_GetError() << endl;
    }

    buttonRect = {screenWidth - 60, 25, 60, 20};
    textRule();
    keyboardDirection();
}

void Option::unloadOptionTextures()
{

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(textTexture);

    for (auto texture : lineTextures)
    {
        SDL_DestroyTexture(texture);
    }
    for (auto texture : arrowTextures)
    {
        SDL_DestroyTexture(texture);
    }
    for (auto texture : lineArrowTextures)
    {
        SDL_DestroyTexture(texture);
    }

    // Clear the texture vectors
    lineTextures.clear();
    arrowTextures.clear();
    lineArrowTextures.clear();

    // Clear the rect vectors
    lineRects.clear();
    arrowRects.clear();
    lineArrowRects.clear();
}

void Option::textRule()
{
    textRulesRect = {screenWidth / 2 - 200, 150, 400, 200};

    vector<string> lines = {
        "Slide the blocking boats in their lanes, until the",
        "path is clear for your boat to escape. Boats can only",
        "slide forward & backward, not sideways. May your",
        "parking skills be sharp and your maneuvers ",
        "smooth as you navigate the waters !"};

    int xOffset = textRulesRect.x + 25;
    int yOffset = textRulesRect.y + 20;
    for (const auto &line : lines)
    {
        SDL_Surface *lineSurface = TTF_RenderText_Blended(fontOption1, line.c_str(), {255, 255, 255, 255});
        SDL_Texture *lineTexture = SDL_CreateTextureFromSurface(renderer, lineSurface);
        int lineWidth, lineHeight;
        TTF_SizeText(fontOption1, line.c_str(), &lineWidth, &lineHeight);
        SDL_Rect lineRect = {xOffset, yOffset, lineWidth, lineHeight};

        lineTextures.push_back(lineTexture);
        lineRects.push_back(lineRect);

        SDL_FreeSurface(lineSurface);
        yOffset += lineHeight + 5;
    }
}

void Option::renderTextRules()
{
    // Transparent rect
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 120);
    SDL_RenderFillRect(renderer, &textRulesRect);

    for (size_t i = 0; i < lineTextures.size(); ++i)
    {
        SDL_RenderCopy(renderer, lineTextures[i], nullptr, &lineRects[i]);
    }
}

void Option::keyboardDirection()
{
    // Text Arrow
    textArrowRect = {100, 380, 400, 250};

    vector<string> linesArrow = {
        "move Up",
        "move Down",
        "move Left",
        "move Right"};

    int xOffset = textArrowRect.x + 130;
    int yOffset = textArrowRect.y + 12;
    for (const auto &line : linesArrow)
    {
        SDL_Surface *lineArrowSurface = TTF_RenderText_Blended(fontOption1, line.c_str(), {255, 255, 255, 255});
        SDL_Texture *lineArrowTexture = SDL_CreateTextureFromSurface(renderer, lineArrowSurface);
        int lineWidth, lineHeight;
        TTF_SizeText(fontOption1, line.c_str(), &lineWidth, &lineHeight);
        SDL_Rect lineArrowRect = {xOffset, yOffset, lineWidth, lineHeight};

        lineArrowTextures.push_back(lineArrowTexture);
        lineArrowRects.push_back(lineArrowRect);

        SDL_FreeSurface(lineArrowSurface);
        yOffset += lineHeight + 36;
    }

    // Arrow image
    vector<string> imagePaths = {"assets/img/ArrowU.png", "assets/img/ArrowD.png", "assets/img/ArrowL.png", "assets/img/ArrowR.png"};

    xOffset = 385;

    for (const auto &imagePath : imagePaths)
    {
        // Load image
        SDL_Surface *surfaceArrow = IMG_Load(imagePath.c_str());
        if (!surfaceArrow)
        {
            cerr << "Failed to load image: " << imagePath << ". Error: " << IMG_GetError() << endl;
        }

        // Texture
        SDL_Texture *textureArrow = SDL_CreateTextureFromSurface(renderer, surfaceArrow);
        SDL_FreeSurface(surfaceArrow);
        if (!textureArrow)
        {
            cerr << "Failed to create texture from image: " << imagePath << ". Error: " << SDL_GetError() << endl;
        }

        // Position + size image
        SDL_Rect rectArrow = {155, xOffset, 40, 40};

        arrowTextures.push_back(textureArrow);
        arrowRects.push_back(rectArrow);

        // Increment x position for next image
        xOffset += 60;
    }
}

void Option::renderKeyboardDirections()
{
    // Transparent rect
    SDL_Rect transparentRectArrow = {100, 370, 400, 250};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 120);
    SDL_RenderFillRect(renderer, &transparentRectArrow);

    for (size_t i = 0; i < arrowTextures.size(); ++i)
    {
        SDL_RenderCopy(renderer, arrowTextures[i], nullptr, &arrowRects[i]);
    }
    for (size_t i = 0; i < lineArrowTextures.size(); ++i)
    {
        SDL_RenderCopy(renderer, lineArrowTextures[i], nullptr, &lineArrowRects[i]);
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
