// lấy các phần khai báo 
#include "../../lib/systems/font_manager.h"

#include <iostream>


FontManager::FontManager()
    : font(nullptr)
{
}

FontManager::~FontManager()
{
    clean();
}

// khởi tạo hệ thống xử lý phông chữ
bool FontManager::init()
{
    if (TTF_WasInit() == 0)
    {
        if (TTF_Init() != 0)
        {
            std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
            return false;
        }
    }
    return true;
}

// tải phông chữ: cách vẽ chữ vào một biến con trỏ 
// sau đó dùng cách vẽ này đẻ vẽ cho từng chữ 
bool FontManager::loadFont(const std::string &path, int size)
{
    font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        std::cerr << "Failed to load font '" << path << "': " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

// copy dữ liệu của các điểm ảnh của hình vẽ vào trong vram
SDL_Texture *FontManager::createTextTexture(SDL_Renderer *renderer, const std::string &text, SDL_Color color)
{
    if (font == nullptr || renderer == nullptr)
        return nullptr;

    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (surf == nullptr)
    {
        std::cerr << "TTF_RenderUTF8_Blended failed: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    if (tex == nullptr)
    {
        std::cerr << "CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
    }

    return tex;
}

void FontManager::clean()
{
    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (TTF_WasInit())
    {
        TTF_Quit();
    }
}
