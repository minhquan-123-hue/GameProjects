#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class FontManager
{
public:
    FontManager();
    ~FontManager();

    // Initialize the TTF subsystem.
    bool init();

    // Load a font file at a given pixel size.
    bool loadFont(const std::string &path, int size);

    // Create an SDL_Texture from text using the loaded font.
    SDL_Texture *createTextTexture(SDL_Renderer *renderer, const std::string &text, SDL_Color color);

    // Free font and shutdown TTF.
    void clean();

private:
    TTF_Font *font;
};