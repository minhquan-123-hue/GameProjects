#pragma once

#include <states/statemachine.h>
#include <systems/font_manager.h>
#include <systems/graphic_manager.h>
#include <SDL2/SDL.h>
#include <string>

// A very simple menu state that shows a background and two selectable items.
class Menu : public State
{
public:
    Menu();
    ~Menu();

    // Provide renderer and managers before entering the state.
    void setRenderer(SDL_Renderer *r);
    void setManagers(FontManager *fm, GraphicManager *gm);

    void onEnter() override;
    void onExit() override;

    void handleInput(const SDL_Event &ev) override;
    void update() override;
    void render(SDL_Renderer *renderer) override;

    // After the user confirms, this returns the selected index (0=Play, 1=High Score), or -1 if none yet.
    int getResult() const;

private:
    int selectedIndex; // 0 = Play, 1 = High Score
    int result; // -1 none, 0 play, 1 highscore

    SDL_Renderer *renderer;
    FontManager *fontMgr;
    GraphicManager *gfxMgr;

    SDL_Texture *playNormal;
    SDL_Texture *playSelected;
    SDL_Texture *highNormal;
    SDL_Texture *highSelected;

    // Helpers
    SDL_Texture *createText(const std::string &text, SDL_Color color);
};