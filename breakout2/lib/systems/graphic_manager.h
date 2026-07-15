#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <map>
#include <string>

class GraphicManager
{
public:
    GraphicManager();
    ~GraphicManager();

    bool init();

    bool loadIMG(SDL_Renderer* renderer,
                 const std::string& name,
                 const std::string& path);

    SDL_Texture* getTexture(const std::string& name) const;

    void clean();

private:
    std::map<std::string, SDL_Texture*> textures;
};