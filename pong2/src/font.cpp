#include <font.h>
#include <iostream>

Font::Font():
menuTexture(nullptr),
win1Texture(nullptr),
win2Texture(nullptr),
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

    if (win1Texture)
    {
        SDL_DestroyTexture(win1Texture);

    }

    if (win2Texture)
    {
        SDL_DestroyTexture(win2Texture);
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
    win1Texture = createTextTexture(renderer, winText, win1Rect);
    win1Rect.x = 20;
    win1Rect.y = 20;

    std::string loseText = "LOSE - R TO PLAY AGAIN";
    win2Texture = createTextTexture(renderer, loseText, win2Rect);
    win2Rect.x = 20;
    win2Rect.y = 20;


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

    rect.w = surface->w;
    rect.h = surface->h;

    SDL_FreeSurface(surface);

    return texture;
}

void Font::renderMenu(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, menuTexture, nullptr, &menuRect);
}

void Font::render1Win(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, win2Texture, nullptr, &win2Rect);
}

void Font::render2Win(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, win1Texture, nullptr, &win1Rect);
}