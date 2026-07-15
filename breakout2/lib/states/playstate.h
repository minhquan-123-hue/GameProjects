#pragma once

#include <SDL2/SDL.h>

#include <entities/paddle.h>
#include <states/statemachine.h>
#include <systems/graphic_manager.h>

class PlayState : public State
{
public:
    explicit PlayState(GraphicManager* graphicManager);
    ~PlayState() override;

    void onEnter() override;
    void onExit() override;

    void handleInput(const SDL_Event& ev) override;
    void update(float dt) override;
    void render(SDL_Renderer* renderer) override;

private:
    GraphicManager* gfxMgr;
    Paddle paddle;
};