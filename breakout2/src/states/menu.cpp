#include "../../lib/states/menu.h"

#include <SDL2/SDL.h>
#include <iostream>

Menu::Menu()
    : selectedIndex(0), result(-1), renderer(nullptr), fontMgr(nullptr), gfxMgr(nullptr),
      playNormal(nullptr), playSelected(nullptr), highNormal(nullptr), highSelected(nullptr)
{
}

Menu::~Menu()
{
    onExit();
}

void Menu::setRenderer(SDL_Renderer *r)
{
    renderer = r;
}

void Menu::setManagers(FontManager *fm, GraphicManager *gm)
{
    fontMgr = fm;
    gfxMgr = gm;
}

// helper func
SDL_Texture *Menu::createText(const std::string &text, SDL_Color color)
{
    if (!renderer || !fontMgr)
    {
        std::cerr << "Menu: renderer or fontMgr not set." << std::endl;
        return nullptr;
    }

    return fontMgr->createTextTexture(renderer, text, color);
}

void Menu::onEnter()
{
    if (!renderer || !fontMgr)
    {
        std::cerr << "Menu: renderer or fontMgr not set." << std::endl;
        return;
    }

    // Pre-create two color variants for each label to keep render simple.
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 200, 0, 255};

    playNormal = createText("Play", white);
    playSelected = createText("Play", yellow);

    highNormal = createText("High Score", white);
    highSelected = createText("High Score", yellow);
}

void Menu::onExit()
{
    if (playNormal) { SDL_DestroyTexture(playNormal); playNormal = nullptr; }
    if (playSelected) { SDL_DestroyTexture(playSelected); playSelected = nullptr; }
    if (highNormal) { SDL_DestroyTexture(highNormal); highNormal = nullptr; }
    if (highSelected) { SDL_DestroyTexture(highSelected); highSelected = nullptr; }
}

void Menu::handleInput(const SDL_Event &ev)
{
    if (ev.type == SDL_KEYDOWN)
    {
        if (ev.key.keysym.sym == SDLK_UP)
        {
            selectedIndex = (selectedIndex == 0) ? 1 : selectedIndex - 1;
        }
        else if (ev.key.keysym.sym == SDLK_DOWN)
        {
            selectedIndex = (selectedIndex == 1) ? 0 : selectedIndex + 1;
        }
        else if (ev.key.keysym.sym == SDLK_RETURN || ev.key.keysym.sym == SDLK_KP_ENTER)
        {
            result = selectedIndex;
        }
    }
}

void Menu::update()
{
    // Nothing dynamic for now.
}

void Menu::render(SDL_Renderer *renderer)
{
    if (!renderer)
        return;

    // Draw background if available
    SDL_Texture *bg = gfxMgr ? gfxMgr->getBackground() : nullptr;
    if (bg)
    {
        SDL_RenderCopy(renderer, bg, nullptr, nullptr);
    }

    // Determine positions
    int winW = 800;
    int winH = 600;
    SDL_Rect r;

    // Draw title (optional simple text)
    // Draw menu items centered
    // Play
    SDL_Texture *tPlay = (selectedIndex == 0) ? playSelected : playNormal;
    if (tPlay)
    {
        SDL_QueryTexture(tPlay, nullptr, nullptr, &r.w, &r.h);
        r.x = (winW - r.w) / 2;
        r.y = (winH / 2) - r.h - 10;
        SDL_RenderCopy(renderer, tPlay, nullptr, &r);
    }

    // High Score
    SDL_Texture *tHigh = (selectedIndex == 1) ? highSelected : highNormal;
    if (tHigh)
    {
        SDL_QueryTexture(tHigh, nullptr, nullptr, &r.w, &r.h);
        r.x = (winW - r.w) / 2;
        r.y = (winH / 2) + 10;
        SDL_RenderCopy(renderer, tHigh, nullptr, &r);
    }
}

int Menu::getResult() const
{
    return result;
}
