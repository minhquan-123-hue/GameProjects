#include "../../lib/systems/graphic_manager.h"

#include <iostream>

GraphicManager::GraphicManager()
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
        std::cerr << "IMG_Init failed: "
                  << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

bool GraphicManager::loadIMG(SDL_Renderer* renderer,
                             const std::string& name,
                             const std::string& path)
{
    if (renderer == nullptr)
    {
        return false;
    }

    SDL_Surface* surf = IMG_Load(path.c_str());

    if (surf == nullptr)
    {
        std::cerr << "IMG_Load failed for '"
                  << path
                  << "': "
                  << IMG_GetError()
                  << std::endl;

        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);

    if (texture == nullptr)
    {
        std::cerr << "SDL_CreateTextureFromSurface failed: "
                  << SDL_GetError()
                  << std::endl;

        return false;
    }

    textures[name] = texture;

    return true;
}

SDL_Texture* GraphicManager::getTexture(const std::string& name) const
{
    auto it = textures.find(name);

    if (it != textures.end())
    {
        return it->second;
    }

    return nullptr;
}

void GraphicManager::clean()
{
    for (auto& pair : textures)
    {
        SDL_DestroyTexture(pair.second);
    }

    textures.clear();

    IMG_Quit();
}