#include "../../lib/systems/graphic_manager.h"

#include <SDL2/SDL_image.h>
#include <iostream>

GraphicManager::GraphicManager()
    : background(nullptr)
{
}

GraphicManager::~GraphicManager()
{
    clean();
}

bool GraphicManager::init()
{
    int flags = IMG_INIT_PNG;
    if ((IMG_Init(flags) & flags) != flags)
    {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

bool GraphicManager::loadBackground(SDL_Renderer *renderer, const std::string &path)
{
    if (renderer == nullptr)
        return false;

    SDL_Surface *surf = IMG_Load(path.c_str());
    if (surf == nullptr)
    {
        std::cerr << "IMG_Load failed for '" << path << "': " << IMG_GetError() << std::endl;
        return false;
    }

    background = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    if (background == nullptr)
    {
        std::cerr << "CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// gọi hàm constant để nhận lại dữ liệu để đọc
// chứ không thể truy cập trực tiếp như là một biến thành viên
SDL_Texture *GraphicManager::getBackground() const
{
    return background;
}

void GraphicManager::clean()
{
    if (background != nullptr)
    {
        SDL_DestroyTexture(background);
        background = nullptr;
    }

    IMG_Quit();
}
