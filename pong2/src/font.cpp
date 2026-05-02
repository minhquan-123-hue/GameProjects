#include <font.h>
#include <iostream>

Font::Font():
menuTexture(nullptr),
winTexture(nullptr),
loseTexture(nullptr),
font(nullptr)
{}

Font::~Font()
{
    clean();
}

void Font::clean()
{
    if (menuTexture)
    {
        SDL_DestroyTexture(menuTexture);
    }

    if (winTexture)
    {
        SDL_DestroyTexture(winTexture);

    }

    if (loseTexture)
    {
        SDL_DestroyTexture(loseTexture);
    }

    if (font)
    {
        TTF_CloseFont(font);
    }

    TTF_Quit();

}

bool Font::initFontSys()
{
    int initResult = TTF_Init();

    if (initResult != 0)
    {
        std::cerr << "không khởi tạo được hệ thống xử lý font" << std::endl;
        return false;
    }

    font = TTF_OpenFont("../assets/font.ttf", 48);

    if (font == nullptr)
    {
        std::cerr << "font rỗng" << std::endl;
        return false;
    }

    return true;
}

void Font::create(SDL_Renderer *renderer)
{
    std::string menuText = "RETURN TO PLAY";
    menuTexture = createTextTexture(renderer, menuText, menuRect);
    menuRect.x = 20;
    menuRect.y = 20;

    std::string winText = "WIN - R TO PLAY AGAIN";
    winTexture = createTextTexture(renderer, winText, winRect);
    winRect.x = 20;
    winRect.y = 20;

    std::string loseText = "LOSE - R TO PLAY AGAIN";
    loseTexture = createTextTexture(renderer, loseText, loseRect);
    loseRect.x = 20;
    loseRect.y = 20;


}

SDL_Texture* Font::createTextTexture(
    SDL_Renderer *renderer,
    const std::string text,
    SDL_Rect &rect)
{
    SDL_Color color = {255,255,255,255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (surface == nullptr)
    {
        std::cerr << "không tạo được surface" << std::endl;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    rect.x = surface->w;
    rect.h = surface->h;

    SDL_FreeSurface(surface);

    return texture;
}

void Font::renderMenu(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, menuTexture, nullptr, &menuRect);
}

void Font::renderLose(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, loseTexture, nullptr, &loseRect);
}

void Font::renderWin(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, winTexture, nullptr, &winRect);
}