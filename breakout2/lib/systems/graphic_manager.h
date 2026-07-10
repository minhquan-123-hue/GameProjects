#pragma once

#include <SDL2/SDL.h>
#include <string>

class GraphicManager
{
public:
    GraphicManager();
    ~GraphicManager();

    // Initialize SDL_image for PNG support.
    bool init();

    // Load a background image from a file and create a texture.
    bool loadBackground(SDL_Renderer *renderer, const std::string &path);

    // Return the loaded background texture (may be nullptr).
    SDL_Texture *getBackground() const;

    // Free resources and shutdown IMG.
    void clean();

private:
    SDL_Texture *background;
};